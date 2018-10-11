
#include "math.h"
#include "trans.h"
#include "trian2d.h"
#include "Vector3f.h"
#include "Poly3gon.h"
#include "Polyhedron.h"

// Неортогональное преобразование трёхмерных векторов в двухмерные

Vector2d transXP ( const Vector3d & u )
{
    return Vector2d ( u.y, u.z );
}

Vector2d transXO ( const Vector3d & u )
{
    return Vector2d ( u.z, u.y );
}

Vector2d transYP ( const Vector3d & u )
{
    return Vector2d ( u.z, u.x );
}

Vector2d transYO ( const Vector3d & u )
{
    return Vector2d ( u.x, u.z );
}

Vector2d transZP ( const Vector3d & u )
{
    return Vector2d ( u.x, u.y );
}

Vector2d transZO ( const Vector3d & u )
{
    return Vector2d ( u.y, u.x );
}

Func3to2 getTrans ( const Vector3d & norm )
{
    const double ax = fabs ( norm.x );
    const double ay = fabs ( norm.y );
    const double az = fabs ( norm.z );

    if ( ax >= ay && ax >= az )
    {
        return norm.x > 0 ? transXP : transXO;
    }

    if ( ay >= ax && ay >= az )
    {
        return norm.y > 0 ? transYP : transYO;
    }

    {
        return norm.z > 0 ? transZP : transZO;
    }
}

ArrRef<Vector2d> trans ( CArrRef<Vector3d> from, const Vector3d & norm, ArrRef<Vector2d> to )
{
    Func3to2 func = getTrans ( norm );
    const nat n = _min ( from.size(), to.size() );
    for ( nat i = 0; i < n; ++i ) to[i] = func ( from[i] );
    return to;
}

// Неортогональное преобразование двухмерных векторов в трёхмерные

Vector3d _transXP ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.x * c.x + u.y * c.y + c.z, u.x, u.y );
}

Vector3d _transXO ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.y * c.x + u.x * c.y + c.z, u.y, u.x );
}

Vector3d _transYP ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.y, u.x * c.x + u.y * c.y + c.z, u.x );
}

Vector3d _transYO ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.x, u.y * c.x + u.x * c.y + c.z, u.y );
}

Vector3d _transZP ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.x, u.y, u.x * c.x + u.y * c.y + c.z );
}

Vector3d _transZO ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( u.y, u.x, u.y * c.x + u.x * c.y + c.z );
}

Vector3d _trans0 ( const Vector3d & c, const Vector2d & u )
{
    return Vector3d ( 0, 0, 0 );
}

Func2to3::Func2to3 ( const Plane3d & plane )
{
    const double ax = fabs ( plane.norm.x );
    const double ay = fabs ( plane.norm.y );
    const double az = fabs ( plane.norm.z );

    if ( ax >= ay && ax >= az )
    {
        if ( ! ax )
        {
            func = _trans0;
            return;
        }
        const double t = -1. / plane.norm.x;
        c.x = plane.norm.y * t;
        c.y = plane.norm.z * t;
        c.z = plane.dist * t;
        func = plane.norm.x > 0 ? _transXP : _transXO;
    }
    else
    if ( ay >= ax && ay >= az )
    {
        const double t = -1. / plane.norm.y;
        c.x = plane.norm.z * t;
        c.y = plane.norm.x * t;
        c.z = plane.dist * t;
        func = plane.norm.y > 0 ? _transYP : _transYO;
    }
    else
    {
        const double t = -1. / plane.norm.z;
        c.x = plane.norm.x * t;
        c.y = plane.norm.y * t;
        c.z = plane.dist * t;
        func = plane.norm.z > 0 ? _transZP : _transZO;
    }
}

ArrRef<Vector3d> trans ( CArrRef<Vector2d> from, const Plane3d & plane, ArrRef<Vector3d> to )
{
    Func2to3 func ( plane );
    const nat n = _min ( from.size(), to.size() );
    for ( nat i = 0; i < n; ++i ) to[i] = func ( from[i] );
    return to;
}

// Ортогональное преобразование трёхмерных векторов в двухмерные

ArrRef<Vector2d> ortho_trans ( CArrRef<Vector3d> from, const Vector3d & norm, ArrRef<Vector2d> to )
{
    Vector3d vx, vy;
    reper ( norm, vx, vy );
    const nat n = _min ( from.size(), to.size() );
    for ( nat i = 0; i < n; ++i )
    {
        to[i].x = vx * from[i];
        to[i].y = vy * from[i];
    }
    return to;
}

// Ортогональное преобразование двухмерных векторов в трёхмерные

ArrRef<Vector3d> ortho_trans ( CArrRef<Vector2d> from, const Plane3d & plane, ArrRef<Vector3d> to )
{
    Vector3d vx, vy;
    reper ( plane.norm, vx, vy );
    const Vector3d vz = - plane.dist * plane.norm;
    const nat n = _min ( from.size(), to.size() );
    for ( nat i = 0; i < n; ++i ) to[i] = vx * from[i].x + vy * from[i].y + vz;
    return to;
}

// Преобразование грани многогранника в многоугольник на плоскости

DynArrRef<Vector2d> & ortho_trans ( CArrRef<Vector3d> v, const Facet & facet, DynArrRef<Vector2d> & p )
{
    Vector3d vx, vy;
    reper ( facet.plane.norm, vx, vy );
    p.resize ( facet.nv );
    for ( nat i = 0; i < facet.nv; ++i )
    {
        const Vector3d & t = v[facet.index[i]];
        p[i].x = vx * t;
        p[i].y = vy * t;
    }
    return p;
}

