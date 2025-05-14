//---------------------------------------------------------------------------

#ifndef GAUSS_W_ThreadH
#define GAUSS_W_ThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TGAUSS_W_Thread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TGAUSS_W_Thread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
