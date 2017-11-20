//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#include <math.hpp>
#include "FImage41.h"
#include "DIBImage41.h"
#include "ExportRaster.h"
#include "ImportRaster.h"
#include "PhImageTool.h"
#pragma hdrstop
#pragma package(smart_init)

#define MAX_ZOOM 10.0f
#define MIN_ZOOM 0.01f
#define ZOOM_STEP 0.1f


#if X64
     extern "C"
    {
      #pragma link "awpipl2b.a"
      #pragma link "JPEGLIB.a"
    }
#else
     extern "C"
    {
      #pragma link "awpipl2b.lib"
      #pragma link "JPEGLIB.lib"
      #pragma link "libpng.lib"
      #pragma link "tifflib.lib"
      #pragma link "zlib.lib"
    }

#endif
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TPhCustomImage *)
{
    new TPhCustomImage(NULL);
}
//---------------------------------------------------------------------------
/*
    Function: TFCustomImage construction
    Purpose:  Создает растровое изображение и объект Selection,
              устанавливает для внутренних переменныех значения по умолчанию
    Comments:
*/
__fastcall TPhCustomImage::TPhCustomImage(TComponent* Owner)
    : TCustomControl(Owner)
{
	FBitmap     = new TDIBImage();
    FSelectedBitmap = NULL;
	FScale      = 1;

	FBorderStyle = bsFSingle;
	// установка наследуемых свойств по умолчанию
	Color = clWindow;
	ParentColor = false;
	Width   = 100;
	Height  = 100;
	FFileName  = "";
	FBeforeOpen = NULL;
	FAfterOpen  = NULL;
	FPosChange  = NULL;
	FScaleChange = NULL;
        FChange      = NULL;
	FStartPoint.x = 0;
	FStartPoint.y = 0;
//	Screen->Cursor = TCursor(crHandOpenCursor);
//	this->Cursor   = TCursor(crHandOpenCursor);
//	Screen->Cursor = TCursor(crDefault);
	FSelRect.Left = 0;
	FSelRect.Top = 0;
	FSelRect.Right = 0;
	FSelRect.Bottom = 0;

	FSelCols = 1;
	FSelRows = 1;

	m_modified = false;
	m_pMediaSource = NULL;

	m_ph_tools = new TList();
    m_selected_ph_tool = 0;
}
/* ---------------------------------------------------------------------------
	Function:  destructor of the  TFCustomImage
	Purpose:   if we have raster data abs other objects delete them
	Comments:
---------------------------------------------------------------------------*/
__fastcall TPhCustomImage::~TPhCustomImage()
{
	Close();
}
/* ---------------------------------------------------------------------------
	Function: TFCustomImage::Init(AnsiString& FileName)
	Purpose:  Init Photon with list of media files
	Comments:
	При замене существующего изображения новым, делается копия существующего
	изображения. В случае аварии при загрузке нового изображения старое
	восстанавливается из копии.
---------------------------------------------------------------------------*/
bool  __fastcall TPhCustomImage::Init(TStrings* Names)
{

    if (Names == NULL || Names->Count == 0)
        return false;

    // todo: this version works only with one file
    if (Names->Count > 1)
        return false;

    // todo: check number of files in the source list
    // open list with limit 4096 files

    AnsiString FileName;
    Close();
    try
    {
       FileName = Names->Strings[0];
       if (FBeforeOpen)
          FBeforeOpen(this);
       if (!LoadFromFile(FileName.c_str()))
          return false;
    }
    catch(Exception& e)
    {
        //FErrorMessage = e.Message;
    }
    catch(...)
    {
       // FErrorMessage = "Unknwn error.";
        return false;
    }
    FFileName = FileName;
    if (FAfterOpen)
        FAfterOpen(this);
    if (FChange)
        FChange(this);
    return true;
}
/*---------------------------------------------------------------------------
    Function: TFCustomImage::Close()
    Purpose:  Освобождает растровые данные и данные selection
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::Close()
{
   FScale          = 1;
   FStartPoint.x   = 0;
   FStartPoint.y   = 0;
   FSelRect.Left = 0;
   FSelRect.Top = 0;
   FSelRect.Right = 0;
   FSelRect.Bottom = 0;
   delete FBitmap;
   FBitmap     = new TDIBImage();

   if (FSelectedBitmap != NULL)
   {
    delete FSelectedBitmap;
    FSelectedBitmap = NULL;
   }

}
void __fastcall     TPhCustomImage::Resize(void)
{
        Paint();
}
/*---------------------------------------------------------------------------
    Function: TFCustomImage::GetScale()
    Purpose:  Возвращает масштаб отображаемого изображения
    Comments:
---------------------------------------------------------------------------*/
float __fastcall TPhCustomImage::GetScale() const
{
    return RoundTo( FScale*100.0f, -2 );
}

//------------------------- Fitting commands --------------------------------
//эта группа методов позволяет пользователю наилучшим образом размещать
//растровые данные во внутренней области компонента
/*
    Function: TFCustomImage::BestFit()
    Purpose:  Размещает изображение таким образом, чтоб оно полностью
              поместилось во внутренней области компонента
    Comments: При этом центр изображения совпадает с центром компонента
*/
void __fastcall TPhCustomImage::BestFit()
{
   if (Empty)
      return;

   FStartPoint.x = 0;
   FStartPoint.y = 0;

   float alfa_c = (float)Width / (float)Height;
   float alfa_i = (float)FBitmap->Width / (float)FBitmap->Height;

   if (alfa_c >= alfa_i)
      FScale = (float)Height / (float)FBitmap->Height;
   else
      FScale = (float)Width / (float)FBitmap->Width;

   FScale = RoundTo( FScale, -2 );

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}
/*
    Function: TFCustomImage::FitWidth()
    Purpose:  Размещает изображение таким образом, что его ширина
              становится равной ширине клиентской области окна.
    Comments: При этом центр изображения совпадает с центром компонента
*/
void __fastcall TPhCustomImage::FitWidth()
{
    if (Empty)
       return;

    float alfa_c = (float)Width / (float)Height;
    float alfa_i = (float)FBitmap->Width / (float)FBitmap->Height;

    if (alfa_c >= alfa_i)
    {
       FStartPoint.x = 0;
       FStartPoint.y = FBitmap->Height / 2 - FBitmap->Width / (2*alfa_c);
       FScale = (float)Height * alfa_c / (float)FBitmap->Width;
    }
    else
    {
       FStartPoint.x = 0;
       FStartPoint.y = 0;
       FScale = (float)Width / (float)FBitmap->Width;
    }
    FScale = RoundTo( FScale, -2 );
    Paint();

   if (FScaleChange)
      FScaleChange(this);
}

/*
    Function: TFCustomImage::FitHeight()
    Purpose:  Размещает изображение таким образом, что его высота
               становится равной высоте клиентской области компонента
    Comments: При этом центр изображения совпадает с центром компонента
*/
void __fastcall TPhCustomImage::FitHeight()
{
   if (Empty)
      return;

   float alfa_c = (float)Width / (float)Height;
   float alfa_i = (float)FBitmap->Width / (float)FBitmap->Height;
   FScale       = (float)Height / (float)FBitmap->Height;

   if (alfa_c >= alfa_i) // картинка влезет целиком на Canvas
   {
      FStartPoint.x = 0;
      FStartPoint.y = 0;
   }
   else
   {
      FStartPoint.x = FBitmap->Width / 2 - Width/(2*FScale);
      FStartPoint.y = 0;
   }

   FScale = RoundTo( FScale, -2 );

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}

