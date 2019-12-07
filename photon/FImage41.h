//---------------------------------------------------------------------------
// FImage.h - TPhImage interface
// version 1.0
// 5 ������� 2004 ����
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
const int crHandOpenCursor  = 1;
const int crHandCloseCursor = 2;
const int crMagnifyCursor   = 3;
const int crLenzCursor      = 4;
const int crZoom2RectCursor = 5;

#include "PhFrames.h"

#include "awpipl.h"

typedef enum {readJob, copyJob, moveJob, deleteJob, convertJob, processJob} EPhJobReason;
typedef void __fastcall (__closure *TPhProgressEvent)(System::TObject* Sender, UnicodeString& strMessage, int Progress);
typedef void __fastcall (__closure *TPhJobEvent) (System::TObject* Sender, EPhJobReason reason, bool Cancel);
typedef void __fastcall (__closure *TPhFrameEvent)(System::TObject* Sender, TGraphic* data);
typedef void __fastcall (__closure *TPhFrameDataEvent)(System::TObject* Sender, int w, int h, int c, BYTE* data);

// forward declarations
class PACKAGE TPhImageTool;
//TPhCustomImage--------------------------------------------------------------------
//TPhCustomImage extends the TCustomControl component
class PACKAGE TPhCustomImage : public TCustomControl
{
friend class TPhImageTool;
friend class TPhSelRectTool;
friend class TPhFrames;
private:
	TNotifyEvent                FBeforeOpen;
	TNotifyEvent                FAfterOpen;
	TNotifyEvent                FScaleChange;
	TNotifyEvent                FPosChange;
	TNotifyEvent                FChange;
    TNotifyEvent                FMosaic;
	TNotifyEvent            	FToolChange;
    TPhProgressEvent  			m_OnProgress;
    TNotifyEvent       			m_OnStart;
    TPhJobEvent		       		m_OnFinish;
	TNotifyEvent       			m_OnCancel;
    TPhFrameEvent               m_OnFrame;
    TPhFrameDataEvent           m_OnFrameData;
protected:
    TTimer*                     m_Timer;
	TList*                  	m_ph_tools;
    TPhFrames*                  m_Frames;
	TGraphic*                   FBitmap;
	TGraphic*                   FSelectedBitmap;
	double                      FScale;      // scale coefficient
	TPoint                      FStartPoint; // ����� ������� ���� ������������ ������� * 100%
	AnsiString                  FFileName;

    int                         m_xx;
    int                         m_yy;
    int                         m_idx;
	// selectoin
	TRect			FSelRect;
	void 			DrawSelRect(Graphics::TBitmap *bm);
    void            __fastcall DrawSelectedItems(Graphics::TBitmap* bm, int xx, int yy);
	// thumbs support
	int				m_tWidth;
	int				m_tHeight;
	// image was modified
	bool                        m_modified;

    bool                        m_mosaic;
	int				 __fastcall GetSelectedIndex();
	void __fastcall         	TimerEventHandler(TObject *Sender);
protected:
	void         __fastcall     SetImage(TGraphic* aBitmap);


	// Painting
	int                         GetWidthToDisplay() const;
	int                         GetHeightToDisplay() const;
	// File system
	bool __fastcall             LoadFromFile(const char* lpFileName);
	// window
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

    bool __fastcall 			GetSlideShow();
    void __fastcall 			SetSlideShow(bool Value);

    bool __fastcall 			GetMosaic();
    void __fastcall 			SetMosaic(bool Value);

    void __fastcall             SetMosaicSelected(int value);


    unsigned int __fastcall 	GetSlideShowInterval();
    void __fastcall 			SetSlideShowInterval(unsigned int Value);


