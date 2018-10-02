
#pragma once

#include "typedef.h"

inline float qmod ( const float & x ) { return x * x; }

inline double qmod ( const double & x ) { return x * x; }

//************************ 10.04.2015 *************************//
//
//                      Двухмерный вектор
//
//************************ 10.04.2015 *************************//

template <class X, class Y = X> 
struct Vector2
{
    X x;
    Y y;

    Vector2 () {}
    Vector2 ( const X & a, const Y & b ) : x(a), y(b) {}
 
    Vector2 & operator += ( const Vector2 & u )
    {
        x += u.x; y += u.y; return *this;
    }

    Vector2 & operator -= ( const Vector2 & u )
    {
        x -= u.x; y -= u.y; return *this;
    }
 
    template <class T> Vector2 & operator *= ( const T & t )
    {
        x *= t; y *= t; return *this;
    }

    template <class T> Vector2 & operator /= ( const T & t )
    {
        x /= t; y /= t; return *this;
    }
};

//************************ 20.11.2002 *************************//
//
// Решение систем линейных уравнений 2-го порядка методом Гаусса
//         Выбор ведущего элемента по столбцам
//
//************************ 10.04.2015 *************************//

template <class T1, class T2 = T1> class SLU2
{
public:
    T1 aa, ab, // aa * x + ab * y = ac
       ba, bb; // ba * x + bb * y = bc
    T2 ac, bc;

// Решение системы линейных уравнений 2-го порядка методом Гаусса
    bool gauss ( T2 & x, T2 & y ) const
    {
        T2 v1, v2;
        const double ma = qmod ( aa );
        const double mb = qmod ( ba );
        if ( ma >= mb )
        {
            if ( ! ma ) return false;
            const T1 c = ab / aa;
            const T1 b = bb - c * ba;
            if ( ! b ) return false;
            ( v1 = ac ) /= aa;
            ( v2 = v1 ) *= ba;
            ( ( y = bc ) -= v2 ) /= b;
            ( v2 = y ) *= c;
        }
        else
        {
            const T1 c = bb / ba;
            const T1 a = ab - c * aa;
            if ( a == 0 ) return false;
            ( v1 = bc ) /= ba;
            ( v2 = v1 ) *= aa;
            ( ( y = ac ) -= v2 ) /= a;
            ( v2 = y ) *= c;
        }
        ( x = v1 ) -= v2;
        return true;
    }

    SLU2 & fill ( const T1 & v1, const T2 & v2 )
    {
        aa = ab =
        ba = bb = v1;
        ac = bc = v2;
        return *this;
    }
};

//************************ 20.11.2002 *************************//
//
// Решение систем линейных уравнений 3-го порядка методом Гаусса
//         Выбор ведущего элемента по столбцам
//
//************************ 08.11.2014 *************************//

