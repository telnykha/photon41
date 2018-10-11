
// 13.03.2004, 27.03.2004, 05.06.2004, 26.06.2004, 25.02.2006, 20.10.2012, 02.02.2013

#ifndef MATRIX_H
#define MATRIX_H

#include "template.h"

template <class Type>
class IMatrix
{
    Type * const * const data;
// ������ ��������� ������������ � ������������ �����
    void operator = ( const IMatrix & );
    IMatrix ( const IMatrix & );
public:
    const nat nRow; // �-�� �����
    const nat nCol; // �-�� ��������

    IMatrix ( nat r, nat c, Type * const * const p ) : nRow(r), nCol(c), data(p) {}

    IMatrix & fill ( const Type & p )
    {
        for ( nat i = 0; i < nRow; ++i )
        {
            Type * t = data[i];
            for ( nat j = 0; j < nCol; ++j ) t[j] = p;
        }
        return *this;
    }
    IMatrix & operator *= ( const Type & p )
    {
        for ( nat i = 0; i < nRow; ++i )
        {
            Type * t = data[i];
            for ( nat j = 0; j < nCol; ++j ) t[j] *= p;
        }
        return *this;
    }
    operator       Type * const * ()       { return data; }
    operator const Type * const * () const { return data; }
};

template <class Type, nat R, nat C>
class SMatrix : public IMatrix<Type>
{
    Type * p[R];
    Type stor[R*C];
public:
    SMatrix () : IMatrix<Type> ( R, C, p )
    {
        p[0] = stor;
        for ( nat i = 1; i < R; ++i ) p[i] = p[i-1] + C;
    }

    SMatrix ( const SMatrix & m ) : IMatrix<Type> ( R, C, p )
    {
        nat i;
        p[0] = stor;
        for ( i = 1; i < R; ++i ) p[i] = p[i-1] + C;
        for ( i = 0; i < R*C; ++i ) stor[i] = m.stor[i];
    }

    SMatrix & operator = ( const SMatrix & m )
    {
        for ( nat i = 0; i < R*C; ++i ) stor[i] = m.stor[i];
        return *this;
    }
};

template <class Type>
class HMatrix : public IMatrix<Type>
{
    Type ** p;
// ������ ��������� ������������
    HMatrix & operator = ( const HMatrix & m );
public:
    HMatrix ( nat r, nat c ) : IMatrix<Type> ( r, c, p = r > 0 ? new Type*[r] : 0 )
    {
        if ( ! nRow ) return;
        p[0] = new Type[nRow*nCol];
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
    }

    explicit HMatrix ( const IMatrix<Type> & m ) : IMatrix<Type> ( m.nRow, m.nCol, p = m.nRow > 0 ? new Type*[m.nRow] : 0 )
    {
        if ( ! nRow ) return;
        const nat n = nRow * nCol;
        Type * t = p[0] = new Type[n];
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
        const Type * s = m[0];
        for ( nat j = 0; j < n; ++j ) t[j] = s[j];
    }

    explicit HMatrix ( const HMatrix<Type> & m ) : IMatrix<Type> ( m.nRow, m.nCol, p = m.nRow > 0 ? new Type*[m.nRow] : 0 )
    {
        if ( ! nRow ) return;
        const nat n = nRow * nCol;
        Type * t = p[0] = new Type[n];
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
        const Type * s = m[0];
        for ( nat j = 0; j < n; ++j ) t[j] = s[j];
    }

    ~HMatrix()
    {
        if ( p != 0 )
        {
            delete[] p[0];
            delete[] p;
        }
    }
};

template <class Type, nat R, nat C>
class CmbMatrix : public IMatrix<Type>
{
    Type ** p;
    Type * pa[R];
    Type stor[R*C];
// ������ ��������� ������������
    CmbMatrix & operator = ( const CmbMatrix & m );
public:
    CmbMatrix ( nat r, nat c ) : IMatrix<Type> ( r, c, p = r > R ? new Type*[r] : pa )
    {
        const nat n = nRow * nCol;
        p[0] = n > R*C ? new Type[n] : stor;
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
    }