//------------------------- Zoom commands ------------------------------------

// макрос, сохраняющий центр видимой области.

#define _VISIBLE_CENTER_      int Cx, Cy;      \
   if ( FBitmap->Height * FScale >= Height )   \
       Cy = int((float)FStartPoint.y + (float)Height / (2.0f*FScale) +0.5f);\
   else                                         \
       Cy = int ((float)FStartPoint.y + (float)FBitmap->Height / 2.0f +0.5f); \
                                            \
   if ( FBitmap->Width * FScale >= Width )    \
       Cx = int((float)FStartPoint.x + (float)Width / (2.0f*FScale) +0.5f); \
   else                                       \
       Cx = int((float)FStartPoint.x + (float)FBitmap->Width / 2.0f +0.5);

/*
    Function:  TFCustomImage::ActualSize()
    Purpose:   Устанавливает коэффициент масштабирования в 100%
    Comments:
*/
void __fastcall TPhCustomImage::ActualSize()
{
   if (Empty)
      return;

   ZoomTo(100);

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}

/*
    Function: TFCustomImage::ZoomIn()
    Purpose:   Увеличивает коэфициент масштабирования изображения на 10%
               от текущего значения todo:
    Comments:
*/
void __fastcall TPhCustomImage::ZoomIn()
{
   if ( Empty || FScale > MAX_ZOOM - ZOOM_STEP )
      return;

   // Сохраним центр видимой области
   _VISIBLE_CENTER_

   FScale = RoundTo( FScale + ZOOM_STEP, -2 );

   // Сместим угол относительно центра
   if ( FBitmap->Width * FScale > Width )
      FStartPoint.x = Cx - Width / (2*FScale);
   else
      FStartPoint.x = 0;

   if ( FBitmap->Height * FScale > Height )
      FStartPoint.y = Cy - Height / (2*FScale);
   else
      FStartPoint.y = 0;

   //
   int Cx1, Cy1;
   if ( FBitmap->Height * FScale >= Height )
       Cy1 = FStartPoint.y + Height / (2*FScale);
   else
       Cy1 = FStartPoint.y + FBitmap->Height / 2;

   if ( FBitmap->Width * FScale >= Width )
       Cx1 = FStartPoint.x + Width / (2*FScale);
   else
       Cx1 = FStartPoint.x + FBitmap->Width / 2;

   FStartPoint.x += Cx - Cx1;
   FStartPoint.y += Cy - Cy1;

   // Скорректируем выходы за границы изображения
   FStartPoint.y = ( FStartPoint.y < 0 ) ? 0 : FStartPoint.y;
   FStartPoint.y = ( FStartPoint.y + GetHeightToDisplay()/FScale > FBitmap->Height ) ?
                     FBitmap->Height - GetHeightToDisplay()/FScale : FStartPoint.y;
   FStartPoint.x = ( FStartPoint.x < 0 ) ? 0 : FStartPoint.x;
   FStartPoint.x = ( FStartPoint.x + GetWidthToDisplay()/FScale > FBitmap->Width ) ?
                     FBitmap->Width - GetWidthToDisplay()/FScale : FStartPoint.x;

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}

/*
    Function: Уменьшает коэфициент масштабирования на 10%
    Purpose:
    Comments:
*/
void __fastcall TPhCustomImage::ZoomOut()
{
   if (Empty || FScale < MIN_ZOOM + ZOOM_STEP)
      return;

    _VISIBLE_CENTER_

   FScale = RoundTo( FScale - ZOOM_STEP, -2 );
   // Сместим угол относительно центра
   if ( FBitmap->Height * FScale > Height )
      FStartPoint.y = Cy - Height / (2*FScale);
   else
      FStartPoint.y = 0;

   if ( FBitmap->Width * FScale > Width )
      FStartPoint.x = Cx - Width / (2*FScale);
   else
      FStartPoint.x = 0;

   int Cx1, Cy1;
   if ( FBitmap->Height * FScale >= Height )
       Cy1 = FStartPoint.y + Height / (2*FScale);
   else
       Cy1 = FStartPoint.y + FBitmap->Height / 2;

   if ( FBitmap->Width * FScale >= Width )
       Cx1 = FStartPoint.x + Width / (2*FScale);
   else
       Cx1 = FStartPoint.x + FBitmap->Width / 2;
   FStartPoint.x += Cx - Cx1;
   FStartPoint.y += Cy - Cy1;

   FStartPoint.y = ( FStartPoint.y < 0 ) ? 0 : FStartPoint.y;
   FStartPoint.y = ( FStartPoint.y + GetHeightToDisplay()/FScale > FBitmap->Height ) ?
                     FBitmap->Height - GetHeightToDisplay()/FScale : FStartPoint.y;
   FStartPoint.x = ( FStartPoint.x < 0 ) ? 0 : FStartPoint.x;
   FStartPoint.x = ( FStartPoint.x + GetWidthToDisplay()/FScale > FBitmap->Width ) ?
                     FBitmap->Width - GetWidthToDisplay()/FScale : FStartPoint.x;

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}
/*
    Function:  TFCustomImage::ZoomTo(int ZoomFactor)
    Purpose:   Изменяет коэфициент масштабирования с соответствии с аргументом
               ZoomFactor
    Comments:  todo: определить допустимые пределы изменения переменной
               ZoomFactor
*/
void __fastcall TPhCustomImage::ZoomTo(int in_ZoomFactor)
{
   if (Empty)
      return;

   float ZoomFactor = (float)in_ZoomFactor/100.0f;

   if (ZoomFactor == FScale ||
       ZoomFactor > MAX_ZOOM ||
       ZoomFactor < MIN_ZOOM)
      return;

   // Сохраним центр видимой области

    _VISIBLE_CENTER_
   // Изменим масштаб
   FScale = ZoomFactor;

   if ( FBitmap->Height * FScale > Height )
      FStartPoint.y = Cy - Height / (2*FScale);
   else
      FStartPoint.y = 0;

   if ( FBitmap->Width * FScale > Width )
      FStartPoint.x = Cx - Width / (2*FScale);
   else
      FStartPoint.x = 0;

   int Cx1, Cy1;
   if ( FBitmap->Height * FScale >= Height )
       Cy1 = FStartPoint.y + Height / (2*FScale);
   else
       Cy1 = FStartPoint.y + FBitmap->Height / 2;

   if ( FBitmap->Width * FScale >= Width )
       Cx1 = FStartPoint.x + Width / (2*FScale);
   else
       Cx1 = FStartPoint.x + FBitmap->Width / 2;
   FStartPoint.x += Cx - Cx1;
   FStartPoint.y += Cy - Cy1;

   FStartPoint.y = ( FStartPoint.y < 0 ) ? 0 : FStartPoint.y;
   FStartPoint.y = ( FStartPoint.y + GetHeightToDisplay()/FScale > FBitmap->Height ) ?
                     FBitmap->Height - GetHeightToDisplay()/FScale : FStartPoint.y;
   FStartPoint.x = ( FStartPoint.x < 0 ) ? 0 : FStartPoint.x;
   FStartPoint.x = ( FStartPoint.x + GetWidthToDisplay()/FScale > FBitmap->Width ) ?
                     FBitmap->Width - GetWidthToDisplay()/FScale : FStartPoint.x;
   Paint();


   if (FScaleChange)
      FScaleChange(this);
}

