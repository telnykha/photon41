//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Clipbrd.hpp>
#include "OCRmain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Exit1Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::fileCloseActionExecute(TObject *Sender)
{
        if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        fileSaveActionExecute(this);
                 }
        }
        PhImage1->Empty = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::fileCloseActionUpdate(TObject *Sender)
{
	fileCloseAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::fileOpenActionExecute(TObject *Sender)
{
         if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        fileSaveActionExecute(this);
                 }
        }

        if (OpenDialog1->Execute())
        {
          // Open Media
          if(!PhImage1->Init(OpenDialog1->Files))
          	ShowMessage("Cannot open file: " + OpenDialog1->Files->Strings[0]);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PhImage1AfterOpen(TObject *Sender)
{
        PhImage1->BestFit();
        if (!PhImage1->Empty)
        {
	        StatusBar1->Panels->Items[1]->Text = IntToStr(PhImage1->Bitmap->Width) + L":" + IntToStr(PhImage1->Bitmap->Height);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::fileSaveActionExecute(TObject *Sender)
{
        if (SaveDialog1->Execute())
        {
          //todo: setup extention
          PhImage1->SaveToFile(SaveDialog1->FileName);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::fileSaveActionUpdate(TObject *Sender)
{
	fileSaveAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editCopyActionExecute(TObject *Sender)
{
	PhImage1->SaveToClipBoard();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editCopyActionUpdate(TObject *Sender)
{
	editCopyAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editPasteActionExecute(TObject *Sender)
{
 	PhImage1->LoadFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editPasteActionUpdate(TObject *Sender)
{
      TClipboard *cb = Clipboard();
      editPasteAction->Enabled = cb->HasFormat(CF_BITMAP);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editClearSelectionActionExecute(TObject *Sender)
{
	PhImage1->ClearSelection();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::editClearSelectionActionUpdate(TObject *Sender)
{
	editClearSelectionAction->Enabled = PhImage1->HasSelection();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PhImage1Change(TObject *Sender)
{
        AnsiString _caption  = "OCR demo  " + PhImage1->AFileName;
        _caption += PhImage1->Modified ? L"*":L"";
		Caption = _caption;
        if (PhImage1->Empty)
        {
                StatusBar1->Panels->Items[2]->Text = "Zoom";
                StatusBar1->Panels->Items[1]->Text = "";
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PhImage1ScaleChange(TObject *Sender)
{
	StatusBar1->Panels->Items[2]->Text =  L"Zoom=" + FormatFloat("###.#", PhImage1->Scale) + L"%";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewZoomInActionExecute(TObject *Sender)
{
 	PhImage1->ZoomIn();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewZoomInActionUpdate(TObject *Sender)
{
	viewZoomInAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewZoomOutActionExecute(TObject *Sender)
{
	PhImage1->ZoomOut();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewZoomOutActionUpdate(TObject *Sender)
{
	viewZoomOutAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewBestFitActionExecute(TObject *Sender)
{
 	PhImage1->BestFit();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewBestFitActionUpdate(TObject *Sender)
{
	viewBestFitAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewActualSizeActionExecute(TObject *Sender)
{
	PhImage1->ActualSize();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewActualSizeActionUpdate(TObject *Sender)
{
	viewActualSizeAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewFitWidthActionExecute(TObject *Sender)
{
	PhImage1->FitWidth();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewFitWidthActionUpdate(TObject *Sender)
{
	viewFitWidthAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewFitHeightActionExecute(TObject *Sender)
{
	PhImage1->FitHeight();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::viewFitHeightActionUpdate(TObject *Sender)
{
	viewFitHeightAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolPaneActionExecute(TObject *Sender)
{
	PhImage1->CurrentTool = ftPane;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolPaneActionUpdate(TObject *Sender)
{
    toolPaneAction->Enabled = !PhImage1->Empty;
    toolPaneAction->Checked = PhImage1->CurrentTool == ftPane;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolZoomToRectActionExecute(TObject *Sender)
{
	PhImage1->CurrentTool = ftZoomToRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolZoomToRectActionUpdate(TObject *Sender)
{
	toolZoomToRectAction->Enabled = !PhImage1->Empty;
    toolZoomToRectAction->Checked = PhImage1->CurrentTool == ftZoomToRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolSelectRectActionExecute(TObject *Sender)
{
	PhImage1->CurrentTool = ftSelRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolSelectRectActionUpdate(TObject *Sender)
{
	toolSelectRectAction->Enabled = !PhImage1->Empty;
    toolSelectRectAction->Checked = PhImage1->CurrentTool == ftSelRect;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolLenzActionExecute(TObject *Sender)
{
	PhImage1->CurrentTool = ftLenz;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::toolLenzActionUpdate(TObject *Sender)
{
	toolLenzAction->Enabled = !PhImage1->Empty;
    toolLenzAction->Checked = PhImage1->CurrentTool == ftLenz;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::PhImage1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
    if (PhImage1->CurrentTool == ftSelRect && PhImage1->HasSelection())
    {
    	//
        TGraphic* selected = PhImage1->SelectedBitmap;
        PhImage2->Bitmap = selected;
        PhImage2->BestFit();

        // set data to tesseract engine
    }
}
//---------------------------------------------------------------------------
