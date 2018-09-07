//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "PhVideoThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TPhVideoThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TPhVideoThread::TPhVideoThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TPhVideoThread::Execute()
{
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
