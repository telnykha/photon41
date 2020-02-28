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
	TDriveComboBox *DriveComboBox1;
	TLabel *Label2;
	TRadioGroup *RadioGroup1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall DirectoryListBox1Change(TObject *Sender);
private:
public:
	virtual __fastcall TcopyForm(TComponent* AOwner);

	bool __fastcall GetCopyPath(UnicodeString& str);
};
//----------------------------------------------------------------------------
extern PACKAGE TcopyForm *copyForm;
//----------------------------------------------------------------------------
#endif    
