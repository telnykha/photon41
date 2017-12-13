//---------------------------------------------------------------------------
#include <vcl.h>
#include <Clipbrd.hpp>
#include <math.hpp>
#include "FImage41.h"
#include "DIBImage41.h"
#include "ExportRaster.h"
#include "PhImageTool.h"
#pragma hdrstop
#pragma package(smart_init)

#define MAX_ZOOM 10.0f
#define MIN_ZOOM 0.01f
#define ZOOM_STEP 0.1f

extern "C"
{
    #pragma link "awpipl2b.lib"
    #pragma link "JPEGLIB.lib"
    #pragma link "libpng.lib"
    #pragma link "tifflib.lib"
    #pragma link "zlib.lib"
}

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
//static inline void ValidCtrCheck(TPhCustomImage *)
//{
 //   new TPhCustomImage(NULL);
//}
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

	m_modified = false;
	m_ph_tools = new TList();
    m_selected_ph_tool = 0;

    this->m_Frames = new TPhFrames(this);
    this->m_Timer = new TTimer(this);
    this->m_Timer->Enabled = false;
    this->m_Timer->OnTimer = TimerEventHandler;
    this->m_Timer->Interval = 500;
    m_tWidth = 128;
    m_tHeight = 128;
    m_mosaic = false;
}
__fastcall TPhCustomImage::TPhCustomImage(HWND Parent):TCustomControl(Parent)
{

}
/* ---------------------------------------------------------------------------
	Function:  destructor of the  TFCustomImage
	Purpose:   if we have raster data abs other objects delete them
	Comments:
---------------------------------------------------------------------------*/
__fastcall TPhCustomImage::~TPhCustomImage()
{
	Close();
    delete this->m_Frames;
    delete this->m_Timer;
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

    // todo: check number of files in the source list
    // open list with limit 4096 files

    AnsiString FileName;
    Close();
    return this->m_Frames->Init(Names);
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
   m_Timer->Enabled = false;
   m_Frames->Close();
   m_mosaic = false;
}

bool __fastcall TPhCustomImage::GetSlideShow()
{
    return this->m_Timer->Enabled;
}

void __fastcall TPhCustomImage::SetSlideShow(bool Value)
{
    if (m_Timer->Enabled == Value)
        return;

    if (!Value)
    {
        this->m_Timer->Enabled = false;
        return;
    }

    if (Value && this->m_Frames->Count > 1)
        this->m_Timer->Enabled = true;
}

unsigned int __fastcall TPhCustomImage::GetSlideShowInterval()
{
    return this->m_Timer->Interval;
}
void __fastcall TPhCustomImage::SetSlideShowInterval(unsigned int Value)
{
    this->m_Timer->Interval = Value;
}
bool __fastcall TPhCustomImage::GetMosaic()
{
   return this->m_mosaic;
}
void __fastcall TPhCustomImage::SetMosaic(bool Value)
{
    if (this->FBitmap->Empty)
        return;

    if (Value == m_mosaic)
        return;
    if (Value && this->m_Timer->Enabled)
    {
        this->m_Timer->Enabled = false;
    }

    if (Value)
    {
       this->FBitmap->Assign(this->m_Frames->Mosaic);
       this->BestFit();
       m_mosaic = true;
    }
    else
    {
        m_Frames->Frame(m_Frames->CurrentFrame);
        m_mosaic = false;
    }

      if (FChange)
          FChange(this);
}


