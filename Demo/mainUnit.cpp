//---------------------------------------------------------------------------
#include <vcl.h>
#include "System.IOUtils.hpp"
#pragma hdrstop
#include <Clipbrd.hpp>
#include "mainUnit.h"
#include "copyFormUnit.h"
#include "resizeFormUnit.h"
#include "rotateFormUnit.h"
#include "convertFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage41"
#pragma link "PhImageTool"
#pragma link "PhPaneTool"
#pragma link "PhLenzTool"
#pragma link "PhZoomToRectTool"
#pragma link "PhSelectRectTool"
#pragma link "PhFrames"
#pragma link "PhTrackBar"
#pragma link "PhRulerTool"
#pragma resource "*.dfm"
TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
    m_selected = new TStringList();
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
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileSaveActionExecute(TObject *Sender)
{
        if (SaveDialog1->Execute())
        {
          //todo: setup extention
          PhImage1->SaveToFile(SaveDialog1->FileName.c_str());
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
        PhTrackBar1->Max = PhImage1->Frames->Count;
        PhTrackBar1->Frequency = PhImage1->Frames->Count / 20;
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
        AnsiString _caption  = "Photon 4.1 demo  " + PhImage1->FileName;
		_caption += PhImage1->Modified ? L"*":L"";
		Caption = _caption;
        if (PhImage1->Empty)
        {
                StatusBar1->Panels->Items[2]->Text = "Zoom";
                StatusBar1->Panels->Items[1]->Text = "";
        }

        if (!PhImage1->Empty)
        {
	        StatusBar1->Panels->Items[1]->Text = IntToStr(PhImage1->Bitmap->Width) + L":" + IntToStr(PhImage1->Bitmap->Height);
        }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        PhImage1->Cancel();
        if (PhImage1->Modified)
        {
		 if (MessageDlg("Save changes?", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
                 {
                        this->fileSaveActionExecute(this);
                 }
        }
        delete m_selected;
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
    if (ParamCount() > 0)
    {
        TStringList* list = new TStringList();
        UnicodeString strFileName = ParamStr(1);
        list->LoadFromFile(strFileName);
/*
        for (int i = 0; i <= ParamCount(); i++)
        {
            if (ExtractFileExt(ParamStr(i)) == L".exe")
                continue;

            list->Add(ParamStr(i));
        }*/

        PhImage1->Init(list);
        delete list;
    }
    else
    {
        this->TrackBar1->Position = this->PhImage1->SlideShowInterval;

        StatusBar1->Panels->Items[2]->Text =  L"Zoom";
        if (PhImage1->PhTool != NULL)
            StatusBar1->Panels->Items[3]->Text =  PhImage1->PhTool->ToolName;
    }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::editClearSelectionActionExecute(TObject *Sender)
{
	PhImage1->ClearSelection();
	if (PhImage1->Mosaic)
        PhImage1->Frames->ClearSelection();
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
void __fastcall TmainForm::TrackBar1Change(TObject *Sender)
{
    PhImage1->SlideShowInterval = TrackBar1->Position;
    Panel3->Caption = L"Slideshow" + IntToStr((int)PhImage1->SlideShowInterval) + L" ms";
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editSelectAllActionExecute(TObject *Sender)
{
	PhImage1->Frames->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editSelectAllActionUpdate(TObject *Sender)
{
	editSelectAllAction->Enabled = this->PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editInvertSelectionActionExecute(TObject *Sender)
{
    PhImage1->Frames->InvertSelection();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editInvertSelectionActionUpdate(TObject *Sender)
{
	editInvertSelectionAction->Enabled = this->PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgCopyActionExecute(TObject *Sender)
{
	if (copyForm->ShowModal() == mrOk)
    {
 		if (MessageDlg(L"This operation can not be canceled. Are you sure you want to copy this image (s)?", mtWarning , TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
         {
			UnicodeString strPathToCopy = copyForm->Edit1->Text;
			strPathToCopy += L"\\";
			this->BuildSelected();
			if (PhImage1->Mosaic && m_selected->Count > 0)
			{
				m_PathTo = strPathToCopy;
				PhImage1->Copy(strPathToCopy.c_str());
			}
		 }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgCopyActionUpdate(TObject *Sender)
{
    imgCopyAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgMoveActionExecute(TObject *Sender)
{
    if (copyForm->ShowModal() == mrOk)
    {
 		if (MessageDlg(L"This operation can not be canceled. Are you sure you want to move this image (s)?", mtWarning , TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
		 {
			UnicodeString strPathToCopy = copyForm->Edit1->Text;
			strPathToCopy += L"\\";
			this->BuildSelected();
			if (PhImage1->Mosaic && m_selected->Count > 0)
			{
				m_PathTo = strPathToCopy;
				PhImage1->Move(strPathToCopy.c_str());
			}
         }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgMoveActionUpdate(TObject *Sender)
{
    imgMoveAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgRotateActionExecute(TObject *Sender)
{
    if (rotateForm->ShowModal() == mrOk)
    {
        //todo: make rotation
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgRotateActionUpdate(TObject *Sender)
{
    imgRotateAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgResizeActionExecute(TObject *Sender)
{
    if (resizeForm->ShowModal() == mrOk)
    {
        //todo: do resize operation
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgResizeActionUpdate(TObject *Sender)
{
	imgResizeAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgGrayScaleActionExecute(TObject *Sender)
{
	//todo: do grayscale action
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgGrayScaleActionUpdate(TObject *Sender)
{
	imgGrayScaleAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgInvertActionExecute(TObject *Sender)
{
	//todo: do invert action
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgInvertActionUpdate(TObject *Sender)
{
    imgInvertAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgConvertActionExecute(TObject *Sender)
{
    if (convertForm->ShowModal() == mrOk)
    {
		//todo: do convert selection
		EPhImageFormats target;
		switch (convertForm->ComboBox1->ItemIndex)
		{
			case 0:
				target = jpegFormat;
			break;
			case 1:
				target = pngFormat;
			break;
			case 2:
				target = tiffFormat;
			break;
			case 3:
				target = awpFormat;
			break;
		}
        PhImage1->Frames->ConvertSelected(target, convertForm->CheckBox1->Checked);
	}
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgConvertActionUpdate(TObject *Sender)
{
    imgConvertAction->Enabled = PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgCropActionExecute(TObject *Sender)
{
	//todo: do crop operation
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgCropActionUpdate(TObject *Sender)
{
    imgCropAction->Enabled = PhImage1->Bitmap != NULL && PhImage1->HasSelection() && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgDeleteActionExecute(TObject *Sender)
{

 if (MessageDlg(L"This operation can not be canceled. Are you sure you want to delete this image (s)?", mtWarning , TMsgDlgButtons() << mbOK << mbCancel, 0) == mrOk)
         {
            PhImage1->Delete();
         }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::imgDeleteActionUpdate(TObject *Sender)
{
    imgDeleteAction->Enabled = !PhImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::fileNewInstanceActionExecute(TObject *Sender)
{
    m_selected->Clear();
    for (int i = 0; i < PhImage1->Frames->Count; i++)
    {
        m_selected->Add(PhImage1->Frames->Frame[i]->strFileName);
    }
    TPath path;
    UnicodeString strTmpFileName = path.GetTempFileNameW();
    m_selected->SaveToFile(strTmpFileName);
    ShellExecute(NULL, L"open",Application->ExeName.c_str(),  strTmpFileName.c_str(),  NULL, SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhImage1Progress(TObject *Sender, UnicodeString &strMessage,
          int Progress)
{
    //
    Label1->Caption = strMessage;
    Gauge1->Progress = Progress;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::Button1Click(TObject *Sender)
{
    PhImage1->Cancel();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhImage1Start(TObject *Sender)
{
    GroupBox1->Caption = L"";
    Gauge1->Progress = 0;
    GroupBox1->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenInExplorer()
{
    ShellExecute(NULL, L"open", m_PathTo.c_str(), NULL, NULL, SW_SHOWNORMAL);
    m_PathTo = L"";
    m_selected->Clear();
}

void __fastcall TmainForm::OpenInNewInstance()
{
    for (int i = 0; i < m_selected->Count; i++)
    {
        UnicodeString str = m_PathTo + L"\\" + m_selected->Strings[i];
        m_selected->Strings[i] = str;
    }
    TPath path;
    UnicodeString strTmpFileName = path.GetTempFileNameW();
    m_selected->SaveToFile(strTmpFileName);
    ShellExecute(NULL, L"open",Application->ExeName.c_str(),  strTmpFileName.c_str(),  NULL, SW_SHOWNORMAL);
}

void __fastcall TmainForm::PhImage1Cancel(TObject *Sender)
{
	ShowMessage(L"Job canceled.");
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::BuildSelected()
{
    //
    m_selected->Clear();
    for (long i = 0; i < PhImage1->Frames->Count; i++)
    {
        if (PhImage1->Frames->Frame[i]->selected)
        {
          m_selected->Add(ExtractFileName(PhImage1->Frames->Frame[i]->strFileName));
        }
    }
}


void __fastcall TmainForm::PhImage1Finish(TObject *Sender, EPhJobReason reason, bool Cancel)

{
	GroupBox1->Visible = false;
	if (Cancel)
        return;
    if (reason == copyJob || reason == moveJob)
    {
        switch(copyForm->RadioGroup1->ItemIndex)
        {
            case 1:
                OpenInExplorer();
            break;
            case 2:
				OpenInNewInstance();
            break;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhImage1Frame(TObject *Sender, TGraphic *data)
{
        PhTrackBar1->Position = PhImage1->Frames->CurrentFrame;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhTrackBar1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
        PhImage1->Frames->GoFrame(PhTrackBar1->Position);
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::PhTrackBar1Change(TObject *Sender)
{
    PhImage1->Frames->GoFrame(PhTrackBar1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::toolRulerActionExecute(TObject *Sender)
{
	 PhImage1->SelectPhTool(PhRulerTool1);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::toolRulerActionUpdate(TObject *Sender)
{
	toolRulerAction->Enabled = !PhImage1->Empty;
	toolRulerAction->Checked =  dynamic_cast< TPhRulerTool*>(PhImage1->PhTool) != NULL;

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


void __fastcall TmainForm::PhImage1Paint(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

