//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "FImage41.h"
#include <Vcl.Dialogs.hpp>
#include <Vcl.Buttons.hpp>
#include "PhImageTool.h"
#include "PhRulerTool.h"
#include "PhPaneTool.h"
#include "CeramUtils.h"
#include "awpipl.h"

//---------------------------------------------------------------------------
class TPhMediaSource;
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *StatusBar1;
	TActionList *ActionList1;
	TAction *fileExitAction;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TPanel *Panel2;
	TPanel *Panel3;
	TPhImage *PhImage1;
	TMenuItem *N3;
	TAction *modeExperimentAction;
	TAction *modeAutoAnalysisAction;
	TAction *modeHandAction;
	TMenuItem *N4;
	TMenuItem *N5;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N8;
	TAction *viewSourceImageAction;
	TAction *viewAnalysisAreaAction;
	TAction *viewObjectContourAction;
	TAction *viewCenterAction;
	TAction *viewAxisAction;
	TAction *viewEllipseAction;
	TMenuItem *N9;
	TMenuItem *N10;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TAction *fileOpenImagesAction;
	TAction *fileOpenVideoAction;
	TAction *fileConnectToCameraAction;
	TAction *fileCloseAction;
	TOpenDialog *OpenDialog1;
	TMenuItem *N15;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TMenuItem *N19;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton9;
	TPanel *Panel1;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TGroupBox *GroupBox2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TAction *viewFirstAction;
	TAction *viewPrevAction;
	TAction *viewNextAction;
	TAction *viewLastAction;
	TAction *viewPlayAction;
	TPhRulerTool *PhRulerTool1;
	TPhPaneTool *PhPaneTool1;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *Edit1;
	TLabel *Label14;
	void __fastcall fileExitActionExecute(TObject *Sender);
	void __fastcall modeExperimentActionExecute(TObject *Sender);
	void __fastcall modeExperimentActionUpdate(TObject *Sender);
	void __fastcall modeAutoAnalysisActionExecute(TObject *Sender);
	void __fastcall modeAutoAnalysisActionUpdate(TObject *Sender);
	void __fastcall modeHandActionExecute(TObject *Sender);
	void __fastcall modeHandActionUpdate(TObject *Sender);
	void __fastcall viewAnalysisAreaActionExecute(TObject *Sender);
	void __fastcall viewAnalysisAreaActionUpdate(TObject *Sender);
	void __fastcall viewObjectContourActionExecute(TObject *Sender);
	void __fastcall viewObjectContourActionUpdate(TObject *Sender);
	void __fastcall viewCenterActionExecute(TObject *Sender);
	void __fastcall viewCenterActionUpdate(TObject *Sender);
	void __fastcall viewAxisActionExecute(TObject *Sender);
	void __fastcall viewAxisActionUpdate(TObject *Sender);
	void __fastcall viewEllipseActionExecute(TObject *Sender);
	void __fastcall viewEllipseActionUpdate(TObject *Sender);
	void __fastcall fileOpenImagesActionExecute(TObject *Sender);
	void __fastcall fileOpenVideoActionExecute(TObject *Sender);
	void __fastcall fileConnectToCameraActionExecute(TObject *Sender);
	void __fastcall fileCloseActionExecute(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PhImage1AfterOpen(TObject *Sender);
	void __fastcall viewFirstActionExecute(TObject *Sender);
	void __fastcall viewFirstActionUpdate(TObject *Sender);
	void __fastcall viewPrevActionExecute(TObject *Sender);
	void __fastcall viewPrevActionUpdate(TObject *Sender);
	void __fastcall viewNextActionExecute(TObject *Sender);
	void __fastcall viewNextActionUpdate(TObject *Sender);
	void __fastcall viewLastActionExecute(TObject *Sender);
	void __fastcall viewLastActionUpdate(TObject *Sender);
	void __fastcall viewPlayActionExecute(TObject *Sender);
	void __fastcall viewPlayActionUpdate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PhImage1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall PhImage1FrameData(TObject *Sender, int w, int h, int c, BYTE *data);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall viewSourceImageActionExecute(TObject *Sender);




private:	// User declarations
    void __fastcall SetMode(TAction* action);
    void __fastcall SetSource(TPhMediaSource* source);
    TPhMediaSource* m_videoSource;
    TAction*        m_modeAction;

    // drawing
    void __fastcall RenderScene(awpImage* img);
    void __fastcall DrawRuler(awpImage* img);
    void __fastcall DrawMask(awpImage* img);
    void __fastcall DrawSource(awpImage* img);
    void __fastcall DrawCenter(awpImage* img);
    void __fastcall DrawObject(awpImage* img);
    void __fastcall DrawEllipce(awpImage* img);
    void __fastcall DrawAxis(awpImage* img);
    // processing
    TCeramImageProcessor m_engine;
    TCeramCalibration    m_c;

    // result
    void __fastcall ShowResult();

public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
