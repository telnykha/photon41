//---------------------------------------------------------------------------
// FImage.h - TPhImage interface
// version 1.0
// 5 августа 2004 года
// verision 2.0
// version 3.0
// version 4.0
// Alt-Soft.Net (c) 2004-2017
#ifndef FImage41H
#define FImage41H

//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "PhFrames.h"

const int crHandOpenCursor  = 1;
const int crHandCloseCursor = 2;
const int crMagnifyCursor   = 3;
const int crLenzCursor      = 4;
const int crZoom2RectCursor = 5;

typedef enum  {bsFNone, bsFSingle} TFBorderStyle;
typedef enum  {msPriview, msPlayBack, msPaused} 	EMediaState;

// forward declarations
class PACKAGE TPhImageTool;
//TPhCustomImage--------------------------------------------------------------------
//TPhCustomImage extends the TCustomControl component
class PACKAGE TPhCustomImage : public TCustomControl
{
friend class TPhImageTool;
friend class TPhSelRectTool;
friend class TPhFrames;
protected:
    TTimer*                     m_Timer;
	TList*                  	m_ph_tools;
    TPhFrames*                  m_Frames;
	TGraphic*                   FBitmap;
	TGraphic*                   FSelectedBitmap;
	double                      FScale;      // scale coefficient
	TPoint                      FStartPoint; // Левый верхний угол отображаемой области * 100%
	TFBorderStyle               FBorderStyle;
	AnsiString                  FFileName;

	TNotifyEvent                FBeforeOpen;
	TNotifyEvent                FAfterOpen;
	TNotifyEvent                FScaleChange;
	TNotifyEvent                FPosChange;
	TNotifyEvent                FChange;
	TNotifyEvent            	FToolChange;
	// selectoin
	TRect			FSelRect;
	void 			DrawSelRect(Graphics::TBitmap *bm);
	// thumbs support
	int                         FSelCols;
	int                         FSelRows;
	int				m_tWidth;
	int				m_tHeight;
	// image was modified
	bool                        m_modified;
	int				 __fastcall GetSelectedIndex();
    void __fastcall         TimerEventHandler(TObject *Sender);
protected:
	void         __fastcall     SetImage(TGraphic* aBitmap);


	// Painting
	int                         GetWidthToDisplay() const;
	int                         GetHeightToDisplay() const;
	// File system
	bool __fastcall             LoadFromFile(const char* lpFileName);
	// window
	void __fastcall             SetBorderStyle(TFBorderStyle Value);
	virtual void __fastcall     CreateParams(Controls::TCreateParams &Params);
	DYNAMIC void __fastcall     Resize(void);

	bool __fastcall             GetModified();
	bool __fastcall             GetEmpty() const;
	void __fastcall             SetEmpty(bool value);
	TPoint __fastcall           GetCorner() const;
	float __fastcall            GetScale() const;
	TRect __fastcall            GetVisibleArea() const;
	TRect __fastcall            GetInternalVisibleArea();

	void  __fastcall            SetSelCols(int num);
	void  __fastcall            SetSelRows(int num);

    bool __fastcall GetSlideShow();
    void __fastcall SetSlideShow(bool Value);