    explicit CmbMatrix ( const IMatrix<Type> & m ) : IMatrix<Type> ( m.nRow, m.nCol, p = m.nRow > R ? new Type*[m.nRow] : pa )
    {
        const nat n = nRow * nCol;
        Type * t = p[0] = n > R*C ? new Type[n] : stor;
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
        const Type * s = m[0];
        for ( nat j = 0; j < n; ++j ) t[j] = s[j];
    }

    explicit CmbMatrix ( const CmbMatrix<Type, R, C> & m ) : IMatrix<Type> ( m.nRow, m.nCol, p = m.nRow > R ? new Type*[m.nRow] : pa )
    {
        const nat n = nRow * nCol;
        Type * t = p[0] = n > R*C ? new Type[n] : stor;
        for ( nat i = 1; i < nRow; ++i ) p[i] = p[i-1] + nCol;
        const Type * s = m[0];
        for ( nat j = 0; j < n; ++j ) t[j] = s[j];
    }

    ~CmbMatrix()
    {
        if ( p[0] != stor ) delete[] p[0];
        if ( p != pa ) delete[] p;
    }
};

template <class Type>
bool copy ( const IMatrix<Type> & a, IMatrix<Type> & b ) // b = a
{
    if ( a.nCol != b.nCol || a.nRow != b.nRow || a.nCol == 0 ) return false;
    if ( a[0] == b[0] ) return true; // a � b - ���� � �� �� �������
    const Type * pa = *a;
          Type * pb = *b;
    for ( int i = b.nRow*b.nCol; --i >= 0; ) *pb++ = *pa++;
    return true;
}

template <class Type>
bool plus ( const IMatrix<Type> & a, const IMatrix<Type> & b, IMatrix<Type> & c ) // c = a + b
{
    if ( a.nCol != b.nCol || a.nRow != b.nRow ) return false;
    if ( a.nCol != c.nCol || a.nRow != c.nRow || a.nRow == 0 ) return false;
    const Type * pa = *a;
    const Type * pb = *b;
          Type * pc = *c;
    for ( int i = a.nRow*a.nCol; --i >= 0; ) *pc++ = *pa++ + *pb++;
    return true;
}

template <class Type>
bool minus ( const IMatrix<Type> & a, const IMatrix<Type> & b, IMatrix<Type> & c ) // c = a - b
{
    if ( a.nCol != b.nCol || a.nRow != b.nRow ) return false;
    if ( a.nCol != c.nCol || a.nRow != c.nRow || a.nRow == 0 ) return false;
    const Type * pa = *a;
    const Type * pb = *b;
          Type * pc = *c;
    for ( int i = a.nRow*a.nCol; --i >= 0; ) *pc++ = *pa++ - *pb++;
    return true;
}

template <class Type>
bool multi ( const IMatrix<Type> & a, const IMatrix<Type> & b, IMatrix<Type> & c ) // c = a * b
{
    if ( a.nCol != b.nRow || a.nRow != c.nRow || b.nCol != c.nCol || a.nRow == 0 ) return false;
    if ( a[0] == c[0] || b[0] == c[0] )
    {
        HMatrix<Type> m ( c.nRow, c.nCol );
        return multi ( a, b, m ) && copy ( m, c );
    }
    for ( int i = c.nRow; --i >= 0; )
    {
        const Type * r = a[i];
        for ( int j = c.nCol; --j >= 0; )
        {
            Type s = 0.;
            for ( int k = a.nCol; --k >= 0; ) s += r[k] * b[k][j];
            c[i][j] = s;
        }
    }
    return true;
}

// ������ �������

bool determinant ( const IMatrix<double> & m, double & d );
bool trans  ( const IMatrix<double> & a, IMatrix<double> & b ); // b = aT
bool inverse( const IMatrix<double> & a, IMatrix<double> & b ); // a * b = 1

// ��������� �����

double norm1 ( const IMatrix<double> & ); // 1-�����
double norm2 ( const IMatrix<double> & ); // 2-�����
double normF ( const IMatrix<double> & ); // ����� ����������
double normU ( const IMatrix<double> & ); // ����������� �����

// C���������� ����������: A = U * W * V

bool svd ( const IMatrix<double> & A, IMatrix<double> & U, IMatrix<double> & W, IMatrix<double> & V ); 

#endif