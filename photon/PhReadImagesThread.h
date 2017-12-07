//---------------------------------------------------------------------------

#ifndef PhReadImagesThreadH
#define PhReadImagesThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "awpipl.h"
//---------------------------------------------------------------------------
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
#endif
