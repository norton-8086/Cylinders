//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Ohm_Win.cpp", Ohm_Window);
USEFORM("CPP_MENU.cpp", MENU);
USEFORM("Grad_Win.cpp", Grad_Form);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TMENU), &MENU);
		Application->CreateForm(__classid(TGrad_Form), &Grad_Form);
		Application->CreateForm(__classid(TOhm_Window), &Ohm_Window);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
