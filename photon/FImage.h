//---------------------------------------------------------------------------
// FImage.h - TPhImage interface
// version 1.0
// 5 ������� 2004 ����
// verision 2.0
// version 3.0
// version 4.0
// Alt-Soft.Net (c) 2004-2017
#ifndef FImageH
#define FImageH

//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <vfw.h>
#include <ExtCtrls.hpp>

const int crHandOpenCursor  = 1;
const int crHandCloseCursor = 2;
const int crMagnifyCursor   = 3;
const int crLenzCursor      = 4;
const int crZoom2RectCursor = 5;

typedef void __fastcall (__closure *TVideoFormatEvent)(System::TObject* Sender, int aWidth, int aHeight);
typedef void __fastcall (__closure *TFrameEvent)(System::TObject* Sender, int widht, int height, int bpp, char* data);

typedef enum  {bsFNone, bsFSingle} TFBorderStyle;
typedef enum  {vsNone, vsImage, vsSlideShow, vsVideo} EMediaSource;
typedef enum  {ftNone, ftPane,  ftZoomToRect, ftLenz, ftSelRect, ftSelPixel, ftThumbSelect} TFTools;

// forward declarations
class PACKAGE TImageTool;
class PACKAGE TMediaSource;

//TFCustomImage--------------------------------------------------------------------
//TFCostomImage extends the TCustomControl component
class PACKAGE TFCustomImage : public TCustomControl
{
friend class TSelRectTool;
protected:

    TGraphic*                   FBitmap;
    double                      FScale;      // scale coefficient
    TPoint                      FStartPoint; // ����� ������� ���� ������������ ������� * 100%
    TFBorderStyle               FBorderStyle;
    AnsiString                  FFileName;
    bool                        FLocalTool;

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
    int				m_Count;
    // image was modified
    bool                        m_modified;
    int				 __fastcall GetSelectedIndex();
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

    // Image tools
    TFTools                 	FCurrentTool;
    TImageTool*             	FTool;
    void __fastcall  	    	SetCurrentTool(TFTools Value);
    void __fastcall         	SetImageTool(TImageTool* pTool);

    // Media source
    // todo:
    TMediaSource*               m_pMediaSource;
    // Close
    virtual void __fastcall             Close();

public:

    __fastcall                  TFCustomImage(TComponent* Owner);
    __fastcall virtual          ~TFCustomImage();

    // ====================operations========================================
    virtual bool __fastcall             Init(TStrings* Names);
    void __fastcall             	SaveToFile(const AnsiString& FileName);

    // Clipboard
    void __fastcall             LoadFromClipboard();
    void __fastcall             SaveToClipBoard();

    virtual void __fastcall     Paint(void);
    // Raster data commands positioning
    void __fastcall         BestFit   ();
    void __fastcall         FitWidth  ();
    void __fastcall         FitHeight ();

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
    void __fastcall 		ClearSelection();
    bool __fastcall		HasSelection();
    TRect		       	GetSelRect();
    void                        SetSelRect(TRect r);
    // Coordinate systems
    int __fastcall              GetImageX(int ScreenX);
    int __fastcall              GetImageY(int ScreenY);
    TRect    __fastcall         GetImageRect(TRect ScreenR);
    TRect    __fastcall    	GetScreenRect(TRect ImageR);
    TPoint   __fastcall         GetScreenPoint(int x, int y);
    // Public properties
    __property  TImageTool*     Tool = {read = FTool, write = SetImageTool};
    __property  AnsiString      AFileName = {read = FFileName, write = FFileName};
    __property  TGraphic*       Bitmap = {read = FBitmap, write = SetImage};
    __property  int             SelCols = {read = FSelCols, write = SetSelCols};
    __property  int             SelRows = {read = FSelRows, write = SetSelRows};
    __property  bool            Modified = {read = GetModified};
    __property  bool            Empty = {read = GetEmpty, write = SetEmpty};

