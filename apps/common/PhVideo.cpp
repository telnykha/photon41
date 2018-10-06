//---------------------------------------------------------------------------
#pragma hdrstop
#include "PhVideo.h"
#include "awpcvvideo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link  "awpcvvideo.lib"
TPhVideoSource::TPhVideoSource(TPhImage* display):TPhMediaSource(display)
{
    m_videoSource = NULL;
    m_pTimer = new TTimer(NULL);
    m_pTimer->Enabled = false;
    m_pTimer->Interval = 50;
    m_pTimer->OnTimer = TimerEventHandler;
    m_SourceStr = L"Видеофайл";
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
    First();
}
void  TPhVideoSource::Close()
{
   if (m_pImage != NULL)
   {
       Stop();
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
          m_pImage->SetImageData(img->sSizeX, img->sSizeY, img->bChannels, (unsigned char*)img->pPixels);
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
    return this->m_pTimer != NULL && this->m_pTimer->Enabled;
}

void  TPhVideoSource::Play()
{
    if (m_videoSource != NULL)
    {
        m_pTimer->Enabled = true;
    }
}

void  TPhVideoSource::Stop()
{
    this->m_pTimer->Enabled = false;
}

void __fastcall TPhVideoSource::TimerEventHandler(TObject *Sender)
{
   if (m_pImage != NULL && m_videoSource != NULL)
   {
      HCVVIDEO h = (HCVVIDEO)m_videoSource;
      awpImage* img = NULL;
      if (awpcvQueryImage(h, &img) == S_OK && img != NULL)
      {
          m_pImage->SetImageData(img->sSizeX, img->sSizeY, img->bChannels, (unsigned char*)img->pPixels);
           m_CurrentFrame++;
          awpcvFreeImage(img);
      }
      else
        Stop();
   }
}

