//---------------------------------------------------------------------------
#ifndef PhPaletteH
#define PhPaletteH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>

//---------------------------------------------------------------------------
class PACKAGE TPhPalette : public TCustomControl
{
private:
	void*  m_image;
	double m_min;
	double m_max;
	TColor m_color;
	TColor m_textColor;
	bool   m_ticksVisible;

	int __fastcall PaletteRight();
	int __fastcall TextWidth();
protected:
	void __fastcall SetColor(TColor color);
	void __fastcall SetTextColor(TColor color);
	void __fastcall DrawTicks(TCanvas* c);
	void __fastcall SetMinValue(double value);
	void __fastcall SetMaxValue(double value);
	void __fastcall SetTicksVisible(bool value);

	virtual void __fastcall     Paint(void);
public:
	__fastcall TPhPalette(TComponent* Owner);
__published:
	__property Align;
	__property 	TColor Color = {read = m_color, write = SetColor};
	__property 	TColor TextColor = {read = m_textColor, write = SetTextColor};
	__property  double MinValue = {read = m_min, write = SetMinValue};
	__property  double MaxValue = {read = m_max, write = SetMaxValue};
	__property bool TicksVisible = {read = m_ticksVisible, write = SetTicksVisible};
};
//---------------------------------------------------------------------------
#endif
