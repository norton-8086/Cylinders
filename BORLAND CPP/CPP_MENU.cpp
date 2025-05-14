//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "Grad_W_Thread.h"
#include "Grad_E_Thread.h"
#include "Grad_E_conserv_Thread.h"
#include "Grad_Fi_Thread.h"
#include "La_Grange_W.h"

#include "Ohm_Thread.h"

#include "CPP_MENU.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMENU *MENU;
//---------------------------------------------------------------------------
__fastcall TMENU::TMENU(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------



void __fastcall TMENU::Grad_WClick(TObject *Sender)
{
	TGrad_W_Thread *Grad_W_Thread = new TGrad_W_Thread(false);
}
//---------------------------------------------------------------------------

void __fastcall TMENU::OhmClick(TObject *Sender)
{
    TOhm_Thread *Ohm_Thread = new TOhm_Thread(false);
}
//---------------------------------------------------------------------------

void __fastcall TMENU::Grad_EClick(TObject *Sender)
{
	TGrad_E_Thread *Grad_E_Thread = new TGrad_E_Thread(false);
}
//---------------------------------------------------------------------------

void __fastcall TMENU::Grad_fiClick(TObject *Sender)
{
	TGrad_Fi_Thread *Grad_Fi_Thread = new TGrad_Fi_Thread(false);
}
//---------------------------------------------------------------------------

void __fastcall TMENU::SLAU_EClick(TObject *Sender)
{
    TGrad_E_conserv_Thread *Grad_E_conserv_Thread = new TGrad_E_conserv_Thread(false);
}
//---------------------------------------------------------------------------

void __fastcall TMENU::SLAU_fiClick(TObject *Sender)
{
    TLa_Grange_W_Thread *La_Grange_W_Thread = new TLa_Grange_W_Thread(false);
}
//---------------------------------------------------------------------------

