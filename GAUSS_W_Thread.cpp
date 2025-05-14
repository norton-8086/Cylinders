//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "GAUSS_W_Thread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TGAUSS_W_Thread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TGAUSS_W_Thread::TGAUSS_W_Thread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TGAUSS_W_Thread::Execute()
{
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
