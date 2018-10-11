
#pragma once

#include "typedef.h"
#include "template.h"

//#define ARRAY_TEST
#ifdef ARRAY_TEST
void outOfRange ( const char * name, nat size, nat index );
#endif

template <class T> class ArrRef;

/********************** CArrRef ************************/
/************ Ссылка на константный массив *************/

template <class T> class CArrRef
{
    void operator= ( const CArrRef & );
    const T * _data;
    nat _size;
public:
    CArrRef () : _data(0), _size(0) {}
    CArrRef ( const T * d, nat n ) : _data(d), _size(n) {}
    CArrRef ( const ArrRef<T> & a ) : _data(a._data), _size(a._size) {}
// Указатель на i-ый элемент:
    const T * operator() ( nat i = 0 ) const { return _size > i ? _data + i : 0; }
#ifdef ARRAY_TEST
    void error ( nat n, nat i ) const { outOfRange ( "CArrRef", n, i ); }
    CArrRef ( CArrRef<T> a, nat i, nat n ) : _data(a(i)), _size(n) { if ( a._size < i + n ) error ( a._size, i + n ); }
// Ссылка на i-ый элемент:
    const T & operator[] ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i]; }
// Ссылка на i-ый элемент от конца:
    const T & las ( nat i = 0 ) const { if ( _size <= i ) error ( _size, i ); return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    const T & cprev ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i>0?i-1:_size-1]; }
// Ссылка на следущий элемент в цикле:
    const T & cnext ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i+1<_size?i+1:0]; }
    const T & cnext ( nat i, nat k ) const { if ( ! _size ) error ( _size, i ); return _data[(i+k)%_size]; }
#else
    CArrRef ( CArrRef<T> a, nat i, nat n ) : _data(a(i)), _size(n) {}
// Ссылка на i-ый элемент:
    const T & operator[] ( nat i ) const { return _data[i]; }
// Ссылка на i-ый элемент от конца:
    const T & las ( nat i = 0 ) const { return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    const T & cprev ( nat i ) const { return _data[i>0?i-1:_size-1]; }
    const T & cprev ( nat i, nat k ) const { return _data[(i+_size-k)%_size]; }
// Ссылка на следущий элемент в цикле:
    const T & cnext ( nat i ) const { return _data[i+1<_size?i+1:0]; }
    const T & cnext ( nat i, nat k ) const { return _data[(i+k)%_size]; }
#endif
// Количество элементов
    nat size () const { return _size; }
friend class ArrRef<T>;
};

/*********************** ArrRef ************************/
/****************** Ссылка на массив *******************/

template <class T> class ArrRef
{
protected:
    T * _data;
    nat _size;
public:
    ArrRef () : _data(0), _size(0) {}
    ArrRef ( T * d, nat n ) : _data ( d ), _size ( n ) {}
    CArrRef<T> operator * () const { return CArrRef<T> ( *this ); }
// Указатель на i-ый элемент:
    T * operator() ( nat i = 0 ) { return _size > i ? _data + i : 0; }
    const T * operator() ( nat i = 0 ) const { return _size > i ? _data + i : 0; }
#ifdef ARRAY_TEST
    void error ( nat n, nat i ) const { outOfRange ( "ArrRef", n, i ); }
    ArrRef ( ArrRef<T> a, nat i, nat n ) : _data ( a(i) ), _size ( n ) { if ( a._size < i + n ) error ( a._size, i + n ); }
// Ссылка на i-ый элемент:
    T & operator[] ( nat i ) { if ( _size <= i ) error ( _size, i );return _data[i]; }
// Ссылка на i-ый элемент от конца:
    T & las ( nat i = 0 ) { if ( _size <= i ) error ( _size, i ); return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    T & cprev ( nat i ) { if ( _size <= i ) error ( _size, i ); return _data[i>0?i-1:_size-1]; }
// Ссылка на следущий элемент в цикле:
    T & cnext ( nat i ) { if ( _size <= i ) error ( _size, i ); return _data[i+1<_size?i+1:0]; }
    T & cnext ( nat i, nat k ) { if ( ! _size ) error ( _size, i ); return _data[(i+k)%_size]; }
// Ссылка на i-ый элемент:
    const T & operator[] ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i]; }
