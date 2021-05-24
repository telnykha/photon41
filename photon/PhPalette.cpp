//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "PhPalette.h"
#include "awpipl.h"
#include "DIBImage41.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

const int c_nLeftMargin    = 8;
const int c_nBottomMargin  = 10;
const int c_nTopMargin     = 10;

static inline void ValidCtrCheck(TPhPalette *)
{
	new TPhPalette(NULL);
}
//---------------------------------------------------------------------------
__fastcall TPhPalette::TPhPalette(TComponent* Owner)
	: TCustomControl(Owner)
{
	m_color = clGray;
	m_textColor = clBlack;
	m_ticksVisible = true;
	m_min = 0;
	m_max =  65535;

	awpImage* img = NULL;
	awpCreateImage(&img, 64, 256, 3, AWP_BYTE);
	AWPBYTE* b = (AWPBYTE*)img->pPixels;
	for (int y = 0; y < 256; y++)
	{
		for (int x = 0; x < 64; x++)
		{
			b[y*3*64 + 3*x] = 255-y;
			b[y*3*64 + 3*x + 1] = 255-y;
			b[y*3*64 + 3*x + 2] = 255-y;
		}
	}

	TDIBImage* dib = new TDIBImage();
	dib->SetAWPImage(img);
	awpReleaseImage(&img);
	m_image = dib;

}
void __fastcall TPhPalette::DrawTicks(TCanvas* c)
{
	 if (!m_ticksVisible) {
         return;
	 }
	 c->Pen->Color = m_textColor;
     c->Font->Color = m_textColor;
	 int w = 4;
	 for (int i = 0; i <= 50; i++)
	 {
		if (i %10 == 0)
		{
			w = 10;
			c->TextOutW(PaletteRight() + 2 + w, Height-20 - i*(Height-20)/50, FormatFloat("0.00", m_min + i*(m_max-m_min) / 50));
		}
		else
			w = 4;
		c->MoveTo(PaletteRight(),     Height-10 - i*(Height -20) / 50);
		c->LineTo(PaletteRight() + w, Height-10 - i*(Height-20)/50);
	 }
}

int __fastcall TPhPalette::PaletteRight()
{
   int w = Width -10;
   if (m_ticksVisible) {
	   w -=  TextWidth();
	   w -= 5;
   }
   return  w;
}

void __fastcall TPhPalette::SetTicksVisible(bool value)
{
	m_ticksVisible = value;
    Paint();
}


int __fastcall TPhPalette::TextWidth()
{
	int wmin = Canvas->TextWidth(FormatFloat("0.00", m_min));
	int wmax = Canvas->TextWidth(FormatFloat("0.00", m_max));
	return wmin>wmax?wmin:wmax;
}

void __fastcall TPhPalette::SetColor(TColor color)
{
	m_color = color;
	Paint();
}

void __fastcall TPhPalette::SetTextColor(TColor color)
{
	m_textColor = color;
    Paint();
}

void __fastcall TPhPalette::SetMinValue(double value)
{
  if (value < m_max)
  {
	 m_min = value;
	 Paint();
  }
}
void __fastcall TPhPalette::SetMaxValue(double value)
{
	if (value > m_min) {
		m_max = value;
		Paint();
	}
}


void __fastcall     TPhPalette::Paint(void)
{
	int wtxt = TextWidth();
	TDIBImage* dib = (TDIBImage*)m_image;
	if (!dib->Empty)
	{
	   Graphics::TBitmap *bm = new Graphics::TBitmap();
	   bm->Width  = Width;
	   bm->Height = Height;
	   bm->Canvas->Brush->Color = m_color;
	   bm->Canvas->FillRect(ClientRect);
	   TRect src_r, dst_r;
	   dst_r.Left   = c_nLeftMargin;
	   dst_r.Right  = PaletteRight();
	   dst_r.Top    = c_nTopMargin;
	   dst_r.Bottom = Height-c_nBottomMargin;
	   src_r.init(0,0,64,256);
	   unsigned char* pDIB = dib->OpenPixels();

	   ::SetStretchBltMode(bm->Canvas->Handle, HALFTONE);
	   ::StretchDIBits(bm->Canvas->Handle,
		  dst_r.Left,
		  dst_r.Top,
		  dst_r.Width(),
		  dst_r.Height(),
		  src_r.Left,
		  src_r.Top,
		  src_r.Width(),
		  src_r.Height(),
		  pDIB,
		  &(dib->DIBInfo),
		  DIB_RGB_COLORS,
		  SRCCOPY);
	   dib->ClosePixels();
	   DrawTicks(bm->Canvas);
	   Canvas->CopyMode = cmSrcCopy;
	   Canvas->Draw(0,0,bm);
	   delete bm;
	}
}
//---------------------------------------------------------------------------
namespace Phpalette
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TPhPalette)};
		RegisterComponents(L"Photon", classes, 0);
	}
}
//---------------------------------------------------------------------------
