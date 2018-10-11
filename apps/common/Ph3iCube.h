//---------------------------------------------------------------------------

#ifndef Ph3iCubeH
#define Ph3iCubeH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "PhMediaSource.h"
#include "awpipl.h"
//---------------------------------------------------------------------------
class TPh3iCubeSource : public TPhMediaSource
{
private:
	int h_iCurrentCam;
	TTimer*   m_pTimer;
protected:
	virtual int __fastcall  GetNumFrames();
	virtual int __fastcall  GetCurrentFrame();
	virtual void __fastcall SetCurrentFrame(int frame);
	virtual bool __fastcall GetIsPlaying();

	void __fastcall DecodePicture();
	void __fastcall TimerEventHandler(TObject *Sender);
public:
   TPh3iCubeSource(TPhImage* display);
   ~TPh3iCubeSource();

   virtual void Open(TStrings* Names);
   virtual void Close();

   virtual void First();
   virtual void Prev();
   virtual void Next();
   virtual void Last();

   // воспроизведение
   virtual void Play();
   virtual void Stop();

   void __fastcall SetData(int w, int h, int c, unsigned char* data);

   void __fastcall SetExploshure(double value);
   void __fastcall SetGain(long value);
   void __fastcall SetBrightness(long value);
   void __fastcall SetContrast(long value);
   void __fastcall SetGamma(long value);
   void __fastcall SetAutoExploshure(bool value);
   void __fastcall SetExploshureTarget(long value);
public:
	TEvent*   m_event;
	awpImage* m_frame;
};
#endif