void __fastcall   TPhCustomImage::TimerEventHandler(TObject *Sender)
{
    this->m_Frames->Next();
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
   bm->Canvas->Pen->Width = 4;
   bm->Canvas->Pen->Color = clRed;
   bm->Canvas->Pen->Mode = pmCopy;

   bm->Canvas->MoveTo(FSelRect1.Left, FSelRect1.Top);
   bm->Canvas->LineTo(FSelRect1.Right, FSelRect1.Top);
   bm->Canvas->LineTo(FSelRect1.Right, FSelRect1.Bottom);
   bm->Canvas->LineTo(FSelRect1.Left, FSelRect1.Bottom);
   bm->Canvas->LineTo(FSelRect1.Left, FSelRect1.Top);

   bm->Canvas->Pen->Style = style;
   bm->Canvas->Pen->Color = color;
   bm->Canvas->Pen->Mode = mode;
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
        DrawSelectedItems(bm, m_xx, m_yy);
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
/*TFCustomImage-------------------------------------------------------------------
    Function: TFCustomImage::LoadFromFile(const AnsiString& FileName)
    Purpose:  Загружает растровые данные из файла. Создает обект типа
              TImportRaster. Генерирует событие BeforeOpen, переводит
              объект в состояние Loading.
    Comments:
---------------------------------------------------------------------------*/
bool  __fastcall TPhCustomImage::LoadFromFile(const char* lpFileName)
{

      if (FBeforeOpen)
         FBeforeOpen(this);
      try
      {
	      FBitmap->LoadFromFile(lpFileName);
      }
      catch(Exception& e)
      {
        ShowMessage(e.Message);
      }

      // setup filename
      FFileName = lpFileName;

      if (FAfterOpen)
          FAfterOpen(this);
      if (FChange)
          FChange(this);

      return true;
}

/*TFCustomImage--------------------------------------------------------------------
    Function: TFCustomImage::SaveToFile(const AnsiString& FileName)
    Purpose:  Save image to file.
    Comments: Default save image in JPEG format
---------------------------------------------------------------------------*/
void __fastcall TPhCustomImage::SaveToFile(const LPWSTR lpwFileName)
{
        UnicodeString FileName = lpwFileName;
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
        if (img != NULL)
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
   {
      if (this->HasSelection())
          Clipboard()->Assign(this->SelectedBitmap);
      else
	      Clipboard()->Assign(FBitmap);
   }
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
void __fastcall 	TPhCustomImage::DblClick(void)
{

   if (GetKeyState(VK_LSHIFT) < 0)
   {
       if (Mosaic && this->m_idx >= 0 && this->m_idx < this->Frames->Count)
       {
            this->m_mosaic = false;
            Frames->Frame(m_idx);
       }
       else
            Mosaic = true;
   }

  TCustomControl::DblClick();
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
   TCustomControl::MouseDown(Button, Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::MouseMove( TShiftState Shift, Integer X, Integer Y)
{
    if (this->Mosaic && Shift.Contains(ssShift))
    {
        // call mosaic helper
        int x = GetImageX(X);
        int y = GetImageY(Y);
        if (x >= 0 && x < FBitmap->Width && y >= 0 && y < FBitmap->Height)
        {
            x /= m_tWidth;
            y /= m_tHeight;
            int w = (int)floor(sqrt((float)this->Frames->Count) + 0.5);
            int idx = (x+w*y);
            if (idx != m_idx && idx < Frames->Count)
            {
                m_xx = X;
                m_yy = Y;
                m_idx = idx;
                Paint();
            }
        }
    }

   TPhImageTool* t =    GetSelectedTool();
   if (t != NULL)
    t->MouseMove(X,Y, Shift);

    TCustomControl::MouseMove(Shift,X,Y);
}
//---------------------------------------------------------------------------
void __fastcall TPhCustomImage::MouseUp(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y)
{

    if (this->Mosaic && Shift.Contains(ssShift))
    {
        // call mosaic helper
        int x = GetImageX(X);
        int y = GetImageY(Y);
        if (x >= 0 && x < FBitmap->Width && y >= 0 && y < FBitmap->Height)
        {
            x /= m_tWidth;
            y /= m_tHeight;
            int w = (int)floor(sqrt((float)this->Frames->Count) + 0.5);
            int idx = (x+w*y);
            if (idx < Frames->Count)
            {
                SFrameItem* item = Frames->GetFrameItem(idx);
                if (item != NULL)
                {
                    item->selected = !item->selected;
                    Paint();
                }
            }
        }
    }


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
    if (FChange)
      FChange(this);
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

void            __fastcall TPhCustomImage::DrawSelectedItems(Graphics::TBitmap* bm, int xx, int yy)
{
    if (!Mosaic)
        return;

	int x = GetImageX(xx);
	int y = GetImageY(yy);

	x /= m_tWidth;
	y /= m_tHeight;

	x*=m_tWidth;
	y*=m_tHeight;

	TRect rect;
	rect.init(x,y,x+m_tWidth,y+m_tHeight);
	TRect rect1 = GetScreenRect(rect);
    TCanvas* cnv = bm->Canvas;
	TColor 			oldColor = cnv->Pen->Color;
	TBrushStyle     oldStyle = cnv->Brush->Style;
	int 			oldWidth = cnv->Pen->Width;
	cnv->Pen->Color = clYellow;
	cnv->Pen->Width = 3;
 	cnv->Brush->Style = bsClear;

	cnv->Rectangle(rect1);

	// draw selected
  	cnv->Pen->Width = 8;
	cnv->Pen->Color = clGreen;
  	int w = (int)floor(sqrt((float)Frames->Count) + 0.5);
	for (int i = 0; i < Frames->Count; i++)
	{
		SFrameItem* item = Frames->GetFrameItem(i);

		if (item->selected)
		{
			x = i % w;
			y = i / w;
			x *= m_tWidth;
			y *= m_tHeight;

			rect.init(x,y,x+m_tWidth,y+m_tHeight);
			rect1 = GetScreenRect(rect);
   			cnv->Pen->Width = 8;
            cnv->Ellipse(rect1);
            rect1.Inflate(-15, -15);
			cnv->Pen->Width = 4;
            cnv->Ellipse(rect1);
            rect1.Inflate(-15, -15);
			cnv->Pen->Width = 2;
            cnv->Ellipse(rect1);
 //			cnv->Rectangle(rect1);
		}
	}

	cnv->Brush->Style = oldStyle;
	cnv->Pen->Color = oldColor;
	cnv->Pen->Width = oldWidth;
}

void __fastcall TPhCustomImage::DoDeleteImage()
{
    if (Frames->Count > 1)
    {
        Frames->DeleteImage(Frames->CurrentFrame);
        Frames->Next();
    }
    else
    {
        DeleteFile(AFileName);
        Close();
    }
}

void __fastcall TPhCustomImage::Delete()
{
    SlideShow = false;
    if (Mosaic)
        Frames->DeleteSelected();
    else
        DoDeleteImage();
}

void __fastcall     TPhCustomImage::Copy(const LPWSTR lpwFolderName)
{
    SlideShow = false;
    UnicodeString FolderName = lpwFolderName;
    if (DirectoryExists(FolderName))
    {
        if (Frames->Count > 1)
        {
            if (!Frames->CopySelected(lpwFolderName))
                ShowMessage(L"Cannot copy files to target folder: " + FolderName);
        }
        else
        {
            AnsiString strSrcFile = this->AFileName;
            AnsiString strDstFile = lpwFolderName;
            strDstFile += ExtractFileName(strSrcFile);
            if (!CopyFile(strSrcFile.c_str(), strDstFile.c_str(), false))
            {
                ShowMessage(L"Cannot copy files to target folder: " + FolderName);
            }
        }
    }
    else
        ShowMessage(L"Target folder does not exists.");
}
void __fastcall     TPhCustomImage::Move(const LPWSTR lpwFolderName)
{
    SlideShow = false;
    UnicodeString FolderName = lpwFolderName;
    if (DirectoryExists(FolderName))
    {
        if (Frames->Count > 1)
        {
            if (!Frames->MoveSelected(lpwFolderName))
                ShowMessage(L"Cannot move files to target folder: " + FolderName);
        }
        else
        {
            AnsiString strSrcFile = this->AFileName;
            AnsiString strDstFile = lpwFolderName;
            strDstFile += ExtractFileName(strSrcFile);
            if (!CopyFile(strSrcFile.c_str(), strDstFile.c_str(), false))
            {
                ShowMessage(L"Cannot copy files to target folder: " + FolderName);
            }
            DeleteFile(strSrcFile);
            Close();
        }
    }
    else
        ShowMessage(L"Target folder does not exists.");
}

//=============================================================================
__fastcall TPhImage::TPhImage(HWND Parent):TPhCustomImage(Parent)
{

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
