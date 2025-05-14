//---------------------------------------------------------------------------

#ifndef Grad_WinH
#define Grad_WinH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGrad_Form : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Qtotal_1;
	TEdit *R_1;
	TEdit *L_1;
	TEdit *N_1;
	TEdit *Qtotal_2;
	TEdit *R_2;
	TEdit *L_2;
	TEdit *N_2;
	TLabel *Label1;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *dt;
	TEdit *betta;
	TEdit *ep;
	TLabel *Label11;
	TEdit *W_now;
	TEdit *Dev_Fi;
	TEdit *Dev_E;
	TLabel *Label12;
	TEdit *W_article;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TEdit *Q_2_now;
	TEdit *Fi_1_now;
	TEdit *Fi_2_now;
	TLabel *Label16;
	TEdit *Q_1_now;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TButton *Start;
	TButton *Stop;
	TEdit *W_far;
	TEdit *dz;
	TEdit *z_now;
	TLabel *Label20;
	TLabel *Label21;
	TEdit *Steps;
	TLabel *Label22;
	TEdit *dt_stop;
	TLabel *Label23;
	TEdit *z_far;
	TLabel *Label24;
	TEdit *dt_change;
	TImage *Image;
	TEdit *Frame;
	TLabel *Label25;
	TListBox *Q_1;
	TListBox *Fi_1;
	TListBox *Q_2;
	TListBox *Fi_2;
	void __fastcall StartClick(TObject *Sender);
	void __fastcall StopClick(TObject *Sender);
private:

public:		// User declarations
	__fastcall TGrad_Form(TComponent* Owner);
    bool start_flag;
};
//---------------------------------------------------------------------------
extern PACKAGE TGrad_Form *Grad_Form;
//---------------------------------------------------------------------------
#endif
