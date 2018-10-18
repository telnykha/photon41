//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "TrainsUtils.h"
#include "trainsMainFormUnit.h"
//---------------------------------------------------------------------------

TTrainsAnalysisEngine::TTrainsAnalysisEngine()
{
    m_trains = NULL;
    m_target = NULL;
    m_process = NULL;
    m_pImage = NULL;
    mutex = new TMutex(true);
    count = 0;
    m_old_norm = -1;
}

TTrainsAnalysisEngine::~TTrainsAnalysisEngine()
{
    Reset();
    delete mutex;
}

bool __fastcall TTrainsAnalysisEngine::Init(TVAInitParams* trains, TVAInitParams* target)
{
      Reset();
      m_trains = trainsInit(trains->Zones[0].Rect, trains->EventSens, 0);
      m_target = trainsTargetInit(*target);

      m_process = new TTrainProcess(true);
      m_process->m_engine = this;
      m_process->Start();
}

bool __fastcall TTrainsAnalysisEngine::Process(awpImage* img)
{
    if (img != NULL && m_target != NULL && mainForm->Mode != NULL && mainForm->Mode == mainForm->modeAnalysisAction)
    {
            double d;
            bool b;
            trainsTargetProcess(m_target, (unsigned char*)img->pPixels, img->sSizeX, img->sSizeY, img->bChannels, &d, &b);
            m_norm = d;
            return true;
    }

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
    if (m_process != NULL)
    {
        m_process->Terminate();
    }


    if (m_trains != NULL)
	    trainsClose(m_trains);
    if (m_target != NULL)
	    trainsTargetClose(m_target);
    m_old_norm = -1;
    count = 0;
}


awpImage* TTrainsAnalysisEngine::GetImage()
{
    if (m_pImage == NULL)
    	return NULL;
    mutex->Acquire();
    awpImage* res = NULL;
    awpCopyImage(m_pImage, &res);
    _AWP_SAFE_RELEASE_(m_pImage)
    mutex->Release();
    return res;
}

void TTrainsAnalysisEngine::SetImage(awpImage* image)
{
    mutex->Acquire();
    awpCopyImage(image, &m_pImage);
    mutex->Release();

}

void __fastcall TTrainsAnalysisEngine::UpdateStatus()
{
    mainForm->Label1->Caption = L"ncc = " +FloatToStr(m_norm);
    mainForm->Panel2->Color = m_norm > 0.72 ? clLime : clRed;
    if (m_old_norm != -1)
    {
        if (m_old_norm < 0.72 && m_norm > 0.72)
            count++;
    }
    mainForm->Label2->Caption = IntToStr(count);
    m_old_norm = m_norm;
}


#pragma package(smart_init)
