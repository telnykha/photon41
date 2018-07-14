//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "FImage41.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Dialogs.hpp>
#include "awpipl.h"
#include "_LF.h"
#include <VCLTee.Series.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TmainForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TStatusBar *StatusBar1;
	TPanel *Panel4;
	TPanel *Panel5;
	TChart *Chart1;
	TPhImage *PhImage1;
	TButton *Button1;
	TButton *Button2;
	TButton *Button7;
	TButton *Button8;
	TSplitter *Splitter1;
	TActionList *ActionList1;
	TAction *fileOpenAction;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TFileExit *fileExitAction;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TAction *viewMosaicAction;
	TMenuItem *N6;
	TMenuItem *N7;
	TMenuItem *N10;
	TOpenDialog *OpenDialog1;
	TAction *viewFirstAction;
	TAction *viewPrevAction;
	TAction *viewNextAction;
	TAction *viewFinishAction;
	TMenuItem *N8;
	TMenuItem *N11;
	TMenuItem *N12;
	TMenuItem *N13;
	TMenuItem *N14;
	TAction *viewAnalysisAreaAction;
	TMenuItem *N15;
	TSplitter *Splitter2;
	TImageList *ImageList1;
	TPanel *Panel6;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton1;
	TPanel *Panel7;
	TListView *ListView1;
	TGroupBox *GroupBox1;
	TSpinEdit *SpinEdit1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TSpinEdit *SpinEdit2;
	TSpinEdit *SpinEdit3;
	TPanel *Panel8;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TBarSeries *Series1;
	TAction *chartViewDensityAction;
	TAction *chartViewSquareAction;
	TAction *chartViewPerimeterAction;
	TMenuItem *N9;
	TMenuItem *N16;
	TMenuItem *N17;
	TMenuItem *N18;
	TPopupMenu *PopupMenu1;
	TMenuItem *N19;
	TMenuItem *N20;
	TMenuItem *N21;
	TAction *viewContoursAction;
	TMenuItem *N22;
	TAction *chartViewDensityAnalysisAction;
	TAction *chartViewNumberAnalysisAction;
	TAction *chartViewSquareAnalysisAction;
	TAction *chartViewPerimeterAnalysisAction;
	TMenuItem *N23;
	TMenuItem *N24;
	TMenuItem *N25;
	TMenuItem *N26;
	TMenuItem *N27;
	TMenuItem *N28;
	TMenuItem *N29;
	TMenuItem *N30;
	TMenuItem *N31;
	TMenuItem *N32;
	TPopupMenu *PopupMenu2;
	TMenuItem *N33;
	TMenuItem *N34;
	TMenuItem *N35;
	TMenuItem *N36;
	TMenuItem *N37;
	TMenuItem *N38;
	TMenuItem *N39;
	TMenuItem *N40;
	TMenuItem *N41;
	TLabel *Label10;
	TSpinEdit *SpinEdit4;
	TAction *editCopyImageAction;
	TMenuItem *N42;
	TMenuItem *N43;
	TAction *editCopyChartAction;
	TMenuItem *N44;
	TMenuItem *N45;
	TAction *viewAreaAction;
	TMenuItem *N46;
	TMenuItem *N47;
	TAction *fileReportAction;
	TMenuItem *N48;
	TMenuItem *N49;
	TMenuItem *N50;
	TMenuItem *N51;
	TAction *helpCallAction;
	TMenuItem *N52;
	TAction *helpAboutAction;
	TMenuItem *N53;
	TAction *fileCloseAction;
	TMenuItem *N54;
	TMenuItem *N55;
	void __fastcall fileOpenActionExecute(TObject *Sender);
	void __fastcall viewMosaicActionUpdate(TObject *Sender);
	void __fastcall viewMosaicActionExecute(TObject *Sender);
	void __fastcall viewFirstActionExecute(TObject *Sender);
	void __fastcall viewFirstActionUpdate(TObject *Sender);
	void __fastcall viewPrevActionExecute(TObject *Sender);
	void __fastcall viewPrevActionUpdate(TObject *Sender);
	void __fastcall viewNextActionExecute(TObject *Sender);
	void __fastcall viewNextActionUpdate(TObject *Sender);
	void __fastcall viewFinishActionExecute(TObject *Sender);
	void __fastcall viewFinishActionUpdate(TObject *Sender);
	void __fastcall PhImage1AfterOpen(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall viewAnalysisAreaActionExecute(TObject *Sender);
	void __fastcall viewAnalysisAreaActionUpdate(TObject *Sender);
	void __fastcall PhImage1Frame(TObject *Sender, TGraphic *data);
	void __fastcall PhImage1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SpinEdit1Change(TObject *Sender);
	void __fastcall SpinEdit2Change(TObject *Sender);
	void __fastcall SpinEdit3Change(TObject *Sender);
	void __fastcall chartViewDensityActionExecute(TObject *Sender);
	void __fastcall chartViewDensityActionUpdate(TObject *Sender);
	void __fastcall chartViewSquareActionExecute(TObject *Sender);
	void __fastcall chartViewSquareActionUpdate(TObject *Sender);
	void __fastcall chartViewPerimeterActionExecute(TObject *Sender);
	void __fastcall chartViewPerimeterActionUpdate(TObject *Sender);
	void __fastcall ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall viewContoursActionExecute(TObject *Sender);
	void __fastcall viewContoursActionUpdate(TObject *Sender);
	void __fastcall chartViewDensityAnalysisActionExecute(TObject *Sender);
	void __fastcall chartViewDensityAnalysisActionUpdate(TObject *Sender);
	void __fastcall chartViewNumberAnalysisActionExecute(TObject *Sender);
	void __fastcall chartViewNumberAnalysisActionUpdate(TObject *Sender);
	void __fastcall chartViewSquareAnalysisActionExecute(TObject *Sender);
	void __fastcall chartViewSquareAnalysisActionUpdate(TObject *Sender);
	void __fastcall chartViewPerimeterAnalysisActionExecute(TObject *Sender);
	void __fastcall chartViewPerimeterAnalysisActionUpdate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall PhImage1Mosaic(TObject *Sender);
	void __fastcall editCopyImageActionExecute(TObject *Sender);
	void __fastcall editCopyImageActionUpdate(TObject *Sender);
	void __fastcall editCopyChartActionExecute(TObject *Sender);
	void __fastcall editCopyChartActionUpdate(TObject *Sender);
	void __fastcall viewAreaActionExecute(TObject *Sender);
	void __fastcall viewAreaActionUpdate(TObject *Sender);
	void __fastcall fileReportActionExecute(TObject *Sender);
	void __fastcall fileReportActionUpdate(TObject *Sender);
	void __fastcall helpCallActionExecute(TObject *Sender);
	void __fastcall helpAboutActionExecute(TObject *Sender);
	void __fastcall fileCloseActionExecute(TObject *Sender);
	void __fastcall fileCloseActionUpdate(TObject *Sender);




private:	// User declarations

    awpImage*           m_first;
    awpImage* 			m_image;
    awpImage* 			m_mask;
    awpImage*           m_binary; //

    double    			m_average;
    double    			m_radius;
    TLFObjectList 		m_objects;
    TLFObjectList       m_analysis;

    TLFHistogramm       m_hd;
    TLFHistogramm       m_hs;
    TLFHistogramm       m_hp;

    int                 m_selected;

    awpImage* __fastcall ProcessFrame(awpImage* img, int frame);
    void  __fastcall Processhelper();
    void  __fastcall DrawObjects(awpImage* img, int selected);
    void  __fastcall DrawAnalysisArea(awpImage* img);
    void  __fastcall PrintObjects();
    void  __fastcall BuildHistogramms();
    void  __fastcall UpdateChart();
    void  __fastcall UpdatePicture();
    void  __fastcall GetSampelSums(int& num, double& density, double& square, double& perim);
    void  __fastcall DoAnalysis();
    bool  __fastcall SaveReport();
    void  __fastcall SaveParams();
    void  __fastcall LoadParams();
    void  __fastcall CloseHelper();
public:		// User declarations
	__fastcall TmainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmainForm *mainForm;
//---------------------------------------------------------------------------
#endif