    __property float            Scale = {read = GetScale};
    __property TPoint           Corner = {read = GetCorner};
    __property TRect            VisibleArea = {read = GetVisibleArea};
   __property  int ObjectsCount = {read = m_Count, write = m_Count};
   // inherited properties
   __property Canvas;
__published:
   //
    __property TFBorderStyle     BorderStyle = {read = FBorderStyle, write = SetBorderStyle};
    __property TFTools CurrentTool = {read = FCurrentTool, write = SetCurrentTool};
    __property int ThumbWidht      = {read  = m_tWidth,  write = m_tWidth};
    __property int ThumbHeight     = {read = m_tHeight, write = m_tHeight};

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
    __property TNotifyEvent     OnToolChange = {read = FToolChange, write = FToolChange};
};
//-------------------------- export TPhImage -------------------------------------
class PACKAGE TPhImage : public TFCustomImage
{
	virtual void foo();
__published:
    __property TFBorderStyle     BorderStyle = {read = FBorderStyle, write = SetBorderStyle};
};
// abstract image tool
class PACKAGE TImageTool
{
friend class TFCustomImage;
protected:
	TFCustomImage* FImage;
public:
	TImageTool(TFCustomImage* aImage);
	virtual ~TImageTool();
	// methods
	virtual void Draw(TCanvas* Canvas) = 0;
	virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft) = 0;
	virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft)   = 0;
	virtual void MouseMove(int X, int Y, TShiftState Shift) = 0;
	virtual void Reset() = 0;
        virtual AnsiString GetName() = 0;
};
// Zoom/pane tool
class PACKAGE TPaneTool : public TImageTool
{
private:
	int mX;
	int mY;
	bool Pressed;
public:
	TPaneTool(TFCustomImage* aImage);
	virtual void Draw(TCanvas* Canvas);
	virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
    virtual void Reset();
    virtual AnsiString GetName();

};
// zoom to rect tool
class PACKAGE TZoomToRectTool : public TImageTool
{
private:
    TRect SelRect;
    void DrawSelRect();
    bool Pressed;
public:
    TZoomToRectTool(TFCustomImage* aImage);
    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
    virtual void Reset();
    virtual AnsiString GetName();
};
// lenz tool
class PACKAGE TLenzTool : public TImageTool
{
private:
    TFCustomImage       *FImage;
    float               Zoom;
    int                 LenzSize;
    bool                Applied;
    HDRAWDIB            FDrawHandle;
    void                ApplyLenz(int X, int Y);

public:
    TLenzTool(TFCustomImage* aImage);
    ~TLenzTool();

    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
	virtual void Reset();
    virtual AnsiString GetName();
};
// select rect tool
class PACKAGE TSelRectTool : public TImageTool
{
private:
    void DrawSelRect();
	bool Pressed;
    TRect FSelRect;
    int   m_numCols;
    int   m_numRows;
public:
    TSelRectTool(TFCustomImage* aImage);
    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
    virtual void Reset();
    virtual AnsiString GetName();

    __property int Cols ={read = m_numCols, write = m_numCols};
    __property int Rows ={read = m_numRows, write = m_numRows};

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
	TThumbSelectTool(TFCustomImage* aImage,  int numThumbs, int tWidth, int tHeight);
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

//abstract media source  interface component
class TMediaSource
{
protected:
    bool m_IsInitialized; // ���� ������������� �����
    bool m_IsPreview;     // ���� ��������������� �����
    bool m_IsPaused;      // ���� ��������� ��������� ���������������.

    int  m_FrameCount;
    TFCustomImage* m_pDisplay;
    virtual bool __fastcall DecodeVideoFrame(int num, bool update_null_time = false) = 0;
    bool __fastcall GetIsPreview();
    virtual void __fastcall SetIsPreview(bool Value) =0;
    virtual void __fastcall SetIsPaused(bool Value)  =0;

public:
    TMediaSource(TFCustomImage* Display);
    virtual void __fastcall Initialize(TStrings* Names)=0;
    virtual void __fastcall Uninitialize() = 0;

    bool __fastcall GetIsInitialized();

   __property bool IsPreview = {read = GetIsPreview, write = SetIsPreview};
   __property bool IsPaused  = {read = m_IsPaused, write = SetIsPaused};
};



// ����� ���
class TSlideShow : public TMediaSource
{
protected:

    TStrings*   m_FileNames;     // ������ ���� ������
    TTimer*     m_Timer;         // ������
    int         m_LastVideoFrame;// ��������� ����������� ����
    int         m_PausedFrame;

    void __fastcall         TimerEventHandler(TObject *Sender);
    virtual bool __fastcall DecodeVideoFrame(int num, bool update_null_time = false);
public:
    TSlideShow(TFCustomImage* Display);
    ~TSlideShow();
    //������������� �������
    virtual void __fastcall Initialize(TStrings* Names);
    virtual void __fastcall Uninitialize();

   void __fastcall SetIsPreview(bool Value);
   void __fastcall SetIsPaused(bool Value);
};

class TFFMPEGVideo : public  TMediaSource
{
protected:
    void*       m_handler;
    TTimer*     m_Timer;
    int         m_currentFrame;

    void __fastcall         TimerEventHandler(TObject *Sender);
    virtual bool __fastcall DecodeVideoFrame(int num, bool update_null_time = false);

public:
    TFFMPEGVideo(TFCustomImage* Display);
    ~TFFMPEGVideo();

    //������������� �������
    virtual void __fastcall Initialize(TStrings* Names);
    virtual void __fastcall Uninitialize();

    void __fastcall SetIsPreview(bool Value);
    void __fastcall SetIsPaused(bool Value);
};
#endif
