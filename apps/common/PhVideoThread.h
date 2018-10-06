//---------------------------------------------------------------------------

#ifndef PhVideoThreadH
#define PhVideoThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TPhVideoThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TPhVideoThread(bool CreateSuspended);
};
//---------------------------------------------------------------------------
#endif
