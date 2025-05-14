//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Grad_Win.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGrad_Form *Grad_Form;
//---------------------------------------------------------------------------
__fastcall TGrad_Form::TGrad_Form(TComponent* Owner)
	: TForm(Owner), start_flag(false)
{
}
//---------------------------------------------------------------------------

void __fastcall TGrad_Form::StartClick(TObject *Sender)
{
    start_flag = true;
}
//---------------------------------------------------------------------------

void __fastcall TGrad_Form::StopClick(TObject *Sender)
{
    start_flag = false;
}
//---------------------------------------------------------------------------