/*
    Function: TFCustomImage::ZoomToRect(const TRect Rect)
    Purpose:  Размещает выбранный внутри изображения прямоугольный фрагмент
              таким образом, чтобы он полностью поместился внутри
              клиетской области компонента.
    Comments:
*/
void __fastcall TPhCustomImage::ZoomToRect(const TRect Rect)
{
   if ( Empty )
      return;

   if ( Rect.Width() <= 0 || Rect.Height() <= 0 )
      return;

   /* Переместим центр */
   int Cx = GetImageX( Rect.Left ) + Rect.Width()/(2*FScale);
   int Cy = FBitmap->Height - GetImageY( Rect.Top ) - Rect.Height()/(2*FScale);

   /* Новый масштаб */
   float alfa_c = (float)Width / (float)Height;
   float alfa_r = (float)Rect.Width() / (float)Rect.Height();
   
   if (alfa_c >= alfa_r)
      FScale = (float)Height * FScale / Rect.Height();
   else
      FScale = (float)Width * FScale / Rect.Width();
   FScale = RoundTo( FScale, -2 );

   /* Сместим угол относительно центра */
   if ( FBitmap->Height * FScale > Height )
      FStartPoint.y = Cy - Height / (2*FScale);
   else
      FStartPoint.y = 0;

   if ( FBitmap->Width * FScale > Width )
      FStartPoint.x = Cx - Width / (2*FScale);
   else
      FStartPoint.x = 0;
      
   /* Скорректируем выходы за границы */
   FStartPoint.y = ( FStartPoint.y < 0 ) ? 0 : FStartPoint.y;
   FStartPoint.y = ( FStartPoint.y + GetHeightToDisplay()/FScale > FBitmap->Height ) ?
                     FBitmap->Height - GetHeightToDisplay()/FScale : FStartPoint.y;
   FStartPoint.x = ( FStartPoint.x < 0 ) ? 0 : FStartPoint.x;
   FStartPoint.x = ( FStartPoint.x + GetWidthToDisplay()/FScale > FBitmap->Width ) ?
                     FBitmap->Width - GetWidthToDisplay()/FScale : FStartPoint.x;

   Paint();

   if (FScaleChange)
      FScaleChange(this);
}

//--------------------------------Pane support--------------------------------
/*
    Function: TFCustomImage::MoveToCenter()
    Purpose:   Совмещает центр изображения с центром компонента
    Comments:
*/
void __fastcall TPhCustomImage::MoveToCenter()
{
   if (Empty)
      return;
   if (GetHeightToDisplay() < Height && GetWidthToDisplay() < Width)
      return;

   FStartPoint.x = FBitmap->Width/2 - Width/(2*FScale);
   FStartPoint.y = FBitmap->Height/2 - Height/(2*FScale);

   Paint();
   if (FPosChange)
    FPosChange(this);
}
/*
    Function:   TFCustomImage::MoveToLeftTop()
    Purpose:    Совмещает верхний левый угол изображения и верхний левый угол
                компонента
    Comments:   Данная операция применима, если размеры изображения больше
                размеров клинетской области компонента
*/
void __fastcall TPhCustomImage::MoveToLeftTop()
{
   if (Empty)
      return;
   if (GetHeightToDisplay() < Height && GetWidthToDisplay() < Width)
      return;

   FStartPoint.x = 0;
   FStartPoint.y = FBitmap->Height - Height/FScale;
   Paint();
   if (FPosChange)
    FPosChange(this);
}

/*
    Function: MoveToRightBottom()
    Purpose:  Совмещает нижний правый угол изображения и нижний правый угол
              компонента
    Comments: Данная операция применима, если размеры изображения больше
              размеров клинетской области компонента
*/
void __fastcall TPhCustomImage::MoveToRightBottom()
{
   if (Empty)
      return;
   if (GetHeightToDisplay() < Height && GetWidthToDisplay() < Width)
      return;

   FStartPoint.x = FBitmap->Width - Width/FScale;
   FStartPoint.y = 0;

   Paint();
   if (FPosChange)
    FPosChange(this);
}

/*  ----------------------------------------------------------
    Function:   TFCustomImage::MoveBy(int in_dX, int in_dY)
    Purpose:    Смещает центр изображения на dX,dY
    Comments:
*/
void __fastcall TPhCustomImage::MoveBy(int in_dX, int in_dY)
{
   if (Empty)
      return;

   double dX = RoundTo( (double)in_dX / RoundTo(FScale, -2), 0 );
   double dY = RoundTo( (double)in_dY / RoundTo(FScale, -2), 0 );
   
   if ( FBitmap->Width * FScale <= Width &&
        FBitmap->Height * FScale <= Height )
      return;

   if ( FBitmap->Width * FScale > Width )
      if ( FStartPoint.x + dX > FBitmap->Width - Width/FScale )
         FStartPoint.x = FBitmap->Width - Width/FScale;
      else if (FStartPoint.x + dX < 0)
         FStartPoint.x = 0;
      else
         FStartPoint.x += dX;
         
   if ( FBitmap->Height * FScale > Height )
      if ( FStartPoint.y - dY > FBitmap->Height - Height/FScale )
         FStartPoint.y = FBitmap->Height - Height/FScale;
      else if (FStartPoint.y - dY < 0)
         FStartPoint.y = 0;
      else
         FStartPoint.y -= dY;

   Paint();
   if (FPosChange)
    FPosChange(this);
}

/*  ----------------------------------------------------------
    Function:   TFCustomImage::MoveTo(int X, int Y)
    Purpose:    Смещает центр изображения в точку (X,Y)
    Comments:
*/
void __fastcall TPhCustomImage::MoveTo(int X, int Y)
{
   if (Empty)
      return;

   // Изображение полностью влазит на компонент
   if (GetHeightToDisplay() < Height && GetWidthToDisplay() < Width)
      return;

   unsigned int x,y; // внутренние координаты
   x = X;
   y = FBitmap->Height - Y;

   FStartPoint.x = x - Width/(2*FScale);
   FStartPoint.y = y - Height/(2*FScale);

   if ( FStartPoint.x + Width/FScale > FBitmap->Width )
      FStartPoint.x = FBitmap->Width - Width/FScale;
   else if ( FStartPoint.x < 0 )
      FStartPoint.x = 0;

   if ( FStartPoint.y + Height/FScale > FBitmap->Height )
      FStartPoint.y = FBitmap->Height - Height/FScale;
   if ( FStartPoint.y < 0 )
      FStartPoint.y = 0;
      
   Paint();
   if (FPosChange)
    FPosChange(this);
}

