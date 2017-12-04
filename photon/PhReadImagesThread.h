//---------------------------------------------------------------------------

#ifndef PhReadImagesThreadH
#define PhReadImagesThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TPhReadImagesThread : public TThread
{
private:
    TStrings* m_names;
protected:
	void __fastcall Execute();
public:
	__fastcall TPhReadImagesThread(bool CreateSuspended);
	void __fastcall SetNames(TStrings* names);
};
//---------------------------------------------------------------------------
#endif