// Ссылка на i-ый элемент от конца:
    const T & las ( nat i = 0 ) const { if ( _size <= i ) error ( _size, i ); return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    const T & cprev ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i>0?i-1:_size-1]; }
// Ссылка на следущий элемент в цикле:
    const T & cnext ( nat i ) const { if ( _size <= i ) error ( _size, i ); return _data[i+1<_size?i+1:0]; }
    const T & cnext ( nat i, nat k ) const { if ( ! _size ) error ( _size, i ); return _data[(i+k)%_size]; }
#else
    ArrRef ( ArrRef<T> a, nat i, nat n ) : _data ( a(i) ), _size ( n ) {}
// Ссылка на i-ый элемент:
    T & operator[] ( nat i ) { return _data[i]; }
// Ссылка на i-ый элемент от конца:
    T & las ( nat i = 0 ) { return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    T & cprev ( nat i ) { return _data[i>0?i-1:_size-1]; }
// Ссылка на следущий элемент в цикле:
    T & cnext ( nat i ) { return _data[i+1<_size?i+1:0]; }
    T & cnext ( nat i, nat k ) { return _data[(i+k)%_size]; }
// Ссылка на i-ый элемент:
    const T & operator[] ( nat i ) const { return _data[i]; }
// Ссылка на i-ый элемент от конца:
    const T & las ( nat i = 0 ) const { return _data[_size-1-i]; }
// Ссылка на предыдущий элемент в цикле:
    const T & cprev ( nat i ) const { return _data[i>0?i-1:_size-1]; }
// Ссылка на следущий элемент в цикле:
    const T & cnext ( nat i ) const { return _data[i+1<_size?i+1:0]; }
    const T & cnext ( nat i, nat k ) const { return _data[(i+k)%_size]; }
#endif
// Операторы присваивания
    ArrRef & operator= ( const CArrRef<T> & p )
    {
        if ( _data == p._data ) return *this;
        const nat n = _min ( _size, p._size );
        for ( nat i = 0; i < n; ++i ) _data[i] = p[i];
        return *this;
    }
    ArrRef & operator= ( const ArrRef & a )
    {
        return this->operator= ( CArrRef<T> ( a ) );
    }
// Изменение порядка следования элементов на обратный
    ArrRef & reverse ()
    {
        if ( _size < 2 ) return *this;
        const nat n = _size - 1;
        const nat m = _size / 2;
        for ( nat i = 0; i < m; ++i ) _swap ( _data[i], _data[n-i] );
        return *this;
    }
// Заполнение всех элементов заданным значением
    ArrRef & fill ( const T & t )
    {
        for ( nat i = 0; i < _size; ++i ) _data[i] = t;
        return *this;
    }
// Выполнение оператора <= для всех элементов массива
    template <class S> ArrRef & operator << ( S & s )
    {
        for ( nat i = 0; i < _size; ++i ) _data[i] <= s;
        return *this;
    }
// Количество элементов
    nat size () const { return _size; }
friend class CArrRef<T>;
};

/*********************** FixArrRef ***********************/
/*********** Ссылка на массив постоянной длины ***********/

template <class T, nat n> class FixArrRef : public ArrRef<T>
{
protected:
    FixArrRef ( T * d ) : ArrRef<T>( d, n ) {}
public:
explicit FixArrRef ( ArrRef<T> a, nat i = 0 ) : ArrRef<T> ( a, i, n ) {}

    FixArrRef & operator= ( const FixArrRef & a )
    {
        if ( _data == a._data ) return *this;
        for ( nat i = 0; i < n; ++i ) _data[i] = a[i];
        return *this;
    }

    FixArrRef & operator+= ( const FixArrRef & a )
    {
        for ( nat i = 0; i < n; ++i ) _data[i] += a[i];
        return *this;
    }

    FixArrRef & operator-= ( const FixArrRef & a )
    {
        for ( nat i = 0; i < n; ++i ) _data[i] -= a[i];
        return *this;
    }

    friend inline void _swap ( FixArrRef & a1, FixArrRef & a2 )
    {
        for ( nat i = 0; i < n; ++i ) _swap ( a1[i], a2[i] );
    }
};

