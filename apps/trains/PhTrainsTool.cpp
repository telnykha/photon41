//---------------------------------------------------------------------------

#pragma hdrstop

#include "PhTrainsTool.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TPhTrainsTool::TPhTrainsTool(TComponent* Owner): TPhImageTool(Owner)
{

}
__fastcall TPhTrainsTool::~TPhTrainsTool()
{

}

void TPhTrainsTool::Draw(TCanvas* Canvas)
{
    if (Canvas == NULL)
        return;
    int w = this->m_pImage->Bitmap->Width;
    int h = this->m_pImage->Bitmap->Height;

    int x1 = w*this->m_numberRect.LeftTop.X / 100.;
    int x2 = w*this->m_numberRect.RightBottom.X / 100.;
    int y1 = h*this->m_numberRect.LeftTop.Y / 100.;
    int y2 = h*this->m_numberRect.RightBottom.Y / 100.;

    TRect rect(x1,y1, x2, y2);
    TRect rect1 = this->m_pImage->GetScreenRect(rect);
    Canvas->Brush->Style = bsClear;
    Canvas->Pen->Color = clRed;
    Canvas->Rectangle(rect1);

    x1 = w*this->m_modelRect.LeftTop.X / 100.;
    x2 = w*this->m_modelRect.RightBottom.X / 100.;
    y1 = h*this->m_modelRect.LeftTop.Y / 100.;
    y2 = h*this->m_modelRect.RightBottom.Y / 100.;

    Canvas->Pen->Color = clLime;
    TRect rect2(x1,y1, x2, y2);
    TRect rect3 = this->m_pImage->GetScreenRect(rect2);
    Canvas->Rectangle(rect3);

}
void TPhTrainsTool::MouseDown(int X, int Y, TMouseButton Button)
{

}
void TPhTrainsTool::MouseUp(int X, int Y, TMouseButton Button)
{

}
void TPhTrainsTool::MouseMove(int X, int Y, TShiftState Shift)
{

}
void TPhTrainsTool::Reset()
{

}


