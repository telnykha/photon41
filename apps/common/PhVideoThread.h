//---------------------------------------------------------------------------

#ifndef PhVideoThreadH
#define PhVideoThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "PhVideo.h"
//---------------------------------------------------------------------------
class TPhVideoThread : public TThread
{
private:
	TPhVideoSource* m_source;
	bool      		m_cancel;
	void __fastcall DecodeHelper();
protected:
	void __fastcall Execute();
public:
	__fastcall TPhVideoThread(bool CreateSuspended, TPhVideoSource* s);

};
//---------------------------------------------------------------------------
#endif