/*********************** FixArray ************************/
/*************** Массив постоянной длины *****************/

template <class T, nat n> class FixArray : public FixArrRef<T, n>
{
    T stor[n];
    FixArray ( const FixArray & );
public:
    FixArray () : FixArrRef<T, n> ( stor ) {}

    FixArray & operator= ( const FixArray & a )
    {
        if ( _data == a._data ) return *this;
        for ( nat i = 0; i < n; ++i ) stor[i] = a.stor[i];
        return *this;
    }

    FixArray & operator+= ( const FixArray & a )
    {
        for ( nat i = 0; i < n; ++i ) stor[i] += a[i];
        return *this;
    }

    FixArray & operator-= ( const FixArray & a )
    {
        for ( nat i = 0; i < n; ++i ) stor[i] -= a[i];
        return *this;
    }

    FixArray & operator*= ( const T & t )
    {
        for ( nat i = 0; i < n; ++i ) stor[i] *= t;
        return *this;
    }
// Заполнение всех элементов заданным значением
    FixArray & fill ( const T & t )
    {
        ArrRef<T>::fill ( t );
        return *this;
    }
};

/********************** DynArrRef **********************/
/******* Ссылка на массив с изменяемым размером ********/

template <class T> class DynArrRef : public ArrRef<T>
{
protected:
    DynArrRef ( T * d, nat n ) : ArrRef<T>( d, n ) {}
public:
    virtual DynArrRef & resize ( nat n = 0 ) = 0;

    DynArrRef & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        if ( _size != r.size() ) resize ( r.size() );
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    DynArrRef & operator= ( const DynArrRef & r )
    {
        return this->operator= ( ( const CArrRef<T> &) r );
    }
};

/********************** DynArray ***********************/
/**************** Динамический массив ******************/

template <class T> class DynArray : public DynArrRef<T>
{
    DynArray ( const DynArray & );
public:
explicit DynArray ( nat n = 0 ) : DynArrRef<T> ( n > 0 ? new T[n] : 0, n ) {}
explicit DynArray ( const CArrRef<T> & r ) : DynArrRef<T> ( new T[r.size()], r.size() )
     {
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
     }

    ~DynArray () { delete[] _data; }

    DynArray & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        if ( _size != r.size() ) resize ( r.size() );
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    DynArray & operator= ( const DynArray & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }

    virtual DynArrRef<T> & resize ( nat n = 0 )
    {
        delete[] _data;
        _data = 0; // на случай исключения в new
        if ( ( _size = n ) > 0 ) _data = new T[n];
        return *this;
    }

    DynArray & swap ( DynArray & a )
    {
        _swap ( _size, a._size );
        _swap ( _data, a._data );
        return *this;
    }

    friend inline void _swap ( DynArray & a1, DynArray & a2 )
    {
        a1.swap ( a2 );
    }
};

/********************** CmbArray ***********************/
/************** Комбинированный массив *****************/

template <class T, nat N> class CmbArray : public DynArrRef<T>
{
    T stor[N];
    CmbArray ( const CmbArray & );
public:
explicit CmbArray ( nat n = 0 ) : DynArrRef<T> ( n > N ? new T[n] : stor, n ) {}
explicit CmbArray ( const CArrRef<T> & r ) : DynArrRef<T> ( r.size() > N ? new T[r.size()] : stor, r.size() )
     {
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
     }

    ~CmbArray () { if ( _data != stor ) delete[] _data; }

    CmbArray & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        resize ( r.size() );
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    CmbArray & operator= ( const CmbArray & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }

    CmbArray & operator -= ( const CmbArray & a )
    {
        const nat n = _min ( _size, a._size );
        for ( nat i = 0; i < n; ++i ) _data[i] -= a[i];
        return *this;
    }

    virtual DynArrRef<T> & resize ( nat n = 0 )
    {
        if ( _size == n ) return *this;
        if ( _data != stor )
        {
            delete[] _data;
            _data = stor;
        }
        if ( ( _size = n ) > N ) _data = new T[_size];
        return *this;
    }
};

/********************** SuiteRef ***********************/
/***** Ссылка на последовательный набор элементов ******/

