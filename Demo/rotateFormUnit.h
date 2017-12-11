//----------------------------------------------------------------------------
#ifndef rotateFormUnitH
#define rotateFormUnitH
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
#include <Vcl.Samples.Spin.hpp>
//----------------------------------------------------------------------------
class TrotateForm : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TRadioGroup *RadioGroup1;
	TLabel *Label1;
	TSpinEdit *SpinEdit1;
	TLabel *Label2;
private:
public:
	virtual __fastcall TrotateForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TrotateForm *rotateForm;
//----------------------------------------------------------------------------
#endif    