	// Mouse
	DYNAMIC void __fastcall     MouseDown(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseMove( TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseUp(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);

	DYNAMIC bool  __fastcall    DoMouseWheelUp(System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos);
	DYNAMIC bool  __fastcall    DoMouseWheelDown(TShiftState Shift, const TPoint &MousePos);
	DYNAMIC bool __fastcall 	DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos);

	// Keyboard
	DYNAMIC void __fastcall     KeyDown(Word &Key, Classes::TShiftState Shift);
	void __fastcall             DlgMessage(TWMGetDlgCode &Message);

	// ph_tools
	int                			m_selected_ph_tool;
	void __fastcall         	AddPhTool(TPhImageTool* tool);
	void __fastcall             RemovePhTool(TPhImageTool* tool);
	TPhImageTool* __fastcall    GetSelectedTool();
	 TGraphic* __fastcall   GetSelectedBitmap();
public:

	__fastcall                  TPhCustomImage(TComponent* Owner);
	__fastcall virtual          ~TPhCustomImage();

	// ====================operations========================================
	virtual bool __fastcall         Init(TStrings* Names);
	// Close
	virtual void __fastcall             Close();
	void __fastcall             	SaveToFile(const AnsiString& FileName);

	// Clipboard
	void __fastcall            		LoadFromClipboard();
	void __fastcall             	SaveToClipBoard();


	virtual void __fastcall     Paint(void);
	// Raster data commands positioning
	void __fastcall         	BestFit   ();
	void __fastcall         	FitWidth  ();
	void __fastcall         	FitHeight ();

	// Data scale
	void __fastcall             ActualSize();
	void __fastcall             ZoomIn();
	void __fastcall             ZoomOut();
	void __fastcall         	ZoomToRect(const TRect Rect);
	void __fastcall             ZoomTo(int ZoomFactor);

	// pane commands
	void __fastcall             MoveToCenter();
	void __fastcall             MoveToLeftTop();
	void __fastcall         	MoveToRightBottom();
	void __fastcall             MoveTo(int X, int Y);
	void __fastcall             MoveBy(int dX, int dY);
	// ROI commends
	void __fastcall 			ClearSelection();
	bool __fastcall				HasSelection();
	TRect		       			GetSelRect();
	void                        SetSelRect(TRect r);
	// Coordinate systems
	int __fastcall              GetImageX(int ScreenX);
	int __fastcall              GetImageY(int ScreenY);
	TRect    __fastcall         GetImageRect(TRect ScreenR);
	TRect    __fastcall    		GetScreenRect(TRect ImageR);
	TPoint   __fastcall         GetScreenPoint(int x, int y);

	//tools
	void __fastcall             SelectPhTool(TPhImageTool* tool);

	// Public properties
	__property  AnsiString      AFileName = {read = FFileName, write = FFileName};
    __property  TPhFrames*      Frames = {read = m_Frames};
	__property  TGraphic*       Bitmap = {read = FBitmap, write = SetImage};
	__property  TGraphic*       SelectedBitmap = {read = GetSelectedBitmap};
	__property  int             SelCols = {read = FSelCols, write = SetSelCols};
	__property  int             SelRows = {read = FSelRows, write = SetSelRows};
	__property  bool            Modified = {read = GetModified};
	__property  bool            Empty = {read = GetEmpty, write = SetEmpty};
    __property  bool            SlideShow = {read = GetSlideShow, write = SetSlideShow};

	__property float            Scale = {read = GetScale};
	__property TPoint           Corner = {read = GetCorner};
	__property TRect            VisibleArea = {read = GetVisibleArea};
 //  __property  int ObjectsCount = {read = m_Count, write = m_Count};
   // inherited properties
   __property Canvas;
	__property TPhImageTool*   PhTool = {read = GetSelectedTool};
__published:
   //
	__property TFBorderStyle     BorderStyle = {read = FBorderStyle, write = SetBorderStyle};
	__property int ThumbWidht      	   = {read  = m_tWidth,  write = m_tWidth};
	__property int ThumbHeight     	   = {read = m_tHeight, write = m_tHeight};


   // наследуемые свойства
	__property Align;
	__property Anchors;
	__property Color;
	__property ParentColor;
	__property Ctl3D;
	__property Enabled;
	__property ParentCtl3D;
	__property ParentShowHint;
	__property PopupMenu;
	__property ShowHint;
	__property Visible;

	// наследуемые события
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
    __property OnMouseWheel;
    __property OnResize;

    // собственные события
    __property TNotifyEvent     BeforeOpen = {read = FBeforeOpen, write = FBeforeOpen};
    __property TNotifyEvent     AfterOpen  = {read = FAfterOpen, write = FAfterOpen};
    __property TNotifyEvent     OnScaleChange = {read = FScaleChange, write = FScaleChange};
    __property TNotifyEvent     OnPane = {read = FPosChange, write = FPosChange};
    __property TNotifyEvent     OnChange = {read = FChange, write = FChange};
    __property TNotifyEvent     OnToolChange = {read = FToolChange, write = FToolChange};
};
//-------------------------- export TPhImage -------------------------------------
class PACKAGE TPhImage : public TPhCustomImage
{
__published:
	__property TFBorderStyle     BorderStyle = {read = FBorderStyle, write = SetBorderStyle};
};

// abstract image tool
class PACKAGE TImageTool
{
friend class TPhCustomImage;
protected:
	TPhCustomImage* FImage;
public:
	TImageTool(TPhCustomImage* aImage);
	virtual ~TImageTool();
	// methods
	virtual void Draw(TCanvas* Canvas) = 0;
	virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft) = 0;
	virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft)   = 0;
	virtual void MouseMove(int X, int Y, TShiftState Shift) = 0;
	virtual void Reset() = 0;
	virtual AnsiString GetName() = 0;
};

class PACKAGE TThumbSelectTool : public TImageTool
{
protected:
	 int m_numThumbs;
	 int m_tWidth;
	 int m_tHeight;
	 int m_x;
	 int m_y;
     bool  m_down;
	 bool* m_selected;
	 int m_lastSelected;

	 bool GetSelected(int index);
public:
	TThumbSelectTool(TPhCustomImage* aImage,  int numThumbs, int tWidth, int tHeight);
	virtual ~TThumbSelectTool();

	virtual void Draw(TCanvas* Canvas);
	virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
	virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
	virtual void MouseMove(int X, int Y, TShiftState Shift);
	virtual void Reset();

	int GetLastSelected();
	void SelectAll();
	void InvertSelection();

	__property int NumItems = {read = m_numThumbs};
	__property bool IsSelected [int index] = {read = GetSelected};
        virtual AnsiString GetName();
};
#endif
