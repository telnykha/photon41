//---------------------------------------------------------------------------

#ifndef TuningUnitH
#define TuningUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "cspin.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.AppEvnts.hpp>
//---------------------------------------------------------------------------
class TTuningForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TCheckBox *CheckBox1;
	TGroupBox *GroupBox2;
	TCheckBox *CheckBox2;
	TTrackBar *TrackBar1;
	TLabel *Label1;
	TEdit *Edit1;
	TLabel *Label2;
	TCSpinEdit *CSpinEdit1;
	TEdit *Edit2;
	TTrackBar *TrackBar2;
	TLabel *Label3;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label4;
	TApplicationEvents *ApplicationEvents1;
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
    bool m_IsModelAvailable;
public:		// User declarations
	__fastcall TTuningForm(TComponent* Owner);
    __property bool IsModelAvailable = {read = m_IsModelAvailable};
};
//---------------------------------------------------------------------------
extern PACKAGE TTuningForm *TuningForm;
//---------------------------------------------------------------------------
#endif
