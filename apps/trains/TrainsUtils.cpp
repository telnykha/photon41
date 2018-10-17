//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "TrainsUtils.h"
//---------------------------------------------------------------------------

TTrainsAnalysisEngine::TTrainsAnalysisEngine()
{
    m_trains = NULL;
    m_target = NULL;
}

TTrainsAnalysisEngine::~TTrainsAnalysisEngine()
{
    Reset();
}

bool __fastcall TTrainsAnalysisEngine::Init(TVAInitParams* trains, TVAInitParams* target)
{
      Reset();

      m_trains = trainsInit(trains->Zones[0].Rect, trains->EventSens, 0);
      m_target = trainsTargetInit(*target);
}

bool __fastcall TTrainsAnalysisEngine::Process(awpImage* img)
{
    return false;
}

bool __fastcall TTrainsAnalysisEngine::CreateModel(awpImage* img)
{
    if (m_target == NULL)
    {
        ShowMessage("Не могу создать модель. Модуль не инициализирован.");
        return false;
    }

    int res = trainsTargetCreate(m_target, (unsigned char*)img->pPixels, img->sSizeX, img->sSizeY, img->bChannels);
    if (res != VA_OK)
    {
        ShowMessage("Не могу создать модель.");
    }

    return res == VA_OK;
}


void __fastcall TTrainsAnalysisEngine::Reset()
{
    if (m_trains != NULL)
	    trainsClose(m_trains);
    if (m_target != NULL)
	    trainsTargetClose(m_target);
}

#pragma package(smart_init)
