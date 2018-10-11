/*
	this libray is a wrapper for ProGraFix project 
	written by Alex A.Telnykh 
*/
#ifndef _pgf_wrapper_h_
#define _pgf_wrapper_h_

#ifdef PGF_WRAPPER_EXPORTS
	#define PGF_API __declspec(dllexport) 
#else
	#define PGF_API __declspec(dllimport) 
#endif


/*
	use awpIpl as a donor of data structures 
*/
#include "awpipl.h"

#define PGF_OK 0
#define PGF_FAIL -1


#define PGF_CIRCLE_1 1 // Sum ( Ri^2 - R^2 )^2 -> min
#define PGF_CIRCLE_2 2 // Sum ( Ri - R )^2 -> min
#define PGF_CIRCLE_3 3 // Sum | Ri - R | -> min

/* circle approximation 
	
*/ 

extern "C"  PGF_API int pgfGetCircle(const awp2DPoint* points, unsigned int num, awp2DPoint* cm, double* radius, int options);

#endif 