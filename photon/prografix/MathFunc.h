
#pragma once

/********************** MathFunc1 ************************/

class MathFunc1
{
public:
    virtual double operator () ( double ) const = 0;
};


//************************* 28.01.2010 **************************************//
//
//                  Функции двух аргументов
//
//************************* 28.01.2010 **************************************//

class MathFunc2
{
public:
    virtual double operator () ( double, double ) const = 0;
};

class MathAdd : public MathFunc2
{
public:
    virtual double operator () ( double a, double b ) const { return a + b; }
};

class MathMul : public MathFunc2
{
public:
    virtual double operator () ( double a, double b ) const { return a * b; }
};
