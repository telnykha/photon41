
#pragma once

#include "template.h"

template <class T>
class MaxHeap // ������� � ������������ �����������
{
    nat _size, max_size;
    T * heap;
// ������ ������������ ����� � ��������� ������������
    MaxHeap ( const MaxHeap & );
    void operator = ( const MaxHeap & );
public:
    explicit MaxHeap ( nat n ) : _size(0), max_size(n), heap ( new T[n+1] ) {}
    ~MaxHeap () { delete[] heap; }
// ��������� �� i-��� ������� ( 0, ���� i ������� �� ������ )
    T * operator[] ( nat i ) { return _size > i ? heap + i + 1 : 0; }
// ���������� ��������� � �������
    nat size() const { return _size; }
// �������� �������
    void clear() { _size = 0; }
// ������� i-��� �������
    void raise ( nat i )
    {
        if ( i >= _size ) return;
        for ( ++i; i > 1; )
        {
            const nat j = i >> 1;
            if ( heap[j] >= heap[i] ) break;
            _swap ( heap[i], heap[j] );
            i = j;
        }
    }
// �������� i-��� �������
    void down ( nat i )
    {
        for (++i;;)
        {
            const nat i1 = i + i;
            if ( i1 > _size ) break;
            const nat i2 = i1 + 1;
            const nat j = i2 > _size ? i1 : heap[i1] >= heap[i2] ? i1 : i2;
            if ( heap[i] >= heap[j] ) break;
            _swap ( heap[i], heap[j] );
            i = j;
        }
    }
// ������� i-��� �������
    void del ( nat i )
    {
        if ( i >= _size ) return;
        const nat i1 = i + 1;
        if ( i1 == _size ) { _size--; return; }
        _swap ( heap[i1], heap[_size] );
        if ( heap[i1] < heap[_size--] )
            down ( i );
        else
            raise ( i );
    }
// �������� ������� � �������
    bool operator << ( const T & o )
    {
        if ( _size == max_size ) return false;
        heap[++_size] = o;
        raise ( _size - 1 );
        return true;
    }
// ������ ������������ ������� �� �������
    bool operator >> ( T & o )
    {
        if ( _size == 0 ) return false;
        o = heap[1];
        _swap ( heap[1], heap[_size--] );
        down ( 0 );
        return true;
    }
};

template <class T>
class MinHeap // ������� � ����������� �����������
{
    nat _size, max_size;
    T * heap;
// ������ ������������ ����� � ��������� ������������
    MinHeap ( const MinHeap & );
    void operator = ( const MinHeap & );
public:
    explicit MinHeap ( nat n ) : _size(0), max_size(n), heap ( new T[n+1] ) {}
    ~MinHeap () { delete[] heap; }
// ��������� �� i-��� ������� ( 0, ���� i ������� �� ������ )
    T * operator[] ( nat i ) { return _size > i ? heap + i + 1 : 0; }
// ���������� ��������� � �������
    nat size() const { return _size; }
// �������� �������
    void clear() { _size = 0; }
// ������� i-��� �������
    void raise ( nat i )
    {
        if ( i >= _size ) return;
        for ( ++i; i > 1; )
        {
            const nat j = i >> 1;
            if ( heap[j] <= heap[i] ) break;
            _swap ( heap[i], heap[j] );
            i = j;
        }
    }
// �������� i-��� �������
    void down ( nat i )
    {
        for (++i;;)
        {
            const nat i1 = i + i;
            if ( i1 > _size ) break;
            const nat i2 = i1 + 1;
            const nat j = i2 > _size ? i1 : heap[i1] <= heap[i2] ? i1 : i2;
            if ( heap[i] <= heap[j] ) break;
            _swap ( heap[i], heap[j] );
            i = j;
        }
    }
// ������� i-��� �������
    void del ( nat i )
    {
        if ( i >= _size ) return;
        const nat i1 = i + 1;
        if ( i1 == _size ) { _size--; return; }
        _swap ( heap[i1], heap[_size] );
        if ( heap[i1] > heap[_size--] )
            down ( i );
        else
            raise ( i );
    }
// �������� ������� � �������
    bool operator << ( const T & o )
    {
        if ( _size == max_size ) return false;
        heap[++_size] = o;
        raise ( _size - 1 );
        return true;
    }
// ������ ����������� ������� �� �������
    bool operator >> ( T & o )
    {
        if ( _size == 0 ) return false;
        o = heap[1];
        _swap ( heap[1], heap[_size--] );
        down ( 0 );
        return true;
    }
};
