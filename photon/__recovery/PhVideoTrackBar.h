//---------------------------------------------------------------------------

#ifndef PhVideoTrackBarH
#define PhVideoTrackBarH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TPhVideoTrackBar : public TCustomControl
{
private:
	double m_pos;
	double m_duration;
    bool   m_mouse_down;
protected:

	virtual void __fastcall     Paint(void);
	DYNAMIC void __fastcall     Resize(void);
	DYNAMIC void __fastcall     MouseDown(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseMove( TShiftState Shift, Integer X, Integer Y);
	DYNAMIC void __fastcall     MouseUp(TMouseButton Button,  TShiftState Shift, Integer X, Integer Y);

public:
	__fastcall TPhVideoTrackBar(TComponent* Owner);
__published:
};
//---------------------------------------------------------------------------
#endif
