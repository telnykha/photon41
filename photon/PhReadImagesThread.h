//---------------------------------------------------------------------------

#ifndef PhReadImagesThreadH
#define PhReadImagesThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "awpipl.h"
//---------------------------------------------------------------------------
// This thread reads the images from TList and creates mosaic
// with tmbWidth and  tmbHeight for each image
class TPhReadImagesThread : public TThread
{
private:
    TList*    m_items;
    awpImage* m_mosaic;
    int       m_tmbWidth;
    int       m_tmbHeight;
protected:
	void __fastcall Execute();
public:
	__fastcall TPhReadImagesThread(bool CreateSuspended);
	void __fastcall SetNames(TList* names);

    __property awpImage* Mosaic = {read = m_mosaic};
    __property int tmbWidth 	= {read = m_tmbWidth, write = m_tmbWidth};
    __property int tmbHeight    = {read = m_tmbHeight, write = m_tmbHeight};
};
//---------------------------------------------------------------------------
class TPhCopyImagesThread : public TThread
{
private:
    TList*    m_items;
    UnicodeString m_FolderName;
    bool      m_move;
protected:
	void __fastcall Execute();
public:
	__fastcall TPhCopyImagesThread(bool CreateSuspended);
	void __fastcall SetNames(TList* names, const LPWSTR lpwFolderName, bool move = false);
    __property bool Move = {read = m_move};
};
#endif
