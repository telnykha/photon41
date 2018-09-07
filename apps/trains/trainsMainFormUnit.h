//---------------------------------------------------------------------------

#ifndef trainsMainFormUnitH
#define trainsMainFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "FImage.h"
#include "TrackBarEx.h"
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "EventsIndicator.h"
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include "LFTrainsModule.h"
extern "C"
{
	#include "vautils.h"
}
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TPanel *Panel1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TTrackBarEx2 *TrackBarEx1;
	TFVideoCapture *FImage1;
	TPanel *Panel2;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TActionList *ActionList1;
	TAction *OpneImageAction;
	TAction *CloseAction;
	TAction *ModePaneAction;
	TAction *ModeSelRectAction;
	TAction *ActualSizeAction;
	TAction *BestFitAction;
	TAction *AboutAction;
	TAction *OpenVideoAction;
	TAction *OpenSlideShowAction;
	TAction *SaveImageAction;
	TAction *CloseVideoAction;
	TAction *PlayAction;
	TAction *FirstFrameAction;
	TAction *PrevFrameAction;
	TAction *NextFrameAction;
	TAction *LastFrameAction;
	TAction *OptionsAction;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TMenuItem *N9;
	TMenuItem *N2;
	TMenuItem *N10;
	TMenuItem *N3;
	TOpenDialog *OpenDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *N11;
	TMenuItem *N14;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *USB1;
	TMenuItem *IP1;
	TMenuItem *N22;
	TMenuItem *N21;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N13;
	TMenuItem *N12;
	TMenuItem *N23;
	TMenuItem *N24;
	TMenuItem *N15;
	TMenuItem *N16;
	TEventsIndicator *EventsIndicator1;
	TAction *videoSourceSizeAction;
	TAction *videoHalfSizeAction;
	TAction *videoQuarterSizeAction;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TListView *ListView1;
	TPanel *Panel3;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton10;
	TGroupBox *GroupBox2;
	TTrackBar *TrackBar1;
	TSaveDialog *SaveDialog1;
	TCheckBox *CheckBox5;
	TAction *logOpenAction;
	TAction *logSaveAction;
	TAction *logClearAction;
	TAction *logInsertAction;
	TAction *logDeleteAction;

    void __fastcall CloseActionExecute(TObject *Sender);
    void __fastcall OpneImageActionExecute(TObject *Sender);
    void __fastcall FormResize(TObject *Sender);
    void __fastcall ModePaneActionExecute(TObject *Sender);
    void __fastcall ModePaneActionUpdate(TObject *Sender);
    void __fastcall ModeSelRectActionExecute(TObject *Sender);
    void __fastcall ModeSelRectActionUpdate(TObject *Sender);
    void __fastcall ActualSizeActionUpdate(TObject *Sender);
    void __fastcall ActualSizeActionExecute(TObject *Sender);
    void __fastcall BestFitActionExecute(TObject *Sender);
    void __fastcall BestFitActionUpdate(TObject *Sender);
    void __fastcall AboutActionExecute(TObject *Sender);
    void __fastcall CloseVideoActionExecute(TObject *Sender);
    void __fastcall CloseVideoActionUpdate(TObject *Sender);
    void __fastcall OpenSlideShowActionExecute(TObject *Sender);
    void __fastcall FImage1BeforeOpen(TObject *Sender);
    void __fastcall OpenVideoActionExecute(TObject *Sender);
    void __fastcall OpenUSBCameraActionExecute(TObject *Sender);
    void __fastcall OpenIPCameraActionExecute(TObject *Sender);
    void __fastcall PlayActionExecute(TObject *Sender);
    void __fastcall PlayActionUpdate(TObject *Sender);
    void __fastcall FirstFrameActionExecute(TObject *Sender);
    void __fastcall FirstFrameActionUpdate(TObject *Sender);
    void __fastcall PrevFrameActionExecute(TObject *Sender);
    void __fastcall PrevFrameActionUpdate(TObject *Sender);
    void __fastcall NextFrameActionExecute(TObject *Sender);
    void __fastcall NextFrameActionUpdate(TObject *Sender);
    void __fastcall LastFrameActionExecute(TObject *Sender);
    void __fastcall LastFrameActionUpdate(TObject *Sender);
    void __fastcall FImage1Frame(TObject *Sender, int widht, int height,
          int bpp, char *data);
	void __fastcall TrackBarEx1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FImage1AfterOpen(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OptionsActionExecute(TObject *Sender);
	void __fastcall OptionsActionUpdate(TObject *Sender);
	void __fastcall FImage1ToolChange(TObject *Sender);
	void __fastcall TrackBarEx1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall videoSourceSizeActionExecute(TObject *Sender);
	void __fastcall videoSourceSizeActionUpdate(TObject *Sender);
	void __fastcall videoHalfSizeActionExecute(TObject *Sender);
	void __fastcall videoHalfSizeActionUpdate(TObject *Sender);
	void __fastcall videoQuarterSizeActionExecute(TObject *Sender);
	void __fastcall videoQuarterSizeActionUpdate(TObject *Sender);
	void __fastcall ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall ListView1Change(TObject *Sender, TListItem *Item, TItemChange Change);
	void __fastcall CheckBox5Click(TObject *Sender);
	void __fastcall logOpenActionExecute(TObject *Sender);
	void __fastcall logOpenActionUpdate(TObject *Sender);
	void __fastcall logSaveActionExecute(TObject *Sender);
	void __fastcall logSaveActionUpdate(TObject *Sender);
	void __fastcall logDeleteActionExecute(TObject *Sender);
	void __fastcall logDeleteActionUpdate(TObject *Sender);
	void __fastcall logInsertActionExecute(TObject *Sender);
	void __fastcall logInsertActionUpdate(TObject *Sender);
	void __fastcall logClearActionExecute(TObject *Sender);
	void __fastcall logClearActionUpdate(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall FImage1Resize(TObject *Sender);



private:	// User declarations
    EVideoSource m_videoSource;
    TLFZones     m_zones;
    TLFImage     m_copy;
    TLFTrains*   m_trains;
    int num_cross;
    awpRect crect;

    void __fastcall ToolDelete(TObject *Sender);
    void __fastcall SetZones();
    void __fastcall SetDefaultZones();

    awpColor m_color;
    void __fastcall RenderZones(awpImage* image);
    void __fastcall RenderZone(awpImage* image, TLFZone* z);
	void __fastcall RenderOpenPolygon(awpImage* image,TLFZone* z);
    void __fastcall RenderLineSegment(awpImage* image,TLFZone* z);
    void __fastcall RenderContour(awpImage* image,TLFZone* z);
    void __fastcall RenderRect(awpImage* image,TLFZone* z);
    void __fastcall DrawZones();

    // Events
    bool __fastcall SaveEventsToXmlFile(UnicodeString& FileName);
    bool __fastcall SaveEventsToTxtFile(UnicodeString& FileName);
    bool __fastcall LoadEventsFromXmlFile(UnicodeString& FileName);
    bool __fastcall LoadEventsFromTxtFile(UnicodeString& FileName);
    bool __fastcall DeleteSelectedEvent();
    bool __fastcall AddNewEvent(TVideoEvent* e);

public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
    void __fastcall UpdateImage();
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
