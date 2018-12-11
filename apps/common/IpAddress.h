//---------------------------------------------------------------------------
#ifndef IpAddressH
#define IpAddressH
#include <vcl.h>
//---------------------------------------------------------------------------
int GetNumMyIpAddressLocal();
const char* GetMyIpAddressLocal();
void GetMyIpAddressList(TStringList* list);
#endif
