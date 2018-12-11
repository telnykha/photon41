//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Ph3iCube.h"
#include "NET_ICube_API.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


long CALLBACK MyCallbackFunc(BYTE * pBuffer, long lBufferSize,PVOID pContext)
{
   if(pBuffer==NULL)
		return -1;
	TPh3iCubeSource* src = (TPh3iCubeSource*)pContext;
	src->m_event->WaitFor(INFINITE);
	src->m_event->ResetEvent();
	memcpy(src->m_frame->pPixels, pBuffer, lBufferSize);
	src->m_event->SetEvent();
	return 42;
}


TPh3iCubeSource::TPh3iCubeSource(TPhImage* display):TPhMediaSource(display)
{
 h_iCurrentCam = 0;
 m_SourceName = L"3iCube";
 m_NumFrames = -1;
 m_CurrentFrame -1;
	m_pTimer = new TTimer(NULL);
	m_pTimer->Enabled = false;
	m_event = new TEvent(true);
	m_pTimer->Interval = 1000;
	m_pTimer->OnTimer = TimerEventHandler;
    m_frame = NULL;
 	if ( LoadICubeApi("ICubeSDK.dll") != IC_SUCCESS )
	{
		ShowMessage("Не могу найти файл ICubeSDK.dll");
		throw 0;
	}
}
TPh3iCubeSource::~TPh3iCubeSource()
{
	   m_pTimer->Enabled = false;
	   delete m_pTimer;
	   delete m_event;
	  if (m_frame != NULL)
	  awpReleaseImage(&m_frame);
	  this->Close();
	  UnloadICubeApi();
}

void TPh3iCubeSource::Open(TStrings* Names)
{
	 int numDevices = 0;
	 numDevices=ICubeSDK_Init();
	 if(numDevices<1)
	 {
		 ShowMessage("Подключенные устройства не обнаружены!");
		 return;
	 }
	int stat = ICubeSDK_Open(h_iCurrentCam);
    if ( stat != IC_SUCCESS )
		ShowMessage("Не могу подключиться к видеокамере!");

	this->m_NumFrames = 0;
	this->m_CurrentFrame = 0;
	//Play();
}
void TPh3iCubeSource::Close()
{
   //	Stop();
	if(ICubeSDK_IsOpen(h_iCurrentCam))
    {
		if(ICubeSDK_Close(h_iCurrentCam)!= IC_SUCCESS )
			ShowMessage("Ошибка при вызове функции ICubeSDK_Close ");
	}
}
// usb video has not navigation---
void TPh3iCubeSource::First(){};
void TPh3iCubeSource::Prev(){};
void TPh3iCubeSource::Next(){};
void TPh3iCubeSource::Last(){};

// воспроизведение
void TPh3iCubeSource::Play()
{
   if( ICubeSDK_SetMode(h_iCurrentCam,MODE_1280x1024)!= IC_SUCCESS )
        ShowMessage("Error ICubeSDK_SetMode ");

	_AWP_SAFE_RELEASE_(m_frame)
	awpCreateImage(&m_frame, 1280, 1024, 3, AWP_BYTE);
	if(ICubeSDK_SetCallback(h_iCurrentCam,CALLBACK_RGB,MyCallbackFunc,this)!= IC_SUCCESS )
        ShowMessage("Error ICubeSDK_SetCallback ");

	if( ICubeSDK_Start(h_iCurrentCam, this->m_pImage->Handle,false,true)!= IC_SUCCESS )
		ShowMessage("Error ICubeSDK_Start ");
	this->m_pTimer->Enabled = true;
    this->m_event->SetEvent();

}
void TPh3iCubeSource::Stop()
{
	int stat = ICubeSDK_Stop(h_iCurrentCam);
	this->m_pTimer->Enabled = false;
	if ( stat != IC_SUCCESS )
		ShowMessage("Error Stop ");
}

int __fastcall  TPh3iCubeSource::GetNumFrames()
{
	return m_NumFrames;
}
int __fastcall  TPh3iCubeSource::GetCurrentFrame()
{
	return  m_CurrentFrame;
}
void __fastcall TPh3iCubeSource::SetCurrentFrame(int frame){};
bool __fastcall TPh3iCubeSource::GetIsPlaying()
{
	int stat = ICubeSDK_IsStarted(h_iCurrentCam);
	return stat != 0;
}

void __fastcall TPh3iCubeSource::SetData(int w, int h, int c, unsigned char* data)
{
  m_pImage->SetImageData(w, h, c, data);
}

void __fastcall TPh3iCubeSource::SetExploshure(double value)
{
	float v = value;
	ICubeSDK_SetExposure(h_iCurrentCam, v);
}

void __fastcall TPh3iCubeSource::SetGain(long value)
{
    ICubeSDK_SetCamParameter(h_iCurrentCam, REG_GAIN, value);
}
void __fastcall TPh3iCubeSource::SetBrightness(long value)
{
  ICubeSDK_SetCamParameter(h_iCurrentCam, REG_BRIGHTNESS, value);
}
void __fastcall TPh3iCubeSource::SetContrast(long value)
{
   ICubeSDK_SetCamParameter(h_iCurrentCam, REG_CONTRAST, value);
}
void __fastcall TPh3iCubeSource::SetGamma(long value)
{
   ICubeSDK_SetCamParameter(h_iCurrentCam, REG_GAMMA, value);
}
void __fastcall TPh3iCubeSource::SetAutoExploshure(bool value)
{
	ICubeSDK_SetParamAuto(h_iCurrentCam, REG_EXPOSURE_TIME, value);
}
void __fastcall TPh3iCubeSource::SetExploshureTarget(long value)
{
	 ICubeSDK_SetCamParameter(h_iCurrentCam, REG_EXPOSURE_TARGET, value);
}

void __fastcall TPh3iCubeSource::TimerEventHandler(TObject *Sender)
{
  if (m_frame != NULL)
  {
	m_event->WaitFor(10);
    m_event->ResetEvent();
	SetData(m_frame->sSizeX,m_frame->sSizeY,m_frame->bChannels,(unsigned char*)m_frame->pPixels);
	m_event->SetEvent();
  }
}

float __fastcall TPh3iCubeSource::GetExploshureTime()
{
	float res = 0;
	ICubeSDK_GetExposure(h_iCurrentCam, &res);
	return res;
}
