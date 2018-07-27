//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm3::IdTCPClient1Connected(TObject *Sender)
{
  //	 Memo1->Lines->Add(L"подключение к серверу");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::IdTCPClient1Disconnected(TObject *Sender)
{
  //	 Memo1->Lines->Add(L"отключение от сервера");
}
//---------------------------------------------------------------------------
void __fastcall TForm3::SetClientState(bool state)
{
    try
    {
        if (state)
        {
           IdTCPClient1->Host = L"127.0.0.1";
           IdTCPClient1->Port = 6000;
           IdTCPClient1->Connect();
        }
        else
        {
            IdTCPClient1->Disconnect();
        }
    }
    catch(...)
    {
        state = false;
        Memo1->Lines->Add(L"Не могу подключиться к серверу.");
    }

    this->CheckBox1->Checked = state;
}

void __fastcall TForm3::CheckBox1Click(TObject *Sender)
{
    this->Timer1->Enabled = this->CheckBox1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Timer1Timer(TObject *Sender)
{
    try
    {
           IdTCPClient1->Connect();
           IdTCPClient1->IOHandler->WriteLn("Hello");
           UnicodeString LLine = IdTCPClient1->IOHandler->ReadLn();
           Memo1->Lines->Add(L"Server says: " + LLine);
           TByteDynArray a;
           a.set_length(66);
           IdTCPClient1->IOHandler->ReadBytes(a,66,false);
           unsigned char* byte = (unsigned char*)&a[0];
           int* tmp = (int*)byte;
           float* f = (float*)&tmp[7];

            Label5->Caption = FormatFloat("000.00  mm", f[0]);
            Label6->Caption = FormatFloat("000.00  mm", f[1]);
            Label7->Caption = FormatFloat("000.00  mm", f[2]);
            Label8->Caption = FormatFloat("000.00  grad",f[5]);
            Label10->Caption = FormatFloat("000.00", f[3]) + L":" + FormatFloat("000.00", f[4]);



           IdTCPClient1->Disconnect();
    }
    catch(Exception& e)
    {
        Memo1->Lines->Add(L"Не могу подключиться к серверу по причине: " + e.Message);
        this->Timer1->Enabled = false;
        this->CheckBox1->Checked = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
   IdTCPClient1->Host = L"127.0.0.1";
   IdTCPClient1->Port = 6000;
}
//---------------------------------------------------------------------------

