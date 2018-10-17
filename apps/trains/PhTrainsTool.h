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
    TVAPoint m_vertex[8];
    int      m_edit_vertex;
    double _2D_Dist(double x1,double y1,double x2,double y2);
    void __fastcall SetVertex(TVAPoint p, int idx);
    TVAPoint __fastcall GetVAPoint(TPoint p);
    TNotifyEvent m_OnChange;
protected:

    void __fastcall SetModelRect(TVARect rect);
    void __fastcall SetNumberRect(TVARect rect);

    bool __fastcall IsPointNearVertex(TPoint p, bool edit = false);
public:
    __fastcall TPhTrainsTool(TComponent* Owner);
   virtual __fastcall ~TPhTrainsTool();

    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
	virtual void Reset();

    __property TVARect modelRect = {read = m_modelRect, write = SetModelRect};
    __property TVARect numberRect = {read = m_numberRect, write = SetNumberRect};
    __property TNotifyEvent OnChange= {read = m_OnChange, write = m_OnChange};
};

#endif