/*  ----------------------------------------------------------
    Function:   TFCustomImage::GetWidthToDisplay()
    Purpose:    Вычисляет ширину отображаемой области с учетом коэффициента
                масштабирования.
    Comments:
*/
int TPhCustomImage::GetWidthToDisplay() const
{
   if ( FBitmap->Width * FScale > Width )
      return Width;
   else
      return (int)(FBitmap->Width * FScale);
}

/*  ----------------------------------------------------------
    Function:   TFCustomImage::GetHeightToDisplay()
    Purpose:    Вычисляет высоту отображаемой области с учетом коэффициента
                масштабирования.
    Comments:
*/
int TPhCustomImage::GetHeightToDisplay() const
{
   if ( FBitmap->Height * FScale > Height )
      return Height;
   else
      return FBitmap->Height * FScale;
}

/*  ----------------------------------------------------------
    Function:   TFCustomImage::GetInternalVisibleArea()
    Purpose:    Вычисляет видимую область изображения во внутреннем
                представлении, т.е. перевернутую по Y
    Comments:
*/
TRect __fastcall TPhCustomImage::GetInternalVisibleArea()
{
    TRect area;

    area.Top    = FStartPoint.y;
    area.Bottom = RoundTo( area.Top + GetHeightToDisplay() / FScale, 0 );

    area.Left   = FStartPoint.x;
    area.Right  = RoundTo( area.Left + GetWidthToDisplay() / FScale, 0 );

    return area;
}

void   TPhCustomImage::DrawSelRect(Graphics::TBitmap *bm)
{
   if (FSelRect.Width() == 0 || FSelRect.Height() == 0)
    return;

   if (bm == NULL)
        return;
   TRect FSelRect1 = GetScreenRect(FSelRect);
   TPenStyle style = bm->Canvas->Pen->Style;
   TColor color = bm->Canvas->Pen->Color;
   TPenMode mode = bm->Canvas->Pen->Mode;

   bm->Canvas->Pen->Style = psDot;
   bm->Canvas->Pen->Width = 2;
   bm->Canvas->Pen->Color = clRed;
   bm->Canvas->Pen->Mode = pmCopy;

   bm->Canvas->MoveTo(FSelRect1.Left, FSelRect1.Top);
   bm->Canvas->LineTo(FSelRect1.Right, FSelRect1.Top);
   bm->Canvas->LineTo(FSelRect1.Right, FSelRect1.Bottom);
   bm->Canvas->LineTo(FSelRect1.Left, FSelRect1.Bottom);
   bm->Canvas->LineTo(FSelRect1.Left, FSelRect1.Top);

   float w = FSelRect1.Width() / this->FSelCols;
   for (int i = 1; i < this->FSelCols; i++)
   {
      int x,y;
      x = FSelRect1.left + i*w;
      y = FSelRect1.top;
      bm->Canvas->MoveTo(x,y);
      y = FSelRect1.bottom;
      bm->Canvas->LineTo(x,y);
   }


   float h = FSelRect1.Height() / this->FSelRows;
   for (int i = 1; i < this->FSelRows; i++)
   {
      int x,y;
      x = FSelRect1.left;
      y = FSelRect1.top + i*h;
      bm->Canvas->MoveTo(x,y);
      x = FSelRect1.right;
      bm->Canvas->LineTo(x,y);
   }

   bm->Canvas->Pen->Style = style;
   bm->Canvas->Pen->Color = color;
   bm->Canvas->Pen->Mode = mode;
}

void  __fastcall TPhCustomImage::SetSelCols(int num)
{
    if (num >= 1 && num <= 16)
    {
       this->FSelCols = num;
       Paint();
    }
}

void  __fastcall TPhCustomImage::SetSelRows(int num)
{
    if (num >= 1 && num <= 16)
    {
       this->FSelRows = num;
       Paint();
    }
}

void __fastcall 	TPhCustomImage::ClearSelection()
{
    FSelRect.Left = 0;
    FSelRect.Top = 0;
    FSelRect.Right = 0;
    FSelRect.Bottom = 0;
    if (this->FSelectedBitmap != NULL)
    {
        delete this->FSelectedBitmap;
        this->FSelectedBitmap = NULL;
    }
    Paint();
}

bool __fastcall		   TPhCustomImage::HasSelection()
{
	if (FSelRect.Width() == 0 && FSelRect.Height() == 0)
    	return false;
    else
    	return true;
}

TRect						TPhCustomImage::GetSelRect()
{
	return FSelRect;
}

void                        TPhCustomImage::SetSelRect(TRect r)
{
     FSelRect = r;
     TDIBImage* dib = dynamic_cast<TDIBImage*>(FBitmap);
     if (dib != NULL)
     {
        // clear selected bitmap
        if (this->FSelectedBitmap != NULL)
        {
            delete this->FSelectedBitmap;
            this->FSelectedBitmap = NULL;
        }

        FSelectedBitmap = new TDIBImage();

        awpImage* src = NULL;
        awpImage* sel = NULL;
        TRect sel_rect = FSelRect;//this->GetImageRect(FSelRect);
        awpRect sel_awprect;
        sel_awprect.left = sel_rect.left;
        sel_awprect.top = sel_rect.top;
        sel_awprect.right = sel_awprect.left + sel_rect.Width();
        sel_awprect.bottom = sel_awprect.top + sel_rect.Height();

        //
        dib->GetAWPImage(&src);
        if (src != NULL)
        {
            awpCopyRect(src, &sel, &sel_awprect);
            if (sel != NULL)
            {

                TDIBImage* sel_image = dynamic_cast<TDIBImage*>(FSelectedBitmap);
                sel_image->SetAWPImage(sel);
	            _AWP_SAFE_RELEASE_(sel)
            }
            _AWP_SAFE_RELEASE_(src)
        }
     }
     this->Paint();
}

/*  ----------------------------------------------------------
	Function: TFCustomImage::Paint(void)
	Purpose:  Отображает растровые данные и границы выбранного фрагмента
			  в клиентской области компонента
	Comments:
*/
void __fastcall TPhCustomImage::Paint(void)
{
	if (FBitmap != NULL)
	{
	   Graphics::TBitmap *bm = new Graphics::TBitmap();
	   bm->Width  = Width;
	   bm->Height = Height;
	   bm->Canvas->Brush->Color = clBlack;
	   bm->Canvas->FillRect(ClientRect);
	   TRect src_r, dst_r;
	   dst_r.Left   = 0;
	   dst_r.Right  = GetWidthToDisplay();
	   dst_r.Top    = 0;
	   dst_r.Bottom = GetHeightToDisplay();

	   // Center image
	   if (dst_r.Right < Width)
	   {
		  dst_r.Left  = (Width - dst_r.Right) / 2;
		  dst_r.Right = dst_r.Left + dst_r.Right;
	   }
	   if (dst_r.Bottom < Height)
	   {
		  dst_r.Top    = (Height - dst_r.Bottom) / 2;
		  dst_r.Bottom = dst_r.Top + dst_r.Bottom;
	   }

	   src_r = GetInternalVisibleArea();
           TDIBImage* dib = dynamic_cast<TDIBImage*>(FBitmap);
	   unsigned char* pDIB = dib->OpenPixels();

	   ::SetStretchBltMode(bm->Canvas->Handle, HALFTONE);
	   ::StretchDIBits(bm->Canvas->Handle,
		  dst_r.Left,
		  dst_r.Top,
		  dst_r.Width(),
		  dst_r.Height(),
		  src_r.Left,
		  src_r.Top,
		  src_r.Width(),
		  src_r.Height(),
		  pDIB,
		  &(dib->DIBInfo),
		  DIB_RGB_COLORS,
		  SRCCOPY);

		DrawSelRect(bm);
        // todo: add drawing
	   dib->ClosePixels();
	   Canvas->CopyMode = cmSrcCopy;
	   Canvas->Draw(0,0,bm);
	   delete bm;
	}
	else
	{
		TColor oldColor = this->Canvas->Brush->Color;
		this->Canvas->Brush->Color = clBlack;
		this->Canvas->FillRect(this->ClientRect);
		this->Canvas->Brush->Color = oldColor;
	}
}

