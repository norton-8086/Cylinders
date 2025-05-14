//---------------------------------------------------------------------------

#ifndef Grad_E_ThreadH
#define Grad_E_ThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include "Grad_Win.h"

//---------------------------------------------------------------------------
class TGrad_E_Thread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TGrad_E_Thread(bool CreateSuspended);
    void __fastcall New_Form();
	void __fastcall Change_param();
	void __fastcall Plot();

    TGrad_Form *Form;

	long double Qtotal_1;
	long double Qtotal_2;
	long double R_1;
	long double R_2;
	long double L_1;
	long double L_2;

	int N_1;
	int N_2;

    long double dt_now;
	long double dt;
	long double dt_stop;
    long double dt_change;

	long double betta;
	long double ep;
	long double z_far;
	long double dz_max;
	long double z_now;

	int steps;

    bool go_flag;

	struct pair_of_cyl pair;

	long double W_article;
	long double W_far;

    int frames;
};
//---------------------------------------------------------------------------
#endif
