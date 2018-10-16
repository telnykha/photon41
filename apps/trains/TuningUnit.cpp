//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "TuningUnit.h"
#include "trainsMainFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TTuningForm *TuningForm;
//---------------------------------------------------------------------------
__fastcall TTuningForm::TTuningForm(TComponent* Owner)
	: TForm(Owner)
{
        m_IsModelAvailable = false;
}
//---------------------------------------------------------------------------
void __fastcall TTuningForm::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
      Button2->Enabled = m_IsModelAvailable;
      Label4->Caption =  m_IsModelAvailable ? L"Модель мишени готова к использованию" : L"Модель мишени не существует";
      Label4->Font->Color = m_IsModelAvailable ? clBlue : clRed;
}
//---------------------------------------------------------------------------


void __fastcall TTuningForm::TrackBar2Change(TObject *Sender)
{
	Edit2->Text = IntToStr(this->TrackBar2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::TrackBar1Change(TObject *Sender)
{
	Edit1->Text = IntToStr(this->TrackBar1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::CheckBox1Click(TObject *Sender)
{
    GroupBox1->Enabled = CheckBox1->Checked;

    for (int i = 0; i < GroupBox1->ControlCount; i++)
    {
        TControl* c = GroupBox1->Controls[i];
        if (c != NULL)
            c->Enabled = CheckBox1->Checked;
    }

}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::CheckBox2Click(TObject *Sender)
{
    GroupBox2->Enabled = CheckBox2->Checked;

    for (int i = 0; i < GroupBox2->ControlCount; i++)
    {
        TControl* c = GroupBox2->Controls[i];
        if (c != NULL)
            c->Enabled = CheckBox2->Checked;
    }
}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::FormCreate(TObject *Sender)
{
 // try to find model file
}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::Button1Click(TObject *Sender)
{
    m_IsModelAvailable = true;
}
//---------------------------------------------------------------------------

void __fastcall TTuningForm::Button2Click(TObject *Sender)
{
    m_IsModelAvailable = false;
}
//---------------------------------------------------------------------------
//
void __fastcall TTuningForm::FormShow(TObject *Sender)
{
   // установливаем два прямоугольника
}
//---------------------------------------------------------------------------

