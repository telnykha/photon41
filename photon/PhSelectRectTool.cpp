//---------------------------------------------------------------------------
#pragma hdrstop
#include "awpipl.h"
#include "PhSelectRectTool.h"
//---------------------------------------------------------------------------
__fastcall TPhSelRectTool::TPhSelRectTool(TComponent* Owner):TPhImageTool(Owner)
{

   Pressed = false;
   vertex = 0;
   m_strToolName = L"SELECT RECT";
}
void TPhSelRectTool::Draw(TCanvas* Canvas)
{
}
void TPhSelRectTool::MouseDown(int X, int Y, TMouseButton Button)
{
   if (m_pImage == NULL)
        return;

   if (Button == mbLeft)
   {
      m_pImage->FSelRect.Top    = 0;
      m_pImage->FSelRect.Bottom = 0;
      m_pImage->FSelRect.Left   = 0;
      m_pImage->FSelRect.Right  = 0;
      m_pImage->Paint();
      FSelRect.Top    = Y;
      FSelRect.Bottom = Y;
      FSelRect.Left   = X;
      FSelRect.Right  = X;
      m_x = X;
      m_y = Y;
      m_pImage->FSelRect = m_pImage->GetImageRect(FSelRect);
      Pressed        = true;
   }
}

void TPhSelRectTool::MouseUp(int X, int Y, TMouseButton Button)
{
   if (m_pImage == NULL)
        return;

   if (Button == mbLeft)
   {
      FSelRect.Left = AWP_MIN(X, FSelRect.Left);
      FSelRect.Top  = AWP_MIN(Y, FSelRect.Top);
      FSelRect.Right = AWP_MAX(X, FSelRect.Right);
      FSelRect.Bottom = AWP_MAX(Y, FSelRect.Bottom);

      Pressed = false;

      m_pImage->SetSelRect(m_pImage->GetImageRect(FSelRect));
      m_pImage->Paint();
   }
}
void TPhSelRectTool::MouseMove(int X, int Y, TShiftState Shift)
{
   if (m_pImage == NULL)
        return;

   if (Pressed)
   {
      DrawSelRect();

      this->SetVertexes(m_x, X, m_y, Y);

      DrawSelRect();
   }
}

void TPhSelRectTool::DrawSelRect()
{
   if (m_pImage == NULL)
        return;

   TPenStyle style = m_pImage->Canvas->Pen->Style;
   TColor color = m_pImage->Canvas->Pen->Color;
   TPenMode mode = m_pImage->Canvas->Pen->Mode;

   m_pImage->Canvas->Pen->Style = psDot;
   m_pImage->Canvas->Pen->Color = clBlack;
   m_pImage->Canvas->Pen->Mode = pmNotXor;

   m_pImage->Canvas->MoveTo(FSelRect.Left, FSelRect.Top);
   m_pImage->Canvas->LineTo(FSelRect.Right, FSelRect.Top);
   m_pImage->Canvas->LineTo(FSelRect.Right, FSelRect.Bottom);
   m_pImage->Canvas->LineTo(FSelRect.Left, FSelRect.Bottom);
   m_pImage->Canvas->LineTo(FSelRect.Left, FSelRect.Top);

   m_pImage->Canvas->Pen->Style = style;
   m_pImage->Canvas->Pen->Color = color;
   m_pImage->Canvas->Pen->Mode = mode;
}
void TPhSelRectTool::Reset()
{
}

void __fastcall TPhSelRectTool::SetVertexes(int x1, int x2, int y1, int y2)
{
    FSelRect.Left  = AWP_MIN(x1,x2);
    FSelRect.Right = AWP_MAX(x1,x2);
    FSelRect.Top   = AWP_MIN(y1,y2);
    FSelRect.Bottom = AWP_MAX(y1,y2);
}

//---------------------------------------------------------------------------
namespace Phselectrecttool
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TPhSelRectTool)};
		RegisterComponents(L"Photon", classes, 0);
	}
}

#pragma package(smart_init)
