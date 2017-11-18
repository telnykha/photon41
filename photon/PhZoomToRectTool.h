//---------------------------------------------------------------------------

#ifndef PhZoomToRectToolH
#define PhZoomToRectToolH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "PhImageTool.h"
//---------------------------------------------------------------------------
class PACKAGE TPhZoomToRectTool : public TPhImageTool
{
private:
    TRect SelRect;
    void DrawSelRect();
    bool Pressed;
public:
    __fastcall TPhZoomToRectTool(TComponent* Owner);
    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
    virtual void Reset();
};
#endif
