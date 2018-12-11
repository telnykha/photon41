//---------------------------------------------------------------------------

#pragma hdrstop

#include "PhSlideShow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define _CHECK_DISPLAY_ 	\
if (this->m_pImage == NULL) \
    return;                 \

TPhSlideShowSource::TPhSlideShowSource(TPhImage* display): TPhMediaSource(display)
{
    m_SourceName = L"Фотографии";
}
TPhSlideShowSource::~TPhSlideShowSource()
{

}

void TPhSlideShowSource::Open(TStrings* Names)
{
	_CHECK_DISPLAY_

    m_pImage->Init(Names);
}
void TPhSlideShowSource::Close()
{
	_CHECK_DISPLAY_
    m_pImage->Close();
}

void TPhSlideShowSource::First()
{
	_CHECK_DISPLAY_

    m_pImage->Frames->First();
}
void TPhSlideShowSource::Prev()
{
	_CHECK_DISPLAY_

    m_pImage->Frames->Prev();
}

void TPhSlideShowSource::Next()
{
	_CHECK_DISPLAY_

    m_pImage->Frames->Next();
}
void TPhSlideShowSource::Last()
{
	_CHECK_DISPLAY_

    m_pImage->Frames->Last();
}

void TPhSlideShowSource::Play()
{
	_CHECK_DISPLAY_

    m_pImage->SlideShow = true;
}
void TPhSlideShowSource::Stop()
{
	_CHECK_DISPLAY_

    m_pImage->SlideShow = false;
}

int __fastcall  TPhSlideShowSource::GetNumFrames()
{
    if (this->m_pImage == NULL)
        return 0;
    else
        return m_pImage->Frames->Count;
}
int __fastcall  TPhSlideShowSource::GetCurrentFrame()
{
    if (this->m_pImage == NULL)
        return 0;
    else
        return m_pImage->Frames->CurrentFrame;
}
void __fastcall TPhSlideShowSource::SetCurrentFrame(int frame)
{
	_CHECK_DISPLAY_

    m_pImage->Frames->GoFrame(frame);
}

bool __fastcall TPhSlideShowSource::GetIsPlaying()
{
    return m_pImage->SlideShow;
}
