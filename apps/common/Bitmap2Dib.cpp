//---------------------------------------------------------------------------
#pragma hdrstop
#include "Bitmap2Dib.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
bool Bitmap2Dib(Graphics::TBitmap* bmp, BITMAPINFO** info, unsigned char** data)
{
   unsigned int InfoSize = 0;
   unsigned int DataSize = 0;

   if (bmp == NULL)
    return false;
   GetDIBSizes(bmp->Handle, InfoSize, DataSize);
   *info = (BITMAPINFO*)malloc(InfoSize);
   if (*info == NULL)
    return false;
   HGLOBAL hglb =  (unsigned char*)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, DataSize);
   if (hglb == NULL)
   {
    free(*info);
    info = NULL;
    return false;
   }
   *data = (unsigned char *) ::GlobalLock( (HGLOBAL)hglb );
   if (!::GetDIB(bmp->Handle, bmp->Palette, *info, *data))
   {
    free(*info);
    info = NULL;
    GlobalFree(*data);
    return false;
   }
   return true;
}

void FreeDib(BITMAPINFO* info, unsigned char* data)
{
    free(info);
    GlobalUnlock(data);
    GlobalFree(data);
}

bool awpwinDrawStatusText(awpImage* img, const char* text, awpRect pos)
{
    if (img == NULL || text == NULL)
        return false;
    if (awpRectInImage(img, &pos) != AWP_OK)
        return false;

    int w = pos.right;
    int h = pos.bottom;

    Graphics::TBitmap* bmp = new Graphics::TBitmap();
    if (bmp == NULL)
        return false;

    bmp->Width   = w;
    bmp->Height  = h;

    TCanvas* cnv = bmp->Canvas;
    cnv->Font->Height = 32;
    UnicodeString str = text;

    int th = cnv->TextHeight(str);
    int tw = cnv->TextWidth(str);

    if (th > h || tw > w)
    {
        delete bmp;
        return false;
    }

    cnv->TextOutW(5,5, str);

    BITMAPINFO* info = NULL;
    unsigned char* data = NULL;
	if (!Bitmap2Dib(bmp, &info, &data))
    {
        delete bmp;
        return false;
    }

    awpImage* tmp = NULL;
    if (awpDIBToImage(info, data, &tmp) != AWP_OK)
    {
        delete bmp;
        FreeDib(info, data);
        return false;
    }

#ifdef _DEBUG
    awpSaveImage("tmp.jpg", tmp);
#endif

    awpPoint p;
    p.X = 0;
    p.Y = 2;

    if (awpPasteRect(tmp, img,  p) != AWP_OK)
    {
        delete bmp;
        FreeDib(info, data);
        return false;
    }

    FreeDib(info, data);
	delete bmp;
    _AWP_SAFE_RELEASE_(tmp)
    return true;
}

bool awpwinDrawRuler(awpImage* img, awpRect rect, const char* text)
{
/*    if (img == NULL || text == NULL)
        return false;
    if (awpRectInImage(img, &rect) != AWP_OK)
        return false;

    int w = pos.right;
    int h = pos.bottom;

    Graphics::TBitmap* bmp = new Graphics::TBitmap();
    if (bmp == NULL)
        return false;

    bmp->Width   = w;
    bmp->Height  = h;

    TCanvas* cnv = bmp->Canvas;
    cnv->Font->Height = 32;
    UnicodeString str = text;

    int th = cnv->TextHeight(str);
    int tw = cnv->TextWidth(str);

    if (th > h || tw > w)
    {
        delete bmp;
        return false;
    }

    cnv->TextOutW(5,5, str);

    BITMAPINFO* info = NULL;
    unsigned char* data = NULL;
	if (!Bitmap2Dib(bmp, &info, &data))
    {
        delete bmp;
        return false;
    }

    awpImage* tmp = NULL;
    if (awpDIBToImage(info, data, &tmp) != AWP_OK)
    {
        delete bmp;
        FreeDib(info, data);
        return false;
    }

#ifdef _DEBUG
    awpSaveImage("tmp.jpg", tmp);
#endif

    awpPoint p;
    p.X = 0;
    p.Y = 2;

    if (awpPasteRect(tmp, img,  p) != AWP_OK)
    {
        delete bmp;
        FreeDib(info, data);
        return false;
    }

    FreeDib(info, data);
	delete bmp;
    _AWP_SAFE_RELEASE_(tmp)
*/
    return true;
}