	// Mouse
	DYNAMIC void __fastcall     MouseDown(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseMove( TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseUp(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);
    DYNAMIC void __fastcall 	DblClick(void);

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
    TGraphic* __fastcall   		GetSelectedBitmap();

    void __fastcall DoDeleteImage();
public:
	__fastcall                  TPhCustomImage(TComponent* Owner);
	__fastcall                  TPhCustomImage(HWND Parent);
	__fastcall virtual          ~TPhCustomImage();

	// ====================operations========================================
	virtual bool __fastcall         Init(TStrings* Names);
    void __fastcall Cancel();
	// Close
	virtual void __fastcall         Close();
	void __fastcall             	SaveToFile(const LPWSTR lpwFileName);

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
	TPoint   __fastcall         GetImagePoint(int x, int y);

	//tools
	void __fastcall             SelectPhTool(TPhImageTool* tool);

    //image operations
    void __fastcall 			Delete();
    void __fastcall             Copy(const LPWSTR lpwFolderName);
    void __fastcall             Move(const LPWSTR lpwFolderName);

    void __fastcall             SetImageData(int w, int h, int c, unsigned char* data);

    bool __fastcall             GetAwpImage(awpImage** img);
    bool __fastcall             SetAwpImage(awpImage* img);

    bool __fastcall             GetSelectedImage(awpImage** img);

	// Public properties
	__property  AnsiString      AFileName = {read = FFileName, write = FFileName};
    __property  TPhFrames*      Frames = {read = m_Frames};
	__property  TGraphic*       Bitmap = {read = FBitmap, write = SetImage};
	__property  TGraphic*       SelectedBitmap = {read = GetSelectedBitmap};

	__property  bool            Modified = {read = GetModified};
	__property  bool            Empty = {read = GetEmpty, write = SetEmpty};
    __property  bool            SlideShow = {read = GetSlideShow, write = SetSlideShow};
    __property  bool            Mosaic = {read = GetMosaic, write = SetMosaic};

	__property float            Scale = {read = GetScale};
	__property TPoint           Corner = {read = GetCorner};
	__property TRect            VisibleArea = {read = GetVisibleArea};
    __property int              MosaicSelected = {read = m_idx, write = SetMosaicSelected};
   // inherited properties
   __property Canvas;
	__property TPhImageTool*   PhTool = {read = GetSelectedTool};
__published:
   //
	__property int ThumbWidht      	   = {read  = m_tWidth,  write = m_tWidth};
	__property int ThumbHeight     	   = {read = m_tHeight, write = m_tHeight};
    __property  unsigned  SlideShowInterval = {read = GetSlideShowInterval, write = SetSlideShowInterval};

   // ����������� ��������
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

	// ����������� �������
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

    // ����������� �������
    __property TNotifyEvent     BeforeOpen = {read = FBeforeOpen, write = FBeforeOpen};
    __property TNotifyEvent     AfterOpen  = {read = FAfterOpen, write = FAfterOpen};
    __property TNotifyEvent     OnScaleChange = {read = FScaleChange, write = FScaleChange};
    __property TNotifyEvent     OnPane = {read = FPosChange, write = FPosChange};
    __property TNotifyEvent     OnChange = {read = FChange, write = FChange};
    __property TNotifyEvent     OnMosaic = {read = FMosaic, write = FMosaic};
    __property TNotifyEvent     OnToolChange = {read = FToolChange, write = FToolChange};
    __property TPhProgressEvent OnProgress = {read = m_OnProgress, write = m_OnProgress};
	__property TNotifyEvent 	OnStart = {read = m_OnStart, write = m_OnStart};
	__property TPhJobEvent	 	OnFinish = {read = m_OnFinish, write = m_OnFinish};
	__property TNotifyEvent 	OnCancel = {read = m_OnCancel, write = m_OnCancel};
    __property TPhFrameEvent    OnFrame  = {read = m_OnFrame, write = m_OnFrame};
    __property TPhFrameDataEvent OnFrameData = {read = m_OnFrameData, write = m_OnFrameData};
};
//-------------------------- export TPhImage -------------------------------------
class PACKAGE TPhImage : public TPhCustomImage
{
public:
    __fastcall TPhImage(HWND Parent);
__published:
};
#endif
