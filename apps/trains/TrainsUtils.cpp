//---------------------------------------------------------------------------

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

}

bool __fastcall TTrainsAnalysisEngine::Init(TVAInitParams* trains, TVAInitParams* target)
{
      m_trains = trainsInit(trains->Zones[0].Rect, 0,0);
      m_target = trainsTargetInit(*target);
}

bool __fastcall TTrainsAnalysisEngine::Process(awpImage* img)
{
    return false;
}

void __fastcall TTrainsAnalysisEngine::Reset()
{
    trainsClose(m_trains);
    trainsTargetClose(m_target);
}

#pragma package(smart_init)
