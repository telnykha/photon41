//---------------------------------------------------------------------------
#ifndef TrainsUtilsH
#define TrainsUtilsH
//---------------------------------------------------------------------------
#include "trains.h"
#include "awpipl.h"
#include "_LF.h"

class TTrainsAnalysisEngine
{
private:
    TRAINSHANDLE m_trains;
    TARGETHANDLE m_target;

    TVAInitParams m_trains_params;
    TVAInitParams m_target_params;

protected:
public:

    TTrainsAnalysisEngine();
    ~TTrainsAnalysisEngine();

    bool __fastcall Init(TVAInitParams* trains, TVAInitParams* target);
    bool __fastcall Process(awpImage* img);
    void __fastcall Reset();

};
#endif
