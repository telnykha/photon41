//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("resizeFormUnit.cpp", resizeForm);
USEFORM("rotateFormUnit.cpp", rotateForm);
USEFORM("convertFormUnit.cpp", convertForm);
USEFORM("copyFormUnit.cpp", copyForm);
USEFORM("mainUnit.cpp", mainForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Carbon");
		Application->CreateForm(__classid(TmainForm), &mainForm);
		Application->CreateForm(__classid(TcopyForm), &copyForm);
		Application->CreateForm(__classid(TresizeForm), &resizeForm);
		Application->CreateForm(__classid(TrotateForm), &rotateForm);
		Application->CreateForm(__classid(TconvertForm), &convertForm);
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
