
#pragma once

#include "template.h"

class Circle3d;
class Triangle3d;
class Parallelogram3d;

namespace Shev
{
    class Polyhedron;
}

using namespace Shev;


//**************************** 29.11.2017 *********************************//
//
//      ������������ ���� ��������� � �������� ������������
//
//**************************** 29.11.2017 *********************************//

Def<Circle3d> maxCircleInConvexPolyhedron ( const Polyhedron & poly );


//**************************** 08.07.2018 *********************************//
//
//      ������������ ����������� ��������� � �������� ������������
//
//**************************** 08.07.2018 *********************************//

Def<Triangle3d> maxTriangleInConvexPolyhedronA ( const Polyhedron & poly );


//**************************** 08.04.2018 *********************************//
//
//      ������������ �������������� ��������� � �������� ������������
//
//**************************** 08.04.2018 *********************************//

Def<Parallelogram3d> maxParallelogramInConvexPolyhedronP ( const Polyhedron & poly );

