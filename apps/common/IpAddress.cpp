//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include <stdio.h>
#pragma hdrstop
#include "IpAddress.h"
//---------------------------------------------------------------------------
const char* GetMyIpAddressLocal()
{
    WSAData wsaData;
    AnsiString _ansi = "";
    char ac[80];
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
        return "";


    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR)
    {
		WSACleanup();
	    return _ansi.c_str();
    }

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0)
    {
		WSACleanup();
	    return _ansi.c_str();
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i)
    {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        _ansi += inet_ntoa(addr);
        _ansi += "  ";
    }

	WSACleanup();
    return _ansi.c_str();
}

int GetNumMyIpAddressLocal()
{
    WSAData wsaData;
    char ac[80];
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
        return 0;


    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR)
    {
		WSACleanup();
	    return 0;
    }

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0)
    {
		WSACleanup();
	    return 0;
    }
    int count = 0;
    for (int i = 0; phe->h_addr_list[i] != 0; ++i)
    {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        count++;
    }

	WSACleanup();
    return count;
}

void GetMyIpAddressList(TStringList* list)
{
    list->Clear();

    WSAData wsaData;
    AnsiString _ansi = "";
    char ac[80];
    if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
        return;

    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR)
    {
		WSACleanup();
	    return;
    }

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0)
    {
		WSACleanup();
	    return;
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i)
    {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        _ansi = inet_ntoa(addr);
        list->Add(_ansi.c_str());
    }

	WSACleanup();
}



#pragma package(smart_init)