template <class T> class SuiteRef : public DynArrRef<T>
{
    SuiteRef ( const SuiteRef & );

    void _del ( nat i )
    {
        if ( i < --_size ) _data[i] = _data[_size];
    }

    virtual void resizeAndCopy ( nat n ) = 0;
protected:
    nat real_size;
    SuiteRef ( T * d, nat n ) : DynArrRef<T>( d, n ) {}
public:
    SuiteRef & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        resize ( r.size() );
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    SuiteRef & operator= ( const SuiteRef & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }

    virtual DynArrRef<T> & resize ( nat n = 0 )
    {
        if ( n > real_size ) resizeAndCopy ( n );
        else _size = n;
        return *this;
    }

    SuiteRef & add ( const T & t )
    {
        inc() = t;
        return *this;
    }

    T & inc ()
    {
        if ( _size == real_size ) resizeAndCopy ( _size + 1 );
        else ++_size;
        return _data[_size-1];
    }

    SuiteRef & inc ( nat n )
    {
        if ( _size + n > real_size ) resizeAndCopy ( _size + n );
        else _size += n;
        return *this;
    }

    SuiteRef & dec ( nat n = 1 )
    {
        _size = _size > n ? _size - n : 0;
        return *this;
    }

    SuiteRef & del ( nat i )
    {
        if ( i < _size ) _del ( i );
#ifdef ARRAY_TEST
        else outOfRange ( "SuiteRef::del", _size, i );
#endif ARRAY_TEST
        return *this;
    }

    SuiteRef & delAndShift ( nat i )
    {
        if ( i < _size )
        {
            --_size;
#if _MSC_VER > 1200 // MS VC 6.0
            for ( ; i < _size; ++i ) copyFunc ( (T&)_data[i], (T&)_data[i+1] );
#else
            for ( ; i < _size; ++i ) (T&)_data[i] = _data[i+1];
#endif
        }
#ifdef ARRAY_TEST
        else outOfRange ( "SuiteRef::delAndShift", _size, i );
#endif ARRAY_TEST
        return *this;
    }

    SuiteRef & addAftLas ( const CArrRef<T> & a )
    {
        const nat s = _size;
        inc ( a.size() );
        for ( nat i = s; i < _size; ++i ) _data[i] = a[i-s];
        return *this;
    }
};

/*********************** Suite *************************/
/********** Последовательный набор элементов ***********/

template <class T> class Suite : public SuiteRef<T>
{
    Suite ( const Suite & );

    virtual void resizeAndCopy ( nat n )
    {
        real_size = _max ( real_size + n, 8u );
        T * tmp = new T[real_size];
#if _MSC_VER > 1200 // MS VC 6.0
        for ( nat i = 0; i < _size; ++i ) copyFunc ( tmp[i], (T&)_data[i] );
#else
        for ( nat i = 0; i < _size; ++i ) tmp[i] = _data[i];
#endif
        delete[] _data;
        _data = tmp;
        _size = n;
    }
public:
    Suite () : SuiteRef<T>(0, real_size=0) {}
    explicit Suite ( nat n, nat m = 0 ) : SuiteRef<T>((real_size=_max(n,m)) > 0 ? new T[real_size] : 0, m) {}
    ~Suite () { delete[] _data; }

    Suite & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        _size = r.size();
        if ( real_size < _size )
        {
            real_size = _size;
            delete[] _data;
            _data = 0; // на случай исключения в new
            _data = new T[_size];
        }
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    Suite & operator= ( const Suite & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }

    Suite & swap ( Suite & a )
    {
        _swap ( real_size, a.real_size );
        _swap ( _size, a._size );
        _swap ( _data, a._data );
        return *this;
    }

    friend inline void _swap ( Suite & a1, Suite & a2 )
    {
        a1.swap ( a2 );
    }
};

#if _MSC_VER > 1200 // MS VC 6.0
template <class T> inline void copyFunc ( T & a, T & b ) { a = b; }
template <class T> inline void copyFunc ( Suite   <T> & a, Suite   <T> & b ) { _swap ( a, b ); }
template <class T> inline void copyFunc ( DynArray<T> & a, DynArray<T> & b ) { _swap ( a, b ); }
#endif

/********************* CmbSuite ************************/
/********** Комбинированный набор элементов ************/

