//----------------------------------------------------------------------------
#ifndef copyFormUnitH
#define copyFormUnitH
//----------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.hpp>
#include <Vcl.FileCtrl.hpp>
//----------------------------------------------------------------------------
class TcopyForm : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TLabel *Label1;
	TEdit *Edit1;
	TDirectoryListBox *DirectoryListBox1;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
private:
public:
	virtual __fastcall TcopyForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TcopyForm *copyForm;
//----------------------------------------------------------------------------
#endif    