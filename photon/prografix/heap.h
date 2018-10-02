
#pragma once

#include "template.h"

template <class T>
class MaxHeap // Очередь с максимальным приоритетом
{
    nat _size, max_size;
    T * heap;
// Запрет конструктора копии и оператора присваивания
    MaxHeap ( const MaxHeap & );
    void operator = ( const MaxHeap & );
public:
    explicit MaxHeap ( nat n ) : _size(0), max_size(n), heap ( new T[n+1] ) {}
    ~MaxHeap () { delete[] heap; }
// Указатель на i-тый элемент ( 0, если i выходит за предел )
    T * operator[] ( nat i ) { return _size > i ? heap + i + 1 : 0; }
// Количество элементов в очереди
    nat size() const { return _size; }
// Очистить очередь
    void clear() { _size = 0; }
// Поднять i-тый элемент
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
// Опустить i-тый элемент
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
// Удалить i-тый элемент
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
// Добавить элемент в очередь
    bool operator << ( const T & o )
    {
        if ( _size == max_size ) return false;
        heap[++_size] = o;
        raise ( _size - 1 );
        return true;
    }
// Убрать максимальный элемент из очереди
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
class MinHeap // Очередь с минимальным приоритетом
{
    nat _size, max_size;
    T * heap;
// Запрет конструктора копии и оператора присваивания
    MinHeap ( const MinHeap & );
    void operator = ( const MinHeap & );
public:
    explicit MinHeap ( nat n ) : _size(0), max_size(n), heap ( new T[n+1] ) {}
    ~MinHeap () { delete[] heap; }
// Указатель на i-тый элемент ( 0, если i выходит за предел )
    T * operator[] ( nat i ) { return _size > i ? heap + i + 1 : 0; }
// Количество элементов в очереди
    nat size() const { return _size; }
// Очистить очередь
    void clear() { _size = 0; }
// Поднять i-тый элемент
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
// Опустить i-тый элемент
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
// Удалить i-тый элемент
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
// Добавить элемент в очередь
    bool operator << ( const T & o )
    {
        if ( _size == max_size ) return false;
        heap[++_size] = o;
        raise ( _size - 1 );
        return true;
    }
// Убрать минимальный элемент из очереди
    bool operator >> ( T & o )
    {
        if ( _size == 0 ) return false;
        o = heap[1];
        _swap ( heap[1], heap[_size--] );
        down ( 0 );
        return true;
    }
};
