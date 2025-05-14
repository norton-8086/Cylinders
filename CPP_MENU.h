//---------------------------------------------------------------------------

#ifndef CPP_MENUH
#define CPP_MENUH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TMENU : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TButton *Grad_W;
	TButton *Grad_fi;
	TButton *Grad_E;
	TButton *SLAU_fi;
	TButton *SLAU_E;
	TButton *Ohm;
	TEdit *Qtotal_1;
	TEdit *R_1;
	TEdit *L_1;
	TEdit *N_1;
	TEdit *Qtotal_2;
	TEdit *R_2;
	TEdit *L_2;
	TEdit *N_2;
	TLabel *Label10;
	void __fastcall Grad_WClick(TObject *Sender);
	void __fastcall OhmClick(TObject *Sender);
	void __fastcall Grad_EClick(TObject *Sender);
	void __fastcall Grad_fiClick(TObject *Sender);
	void __fastcall SLAU_EClick(TObject *Sender);
	void __fastcall SLAU_fiClick(TObject *Sender);

	private:
	__published:

	__fastcall TMENU(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMENU *MENU;
//---------------------------------------------------------------------------
#endif