/*  ----------------------------------------------------------
*/
int __fastcall TPhCustomImage::GetImageX(int ScreenX)
{
   if (FBitmap == NULL)
    return -1;

   int display_w = GetWidthToDisplay();
   int left, right;

   if ( display_w < Width )
   {
      left = (Width - display_w) / 2;
      right = left + display_w;

      if ( ScreenX < left || ScreenX >= right )
         return -1;
   }
   else
   {
      left = 0;
      right = display_w;
   }

   double sx = RoundTo( FStartPoint.x + (double)(ScreenX - left) / FScale, 0 );

   return ( sx >= 0 && sx <= FBitmap->Width ) ? sx : -1;
}

/*  ----------------------------------------------------------
*/
int __fastcall TPhCustomImage::GetImageY( int ScreenY )
{
   if (FBitmap == NULL)
    return -1;

   int display_h = GetHeightToDisplay();
   int top, bottom;
   int sY = Height - ScreenY;

   if ( display_h < Height )
   {
      top    = ( Height - display_h ) / 2;
      bottom = top + display_h;

      if ( sY <= top || sY > bottom )
         return -1;
   }
   else
   {
      top = 0;
      bottom = display_h;
   }

   double sy  = RoundTo( FBitmap->Height - FStartPoint.y - (double)(sY - top) / FScale, 0 );

   return (sy >= 0 && sy <= FBitmap->Height) ? sy : -1;
}

/*  ----------------------------------------------------------
*/
TRect __fastcall TPhCustomImage::GetImageRect(TRect ScreenR)
{
    TRect ImageR = TRect(-1, -1, -1, -1);

    if ( !Empty )
    {
        ImageR.Left   = GetImageX( ScreenR.Left );
        ImageR.Right  = GetImageX( ScreenR.Right );
        ImageR.Top    = GetImageY( ScreenR.Top );
        ImageR.Bottom = GetImageY( ScreenR.Bottom );
    }

    return ImageR;
}
TPoint   __fastcall         TPhCustomImage::GetScreenPoint(int x, int y)
{
     TPoint result;
     result.x = 0;
     result.y = 0;
     if (Empty)
        return result;
    int dx = 0;
    int dy = 0;

    if ( GetWidthToDisplay() < Width )
        dx = (Width - GetWidthToDisplay()) / 2;

    if ( GetHeightToDisplay() < Height )
        dy = (Height - GetHeightToDisplay()) / 2;

    result.x    =  (x - Corner.x)*FScale + dx;
    result.y    = (y - Corner.y)*FScale + dy;//FStartPoint.y + FScale*ImageR.Top;//GetImageY( ScreenR.Top );

    return result;
}
TRect	 __fastcall  		TPhCustomImage::GetScreenRect(TRect ImageR)
{
   TRect ScreenR = TRect(-1, -1, -1, -1);

    int dx = 0;
    int dy = 0;
    if ( GetWidthToDisplay() < Width )
        dx = (Width - GetWidthToDisplay()) / 2;

    if ( GetHeightToDisplay() < Height )
        dy = (Height - GetHeightToDisplay()) / 2;

    if ( !Empty )
    {
        ScreenR.Left   = (ImageR.Left - Corner.x)*FScale + dx;
        ScreenR.Right  = (ImageR.Right - Corner.x)*FScale + dx;//FStartPoint.x + FScale*ImageR.Right;//GetImageX( ScreenR.Right );
        ScreenR.Top    = (ImageR.Top - Corner.y)*FScale + dy;//FStartPoint.y + FScale*ImageR.Top;//GetImageY( ScreenR.Top );
        ScreenR.Bottom = (ImageR.Bottom - Corner.y)*FScale + dy;//GetImageY( ScreenR.Bottom );
    }
    return ScreenR;
}

 /*  ----------------------------------------------------------
    Function:   TFCustomImage::GetVisibleArea()
    Purpose:    Вычисляет видимую область изображения
    Comments:
*/
TRect __fastcall TPhCustomImage::GetVisibleArea() const
{
    TRect area;

    if ( FBitmap->Height * FScale > Height )
        area.Top = FBitmap->Height - Height/FScale - FStartPoint.y;
    else
        area.Top = 0;
    area.Bottom = area.Top + GetHeightToDisplay() / FScale;
    if (FBitmap->Width * FScale > Width)
        area.left = FBitmap->Width - Width/FScale - FStartPoint.x;
    else
        area.left = 0;
    area.Right  = area.Left + GetWidthToDisplay() / FScale;

    return area;
}

/* ---------------------------------------------------------------------------
    Function:
    Purpose:
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::SetBorderStyle(TFBorderStyle Value)
{
  if (FBorderStyle != Value)
  {
    FBorderStyle = Value;
    RecreateWnd();
  };
}
/* ---------------------------------------------------------------------------
    Function:
    Purpose:
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::CreateParams(Controls::TCreateParams &Params)
{
  TCustomControl::CreateParams(Params);
    if (FBorderStyle == bsFSingle)
    {
      if (Ctl3D)
        Params.ExStyle |= WS_EX_CLIENTEDGE;
      else
        Params.Style |=  WS_BORDER;
      Params.WindowClass.style = Params.WindowClass.style & !(CS_HREDRAW | CS_VREDRAW);
    };
}
/*TFCustomImage-------------------------------------------------------------------
    Function: TFCustomImage::LoadFromFile(const AnsiString& FileName)
    Purpose:  Загружает растровые данные из файла. Создает обект типа
              TImportRaster. Генерирует событие BeforeOpen, переводит
              объект в состояние Loading.
    Comments:
---------------------------------------------------------------------------*/
bool  __fastcall TPhCustomImage::LoadFromFile(const char* lpFileName)
{
      awpImage* tmp = NULL;
      AnsiString strExt = ExtractFileExt(lpFileName);
      if (strExt != ".awp" && strExt != ".jpg" && strExt != ".bmp" && strExt != ".ppm" && strExt != ".tga")
      {
          TImportRaster* import = new TImportRaster();
          try
          {
             import->FileName = lpFileName;
             import->Image = this;
             import->Execute();
          }
          catch(...)
          {
                delete import;
                return false;
          }
          delete import;
          return true;
      }
      else
      {
        if (awpLoadImage(lpFileName, &tmp) != AWP_OK)
            return false;
      }

      if (tmp->dwType != AWP_BYTE)
            awpConvert(tmp, AWP_CONVERT_TO_BYTE_WITH_NORM);
      m_modified = false;
      TDIBImage* dib = dynamic_cast<TDIBImage*>(FBitmap);
      dib->SetAWPImage(tmp);
      awpReleaseImage(&tmp);
      return true;
}

