//---------------------------------------------------------------------------
#pragma hdrstop
#include "awpipl.h"
#include "PhSelectRectTool.h"
//---------------------------------------------------------------------------
__fastcall TPhSelRectTool::TPhSelRectTool(TComponent* Owner):TPhImageTool(Owner)
{

   Pressed = false;
   this->m_numCols = 1;//aImage->SelCols;
   this->m_numRows = 1;//aImage->SelRows;
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
      FSelRect.Left = AWP_MIN(X, FSelRect.Left);
      FSelRect.Top  = AWP_MIN(Y, FSelRect.Top);
      FSelRect.Right = AWP_MAX(X, FSelRect.Right);
      FSelRect.Bottom = AWP_MAX(Y, FSelRect.Bottom);

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

   float w = FSelRect.Width() / this->m_numCols;
   for (int i = 1; i < this->m_numCols; i++)
   {
      int x,y;
      x = FSelRect.left + i*w;
      y = FSelRect.top;
      m_pImage->Canvas->MoveTo(x,y);
      y = FSelRect.bottom;
      m_pImage->Canvas->LineTo(x,y);
   }


   float h = FSelRect.Height() / this->m_numRows;
   for (int i = 1; i < this->m_numRows; i++)
   {
      int x,y;
      x = FSelRect.left;
      y = FSelRect.top + i*h;
      m_pImage->Canvas->MoveTo(x,y);
      x = FSelRect.right;
      m_pImage->Canvas->LineTo(x,y);
   }

   m_pImage->Canvas->Pen->Style = style;
   m_pImage->Canvas->Pen->Color = color;
   m_pImage->Canvas->Pen->Mode = mode;
}
void TPhSelRectTool::Reset()
{
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
