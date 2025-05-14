//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ohm_Win.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOhm_Window *Ohm_Window;
//---------------------------------------------------------------------------
__fastcall TOhm_Window::TOhm_Window(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TOhm_Window::StartClick(TObject *Sender)
{
    start_flag = true;
}
//---------------------------------------------------------------------------

