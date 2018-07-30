//---------------------------------------------------------------------------

#ifndef Bitmap2DibH
#define Bitmap2DibH
#include <vcl.h>
#include "awpipl.h"
//---------------------------------------------------------------------------
bool Bitmap2Dib(Graphics::TBitmap *bm, BITMAPINFO** info, int* InfoSize, unsigned char** data, int* DataSize);
void FreeDib(BITMAPINFO* info, unsigned char* data);
bool awpwinDrawStatusText(awpImage* img, const char* text, awpRect pos);

#endif
