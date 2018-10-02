
#include <math.h>

#include "func3d.h"
#include "Vector2d.h"
#include "Vector3d.h"
#include "WireModel.h"
#include "opti2d_3d.h"
#include "Polyhedron.h"

//**************************** 29.11.2017 *********************************//
//
//      ћаксимальный круг вписанный в выпуклый многогранник
//
//**************************** 29.11.2017 *********************************//

class FarPoint
{
public:
    virtual Vector3d operator() ( const Vector3d & a, const Vector3d & v ) = 0;
};

bool maxSolidOfRevolutionInConvexPolyhedron ( const Polyhedron & poly, bool sym, List< Vertex<6> > & stor,
                                              Conform3d & res, FarPoint & func );

class CircleFarPoint : public FarPoint
{
public:
    virtual Vector3d operator() ( const Vector3d & a, const Vector3d & v )
    {
        return ( a - ( a * v ) * v ).setNorm2();
    }
};

Def<Circle3d> maxCircleInConvexPolyhedron ( const Polyhedron & poly )
{
    Conform3d conf;
    Def<Circle3d> res;
    List< Vertex<6> > stor;
    if ( ! maxSolidOfRevolutionInConvexPolyhedron ( poly, true, stor, conf, CircleFarPoint() ) )
        return res;
    res.isDef = true;
    res.spin = conf.spin;
    res.o = conf.trans;
    res.r = conf.magn;
    return res;
}

//**************************** 08.07.2018 *********************************//
//
//      ћаксимальный треугольник вписанный в выпуклый многогранник
//
//**************************** 08.07.2018 *********************************//

Def<Triangle3d> maxTriangleInConvexPolyhedronA ( const Polyhedron & poly )
{
    Def<Triangle3d> triangle;
    CArrRef<Vector3d> vert = poly.vertex;
    if ( vert.size() < 3 ) return triangle;
    nat m0(0), m1(1), m2(2);
    double max = qmod ( ( vert[m1] - vert[m0] ) % ( vert[m2] - vert[m1] ) );
    for ( nat i0 =    0; i0 < vert.size() - 2; ++i0 )
    for ( nat i1 = i0+1; i1 < vert.size() - 1; ++i1 )
    for ( nat i2 = i1+1; i2 < vert.size()    ; ++i2 )
    {
        const double d = qmod ( ( vert[i1] - vert[i0] ) % ( vert[i2] - vert[i1] ) );
        if ( max < d )
        {
            max = d;
            m0 = i0;
            m1 = i1;
            m2 = i2;
        }
    }
    triangle.a = vert[m0];
    triangle.b = vert[m1];
    triangle.c = vert[m2];
    triangle.isDef = true;
    return triangle;
}

//**************************** 08.04.2018 *********************************//
//
//      ћаксимальный параллелограмм вписанный в выпуклый многогранник
//
//**************************** 08.04.2018 *********************************//

static bool maxParallelogramPerimeter ( const WireModel<9> & model, Double<9> & best )
{
    Show< Vertex<9> > show ( model.vlist );
    double max = 0.;
    if ( show.top() )
    do
    {
        const Double<9> & pc = show.cur()->coor;
        const double t = sqrt ( pc.d3 * pc.d3 + pc.d4 * pc.d4 + pc.d5 * pc.d5 ) +
                         sqrt ( pc.d6 * pc.d6 + pc.d7 * pc.d7 + pc.d8 * pc.d8 );
        if ( max < t ) max = t, best = pc;
    }
    while ( show.next() );
    return max > 0;
}

static
bool maxParallelogramInConvexPolyhedron ( CArrRef<Vector2d> poly, CArrRef<Plane3d> plane, 
                                          WireModel<9> & model, List< Vertex<9> > & stor,
                                          Parallelogram3d & res
                                        )
{
    for ( nat i = 0; i < 1000; ++i )
    {
// ѕоиск максимального решени€
        Double<9> best;
        if ( ! maxParallelogramPerimeter ( model, best ) ) return false;
// ѕоиск максимального нарушени€ ограничений дл€ выбранного решени€
        nat km;
        Vector2d pm;
        double max = 0.;
        for ( nat j = 0; j < poly.size(); ++j )
        {
            const Vector2d & p = poly[j];
            const Vector3d v ( best.d6*p.y + best.d3*p.x + best.d0,
                               best.d7*p.y + best.d4*p.x + best.d1,
                               best.d8*p.y + best.d5*p.x + best.d2 );
            for ( nat k = 0; k < plane.size(); ++k )
            {
                const double t = plane[k] % v;
                if ( max < t ) max = t, pm = p, km = k;
            }
        }
// ≈сли нарушение мало, то завершение программы
        if ( max < 1e-5 )
        {
            Vector3d a ( best.d0, best.d1, best.d2 ), 
                     b ( best.d3, best.d4, best.d5 ), 
                     c ( best.d6, best.d7, best.d8 );
            res = Parallelogram3d ( a, a + b, a + b + c );
//display << i+1 << model.vlist.size() << NL;
            return true;
        }
// ѕрименение ограничени€ к области допустимых преобразований
        const Vector3d & n = plane[km].norm;
        Double<10> g;
        g.d0 = n.x;
        g.d1 = n.y;
        g.d2 = n.z;
        g.d3 = n.x * pm.x;
        g.d4 = n.y * pm.x;
        g.d5 = n.z * pm.x;
        g.d6 = n.x * pm.y;
        g.d7 = n.y * pm.y;
        g.d8 = n.z * pm.y;
        g.d9 = plane[km].dist;
        model.cut ( g, stor );
    }
    return false;
}

Def<Parallelogram3d> maxParallelogramInConvexPolyhedronP ( const Polyhedron & poly )
{
    Def<Parallelogram3d> res;
// ѕриведение многоугольника к стандартному положению
    DynArray<Plane3d> plane ( poly.facet.size() );
    nat i;
    for ( i = 0; i < poly.facet.size(); ++i ) plane[i] = poly.facet[i].plane;
    const Segment3d seg = dimensions ( poly.vertex );
    const double max = normU ( seg );
    if ( max == 0 ) return res;
    const double coef = 2. / max;
    const Conform3d conf ( -0.5 * coef * ( seg.a + seg.b ), coef );
    plane *= Similar3d ( conf );
    FixArray<Vector2d, 4> coor;
    coor[0] = Vector2d(0,0);
    coor[1] = Vector2d(1,0);
    coor[2] = Vector2d(1,1);
    coor[3] = Vector2d(0,1);
    WireModel<9> model;
    List< Vertex<9> > stor;
    model.simplex ( 2*9, stor );
    Double<9> dn;
    dn.fill ( 1. );
    model.vlist -= dn;
    Double<10> g;
    g.d3 = 1;
    g.d6 = -1;
    g.d0 = g.d1 = g.d2 = g.d4 = g.d5 = g.d7 = g.d8 = g.d9 = 0;
    model.cut ( g, stor );
    if ( maxParallelogramInConvexPolyhedron ( coor, plane, model, stor, res ) )
    {
        res.isDef = true;
        res *= ~conf;
    }
    return res;
}