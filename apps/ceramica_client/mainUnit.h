//---------------------------------------------------------------------------

#ifndef mainUnitH
#define mainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdAntiFreeze.hpp>
#include <IdAntiFreezeBase.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TGroupBox *GroupBox2;
	TEdit *Edit1;
	TMemo *Memo1;
	TIdTCPClient *IdTCPClient1;
	TPanel *Panel1;
	TCheckBox *CheckBox1;
	TIdAntiFreeze *IdAntiFreeze1;
	TTimer *Timer1;
	void __fastcall IdTCPClient1Connected(TObject *Sender);
	void __fastcall IdTCPClient1Disconnected(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
    void __fastcall SetClientState(bool state);
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
