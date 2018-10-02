#include <stdio.h>
#include "pgf_wrapper.h"
#include "..\approx2d.h"

PGF_API int pgfGetCircle(const awp2DPoint* points, int num, awp2DPoint* cm, double* radius, int options)
{
	if (points == NULL || num == 0 || cm == NULL || radius == NULL)
		return PGF_FAIL;
	
	Vector2d* v = new Vector2d[num];
	for (int i = 0; i < num; i++)
	{
		Vector2d p;
		v[i].x = points[i].X;
		v[i].y = points[i].Y;
	}

	ArrRef<Vector2d> points2d(v, num);
	CArrRef<Vector2d> _points(points2d);
	Def<Circle2d> circle;
	
	switch (options)
	{
	case PGF_CIRCLE_1:
		circle = getCirclePnt22(_points);
		break;
	case PGF_CIRCLE_2:
		circle = getCirclePnt2(_points);
		break;
	case PGF_CIRCLE_3:
		circle = getCirclePnt1(_points);
		break;
	default:
		circle = getCirclePnt22(_points);
		break;
	}
	circle = getCirclePnt22(_points);

	cm->X = circle.o.x;
	cm->Y = circle.o.y;
	*radius = circle.r;

	delete v;
	return PGF_OK;
}
