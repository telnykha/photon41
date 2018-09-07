//----------------------------------------------------------------------------
#ifndef NewEventUnitH
#define NewEventUnitH
//----------------------------------------------------------------------------
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include <Vcl.Samples.Spin.hpp>
//----------------------------------------------------------------------------
class TNewEventDlg : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TSpinEdit *SpinEdit1;
private:
public:
	virtual __fastcall TNewEventDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TNewEventDlg *NewEventDlg;
//----------------------------------------------------------------------------
#endif    
