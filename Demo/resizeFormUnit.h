//----------------------------------------------------------------------------
#ifndef resizeFormUnitH
#define resizeFormUnitH
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
class TresizeForm : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TLabel *Label1;
	TComboBox *ComboBox1;
	TLabel *Label2;
	TEdit *Edit1;
	TLabel *Label3;
	TEdit *Edit2;
	TCheckBox *CheckBox1;
private:
public:
	virtual __fastcall TresizeForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TresizeForm *resizeForm;
//----------------------------------------------------------------------------
#endif    
