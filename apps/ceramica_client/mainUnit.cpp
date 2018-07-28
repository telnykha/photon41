//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

extern "C"
{
    #pragma link "awpipl2b.lib"
    #pragma link "JPEGLIB.lib"
}
    #pragma link "awplflibb.lib"

TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
    m_buffer = new TLFBuffer(32, 0);
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
           IdTCPClient1->Disconnect();

           unsigned char* byte = (unsigned char*)&a[0];
           int* tmp = (int*)byte;
           float* f = (float*)&tmp[7];

            Label5->Caption = FormatFloat("000.00  mm", f[0]);
            Label6->Caption = FormatFloat("000.00  mm", f[1]);
            Label7->Caption = FormatFloat("000.00  mm", f[2]);
            Label8->Caption = FormatFloat("000.00  grad",f[5]);
            Label10->Caption = FormatFloat("000.00", f[3]) + L":" + FormatFloat("000.00", f[4]);
            m_buffer->Push(f[0]);
            Series1->Clear();
            for (int i = 0; i < m_buffer->GetSize(); i++)
                Series1->Add(m_buffer->GetValue(i));
    }
    catch(Exception& e)
    {
        Memo1->Lines->Add(L"Не могу подключиться к серверу по причине: " + e.Message);
        this->Timer1->Enabled = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
     delete m_buffer;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
    if (!this->Timer1->Enabled)
    {
       UnicodeString ipAddr = L"";
       ipAddr += Edit1->Text;
       ipAddr += L".";
       ipAddr += Edit2->Text;
       ipAddr += L".";
       ipAddr += Edit3->Text;
       ipAddr += L".";
       ipAddr += Edit4->Text;

       IdTCPClient1->Host = ipAddr;
       IdTCPClient1->Port = this->SpinEdit3->Value;
       this->Timer1->Enabled = true;
    }
    else
       this->Timer1->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ApplicationEvents1Idle(TObject *Sender, bool &Done)
{
    this->GroupBox2->Enabled = !this->Timer1->Enabled;
    if (this->Timer1->Enabled)
        this->Button1->Caption = "Отключиться";
    else
        this->Button1->Caption = "Подключиться";
}
//---------------------------------------------------------------------------

