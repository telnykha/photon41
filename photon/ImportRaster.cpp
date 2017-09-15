//---------------------------------------------------------------------------
#pragma hdrstop
#include "ImportRaster.h"
#include "tifflibio.h"
#define Z_PREFIX
#include "zlib.h"
#include "png.h"
#include "tiff.h"
#include "pnglibio.h"

/* TImageDecoder-------------------------------------------------------------
    Function:  TImageDecoder::TImageDecoder(const AnsiString& FileName)
    Purpose:   ������� ����������� ��� ���� �������� ����������� ���������
               �����������
    Comments:  ��������� ����������� ����� Init(), ������� ����� �������
               ������������� ��������
---------------------------------------------------------------------------*/
TImageDecoder::TImageDecoder(const AnsiString& FileName)
{
    FFileName = FileName;
    FBof = false;
    FEof = false;
    FCurrentScanLine = 0;
    FNumScanLines    = 0;
    FBufferSize      = 0;
    FScanBuffer      = NULL;
    FWidth           = 0;
}
/* TImageDecoder--------------------------------------------------------------
    Function:  TImageDecoder::~TImageDecoder()
    Purpose:    ������� ���������� ��� ���� �������� ���������� ���������
                ������
    Comments:   �������� �����������  ����� Close()
---------------------------------------------------------------------------*/
TImageDecoder::~TImageDecoder()
{
    if (FScanBuffer != NULL)
        delete[] FScanBuffer;
}
/*TImageDecoder--------------------------------------------------------------
    Function:  TImageDecoder::NextScalLine()
    Purpose:   ��������� ����� ������ ������� �� ������� ������ � �����������
               ������� ����������� ����� �� �������. ���� ������� ������
               �������� ������� ����� �����, �� ��������� ������������� �
               ������������ ���� Eof
    Comments:  �������� ����������� ����� ReadScanLine
---------------------------------------------------------------------------*/
void __fastcall TImageDecoder::NextScalLine()
{
   ReadScanLine(FCurrentScanLine);
   FCurrentScanLine++;
   if (FCurrentScanLine >= FNumScanLines)
   {
       FCurrentScanLine = FNumScanLines;
       FEof = true;
   }
}
/*TImportRaster-------------------------------------------------------------
    Function: TImportRaster::TImportRaster(bool CreateSuspended)
    Purpose:  ����������� ������ TImportRaster
    Comments: �������������� ���������� ����������
---------------------------------------------------------------------------*/
__fastcall TImportRaster::TImportRaster()
{
     FBitmap  = NULL;
     FDecoder = NULL;
     FFileName = "";
     FImage = NULL;
}
/*TImportRaster-------------------------------------------------------------
    Function: TImportRaster::TImportRaster(bool CreateSuspended)
    Purpose:  ����������� ������ TImportRaster
    Comments: �������������� ���������� ����������
---------------------------------------------------------------------------*/
__fastcall TImportRaster::TImportRaster(TFCustomImage* AImage, const AnsiString& FileName)
{
    Image = AImage;
    SetFileName(FileName); 
}


