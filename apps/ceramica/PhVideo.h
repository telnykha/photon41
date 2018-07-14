//---------------------------------------------------------------------------
#ifndef PhVideoH
#define PhVideoH
#include "PhMediaSource.h"
//---------------------------------------------------------------------------
class TPhVideoSource : public TPhMediaSource
{
private:
    HANDLE    m_videoSource;
    TTimer*   m_pTimer;
protected:
    virtual int __fastcall  GetNumFrames();
    virtual int __fastcall  GetCurrentFrame();
    virtual void __fastcall SetCurrentFrame(int frame);
    virtual bool __fastcall GetIsPlaying();

    void __fastcall DecodePicture();
	void __fastcall TimerEventHandler(TObject *Sender);
public:
   TPhVideoSource(TPhImage* display);
   ~TPhVideoSource();

   virtual void Open(TStrings* Names);
   virtual void Close();

   virtual void First();
   virtual void Prev();
   virtual void Next();
   virtual void Last();

   // ���������������
   virtual void Play();
   virtual void Stop();
};
#endif