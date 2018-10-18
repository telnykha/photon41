//---------------------------------------------------------------------------
#ifndef TrainsUtilsH
#define TrainsUtilsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include "trains.h"
#include "awpipl.h"
#include "_LF.h"
#include "TrainProcess.h"

class TTrainsAnalysisEngine
{
private:
    TRAINSHANDLE m_trains;
    TARGETHANDLE m_target;

    TVAInitParams m_trains_params;
    TVAInitParams m_target_params;

    TTrainProcess* m_process;
    awpImage* m_pImage;
   	TMutex*   mutex;
    double    m_norm;
    double    m_old_norm;
protected:
    int count;
public:

    TTrainsAnalysisEngine();
    ~TTrainsAnalysisEngine();

    bool __fastcall Init(TVAInitParams* trains, TVAInitParams* target);
    bool __fastcall Process(awpImage* img);
    void __fastcall Reset();
    bool __fastcall CreateModel(awpImage* img);

    awpImage* GetImage();
    void SetImage(awpImage* image);
public:
    void __fastcall UpdateStatus();
};
#endif