template <class T, nat N> class CmbSuite : public SuiteRef<T>
{
    T stor[N];
    CmbSuite ( const CmbSuite & );

    virtual void resizeAndCopy ( nat n )
    {
        real_size = _max ( real_size + n, 8u );
        T * tmp = new T[real_size];
#if _MSC_VER > 1200 // MS VC 6.0
        for ( nat i = 0; i < _size; ++i ) copyFunc ( tmp[i], (T&)_data[i] );
#else
        for ( nat i = 0; i < _size; ++i ) tmp[i] = _data[i];
#endif
        if ( _data != stor ) delete[] _data;
        _data = tmp;
        _size = n;
    }
public:
    CmbSuite () : SuiteRef<T>(stor, 0) { real_size = N; }
    explicit CmbSuite ( nat n, nat m = 0 ) : 
        SuiteRef<T> ( ( real_size = _max(n,m) ) > N ? new T[real_size] : ( real_size = N, stor ), m ) {}
    ~CmbSuite () { if ( _data != stor ) delete[] _data; }

    CmbSuite & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        _size = r.size();
        if ( real_size < _size )
        {
            real_size = _size;
            if ( _data != stor )
            {
                delete[] _data;
                _data = stor; // на случай исключения в new
            }
            _data = new T[_size];
        }
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    CmbSuite & operator= ( const CmbSuite & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }
};

/********************* LtdSuiteRef *********************/
/*** Ссылка на набор элементов ограниченного размера ***/

template <class T> class LtdSuiteRef : public SuiteRef<T>
{
    virtual void resizeAndCopy ( nat n )
    {
#ifdef ARRAY_TEST
        if ( n > real_size ) outOfRange ( "LtdSuiteRef::resizeAndCopy", real_size, n );
#endif
        _size = real_size;
    }
public:
    LtdSuiteRef ( ArrRef<T> a, nat i, nat n ) : SuiteRef<T>( a(i), 0 )
    {
        real_size = n;
#ifdef ARRAY_TEST
        if ( a.size() < i + n ) outOfRange ( "LtdSuiteRef", a.size(), i + n );
#endif
    }

    LtdSuiteRef & operator= ( const CArrRef<T> & r )
    {
        if ( _data == r() ) return *this;
        _size = r.size();
#ifdef ARRAY_TEST
        if ( _size > real_size ) outOfRange ( "LtdSuiteRef::operator=", real_size, _size );
#endif
        if ( _size > real_size ) _size = real_size;
        for ( nat i = 0; i < _size; ++i ) _data[i] = r[i];
        return *this;
    }

    LtdSuiteRef & operator= ( const LtdSuiteRef & a )
    {
        return this->operator= ( ( const CArrRef<T> &) a );
    }
};

/*************** Операции с массивами без их изменения ***************/

template <class T> inline 
bool operator == ( CArrRef<T> a, CArrRef<T> b )
{
    if ( a.size() != b.size() ) return false;
    for ( nat i = 0; i < a.size(); ++i ) 
        if ( a[i] != b[i] ) return false;
    return true;
}

template <class T> inline 
bool operator == ( const ArrRef<T> & a, const ArrRef<T> & b )
{
    return *a == *b;
}

template <class T> inline 
bool operator != ( const CArrRef<T> & a, const CArrRef<T> & b )
{
    if ( a.size() != b.size() ) return true;
    for ( nat i = 0; i < a.size(); ++i ) 
        if ( a[i] != b[i] ) return true;
    return false;
}

template <class T1, class T2> inline 
T1 & operator += ( T1 & t, CArrRef<T2> a )
{
    for ( nat i = 0; i < a.size(); ++i ) t += a[i];
    return t;
}

template <class T1, class T2> inline 
T1 & operator << ( T1 & t, CArrRef<T2> a )
{
    for ( nat i = 0; i < a.size(); ++i ) t << a[i];
    return t;
}

template <class A, class B> inline 
nat count ( const A & a, const B & b, nat from = 0 )
{
    nat n = 0;
    for ( nat i = from; i < a.size(); ++i ) if ( a[i] == b ) ++n;
    return n;
}

