//---------------------------------------------------------------------------
#ifndef ImportRasterH
#define ImportRasterH
#include "FImage.h"
#include "DIBImage.h"
//TImageDecoder class----------------------------
//���������� ������� ����� ��������������� ���
//����������� ���������� ������� ����������� ��������� ������

class TImageDecoder
{
protected:
    unsigned char* FScanBuffer;     //�����, � ������� ���������� ��������� ����������� ������ �����������
    int            FBufferSize;     //������ ������ ������
    int            FNumScanLines;   //����� ����� ��� ������
    int            FCurrentScanLine;// ����� �������, ������� ����� �������� ���������.
    bool           FBof;            // ���� ������ �����
    bool           FEof;            // ���� ����� �����
    AnsiString     FFileName;       // ��� ����� ��� �����������
    int            FWidth;          // ������ ����������� � ��������
protected:
    virtual void __fastcall ReadScanLine(int ScanLine) = 0;
public:
    TImageDecoder(const AnsiString& FileName);
    ~TImageDecoder();

    virtual void __fastcall Init() =0;
    virtual void __fastcall Close()=0;

    void __fastcall NextScalLine();

    __property unsigned char* ScanLine = {read = FScanBuffer};
    __property int ScanLineSize = {read = FBufferSize};
    __property int NumScanLines = {read = FNumScanLines};
    __property int CurrentScanLine = {read = FCurrentScanLine};
    __property bool Bof = {read = FBof};
    __property bool Eof = {read = FEof};
    __property int  Width = {read = FWidth}; 
};


//TImportRaster class----------------------------
//����� ��������� TThred ��� ������ ��������� ������
//��� ������ ���������� ��������� TImageDecoder
//���������� ������ ����������� ����� - ��������������� ������������
//todo: ���������� ��� ������������ ��� ����� ������ 1. � ���������� TFImage 2. c ���������� TBitmap
class TImportRaster /*: public TThread*/
{
friend class TFImage;
private:
    TDIBImage*       FBitmap;  //�����, ���� ����� ��������������� ��������� ������
    TImageDecoder*  FDecoder; //������� ��������� ������
    AnsiString      FFileName;//��� ����� � ���������� �������
    TFCustomImage*        FImage;   //
    void __fastcall SetFileName(AnsiString FileName);
    void __fastcall SetImage(TFCustomImage* AImage);
    void __fastcall SetBitmap(TDIBImage* ABitmap);
public:
   __fastcall TImportRaster();
   __fastcall TImportRaster(TFCustomImage* AImage, const AnsiString& FileName);
   __fastcall ~TImportRaster();
   void __fastcall UpdateUI();
   virtual void __fastcall Execute();
   //properties
   __property TDIBImage*         Bitmap = {read = FBitmap, write = SetBitmap};
   __property AnsiString         FileName = {read = FFileName, write = SetFileName};
   __property TFCustomImage*     Image = {read = FImage, write = SetImage};
};
//---------------------------------------------------------------------------
#endif
