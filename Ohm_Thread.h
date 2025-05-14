//---------------------------------------------------------------------------

#ifndef Ohm_ThreadH
#define Ohm_ThreadH

#include "Ohm_Win.h"


//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TOhm_Thread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TOhm_Thread(bool CreateSuspended);
	void __fastcall New_Form();
    void __fastcall Change_param();
    void __fastcall Plot();

	TOhm_Window *Form;

	long double Qtotal_1;
	long double Qtotal_2;
	long double R_1;
	long double R_2;
	long double L_1;
	long double L_2;
	int N_1;
	int N_2;
	long double dt;
	long double betta;
	long double ep;

	struct pair_of_cyl pair;

    long double Resist;
};
//---------------------------------------------------------------------------
#endif
