
#ifndef VECTOR4D_H
#define VECTOR4D_H

class Vector4d
{
public:
    double x1, x2, x3, x4;
    Vector4d () {}
    Vector4d ( double a, double b, double c, double d ) : x1(a), x2(b), x3(c), x4(d) {}
 
    Vector4d operator - () const
    {
        return Vector4d ( - x1, - x2, - x3, - x4 );
    }

    Vector4d & operator += ( const Vector4d & v )
    {
        x1 += v.x1;
        x2 += v.x2;
        x3 += v.x3;
        x4 += v.x4;
        return * this;
    }

    Vector4d & operator -= ( const Vector4d & v )
    {
        x1 -= v.x1;
        x2 -= v.x2;
        x3 -= v.x3;
        x4 -= v.x4;
        return * this;
    }

    Vector4d & operator *= ( const double d )
    {
        x1 *= d;
        x2 *= d;
        x3 *= d;
        x4 *= d;
        return * this;
    }

    Vector4d & operator /= ( const double d )
    {
        x1 /= d;
        x2 /= d;
        x3 /= d;
        x4 /= d;
        return * this;
    }

    Vector4d & fill ( double d = 0 )
    {
        x1 = x2 = x3 = x4 = d;
        return * this;
    }

    bool operator ! () const
    {
        return !x1 && !x2 && !x3 && !x4;
    }
};

inline Vector4d operator + ( const Vector4d & a, const Vector4d & b )
{
    return Vector4d ( a.x1 + b.x1, a.x2 + b.x2, a.x3 + b.x3, a.x4 + b.x4 );
}

inline Vector4d operator - ( const Vector4d & a, const Vector4d & b )
{
    return Vector4d ( a.x1 - b.x1, a.x2 - b.x2, a.x3 - b.x3, a.x4 - b.x4 );
}
 
inline Vector4d operator * ( const Vector4d & a, const double d )
{
    return Vector4d ( a.x1 * d, a.x2 * d, a.x3 * d, a.x4 * d );
}
 
inline Vector4d operator / ( const Vector4d & a, const double d )
{
    return Vector4d ( a.x1 / d, a.x2 / d, a.x3 / d, a.x4 / d );
}
 
inline Vector4d operator * ( const double d, const Vector4d & a )
{
    return Vector4d ( a.x1 * d, a.x2 * d, a.x3 * d, a.x4 * d );
}

inline double operator * ( const Vector4d & a, const Vector4d & b )
{
    return a.x1 * b.x1 + a.x2 * b.x2 + a.x3 * b.x3 + a.x4 * b.x4;
}

inline double qmod ( const Vector4d & a )
{
    return a.x1 * a.x1 + a.x2 * a.x2 + a.x3 * a.x3 + a.x4 * a.x4;
}

inline bool operator == ( const Vector4d & a, const Vector4d & b )
{
    return a.x1 == b.x1 && a.x2 == b.x2 && a.x3 == b.x3 && a.x4 == b.x4;
}

inline bool operator != ( const Vector4d & a, const Vector4d & b )
{
    return a.x1 != b.x1 || a.x2 != b.x2 || a.x3 != b.x3 || a.x4 != b.x4;
}

class Plane4d
{
public:
    Vector4d norm;
    double   dist;

    Plane4d () {}
    Plane4d ( const Vector4d & v, const double & d ) : norm ( v ), dist ( d ) {}

    double operator % ( const Vector4d & v ) const
    {
        return norm * v + dist;
    }
};

#endif