//---------------------------------------------------------------------------

#ifndef OCRmainH
#define OCRmainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "FImage41.h"
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPhImage *PhImage1;
	TStatusBar *StatusBar1;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Open1;
	TMenuItem *SaveAs1;
	TMenuItem *N2;
	TMenuItem *Closemedia1;
	TMenuItem *N3;
	TMenuItem *Exit1;
	TMenuItem *Edit1;
	TMenuItem *Copy1;
	TMenuItem *Paste1;
	TMenuItem *N7;
	TMenuItem *ClearSelection1;
	TMenuItem *Mode1;
	TMenuItem *PaneTool1;
	TMenuItem *ZoomToRectTool1;
	TMenuItem *toolSelectRectAction1;
	TMenuItem *LenzTool1;
	TMenuItem *View1;
	TMenuItem *ZoomIn1;
	TMenuItem *ZoomOut1;
	TMenuItem *ZoomTo1;
	TMenuItem *BestFit1;
	TMenuItem *FitToWidth1;
	TMenuItem *FitHeight1;
	TActionList *ActionList1;
	TAction *fileOpenAction;
	TAction *fileSaveAction;
	TAction *fileCloseAction;
	TFileExit *fileExitAction;
	TAction *editCopyAction;
	TAction *editPasteAction;
	TAction *toolPaneAction;
	TAction *toolZoomToRectAction;
	TAction *toolSelectRectAction;
	TAction *toolLenzAction;
	TAction *viewZoomInAction;
	TAction *viewZoomOutAction;
	TAction *viewBestFitAction;
	TAction *viewActualSizeAction;
	TAction *viewFitWidthAction;
	TAction *viewFitHeightAction;
	TAction *editClearSelectionAction;
	TPanel *Panel1;
	TPhImage *PhImage2;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall fileCloseActionExecute(TObject *Sender);
	void __fastcall fileCloseActionUpdate(TObject *Sender);
	void __fastcall fileOpenActionExecute(TObject *Sender);
	void __fastcall PhImage1AfterOpen(TObject *Sender);
	void __fastcall fileSaveActionExecute(TObject *Sender);
	void __fastcall fileSaveActionUpdate(TObject *Sender);
	void __fastcall editCopyActionExecute(TObject *Sender);
	void __fastcall editCopyActionUpdate(TObject *Sender);
	void __fastcall editPasteActionExecute(TObject *Sender);
	void __fastcall editPasteActionUpdate(TObject *Sender);
	void __fastcall editClearSelectionActionExecute(TObject *Sender);
	void __fastcall editClearSelectionActionUpdate(TObject *Sender);
	void __fastcall PhImage1Change(TObject *Sender);
	void __fastcall PhImage1ScaleChange(TObject *Sender);
	void __fastcall viewZoomInActionExecute(TObject *Sender);
	void __fastcall viewZoomInActionUpdate(TObject *Sender);
	void __fastcall viewZoomOutActionExecute(TObject *Sender);
	void __fastcall viewZoomOutActionUpdate(TObject *Sender);
	void __fastcall viewBestFitActionExecute(TObject *Sender);
	void __fastcall viewBestFitActionUpdate(TObject *Sender);
	void __fastcall viewActualSizeActionExecute(TObject *Sender);
	void __fastcall viewActualSizeActionUpdate(TObject *Sender);
	void __fastcall viewFitWidthActionExecute(TObject *Sender);
	void __fastcall viewFitWidthActionUpdate(TObject *Sender);
	void __fastcall viewFitHeightActionExecute(TObject *Sender);
	void __fastcall viewFitHeightActionUpdate(TObject *Sender);
	void __fastcall toolPaneActionExecute(TObject *Sender);
	void __fastcall toolPaneActionUpdate(TObject *Sender);
	void __fastcall toolZoomToRectActionExecute(TObject *Sender);
	void __fastcall toolZoomToRectActionUpdate(TObject *Sender);
	void __fastcall toolSelectRectActionExecute(TObject *Sender);
	void __fastcall toolSelectRectActionUpdate(TObject *Sender);
	void __fastcall toolLenzActionExecute(TObject *Sender);
	void __fastcall toolLenzActionUpdate(TObject *Sender);
	void __fastcall PhImage1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
