//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VideoControlUnit.h"
#include "MainUnit.h"
#include "Ph3iCube.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVideoControlDlg *VideoControlDlg;
//---------------------------------------------------------------------------
__fastcall TVideoControlDlg::TVideoControlDlg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::TrackBar8Change(TObject *Sender)
{
	double value = this->TrackBar9->Position + (this->TrackBar8->Position) / 100.;
	Edit8->Text = FormatFloat("#####.##", value);
	///
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
       src->SetExploshure(value);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::TrackBar1Change(TObject *Sender)
{
	Edit1->Text = IntToStr(this->TrackBar1->Position);
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
       src->SetBrightness(TrackBar1->Position);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::TrackBar2Change(TObject *Sender)
{
	Edit2->Text = IntToStr(this->TrackBar2->Position);
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
	   src->SetContrast(TrackBar2->Position);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::TrackBar7Change(TObject *Sender)
{
	Edit7->Text = IntToStr(this->TrackBar7->Position);
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
	   src->SetGain(TrackBar7->Position);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::TrackBar5Change(TObject *Sender)
{
	double value = (this->TrackBar5->Position) / 100.;
	Edit5->Text = FormatFloat("#####.##", value);
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
	   src->SetGamma(TrackBar5->Position);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::FormShow(TObject *Sender)
{
	TrackBar8Change(NULL);
	TrackBar1Change(NULL);
	TrackBar2Change(NULL);
	TrackBar7Change(NULL);
	TrackBar5Change(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TVideoControlDlg::CheckBox1Click(TObject *Sender)
{
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
	   src->SetAutoExploshure(this->CheckBox1->Checked);
	}

	if (!this->CheckBox1->Checked)
         TrackBar8Change(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TVideoControlDlg::TrackBar3Change(TObject *Sender)
{
	Edit3->Text = IntToStr(this->TrackBar3->Position);
	TPh3iCubeSource* src = dynamic_cast<TPh3iCubeSource*>(MainForm->videoSource);
	if (src != NULL)
	{
	   src->SetExploshureTarget(TrackBar3->Position);
	}
}
//---------------------------------------------------------------------------

