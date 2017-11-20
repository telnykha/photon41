//---------------------------------------------------------------------------
#ifndef PhSelectRectToolH
#define PhSelectRectToolH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "PhImageTool.h"
//---------------------------------------------------------------------------
// select rect tool
class PACKAGE TPhSelRectTool : public TPhImageTool
{
private:
    void DrawSelRect();
	bool Pressed;
    TRect FSelRect;
    int   m_numCols;
    int   m_numRows;
public:
    __fastcall TPhSelRectTool(TComponent* Owner);
    virtual void Draw(TCanvas* Canvas);
    virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
    virtual void MouseMove(int X, int Y, TShiftState Shift);
    virtual void Reset();

    __property int Cols ={read = m_numCols, write = m_numCols};
    __property int Rows ={read = m_numRows, write = m_numRows};

};
//---------------------------------------------------------------------------
#endif
