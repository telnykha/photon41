//---------------------------------------------------------------------------
#ifndef PhSlideShowH
#define PhSlideShowH
#include "PhMediaSource.h"
//---------------------------------------------------------------------------
class TPhSlideShowSource : public TPhMediaSource
{
protected:
    virtual int __fastcall  GetNumFrames();
    virtual int __fastcall  GetCurrentFrame();
    virtual void __fastcall SetCurrentFrame(int frame);
    virtual bool __fastcall GetIsPlaying();
public:
    TPhSlideShowSource(TPhImage* display);
    ~TPhSlideShowSource();

    virtual void Open(TStrings* Names);
    virtual void Close();

    virtual void First();
    virtual void Prev();
    virtual void Next();
    virtual void Last();

    virtual void Play();
    virtual void Stop();
};
#endif
