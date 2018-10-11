//---------------------------------------------------------------------------

#ifndef VideoControlUnitH
#define VideoControlUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TVideoControlDlg : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TTrackBar *TrackBar1;
	TTrackBar *TrackBar2;
	TTrackBar *TrackBar5;
	TLabel *Label5;
	TLabel *Label7;
	TTrackBar *TrackBar7;
	TLabel *Label8;
	TLabel *Label9;
	TTrackBar *TrackBar8;
	TLabel *Label10;
	TTrackBar *TrackBar9;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit5;
	TEdit *Edit7;
	TEdit *Edit8;
	TCheckBox *CheckBox1;
	TLabel *Label3;
	TTrackBar *TrackBar3;
	TEdit *Edit3;
	void __fastcall TrackBar8Change(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall TrackBar2Change(TObject *Sender);
	void __fastcall TrackBar7Change(TObject *Sender);
	void __fastcall TrackBar5Change(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall TrackBar3Change(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TVideoControlDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVideoControlDlg *VideoControlDlg;
//---------------------------------------------------------------------------
#endif