template <class A, class B> inline 
nat firEqu ( const A & a, const B & b, nat from = 0 )
{
    for ( nat i = from; i < a.size(); ++i ) if ( a[i] == b ) return i;
    return a.size();
}

template <class A, class B> inline 
nat lasEqu ( const A & a, const B & b )
{
    for ( nat i = a.size(); i > 0; --i ) if ( a[i-1] == b ) return i-1;
    return a.size();
}

template <class A, class B> inline 
bool hasEqu ( const A & a, const B & b )
{
    for ( nat i = 0; i < a.size(); ++i ) if ( a[i] == b ) return true;
    return false;
}

template <class T> inline 
nat firMin ( const T & a )
{
    nat m = 0;
    for ( nat i = 1; i < a.size(); ++i ) if ( a[i] < a[m] ) m = i;
    return m;
}

template <class T> inline 
nat firMax ( const T & a )
{
    nat m = 0;
    for ( nat i = 1; i < a.size(); ++i ) if ( a[i] > a[m] ) m = i;
    return m;
}

template <class T> inline 
Def<T> amean ( const CArrRef<T> & a )
{
    if ( a.size() == 0 ) return Def<T>();
    T res ( a[0] );
    for ( nat i = 1; i < a.size(); ++i ) res += a[i];
    return res / a.size();
}

template <class T> inline 
Def<T> amean ( const ArrRef<T> & a )
{
    return amean ( *a );
}

/**************** Операции с упорядоченными массивами ****************/

template <class A, class B> inline 
nat lasEqu123 ( const A & a, const B & b )
{
    if ( a.size() == 0 ) return 0;
    nat from = 0, before = a.size();
    while ( from + 1 < before )
    {
        const nat i = ( from + before ) / 2;
        if ( a[i] > b ) before = i; else from = i;
    }
    return a[from] == b ? from : a.size();
}

/**************** Операции с массивами с изменениями *****************/

template <class T> inline 
ArrRef<T> & operator <<= ( ArrRef<T> & a, nat k )
{
    const nat n = a.size();
    if ( n < 2 || ! ( k %= n ) ) return a;
    const nat m = n - k;
    if ( m < k ) return a >>= m;
    nat i;
    CmbArray<T, 64> b ( k );
    for ( i = 0; i < k; ++i ) b[i] = a[i];
    for ( i = 0; i < m; ++i ) a[i] = a[i+k];
    for ( i = 0; i < k; ++i ) a[i+m] = b[i];
    return a;
}

template <class T> inline 
ArrRef<T> & operator >>= ( ArrRef<T> & a, nat k )
{
    const nat n = a.size();
    if ( n < 2 || ! ( k %= n ) ) return a;
    const nat m = n - k;
    if ( m < k ) return a <<= m;
    nat i;
    CmbArray<T, 64> b ( k );
    for ( i = 0; i < k; ++i ) b[i] = a[i+m];
    for ( i = m; --i > 0; ) a[i+k] = a[i]; a[k] = a[0];
    for ( i = 0; i < k; ++i ) a[i] = b[i];
    return a;
}

template <class T1, class T2> inline 
ArrRef<T1> & operator += ( ArrRef<T1> & a, const T2 & b )
{
    for ( nat i = 0; i < a.size(); ++i ) a[i] += b;
    return a;
}

template <class T1, class T2> inline 
ArrRef<T1> & operator -= ( ArrRef<T1> & a, const T2 & b )
{
    for ( nat i = 0; i < a.size(); ++i ) a[i] -= b;
    return a;
}

template <class T1, class T2> inline 
ArrRef<T1> & operator *= ( ArrRef<T1> & a, const T2 & b )
{
    for ( nat i = 0; i < a.size(); ++i ) a[i] *= b;
    return a;
}

template <class T1, class T2> inline 
ArrRef<T1> & operator /= ( ArrRef<T1> & a, const T2 & b )
{
    for ( nat i = 0; i < a.size(); ++i ) a[i] /= b;
    return a;
}

template <class A, class B, class C> inline 
A & sum ( A & a, const B & b, const C & c )
{
    const nat n = _min ( a.size(), b.size(), c.size() );
    for ( nat i = 0; i < n; ++i ) a[i] = b[i] + c[i];
    return a;
}
