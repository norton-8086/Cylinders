//---------------------------------------------------------------------------

#ifndef Ohm_WinH
#define Ohm_WinH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOhm_Window : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TEdit *Qtotal_1;
	TEdit *R_1;
	TEdit *L_1;
	TEdit *N_1;
	TEdit *Qtotal_2;
	TEdit *R_2;
	TEdit *L_2;
	TEdit *N_2;
	TEdit *W_now;
	TEdit *Dev_Fi;
	TEdit *Dev_E;
	TEdit *W_article;
	TEdit *Q_2_now;
	TEdit *Fi_1_now;
	TEdit *Fi_2_now;
	TEdit *Q_1_now;
	TEdit *Command;
	TButton *Start;
	TListBox *Q_1;
	TListBox *Fi_1;
	TListBox *Q_2;
	TListBox *Fi_2;
	TLabel *Label1;
	TEdit *Resist;
	void __fastcall StartClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOhm_Window(TComponent* Owner);
    bool start_flag;
};
//---------------------------------------------------------------------------
extern PACKAGE TOhm_Window *Ohm_Window;
//---------------------------------------------------------------------------
#endif
