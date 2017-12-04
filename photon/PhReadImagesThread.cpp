//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "PhReadImagesThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TPhReadImagesThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TPhReadImagesThread::TPhReadImagesThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	this->m_names = new TStringList();
}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::Execute()
{
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::SetNames(TStrings* names)
{
	m_names->Clear();
	m_names->SetStrings(names);

	Resume();
}
