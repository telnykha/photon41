//---------------------------------------------------------------------------
#pragma hdrstop
#include "PhVideo.h"
#include "awpcvvideo.h"
#include "PhVideoThread.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link  "awpcvvideo.lib"
TPhVideoSource::TPhVideoSource(TPhImage* display):TPhMediaSource(display)
{
    m_videoSource = NULL;
	m_SourceStr = L"";
    m_SourceName = "Видеофайл";
    m_videoThread = NULL;
}
TPhVideoSource::~TPhVideoSource()
{
   if (m_videoSource != NULL)
			Close();
}

void  TPhVideoSource::Open(TStrings* Names)
{
	Close();
    AnsiString _ansi = Names->Strings[0];
    m_videoSource = awpcvConnect(_ansi.c_str());
    if (m_videoSource != NULL)
    {
        awpcvNumFrames((HCVVIDEO)m_videoSource, &m_NumFrames);
    }
    else
        return;
    this->m_SourceStr = Names->Strings[0];
	First();
    if (this->m_pImage->AfterOpen != NULL)
	    this->m_pImage->AfterOpen(NULL);

	this->m_videoThread = new TPhVideoThread(true, this);
	this->m_videoThread->FreeOnTerminate = true;
}
void  TPhVideoSource::Close()
{
   if (m_pImage != NULL)
   {
	   Stop();
       if (this->m_videoThread != NULL)
        this->m_videoThread->Terminate();

	   awpcvDisconnect((HCVVIDEO)m_videoSource);
	   m_CurrentFrame = 0;
   }
}

void  __fastcall TPhVideoSource::DecodePicture()
{
   if (m_pImage != NULL && m_videoSource != NULL)
   {
      HCVVIDEO h = (HCVVIDEO)m_videoSource;
      awpImage* img = NULL;
      if (awpcvQueryImagePos(h, &img, m_CurrentFrame) == S_OK && img != NULL)
      {
          awpImage* img1 = NULL;
          awpCopyImage(img, &img1);
          awpResize(img1, img1->sSizeX / 3, img1->sSizeY / 3);
		  m_pImage->SetImageData(img1->sSizeX, img1->sSizeY, img1->bChannels, (unsigned char*)img1->pPixels);
          awpReleaseImage(&img1);
          awpcvFreeImage(img);
      }
   }
}
void  TPhVideoSource::First()
{
   m_CurrentFrame = 0;
   DecodePicture();
}
void  TPhVideoSource::Prev()
{
   m_CurrentFrame--;
   if (m_CurrentFrame < 0)
    m_CurrentFrame = 0;
   DecodePicture();
}
void  TPhVideoSource::Next()
{
    m_CurrentFrame++;
    if (m_CurrentFrame >= m_NumFrames)
        m_CurrentFrame =  m_NumFrames-1;
   DecodePicture();
}

void  TPhVideoSource::Last()
{
    m_CurrentFrame =  m_NumFrames-1;
    DecodePicture();
}

int __fastcall TPhVideoSource::GetNumFrames()
{
    return m_NumFrames;
}
void  __fastcall TPhVideoSource::SetCurrentFrame(int frame)
{
    if (frame >=0 && frame < m_NumFrames)
      m_CurrentFrame = frame;
    DecodePicture();
}

int __fastcall  TPhVideoSource::GetCurrentFrame()
{
    return this->m_CurrentFrame;
}

bool __fastcall TPhVideoSource::GetIsPlaying()
{
	return this->m_videoThread != NULL && !this->m_videoThread->Suspended;
}

void  TPhVideoSource::Play()
{
    if (m_videoSource != NULL)
    {
	   // m_pTimer->Enabled = true;
	   this->m_videoThread->Resume();
	}
}

void  TPhVideoSource::Stop()
{
   //	this->m_pTimer->Enabled = false;
	if (this->m_videoThread != NULL)
	  this->m_videoThread->Suspend();
}

void __fastcall TPhVideoSource::TimerEventHandler(TObject *Sender)
{
   if (m_pImage != NULL && m_videoSource != NULL)
   {
	  HCVVIDEO h = (HCVVIDEO)m_videoSource;
	  awpImage* img = NULL;
	  if (awpcvQueryImage(h, &img) == S_OK && img != NULL)
	  {
          awpImage* img1 = NULL;
          awpCopyImage(img, &img1);
          awpResize(img1, img1->sSizeX / 3, img1->sSizeY / 3);

		  m_pImage->SetImageData(img1->sSizeX, img1->sSizeY, img1->bChannels, (unsigned char*)img1->pPixels);

          awpReleaseImage(&img1);
		  m_CurrentFrame++;
		  awpcvFreeImage(img);
	  }
	  else
		Stop();

	  Application->ProcessMessages();
   }
}