/*TImportRaster-------------------------------------------------------------
    Function: TImportRaster::~TImportRaster()
    Purpose:  ���������� ������ TImportRaster
    Comments: ������������ ��� �������� ������� Decoder ���� ��� ��� ������
---------------------------------------------------------------------------*/
__fastcall TImportRaster::~TImportRaster()
{
   if (FDecoder != NULL)
   {
        delete FDecoder;
   }
 //  if( FBitmap != NULL )
 //   FBitmap->Clear();
}
/*TImportRaster-------------------------------------------------------------
    Function: TImportRaster::Execute()
    Purpose:  ������� ������� ����� TImportRaster ��������� �������������
              ���������� ����� � �������������� ��� � Bitmap
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TImportRaster::Execute()
{
  // DONE: implement TImportRaster::Execute()

  // ������������� ������ FBitmap
  __try
  {
    try
    {
      FDecoder->Init();
      FBitmap->Clear();
      FBitmap->Width  = FDecoder->Width;
      FBitmap->Height = FDecoder->NumScanLines;
      FBitmap->DIBInfo.bmiHeader.biBitCount = 8*FDecoder->ScanLineSize/FDecoder->Width;
      FBitmap->OpenPixels();
      while(!FDecoder->Eof)
      {
           FDecoder->NextScalLine();
           // DONE: copy pixels from decoder to bitmap
           // ��� ��� �������� ������� ������ ��������� ������ � ������� RGB
           // ��������� �� � ������� FBitmap
           unsigned char* dst = (unsigned char*)FBitmap->ScanLine[FDecoder->CurrentScanLine-1];
           unsigned char* src = FDecoder->ScanLine;
           memcpy(dst, src, FDecoder->ScanLineSize);
      }
      FBitmap->ClosePixels();
//      if (!Terminated)
//          FImage->FinishLoading();
      if (FDecoder != NULL)
      {
          try
          {
            FDecoder->Close();
          }
          catch(...)
          {
                //
                FBitmap->Clear();
          }
          delete FDecoder;
          FDecoder = NULL;
      }
    }
    catch(...)
    {
        //owMessage("Exception.");
        if (FDecoder != NULL)
        {
            try
            {
                FDecoder->Close();
            }
            catch(...)
            {
                FBitmap->Clear();
            }
            delete FDecoder;
            FDecoder = NULL;
        }
        throw;
    }
  }
  __finally
  {
///    if (!Terminated)
//        FImage->FinishLoading();
    if (FDecoder != NULL)
    {
      delete FDecoder;
      FDecoder = NULL;
    }
  }
}
/*TImportRaster--------------------------------------------------------------
    Function: TImportRaster::UpdateUI()
    Purpose:  ������������ ��� ������ ������� ���������� �����������������
              ���������� �� ����� �������� ��������� ������
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TImportRaster::UpdateUI()
{
  // DONE: implement TImportRaster::UpdateUI()
  if (FBitmap != NULL && FBitmap->OnProgress)
  {
    Byte PercentDone = 100*FDecoder->CurrentScanLine/FDecoder->NumScanLines;
    bool Redraw = PercentDone %10 == 0?true:false; // call redraw each 10 %
    TRect R; R.left = 0; R.top = 0;
    R.Right = FDecoder->Width; R.Bottom = FDecoder->CurrentScanLine;
    FBitmap->OnProgress(FBitmap, psRunning, PercentDone, Redraw, R, "Loading");
  }
}
/*TImportRaster-------------------------------------------------------------
    Function: TImportRaster::SetFileName(AnsiString& FileName)
    Purpose:  ������������� ��� ����� ��� ������� ������� � ��������������
              ������� ��������� ������, ���������� �� ���������� �����
    Comments: ��������� ���� ���������� ����������� �� ����� ����������
              �����
---------------------------------------------------------------------------*/
void __fastcall TImportRaster::SetFileName(AnsiString FileName)
{
  try
  {
        AnsiString strExt = ExtractFileExt(FileName);
        strExt = strExt.UpperCase();
       if (strExt == ".TIFF" || strExt == ".TIF")
            FDecoder = new TTiffDecoder(FileName);
        else if (strExt == ".PNG")
            FDecoder = new TPngDecoder(FileName);
        else  //todo: add another file formats
            throw   Exception("Invalid file format");
  }
  catch(const Exception& e)// <-- catch exeptions
  {
     // ��������� ������� ���� ����������
     if (FDecoder != NULL)
        delete FDecoder;
     FFileName = "";
     throw;
  }
  catch(...)
  {
     // ��������� ������� ���� ����������
     if (FDecoder != NULL)
        delete FDecoder;
     FFileName = "";
     throw;
  }
}
/*TImportRaster-------------------------------------------------------------
    Function:  TImportRaster::SetImage(TFCustomImage* AImage)
    Purpose:   ������������� ��������� �� ��������� � ������� ����� ���������������
               �����������
    Comments:  ��������� ���� ���������� ����������� �� ����� ����������
              �����
---------------------------------------------------------------------------*/
void __fastcall TImportRaster::SetImage(TFCustomImage* AImage)
{
   if (AImage != NULL && AImage != FImage)
   {
        FImage = AImage;
        FBitmap = dynamic_cast<TDIBImage*>(FImage->Bitmap);
   }
}
/*TImportRaster--------------------------------------------------------------
    Function: TImportRaster::SetBitmap(Graphics::TBitmap* ABitmap)
    Purpose:  ������������� ��������� �� Bitmap � ������� ����� ���������������
              �����������
    Comments: ��������� ���� ���������� ����������� �� ����� ����������
              �����
---------------------------------------------------------------------------*/
void __fastcall TImportRaster::SetBitmap(TDIBImage* ABitmap)
{
    if (FBitmap != ABitmap)
        FBitmap = ABitmap;
    if (FImage != NULL)
        FImage = NULL;
}
#pragma package(smart_init)
