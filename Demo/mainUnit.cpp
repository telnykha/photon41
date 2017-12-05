//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <Clipbrd.hpp>
#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage41"
#pragma link "PhImageTool"
#pragma link "PhPaneTool"
#pragma link "PhLenzTool"
#pragma link "PhZoomToRectTool"
#pragma link "PhSelectRectTool"
#pragma link "PhFrames"
#pragma resource "*.dfm"
TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileOpenActionExecute(TObject *Sender)
{
         if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        this->fileSaveActionExecute(this);
                 }
        }

        if (OpenDialog1->Execute())
        {
          // Open Media
          if(!PhImage1->Init(OpenDialog1->Files))
          	ShowMessage("Cannot open file: " + OpenDialog1->Files->Strings[0]);
          this->Panel1->Visible = OpenDialog1->Files->Count > 1;
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileSaveActionExecute(TObject *Sender)
{
        if (SaveDialog1->Execute())
        {
          //todo: setup extention
          PhImage1->SaveToFile(SaveDialog1->FileName);
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileSaveActionUpdate(TObject *Sender)
{
        fileSaveAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileCloseActionExecute(TObject *Sender)
{
        if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        this->fileSaveActionExecute(this);
                 }
        }
        PhImage1->Close();
        PhImage1->Empty = true;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileCloseActionUpdate(TObject *Sender)
{
	fileCloseAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PhImage1AfterOpen(TObject *Sender)
{
        PhImage1->BestFit();
        if (!PhImage1->Empty)
        {
	        StatusBar1->Panels->Items[1]->Text = IntToStr(PhImage1->Bitmap->Width) + L":" + IntToStr(PhImage1->Bitmap->Height);
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editCopyActionExecute(TObject *Sender)
{
		PhImage1->SaveToClipBoard();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editCopyActionUpdate(TObject *Sender)
{
	editCopyAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editPasteActionExecute(TObject *Sender)
{
        PhImage1->LoadFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editPasteActionUpdate(TObject *Sender)
{
      TClipboard *cb = Clipboard();
      editPasteAction->Enabled = cb->HasFormat(CF_BITMAP);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PhImage1Change(TObject *Sender)
{
        AnsiString _caption  = "Photon 4.1 demo  " + PhImage1->AFileName;
		_caption += PhImage1->Modified ? L"*":L"";
		Caption = _caption;
        if (PhImage1->Empty)
        {
                StatusBar1->Panels->Items[2]->Text = "Zoom";
                StatusBar1->Panels->Items[1]->Text = "";
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        this->fileSaveActionExecute(this);
                 }
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolPaneActionExecute(TObject *Sender)
{
      PhImage1->SelectPhTool(PhPaneTool1);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolPaneActionUpdate(TObject *Sender)
{
    toolPaneAction->Enabled = !PhImage1->Empty;
    toolPaneAction->Checked =  dynamic_cast< TPhPaneTool*>(PhImage1->PhTool) != NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolZoomToRectActionExecute(TObject *Sender)
{
         PhImage1->SelectPhTool(PhZoomToRectTool1);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolZoomToRectActionUpdate(TObject *Sender)
{
	toolZoomToRectAction->Enabled = !PhImage1->Empty;
    toolZoomToRectAction->Checked = dynamic_cast< TPhZoomToRectTool*>(PhImage1->PhTool) != NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolSelectRectActionExecute(TObject *Sender)
{
        PhImage1->SelectPhTool(PhSelRectTool1);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolSelectRectActionUpdate(TObject *Sender)
{
	toolSelectRectAction->Enabled = !PhImage1->Empty;
    toolSelectRectAction->Checked = dynamic_cast< TPhSelRectTool*>(PhImage1->PhTool) != NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolLenzActionExecute(TObject *Sender)
{
      PhImage1->SelectPhTool(PhLenzTool1);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::toolLenzActionUpdate(TObject *Sender)
{
	toolLenzAction->Enabled = !PhImage1->Empty;
    toolLenzAction->Checked =  dynamic_cast< TPhLenzTool*>(PhImage1->PhTool) != NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomInActionExecute(TObject *Sender)
{
        PhImage1->ZoomIn();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomInActionUpdate(TObject *Sender)
{
        viewZoomInAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomOutActionExecute(TObject *Sender)
{
        PhImage1->ZoomOut();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomOutActionUpdate(TObject *Sender)
{
     viewZoomOutAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomToActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewZoomToActionUpdate(TObject *Sender)
{
        viewZoomToAction->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewBestFitActionExecute(TObject *Sender)
{
    PhImage1->BestFit();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewBestFitActionUpdate(TObject *Sender)
{
	viewBestFitAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewActualSizeActionExecute(TObject *Sender)
{
        PhImage1->ActualSize();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewActualSizeActionUpdate(TObject *Sender)
{
        viewActualSizeAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewFitWidthActionExecute(TObject *Sender)
{
        PhImage1->FitWidth();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewFitWidthActionUpdate(TObject *Sender)
{
	viewFitWidthAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewFitHeightActionExecute(TObject *Sender)
{
        PhImage1->FitHeight();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewFitHeightActionUpdate(TObject *Sender)
{
	viewFitHeightAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveCenterActionExecute(TObject *Sender)
{
        PhImage1->MoveToCenter();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveCenterActionUpdate(TObject *Sender)
{
	viewMoveCenterAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveLeftTopActionExecute(TObject *Sender)
{
        PhImage1->MoveToLeftTop();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveLeftTopActionUpdate(TObject *Sender)
{
	viewMoveLeftTopAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveRightBottomActionExecute(TObject *Sender)
{
        PhImage1->MoveToRightBottom();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveRightBottomActionUpdate(TObject *Sender)
{
	viewMoveRightBottomAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveToActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveToActionUpdate(TObject *Sender)
{
        viewMoveToAction->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveByActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMoveByActionUpdate(TObject *Sender)
{
	viewMoveByAction->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PhImage1ScaleChange(TObject *Sender)
{
    StatusBar1->Panels->Items[2]->Text =  L"Zoom=" + FormatFloat("###.#", PhImage1->Scale) + L"%";
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PhImage1ToolChange(TObject *Sender)
{
      if (PhImage1->PhTool != NULL)
	    StatusBar1->Panels->Items[3]->Text =  PhImage1->PhTool->ToolName;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormCreate(TObject *Sender)
{
    StatusBar1->Panels->Items[2]->Text =  L"Zoom";
    if (PhImage1->PhTool != NULL)
	    StatusBar1->Panels->Items[3]->Text =  PhImage1->PhTool->ToolName;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editClearSelectionActionExecute(TObject *Sender)
{
	PhImage1->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editClearSelectionActionUpdate(TObject *Sender)
{
        editClearSelectionAction->Enabled = PhImage1->HasSelection();
}
//---------------------------------------------------------------------------
 void __fastcall TmainForm::navFirstActionExecute(TObject *Sender)
{
    this->PhImage1->Frames->First();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navFirstActionUpdate(TObject *Sender)
{
    navFirstAction->Enabled = PhImage1->Frames->Count > 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navLastActionExecute(TObject *Sender)
{
    this->PhImage1->Frames->Last();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navLastActionUpdate(TObject *Sender)
{
    navLastAction->Enabled = PhImage1->Frames->Count > 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navPrevActionExecute(TObject *Sender)
{
    this->PhImage1->Frames->Prev();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navPrevActionUpdate(TObject *Sender)
{
    navPrevAction->Enabled =  PhImage1->Frames->Count > 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navNextActionExecute(TObject *Sender)
{
    this->PhImage1->Frames->Next();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navNextActionUpdate(TObject *Sender)
{
    navNextAction->Enabled = PhImage1->Frames->Count > 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navPlayActionExecute(TObject *Sender)
{
    this->PhImage1->SlideShow = !this->PhImage1->SlideShow;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::navPlayActionUpdate(TObject *Sender)
{
    navPlayAction->Enabled =   PhImage1->Frames->Count > 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewMosaicActionExecute(TObject *Sender)
{
   PhImage1->Mosaic = !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewMosaicActionUpdate(TObject *Sender)
{
   viewMosaicAction->Enabled = !this->PhImage1->Frames->Mosaic->Empty;
   viewMosaicAction->Checked =  this->PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