/*TFCustomImage--------------------------------------------------------------------
    Function: TFCustomImage::SaveToFile(const AnsiString& FileName)
    Purpose:  Save image to file.
    Comments: Default save image in JPEG format
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::SaveToFile(const AnsiString& FileName)
{
        AnsiString strExt = ExtractFileExt(FileName);
        AnsiString strFileName = FileName;
        if (strExt == "")
        {
            strFileName += ".jpg";
            strExt = ".jpg";
        }

        awpImage* img = NULL;
        TDIBImage* dib = dynamic_cast<TDIBImage*>(FBitmap);
        dib->GetAWPImage(&img);
        if (img)
        {
            strExt = ExtractFileExt(strFileName);
            strExt =strExt.LowerCase();
            if (strExt == ".awp" || strExt == ".jpg")
                awpSaveImage(strFileName.c_str(), img);
            else
            {
                strExt =strExt.UpperCase();
                if (strExt == ".TIF" || strExt == ".TIFF")
                    saveToTiff( strFileName.c_str(), dib );
                if (strExt == ".PNG")
                    saveToPng( strFileName.c_str(), dib );
            }
            awpReleaseImage(&img);
            this->m_modified = false;
            FFileName = strFileName;
            if (FChange)
                FChange(this);
        }
}
/*TFCustomImage--------------------------------------------------------------------
    Function: TFCustomImage::LoadFromClipboard()
    Purpose:  Импортирует изображение из буфера обмена.
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::LoadFromClipboard()
{
   FBitmap->Assign(Clipboard());
   this->m_modified = true;
   FFileName = "";
    if (FChange)
        FChange(this);
   Paint();
}
/*TFCustomImage--------------------------------------------------------------------
    Function: TFCustomImage::SaveToClipBoard()
    Purpose: Записывает изображение в буфер обмена
    Comments:
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::SaveToClipBoard()
{
   if (!Empty)
      Clipboard()->Assign(FBitmap);
}
/*TFCustomImage--------------------------------------------------------------------
    Function:
    Purpose:
    Comments:
---------------------------------------------------------------------------*/
bool __fastcall TPhCustomImage::GetModified()
{
        return this->m_modified;
}
/*TFCustomImage-----------------------------------------------------------------
    Function:  TFCustomImage::GetCorner()
    Purpose:    Смещение центра изображения относительно центра компонента.
    Comments:
---------------------------------------------------------------------------*/
TPoint __fastcall TPhCustomImage::GetCorner() const
{
   TPoint C( -1, -1 );

   if (!Empty)
   {
      C.x = FStartPoint.x;
      if ( FBitmap->Height * FScale > Height )
          C.y = RoundTo( FBitmap->Height - Height/FScale - FStartPoint.y, 0 );
      else
          C.y = 0;
   }

   return C;
}
/*TFCustomImage--------------------------------------------------------------------
    Function:
    Purpose:
    Comments:
---------------------------------------------------------------------------*/
bool __fastcall TPhCustomImage::GetEmpty() const
{
    try
    {
       if (FBitmap != NULL)
           return FBitmap->Empty;
       else
           return true;
    }
    catch (...)
    {
       return true;
    }
}

