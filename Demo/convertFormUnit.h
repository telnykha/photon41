//----------------------------------------------------------------------------
#ifndef convertFormUnitH
#define convertFormUnitH
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
//----------------------------------------------------------------------------
class TconvertForm : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TCheckBox *CheckBox1;
private:
public:
	virtual __fastcall TconvertForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TconvertForm *convertForm;
//----------------------------------------------------------------------------
#endif    