template <class T1, class T2 = T1> class SLU3
{
public:
    T1 aa, ab, ac, // aa * x + ab * y + ac * z = ad
       ba, bb, bc, // ba * x + bb * y + bc * z = bd
       ca, cb, cc; // ca * x + cb * y + cc * z = cd
    T2 ad, bd, cd;

// Решение системы линейных уравнений 3-го порядка методом Гаусса
    bool gauss ( T2 & x, T2 & y, T2 & z ) const
    {
        SLU2<T1, T2> slu;
        T1 a, b;
        T2 d, e;
        const double ma = qmod ( ac );
        const double mb = qmod ( bc );
        const double mc = qmod ( cc );
        if ( mc >= mb && mc >= ma )
        {
            if ( ! mc ) return false;
            a = ca / cc;
            b = cb / cc;
            ( d = cd ) /= cc;
            slu.aa = aa - a * ac;   slu.ab = ab - b * ac;   ( e = d ) *= ac;   ( slu.ac = ad ) -= e;
            slu.ba = ba - a * bc;   slu.bb = bb - b * bc;   ( e = d ) *= bc;   ( slu.bc = bd ) -= e;
        }
        else
        if ( mb >= ma )
        {
            a = ba / bc;
            b = bb / bc;
            ( d = bd ) /= bc;
            slu.aa = aa - a * ac;   slu.ab = ab - b * ac;   ( e = d ) *= ac;    ( slu.ac = ad ) -= e;
            slu.ba = ca - a * cc;   slu.bb = cb - b * cc;   ( e = d ) *= cc;    ( slu.bc = cd ) -= e;
        }
        else
        {
            a = aa / ac;
            b = ab / ac;
            ( d = ad ) /= ac;
            slu.aa = ba - a * bc;   slu.ab = bb - b * bc;   ( e = d ) *= bc;    ( slu.ac = bd ) -= e;
            slu.ba = ca - a * cc;   slu.bb = cb - b * cc;   ( e = d ) *= cc;    ( slu.bc = cd ) -= e;
        }
        if ( ! slu.gauss ( x, y ) ) return false;
        z = d;
        ( e = x ) *= a; z -= e;
        ( e = y ) *= b; z -= e;
        return true;
    }

    SLU3 & fill ( const T1 & v1, const T2 & v2 )
    {
        aa = ab = ac = 
        ba = bb = bc = 
        ca = cb = cc = v1;
        ad = bd = cd = v2;
        return *this;
    }
};

//*************************** 19.02.2017 ******************************//
//
//      Метод исключений Гаусса.
//      Выбор ведущего элемента по строкам.
//      nRow, nCol - размеры матрицы.
//      index - массив для индексов выбранных столбцов.
//      mRow, mCol - размеры подматрицы, где выбираются ведущие элементы.
//
//*************************** 19.02.2017 ******************************//

template <class Matrix>
bool _doGaussRow ( Matrix & data, nat nRow, nat nCol, nat index[], nat mRow, nat mCol )
{
    if ( nRow == 0 || nCol <= nRow ) return false;
    if ( mRow > nRow ) mRow = nRow;
    if ( mCol > nCol ) mCol = nCol;
    if ( mRow > mCol ) return false;
// Прямой ход
    nat i, j, k;
    for ( k = 0; k < mRow; ++k )
    {
// Поиск максимального по модулю члена в k-ой строке
        nat m = 0;
        double * rk = & data[k][0];
        double max = fabs ( rk[0] );
        for ( i = 1; i < mCol; ++i )
        {
            const double t = fabs ( rk[i] );
            if ( max < t ) max = t, m = i;
        }
        if ( max == 0 ) return false;
        index[k] = m;
// Нормализация строки
        const double p = 1. / rk[m];
        for ( i = 0; i < nCol; ++i ) rk[i] *= p;
        rk[m] = 1;
// Вычитание строк
        for ( j = k+1; j < nRow; ++j )
        {
            double * rj = & data[j][0];
            const double t = rj[m];
            for ( i = 0; i < nCol; ++i )
            {
                if ( fabs ( rj[i] -= rk[i] * t ) < 1e-290 ) rj[i] = 0;
            }
        }
    }
// Обратная подстановка
    for ( j = mRow; --j > 0; )
    {
        const double * rj = & data[j][0];
        for ( i = 0; i < j; ++i )
        {
            double * ri = & data[i][0];
            const double t = ri[index[j]];
            for ( k = 0; k < nCol; ++k ) ri[k] -= rj[k] * t;
        }
    }
    return true;
}

template <class T> class IMatrix;

template <class T> inline
bool doGaussRow ( IMatrix<T> & data, nat nRow, nat nCol, unsigned * index, nat mRow, nat mCol )
{
    return _doGaussRow ( data, nRow, nCol, index, mRow, mCol );
}

template <class T> class ArrRef2;

template <class T> inline
bool doGaussRow ( ArrRef2<T> & data, nat nRow, nat nCol, unsigned * index, nat mRow, nat mCol )
{
    return _doGaussRow ( data, nRow, nCol, index, mRow, mCol );
}
