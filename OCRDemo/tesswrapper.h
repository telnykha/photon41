#pragma once
#ifndef __tess_wrapper_h__
#define __tess_wrapper_h__

#ifdef TESS_EXPORTS
#define TESS_API  __declspec(dllexport)  
#else
#define TESS_API __declspec(dllimport) 
#endif

#define TESSHANDLE void*

extern "C" TESS_API TESSHANDLE  tessInit();
extern "C" TESS_API int  tessProcess(TESSHANDLE tess, unsigned char* data, int width, int height, int bpp, char r[10]);
extern "C" TESS_API int  tessClose(TESSHANDLE tess);


#endif 