#ifndef __image_h__
#define __image_h__

#ifdef IMAGE_EXPORTS
#define IMAGE_API __declspec(dllexport)
#else
#define IMAGE_API __declspec(dllimport)
#endif

DECLARE_HANDLE(HIMAGE);
DECLARE_HANDLE(HFILTER);
DECLARE_HANDLE(HCONFIG);


IMAGE_API HIMAGE   __stdcall createImage(unsigned short width, unsigned short height, unsigned char channels);
IMAGE_API HRESULT  __stdcall releaseImage(HIMAGE himage);
IMAGE_API HIMAGE   __stdcall copyImage(HIMAGE himage);

IMAGE_API HRESULT  __stdcall loadImage(HIMAGE himage, LPWSTR lpFileName);
IMAGE_API HRESULT  __stdcall saveImage(HIMAGE himage, LPWSTR lpFileName);

IMAGE_API HRESULT  __stdcall imageProps(HIMAGE himage, unsigned short& width, unsigned short& height, unsigned char& channels, unsigned char** data);
IMAGE_API HRESULT  __stdcall imageSetProps(HIMAGE himage, unsigned short width, unsigned short height, unsigned char channels, unsigned char* data);

IMAGE_API HRESULT __stdcall  imageLoadFromDIB(HIMAGE himage, const BITMAPINFO* header, const void* pixels);

#endif //__image_h__