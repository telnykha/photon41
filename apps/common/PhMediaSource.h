//---------------------------------------------------------------------------
#ifndef PhMediaSourceH
#define PhMediaSourceH
//---------------------------------------------------------------------------
#include "FImage41.h"
class TPhMediaSource
{
protected:
    TPhImage* m_pImage;
    int       m_NumFrames;
    int       m_CurrentFrame;
    UnicodeString m_SourceStr;
    UnicodeString m_SourceName;
protected:
    virtual int __fastcall  GetNumFrames()              = 0;
    virtual int __fastcall  GetCurrentFrame()           = 0;
    virtual void __fastcall SetCurrentFrame(int frame)  = 0;
    virtual bool __fastcall GetIsPlaying()              = 0;
public:
    TPhMediaSource(TPhImage* display);
    virtual ~TPhMediaSource(){}
    virtual void Open(TStrings* Names) = 0;
    virtual void Close() = 0;

    virtual void First() = 0;
    virtual void Prev()  = 0;
    virtual void Next()  = 0;
    virtual void Last()  = 0;

    virtual void Play()  = 0;
    virtual void Stop()  = 0;

	__property int NumFrames = {read = GetNumFrames};
	__property int CurrentFrame = {read = GetCurrentFrame, write = SetCurrentFrame};
    __property bool IsPlaying = {read = GetIsPlaying};
    __property UnicodeString Source = {read = m_SourceStr};
    __property UnicodeString SourceName = {read = m_SourceName};
};
#endif
