//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "copyFormUnit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TcopyForm *copyForm;
//--------------------------------------------------------------------- 
__fastcall TcopyForm::TcopyForm(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TcopyForm::FormShow(TObject *Sender)
{
    Edit1->Text = this->DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------


void __fastcall TcopyForm::DirectoryListBox1Change(TObject *Sender)
{
    Edit1->Text = this->DirectoryListBox1->Directory;
}
//---------------------------------------------------------------------------


