//---------------------------------------------------------------------------

#pragma hdrstop

#include "PhMediaSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TPhMediaSource::TPhMediaSource(TPhImage* display)
{
    this->m_pImage = display;
    m_CurrentFrame = 0;
    m_NumFrames    = 0;
}
