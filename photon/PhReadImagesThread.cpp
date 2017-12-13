//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "PhReadImagesThread.h"
#include "DIBImage41.h"
#include "PhFrames.h"
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
    m_items = NULL;
    m_tmbWidth  = 128;
    m_tmbHeight = 128;
}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::Execute()
{
    if (m_items == NULL)
        return;
	//---- Place thread code here ----
    TDIBImage* dib = new TDIBImage();

    awpRect rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = m_tmbWidth;
    rect.bottom = m_tmbHeight;

   int imgCount =  floor(sqrt((float)this->m_items->Count) + 0.5);
   int imgWidth  = m_tmbWidth*imgCount;
   int imgHeight = m_tmbHeight*imgCount;
   awpImage* result = NULL;
   awpCreateImage(&result, imgWidth, imgHeight, 3, AWP_BYTE);
   int num = 0;
    for (int i = 0; i < m_items->Count; i++)
    {
        //
        if (this->Terminated)
            break;
        try
        {
            SFrameItem* item = (SFrameItem*)(m_items->Items[i]);
	        dib->LoadFromFile(item->strFileName);
            awpImage* tmp = NULL;
            dib->GetAWPImage(&tmp);

            item->width = tmp->sSizeX;
            item->height = tmp->sSizeY;

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

            //todo: if the thread cannot read the image
            //remove item about it.

            continue;
        }
     }
    delete dib;
    _AWP_SAFE_RELEASE_(m_mosaic)
    awpCopyImage(result, &m_mosaic);
    _AWP_SAFE_RELEASE_(result)
}
//---------------------------------------------------------------------------
void __fastcall TPhReadImagesThread::SetNames(TList* names)
{
    m_items = names;
}

__fastcall TPhCopyImagesThread::TPhCopyImagesThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
    m_items = NULL;
    m_FolderName = L"";
    m_move = false;
}
void __fastcall TPhCopyImagesThread::SetNames(TList* names, const LPWSTR lpwFolderName, bool move)
{
    m_items = names;
    m_FolderName = lpwFolderName;
    m_move = move;
}
void __fastcall TPhCopyImagesThread::Execute()
{
    if (m_items == NULL)
        return;
    if (!DirectoryExists(m_FolderName))
        return;

    for (int i = m_items->Count - 1; i >= 0 ; i--)
    {
        //
        if (this->Terminated)
            break;
        try
        {
            SFrameItem* item = (SFrameItem*)(m_items->Items[i]);
            if (!item->selected)
                continue;
            AnsiString strSrcFile = item->strFileName;
            AnsiString strDstFile = m_FolderName;
            strDstFile += ExtractFileName(strSrcFile);
            if (!CopyFile(strSrcFile.c_str(), strDstFile.c_str(), false))
            {
                //todo: add error status
//                ShowMessage(L"Cannot copy files to target folder: " + FolderName);
            }
            if (m_move)
            {
                DeleteFile(item->strFileName);
                m_items->Delete(i);
            }
        }
        catch(Exception& e)
        {

            //todo: if the thread cannot read the image
            //remove item about it.

            continue;
        }
     }
}
