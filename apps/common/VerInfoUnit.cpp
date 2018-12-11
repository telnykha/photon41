//---------------------------------------------------------------------------
#pragma hdrstop

#include "VerInfoUnit.h"
#include <TypInfo.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TVersionInfo::TVersionInfo(TComponent* Owner) : TComponent(Owner)
{
  SetVersionInfo();
}

UnicodeString  __fastcall TVersionInfo::GetCompanyName()
{
   return  GetVersionInfo(vtCompanyName);
}
UnicodeString  __fastcall TVersionInfo::GetFileDescription()
{
   return  GetVersionInfo(vtFileDescription);
}
UnicodeString  __fastcall TVersionInfo::GetFileVersion()
{
  return  GetVersionInfo(vtFileVersion);
}
UnicodeString  __fastcall TVersionInfo::GetInternalName()
{
  return   GetVersionInfo(vtInternalName);
}
UnicodeString  __fastcall TVersionInfo::GetLegalCopyright()
{
   return  GetVersionInfo(vtLegalCopyright);
}
UnicodeString  __fastcall TVersionInfo::GetLegalTradeMark()
{
  return  GetVersionInfo(vtLegalTradeMark);
}
UnicodeString  __fastcall TVersionInfo::GetOriginalFileName()
{
  return   GetVersionInfo(vtOriginalFileName);
}
UnicodeString  __fastcall TVersionInfo::GetProductName()
{
  return   GetVersionInfo(vtProductName);
}
UnicodeString  __fastcall TVersionInfo::GetProductVersion()
{
   return   GetVersionInfo(vtProductVersion);
}
UnicodeString  __fastcall TVersionInfo::GetComments()
{
  return   GetVersionInfo(vtComments);
}

UnicodeString TVersionInfo::GetVersionInfo( EVersionInfoType VersionType)
{
   return FVersionInfo[VersionType];
}
void  TVersionInfo::SetVersionInfo()
{
  UnicodeString sAppName = Application->ExeName;
  unsigned long  iAppSize = GetFileVersionInfoSize(sAppName.c_str(), &iAppSize);
  if (iAppSize > 0)
  {
    wchar_t* pcBuf = (wchar_t*)malloc(iAppSize*sizeof(wchar_t));
    GetFileVersionInfo(sAppName.c_str(), 0, iAppSize, pcBuf);

    for (int i = 0; i < 10; i++)
    {
      AnsiString sVersionType = GetEnumName(__delphirtti(EVersionInfoType), i);
      sVersionType = sVersionType.SubString(3,sVersionType.Length());
	  UnicodeString subBlock = L"StringFileInfo\\040904E4\\";
      subBlock += sVersionType;
      wchar_t* pcValue;
      unsigned int iLenOfValue = 0;
      if (VerQueryValue(pcBuf, subBlock.c_str(), &((void*)pcValue), &iLenOfValue))
        FVersionInfo[i] = pcValue;
    }
    free(pcBuf);
  }
}