DynArrRef<Vector2d> & trans ( CArrRef<Vector3d> v, const Facet & facet, DynArrRef<Vector2d> & p )
{
    const double ax = fabs ( facet.plane.norm.x );
    const double ay = fabs ( facet.plane.norm.y );
    const double az = fabs ( facet.plane.norm.z );
    CArrRef<nat> index ( facet.index, 0, facet.nv );
    p.resize ( facet.nv );
    if ( ax >= ay && ax >= az )
    {
        if ( facet.plane.norm.x > 0 )
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.y;
                p[i].y = t.z;
            }
        }
        else
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.z;
                p[i].y = t.y;
            }
        }
    }
    else
    if ( ay >= ax && ay >= az )
    {
        if ( facet.plane.norm.y > 0 )
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.z;
                p[i].y = t.x;
            }
        }
        else
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.x;
                p[i].y = t.z;
            }
        }
    }
    else
    {
        if ( facet.plane.norm.z > 0 )
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.x;
                p[i].y = t.y;
            }
        }
        else
        {
            for ( nat i = 0; i < facet.nv; ++i )
            {
                const Vector3d & t = v[index[i]];
                p[i].x = t.y;
                p[i].y = t.x;
            }
        }
    }
    return p;
}

//**************************** 25.01.2006 ****************************
//
//  Шаблоны копирования Polyhedron в Poly3gon<Vector, Vector> и наоборот
//
//**************************** 06.09.2012 ****************************

template < class Vector >
void tempCopy1 ( const Poly3gon<Vector, Vector> & poly1, Polyhedron & poly2 )
{
    poly2.vertex.resize ( poly1.vertex.size() );
    poly2.facet.resize ( poly1.side.size() );

    nat i;
    for ( i = 0; i < poly2.vertex.size(); ++i )
    {
        const Vector & v1 = poly1.vertex[i];
        Vector3d & v2 = poly2.vertex[i];
        v2.x = v1.x;
        v2.y = v1.y;
        v2.z = v1.z;
    }

    for ( i = 0; i < poly2.facet.size(); ++i )
    {
        const Trigon<Vector> & t = poly1.side[i];
        Facet & facet = poly2.facet[i];
        facet.plane = Plane3d ( poly2.vertex[t.a], poly2.vertex[t.b], poly2.vertex[t.c] );
        facet.resize ( 3 );
        facet.index[0] = t.a;
        facet.index[1] = t.b;
        facet.index[2] = t.c;
    }

    poly2.linkFacets();
}

template < class Scalar, class Vector >
void tempCopy2 ( const Polyhedron & poly1, Poly3gon<Vector, Vector> & poly2 )
{
    poly2.vertex.resize ( poly1.vertex.size() );
    nat i;
    for ( i = 0; i < poly1.vertex.size(); ++i )
    {
        const Vector3d & v1 = poly1.vertex[i];
        Vector & v2 = poly2.vertex[i];
        v2.x = (Scalar) v1.x;
        v2.y = (Scalar) v1.y;
        v2.z = (Scalar) v1.z;
    }

    Suite< Trigon<Vector> > temp ( poly1.facet.size() );
    Suite<Vector2d> vbuf;
    Suite<Set3<nat> > tbuf;
    for ( i = 0; i < poly1.facet.size(); ++i )
    {
        const Facet & facet = poly1.facet[i];
        if ( facet.nv < 3 ) continue;
        if ( facet.nv == 3 )
        {
            Trigon<Vector> & g = temp.inc();
            g.a = facet.index[0];
            g.b = facet.index[1];
            g.c = facet.index[2];
            g.info.x = (Scalar) facet.plane.norm.x;
            g.info.y = (Scalar) facet.plane.norm.y;
            g.info.z = (Scalar) facet.plane.norm.z;
            continue;
        }
        ortho_trans ( poly1.vertex, facet, vbuf );
        tbuf.resize ( facet.nv - 2 );
        const nat n = trianNat1L1MaxMinTan ( vbuf, tbuf ).size();
        for ( nat j = 0; j < n; ++j )
        {
            const Set3<nat> & t = tbuf[j];
            Trigon<Vector> & g = temp.inc();
            g.a = facet.index[t.a];
            g.b = facet.index[t.b];
            g.c = facet.index[t.c];
            g.info.x = (Scalar) facet.plane.norm.x;
            g.info.y = (Scalar) facet.plane.norm.y;
            g.info.z = (Scalar) facet.plane.norm.z;
        }
    }
    poly2.side = temp;
}

//**************************** 25.01.2006 ****************************
//
//  Копирование Polyhedron в Poly3gon<Vector3f, Vector3f> и наоборот
//
//**************************** 25.03.2009 ****************************

void copy ( const Poly3gon<Vector3f, Vector3f> & poly1, Polyhedron & poly2 )
{
    tempCopy1 ( poly1, poly2 );
}

void copy ( const Polyhedron & poly1, Poly3gon<Vector3f, Vector3f> & poly2 )
{
    tempCopy2 <float, Vector3f> ( poly1, poly2 );
}

//**************************** 31.01.2007 ****************************
//
//  Копирование Polyhedron в Poly3gon<Vector3d, Vector3d> и наоборот
//
//**************************** 25.03.2009 ****************************

void copy ( const Poly3gon<Vector3d, Vector3d> & poly1, Polyhedron & poly2 )
{
    tempCopy1 ( poly1, poly2 );
}

void copy ( const Polyhedron & poly1, Poly3gon<Vector3d, Vector3d> & poly2 )
{
    tempCopy2 <double, Vector3d> ( poly1, poly2 );
}

