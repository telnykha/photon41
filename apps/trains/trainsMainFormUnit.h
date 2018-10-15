//---------------------------------------------------------------------------

#ifndef trainsMainFormUnitH
#define trainsMainFormUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include "FImage41.h"
#include "TrainsUtils.h"
extern "C"
{
	#include "vautils.h"
}

#include "_LF.h"

//---------------------------------------------------------------------------
class TPhMediaSource;
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
	TActionList *ActionList1;
	TAction *CloseAction;
	TAction *ModePaneAction;
	TAction *ModeSelRectAction;
	TAction *ActualSizeAction;
	TAction *BestFitAction;
	TAction *AboutAction;
	TAction *OpenVideoAction;
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
	TSaveDialog *SaveDialog1;
	TAction *logOpenAction;
	TAction *logSaveAction;
	TAction *logClearAction;
	TAction *logInsertAction;
	TAction *logDeleteAction;
	TPhImage *FImage1;
	TMenuItem *N25;
	TMenuItem *FirstFrameAction1;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *N30;
	TMenuItem *N31;
	TMenuItem *N32;
	TAction *GotoFrameAction;
	TAction *modeAnalysisAction;
	TAction *modeTuningAction;
	TMenuItem *N33;
	TMenuItem *N34;
	TMenuItem *N35;

    void __fastcall CloseActionExecute(TObject *Sender);
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
	void __fastcall FImage1AfterOpen(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall N16Click(TObject *Sender);
	void __fastcall FImage1Resize(TObject *Sender);
	void __fastcall GotoFrameActionExecute(TObject *Sender);
	void __fastcall GotoFrameActionUpdate(TObject *Sender);
	void __fastcall FImage1FrameData(TObject *Sender, int w, int h, int c, BYTE *data);
	void __fastcall modeAnalysisActionExecute(TObject *Sender);
	void __fastcall modeAnalysisActionUpdate(TObject *Sender);
	void __fastcall modeTuningActionExecute(TObject *Sender);
	void __fastcall modeTuningActionUpdate(TObject *Sender);




private:	// User declarations
    TLFImage     m_copy;
    TPhMediaSource* m_videoSource;
    TAction*        m_modeAction;

    TVAInitParams   m_trains_params;
    TVAInitParams   m_target_params;


    TTrainsAnalysisEngine m_engine;

    void __fastcall SetSource(TPhMediaSource* source);
	void __fastcall SetMode(TAction* action);

    void __fastcall RenderZones(awpImage* image);
    void __fastcall DrawZones();

public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
    void __fastcall UpdateImage();
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