void __fastcall  TPhCustomImage::SetEmpty(bool value)
{
    if (FBitmap != NULL)
    {
        FBitmap->Assign(NULL);
        Paint();
        this->AFileName = "";
        m_modified = false;
        if (FChange)
	    FChange(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::DlgMessage( TWMGetDlgCode &Message )
{
    Message.Result = DLGC_WANTARROWS;
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    int step = 3;
    if ( Shift.Contains( ssCtrl ) )
    {
        step *= 10;
        if ( Key == 'V' )
            LoadFromClipboard();
        if ( Key == 'C' || Key == VK_INSERT )
            SaveToClipBoard();
    }
    if ( Shift.Contains( ssShift ) )
    {
        if ( Key == VK_INSERT )
            LoadFromClipboard();
    }
    
    switch ( Key )
    {
    case VK_UP:
        MoveBy(0, -step);
        break;

    case VK_DOWN:
        MoveBy(0, step);
        break;

    case VK_LEFT:
        MoveBy(-step, 0);
        break;

    case VK_RIGHT:
        MoveBy(step, 0);
        break;

    case VK_ADD:
        ZoomIn();
        break;

    case VK_SUBTRACT:
        ZoomOut();
        break;

    case VK_MULTIPLY:
        BestFit();
        break;

    case VK_DIVIDE:
        ActualSize();
        break;
    }

}

//---------------------------------------------------------------------------
bool __fastcall TPhCustomImage::DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos)
{
	if (WheelDelta > 0)
    {
    	ZoomIn();
    }
    else
    {
    	ZoomOut();
    }
    return true;
}
bool  __fastcall TPhCustomImage::DoMouseWheelUp(TShiftState Shift, const TPoint &MousePos)
{
   ZoomIn();

   TCustomControl::DoMouseWheelUp(Shift, MousePos);
   return true;
}
//---------------------------------------------------------------------------

bool  __fastcall TPhCustomImage::DoMouseWheelDown(TShiftState Shift, const TPoint &MousePos)
{
   ZoomOut();

   TCustomControl::DoMouseWheelDown(Shift, MousePos);
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::MouseDown(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y)
{
   SetFocus();
   TPhImageTool* t =    GetSelectedTool();
   if (t != NULL)
	t->MouseDown(X,Y, Button);
 //  if (FTool != NULL)
 //       FTool->MouseDown(X,Y, Button);
   TCustomControl::MouseDown(Button, Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::MouseMove( TShiftState Shift, Integer X, Integer Y)
{
//   if (FTool != NULL)
//        FTool->MouseMove(X,Y, Shift);
   TPhImageTool* t =    GetSelectedTool();
   if (t != NULL)
	t->MouseMove(X,Y, Shift);
    TCustomControl::MouseMove(Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::MouseUp(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y)
{
//   if (FTool != NULL)
//        FTool->MouseUp(X,Y, Button);
    TPhImageTool* t =    GetSelectedTool();
   if (t != NULL)
	t->MouseUp(X,Y, Button);
    TCustomControl::MouseUp(Button, Shift,X,Y);
}

//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::SetImage(TGraphic* aBitmap)
{
    TDIBImage* dib = dynamic_cast<TDIBImage*>(FBitmap);
    dib->Assign(aBitmap);
}

TGraphic* __fastcall   TPhCustomImage::GetSelectedBitmap()
{
    return this->FSelectedBitmap;
}
//todo: working with tools
int	 __fastcall TPhCustomImage::GetSelectedIndex()
{
 /*	TThumbSelectTool* tool = dynamic_cast<TThumbSelectTool*>(FTool);
	if (tool != NULL)
		return tool->GetLastSelected();
	else
		return -1; */
}

void __fastcall TPhCustomImage::SetMediaSource(TPhMediaSource* source)
{
        if (source == NULL)
                this->m_pMediaSource->SetDisplay(NULL);

        this->m_pMediaSource = source;
        if (source != NULL)
	        m_pMediaSource->SetDisplay(this);
}

void __fastcall  TPhCustomImage::AddPhTool(TPhImageTool* tool)
{
	if (tool != NULL)
	{
		if (m_ph_tools->IndexOf(tool) < 0)
            m_ph_tools->Add(tool);
	}
}
void __fastcall  TPhCustomImage::RemovePhTool(TPhImageTool* tool)
{
   if (m_ph_tools->IndexOf(tool) > 0)
	m_ph_tools->Remove(tool);
}
void __fastcall   TPhCustomImage::SelectPhTool(TPhImageTool* tool)
{
	int old_selected_tool_index = m_selected_ph_tool;

	if (tool == NULL)
		this->m_selected_ph_tool = 0;
	else if (this->m_ph_tools->IndexOf(tool) >= 0)
		this->m_selected_ph_tool = this->m_ph_tools->IndexOf(tool);
	else
		this->m_selected_ph_tool = 0;

	if (old_selected_tool_index != m_selected_ph_tool)
	{
	   TPhImageTool* t = (TPhImageTool*)this->m_ph_tools->Items[old_selected_tool_index];
	   if (t != NULL)
			t->SetActive(false);
	   t = (TPhImageTool*)this->m_ph_tools->Items[m_selected_ph_tool];
	   if (t != NULL)
			t->SetActive(true);
	}

    if (FToolChange != NULL)
        FToolChange(this);
}

TPhImageTool* __fastcall    TPhCustomImage::GetSelectedTool()
{
	if (m_selected_ph_tool < m_ph_tools->Count)
		return (TPhImageTool*)this->m_ph_tools->Items[m_selected_ph_tool];
	else
		return NULL;
}

void TPhImage::foo()
{}

//------------------------------- Video Source ---------------------------------
TMediaSource::TMediaSource(TPhCustomImage* Display)
{

   m_FrameCount = 0;
   m_pDisplay = Display;
   m_media_type = vsNone;

}
TMediaSource::~TMediaSource()
{
}
/*
bool __fastcall TMediaSource::GetIsInitialized()
{
       return false;
}

bool __fastcall TMediaSource::GetIsPreview()
{
       return false;
}*/

//-------------------------------- Slide Show ----------------------------------
TSlideShow::TSlideShow(TPhCustomImage* Display):TMediaSource(Display)
{
  m_FileNames = NULL;
  m_Timer     = new TTimer(NULL);
  m_LastVideoFrame =0;
  m_Timer->Interval = 500;
  m_Timer->OnTimer = TimerEventHandler;
  m_Timer->Enabled = false;
  m_PausedFrame = 0;
}

TSlideShow::~TSlideShow()
{
  Uninitialize();
  delete m_Timer;
}

void __fastcall TSlideShow::Initialize(TStrings* Names)
{
	if (Names != NULL && Names->Count > 1)
    {
       m_FileNames = new TStringList();
	   m_FileNames->AddStrings(Names);
 //      this->m_pDisplay->m_FileNames->AddStrings(Names);
  //    if (m_pDisplay != NULL)
//      {
 //       m_pDisplay->TotalFrames =  Names->Count;
 //     }

     //m_IsInitialized = true;

      DecodeVideoFrame(0, true);
    }
}

void __fastcall TSlideShow::Uninitialize()
{
  if (m_FileNames != NULL)
  {
     delete m_FileNames;
     m_FileNames = NULL;
  }
 // m_IsInitialized     = false;
}


void __fastcall TSlideShow::TimerEventHandler(TObject *Sender)
{
   if (m_LastVideoFrame >= m_FileNames->Count)
   {
       m_LastVideoFrame = 0;
      // this->IsPaused = true;
      // m_pDisplay->IsPaused = true;
   }
   DecodeVideoFrame(m_LastVideoFrame);
   m_LastVideoFrame++;
}

bool __fastcall TSlideShow::DecodeVideoFrame(int num, bool update_null_time)
{
	if ( m_pDisplay!= NULL )
    {
	   awpImage* pImage = NULL;
	   AnsiString str = m_FileNames->Strings[num];
	   awpLoadImage(str.c_str(), &pImage);
	   m_pDisplay->AFileName = str;
//           if (m_pDisplay->m_NewFrame)
//               m_pDisplay->OnFrame(m_pDisplay, pImage->sSizeX, pImage->sSizeY, 8*pImage->bChannels, (char*)pImage->pPixels);
//	   this->m_pDisplay->Draw(pImage);

	   m_pDisplay->BestFit();
 //	   m_pDisplay->m_CurrentFrame = num;

 //	   m_pDisplay->m_FrameCount++;

       awpReleaseImage(&pImage);
    }
    return true;
}

void __fastcall TSlideShow::SetIsPreview(bool Value)
{
  //  m_IsPreview = Value;
   // m_Timer->Enabled = m_IsPreview;
    m_LastVideoFrame = 0;
}

void __fastcall TSlideShow::SetIsPaused(bool Value)
{
    m_Timer->Enabled = !Value;
   // m_IsPaused = !m_Timer->Enabled;
}
//----------------------------- FFMEG Video ------------------------------------

TFFMPEGVideo::TFFMPEGVideo(TPhCustomImage* Display):TMediaSource(Display)
{
    m_handler = NULL;
    m_Timer     = new TTimer(NULL);
    m_Timer->Enabled = false;
    m_Timer->Interval = 10;
    m_currentFrame  = 0;
    m_Timer->OnTimer =  TimerEventHandler;
  //  m_IsPaused = true;
}
TFFMPEGVideo::~TFFMPEGVideo()
{
  Uninitialize();
  delete m_Timer;
}

//Инициализация объекта
void __fastcall TFFMPEGVideo::Initialize(TStrings* Names)
{
/*    if (m_handler != NULL)
    {
        Uninitialize();
    }

    m_handler =  awpcvConnect(name);
    if (m_handler == NULL)
    {
        ShowMessage("Cannot open " + AnsiString(name));
        return;
    }
    // получим число кадров в файле
    if (m_pDisplay != NULL)
    {
      int num = 0;
	  if (awpcvNumFrames((HCVVIDEO)m_handler, &num) != S_OK)
        return;

      m_pDisplay->TotalFrames =  num;
	  this->m_FrameCount = num;
	  m_IsInitialized = true;
      DecodeVideoFrame(0, true);
    }
 */
}
void __fastcall TFFMPEGVideo::Uninitialize()
{
 /*   if (m_handler)
    {
        awpcvDisconnect((HCVVIDEO)m_handler);
        this->m_IsInitialized = false;
        this->m_Timer->Enabled = false;
    } */
}

void __fastcall TFFMPEGVideo::SetIsPreview(bool Value)
{
 //   m_IsPreview = Value;
//    m_Timer->Enabled = m_IsPreview;
}
void __fastcall TFFMPEGVideo::SetIsPaused(bool Value)
{
//    m_Timer->Enabled = !Value;
   // m_IsPaused = !m_Timer->Enabled;
}

void __fastcall TFFMPEGVideo::TimerEventHandler(TObject *Sender)
{
/*   m_currentFrame++;
    if (m_currentFrame < this->m_FrameCount)
    {
       if (m_currentFrame % this->m_pDisplay->Skip == 0)
        DecodeVideoFrame(m_currentFrame);
    }
    else
    {
        this->m_Timer->Enabled = false;
     //   this->IsPaused = true;
     	m_pDisplay->IsPaused = true;
    }*/
}
bool __fastcall TFFMPEGVideo::DecodeVideoFrame(int num, bool update_null_time)
{
/*    awpImage* img = NULL;
	HRESULT res  = S_OK;
    if (num == this->m_currentFrame)
		res = awpcvQueryImage((HCVVIDEO)m_handler, &img);
    else
		res = awpcvQueryImagePos((HCVVIDEO)m_handler, &img, num);


    if (res == S_OK && img != NULL)
    {
        awpImage* im1 = NULL;
        awpCopyImage(img, &im1);
        awpcvFreeImage(img);
        awpResize(im1, im1->sSizeX / m_pDisplay->Rescale, im1->sSizeY / m_pDisplay->Rescale);
	    if (m_pDisplay->m_NewFrame)
			  m_pDisplay->OnFrame(m_pDisplay, im1->sSizeX, im1->sSizeY, 8*im1->bChannels, (char*)im1->pPixels);

	   if (m_pDisplay->VideoDetector != NULL && m_pDisplay->VideoDetector->Enabled)
	   {
			m_pDisplay->VideoDetector->Frame = im1;


			if (m_pDisplay->VideoDetector->NeedDrawResults)
			{
			  if (!this->IsPaused)
			  {
				this->m_pDisplay->Draw(m_pDisplay->VideoDetector->Frame);
			  }
			   else
			   {

					m_pDisplay->Bitmap->SetAWPImage(m_pDisplay->VideoDetector->Frame);
               }
            }
            else
            {
                if (!this->IsPaused)
                    this->m_pDisplay->Draw(im1);
                else

                    m_pDisplay->Bitmap->SetAWPImage(im1);
            }
       }
       else
       {
            if (!this->IsPaused)
                this->m_pDisplay->Draw(im1);
            else
              m_pDisplay->Bitmap->SetAWPImage(im1);
       }

      if (this->IsPaused)
        m_pDisplay->BestFit();
      m_pDisplay->m_CurrentFrame = num;


      this->m_currentFrame = num;


      awpReleaseImage(&im1);

    }
    */
    return true;
}

TImageTool::TImageTool(TPhCustomImage* aImage)
{
    FImage = aImage;
}
TImageTool::~TImageTool()
{

}

TThumbSelectTool::TThumbSelectTool(TPhCustomImage* aImage, int numThumbs, int tWidth, int tHeight):TImageTool(aImage)
{
	m_numThumbs = numThumbs;
	m_tWidth 	= tWidth;
	m_tHeight 	= tHeight;
	m_down 		= false;
	m_selected  = new bool[numThumbs];
	memset(m_selected, false, numThumbs*sizeof(bool));
	this->m_lastSelected = -1;
}
TThumbSelectTool::~TThumbSelectTool()
{
   if (m_selected)
	delete[] m_selected;
}
void TThumbSelectTool::Draw(TCanvas* Canvas)
{
	if (FImage == NULL)
		return;

	//int image_width =
	int x = FImage->GetImageX(m_x);
	int y = FImage->GetImageY(m_y);

	x /= m_tWidth;
	y /= m_tHeight;

	x*=m_tWidth;
	y*=m_tHeight;

	TRect rect;
	rect.init(x,y,x+m_tWidth,y+m_tHeight);
	TRect rect1 = FImage->GetScreenRect(rect);

	TColor 			oldColor = Canvas->Pen->Color;
	TBrushStyle     oldStyle = Canvas->Brush->Style;
	int 			oldWidth = Canvas->Pen->Width;
	Canvas->Pen->Color = clYellow;
	Canvas->Pen->Width = 3;
	Canvas->Brush->Style = bsClear;

	Canvas->Rectangle(rect1);

	// draw selected
	Canvas->Pen->Color = clRed;
	int w = (int)floor(sqrt((float)m_numThumbs) + 0.5);
	for (int i = 0; i < m_numThumbs; i++)
	{
		if (m_selected[i])
		{
			x = i % w;
			y = i / w;
			x *= m_tWidth;
			y *= m_tHeight;

			rect.init(x,y,x+m_tWidth,y+m_tHeight);
			rect1 = FImage->GetScreenRect(rect);
			Canvas->Rectangle(rect1);
		}
	}

	Canvas->Brush->Style = oldStyle;
	Canvas->Pen->Color = oldColor;
	Canvas->Pen->Width = oldWidth;
}
void TThumbSelectTool::MouseDown(int X, int Y, TMouseButton Button)
{
	if (FImage == NULL)
		return;

//   if (Button == mbLeft)
   {
	 m_down = true;
	 m_x = X;
	 m_y = Y;
   }
}
void TThumbSelectTool::MouseUp(int X, int Y, TMouseButton Button)
{
	if (FImage == NULL)
		return;
	if (m_down)
	{

		m_down = false;
	   //	return;
	}

	//int image_width =
	int x = FImage->GetImageX(X);
	int y = FImage->GetImageY(Y);

	x /= m_tWidth;
	y /= m_tHeight;
	int w = (int)floor(sqrt((float)m_numThumbs) + 0.5);
	int idx = (x+w*y);
	if (idx < m_numThumbs)
	{
		m_selected[idx] = !m_selected[idx];
		this->m_lastSelected = idx;
	}

	FImage->Paint();
}
void TThumbSelectTool::MouseMove(int X, int Y, TShiftState Shift)
{
	if (FImage == NULL)
		return;


	if (m_down)
	  FImage->MoveBy( m_x-X, m_y-Y );

	 m_x = X;
	 m_y = Y;

	FImage->Paint();
}
void TThumbSelectTool::Reset()
{
	if (FImage == NULL)
		return;

	for (int i = 0; i < m_numThumbs; i++)
	{
		m_selected[i] = false;
	}

	FImage->Paint();
}
int TThumbSelectTool::GetLastSelected()
{
	return this->m_lastSelected;
}

void TThumbSelectTool::SelectAll()
{
	if (FImage == NULL)
		return;

	for (int i = 0; i < m_numThumbs; i++)
	{
		m_selected[i] = true;
	}

	FImage->Paint();
}
void TThumbSelectTool::InvertSelection()
{
	if (FImage == NULL)
		return;

	for (int i = 0; i < m_numThumbs; i++)
	{
		m_selected[i] = !m_selected[i];
	}

	FImage->Paint();
}

bool TThumbSelectTool::GetSelected(int index)
{
	if (index < 0 || index > m_numThumbs)
		return false;
	return  m_selected[index];
}

AnsiString TThumbSelectTool::GetName()
{
	return "Thumb";
}

//---------------------------------------------------------------------------
namespace Fimage41
{

	void __fastcall PACKAGE Register    ()
	{
		 TComponentClass classes[1] =
		 {
		 __classid(TPhImage)
		 };
		 RegisterComponents("Photon", classes,
		 (sizeof(classes)/sizeof(TComponentClass))-1);
	}
}
//----------------------------------------------------------------------------
