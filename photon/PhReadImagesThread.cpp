//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "PhReadImagesThread.h"
#include "DIBImage41.h"
#pragma package(smart_init)

static awpImage* _awpFitImage(awpRect rect, awpImage* img)
{
	int W = rect.right - rect.left;
	int H = rect.bottom - rect.top;

	double ar1 = (double) W / (double) H;
	double ar2 = (double) img->sSizeX / (double)img->sSizeY;

	awpImage* result = NULL;
	awpCreateImage(&result, W, H, img->bChannels, AWP_BYTE);



	if (result != NULL)
	{
	  int sx = 0;
	  int sy = 0;
	  int w  = img->sSizeX;
	  int h  = img->sSizeY;
	  int w1, h1;
	  double alfa = 1;

	  if (ar1 > ar2)
	  {
		 h1 = H;
		 alfa = (double)H/(double)h;
		 w1 = floor(alfa*w );
		 sx = (W - w1) /2;
		 if (sx < 0) sx = 0;
		 sy = 0;
	  }
	  else
	  {
		w1 = W;
		alfa = (double)W / (double)w;
		h1 = floor((double)h*alfa );
		sx = 0;
		sy = (H-h1) /2;
		if (sy < 0) sy = 0;
	  }
	  awpPoint p;
	  p.X = sx;
	  p.Y = sy;
	  awpImage* dst = NULL;

	  awpCopyImage(img, &dst);
	  awpResizeBilinear(dst, w1, h1);

	  if (dst != NULL)
	  {
		awpPasteRect( dst, result,  p);
		_AWP_SAFE_RELEASE_(dst)
	  }
	  else
	  {
		_AWP_SAFE_RELEASE_(result)
	  }

	}
	return result;
}


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TPhReadImagesThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TPhReadImagesThread::TPhReadImagesThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	this->m_names = new TStringList();
    m_tmbWidth  = 128;
    m_tmbHeight = 128;

}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::Execute()
{
	//---- Place thread code here ----
    TDIBImage* dib = new TDIBImage();

    awpRect rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = m_tmbWidth;
    rect.bottom = m_tmbHeight;

   int imgCount =  floor(sqrt((float)this->m_names->Count) + 0.5);
   int imgWidth  = m_tmbWidth*imgCount;
   int imgHeight = m_tmbHeight*imgCount;
   awpImage* result = NULL;
   awpCreateImage(&result, imgWidth, imgHeight, 3, AWP_BYTE);
   int num = 0;
    for (int i = 0; i < this->m_names->Count; i++)
    {
        //
        try
        {
	        dib->LoadFromFile(m_names->Strings[i]);
            awpImage* tmp = NULL;
            dib->GetAWPImage(&tmp);
            if (tmp != NULL)
            {
                awpImage* fit = _awpFitImage(rect, tmp);
                if (fit != NULL)
                {
					 awpPoint p;
					 p.Y = (num / imgCount)*m_tmbHeight;
					 p.X = (num % imgCount)*m_tmbWidth;

					 awpPasteRect(fit, result, p);

					_AWP_SAFE_RELEASE_(fit)
                    num++;
                }
                _AWP_SAFE_RELEASE_(tmp)
            }

        }
        catch(Exception& e)
        {
            break;
        }

    }
    delete dib;
    _AWP_SAFE_RELEASE_(m_mosaic)
    awpCopyImage(result, &m_mosaic);
    _AWP_SAFE_RELEASE_(result)
}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::SetNames(TStrings* names)
{
	m_names->Clear();
	m_names->SetStrings(names);

	this->Resume();
}

