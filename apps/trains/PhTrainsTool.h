//---------------------------------------------------------------------------

#ifndef PhTrainsToolH
#define PhTrainsToolH
//---------------------------------------------------------------------------
#include "PhImageTool.h"
#include "va_common.h"

class PACKAGE TPhTrainsTool : public TPhImageTool
{
private:
    TVARect m_modelRect;
    TVARect m_numberRect;
protected:

    double __fastcall GetLenght();
public:
    __fastcall TPhTrainsTool(TComponent* Owner);
   virtual __fastcall ~TPhTrainsTool();

    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
	virtual void Reset();

    __property TVARect modelRect = {read = m_modelRect, write = m_modelRect};
    __property TVARect numberRect = {read = m_numberRect, write = m_numberRect};

};

#endif
