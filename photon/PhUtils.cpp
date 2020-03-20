//---------------------------------------------------------------------------
#include "PhUtils.h"
#include "System.SysUtils.hpp"
#include "Dialogs.hpp"
#pragma hdrstop
//---------------------------------------------------------------------------
static UnicodeString _ExtractFileNameWithoutExt(UnicodeString str)
{
	UnicodeString result = ExtractFileName(str);
	return ChangeFileExt(result, L"");
}
//---------------------------------------------------------------------------
static UnicodeString _makeName(int value, UnicodeString str)
{
	UnicodeString result = str;
	String dir  = ExtractFileDir(result);
	String name = _ExtractFileNameWithoutExt(result);

	int pos1 = name.Pos(L")");
	if (pos1 != 0)
	{
	  int pos2 = name.Pos(L" (");
	  if (pos2 != 0)
	  {
		name = name.SubString(0, pos2);
	  }

	}

	String ext = ExtractFileExt(result);
	result = dir + L"\\" + name;
	result += L" (";
	result += IntToStr(value);
	result += L")";
	result += ext;
	return result;
}
//---------------------------------------------------------------------------
UnicodeString MakeNewFileName(UnicodeString strFileName)
{
	UnicodeString result = strFileName;
	int pos1 = result.Pos(L").");
	if (pos1 != 0)
	{
	  int pos2 = result.Pos(L" (");
	  if (pos2 != 0)
	  {
		 UnicodeString str = result.SubString(pos2+2, pos1-pos2-2);
		 //ShowMessage(str);
		 int value = StrToInt(str);
		 do
		 {
			value++;
			result = _makeName(value, strFileName);
			if (!FileExists(result, true))
				break;
		 }
		 while(true);
	  }
	}
	else
	   result = _makeName(1, strFileName);
	return result;
}

#pragma package(smart_init)
