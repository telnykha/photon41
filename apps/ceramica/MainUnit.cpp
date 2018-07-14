//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "CeramUtils.h"
#include "PhVideo.h"
#include "PhSlideShow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage41"
#pragma link "PhImageTool"
#pragma link "PhRulerTool"
#pragma link "PhPaneTool"
#pragma resource "*.dfm"
TMainForm *MainForm;
extern "C"
{
    #pragma link "awpipl2b.lib"
    #pragma link "JPEGLIB.lib"
}
    #pragma link "awplflibb.lib"

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
    m_videoSource = NULL;
    m_modeAction  = NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::fileExitActionExecute(TObject *Sender)
{
    Close();
}
#define _MODE_ENABLED_(v) \
    v->Enabled = m_videoSource != NULL && m_videoSource->NumFrames > 0;

//---------------------------------------------------------------------------
void __fastcall TMainForm::modeExperimentActionExecute(TObject *Sender)
{
	SetMode(modeExperimentAction);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::modeExperimentActionUpdate(TObject *Sender)
{
    _MODE_ENABLED_(modeExperimentAction)
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::modeAutoAnalysisActionExecute(TObject *Sender)
{
	SetMode(modeAutoAnalysisAction);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::modeAutoAnalysisActionUpdate(TObject *Sender)
{
    _MODE_ENABLED_(modeAutoAnalysisAction)
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::modeHandActionExecute(TObject *Sender)
{
	SetMode(modeHandAction);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::modeHandActionUpdate(TObject *Sender)
{
    _MODE_ENABLED_(modeHandAction)
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewAnalysisAreaActionExecute(TObject *Sender)
{
	viewAnalysisAreaAction->Checked = !viewAnalysisAreaAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewAnalysisAreaActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewObjectContourActionExecute(TObject *Sender)
{
    viewObjectContourAction->Checked = !viewObjectContourAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewObjectContourActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewCenterActionExecute(TObject *Sender)
{
    viewCenterAction->Checked = !viewCenterAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewCenterActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewAxisActionExecute(TObject *Sender)
{
    viewAxisAction->Checked = !viewAxisAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewAxisActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewEllipseActionExecute(TObject *Sender)
{
    viewEllipseAction->Checked = !viewEllipseAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewEllipseActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::fileOpenImagesActionExecute(TObject *Sender)
{
	AnsiString cstrImages = "Jpeg images|*.jpeg;*.jpg|AWP images|*.awp";
    OpenDialog1->Filter = cstrImages;
    if (OpenDialog1->Execute())
    {
        TPhMediaSource* videoSource = new TPhSlideShowSource(PhImage1);
        videoSource->Open(OpenDialog1->Files);
        this->SetSource(videoSource);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::fileOpenVideoActionExecute(TObject *Sender)
{
	AnsiString cstrVideos = "Videos |*.avi;*.mp4;*.mpg;|Avi videos|*.avi;|MP4 videos|*.mp4|mpeg files|*.mpg";
    OpenDialog1->Filter = cstrVideos;
    if (OpenDialog1->Execute())
    {
        TPhMediaSource* videoSource= new TPhVideoSource(PhImage1);
        videoSource->Open(OpenDialog1->Files);
        if (videoSource->NumFrames == 0)
        {
            ShowMessage(L"Не могу открыть файл: " + OpenDialog1->FileName);
            SetSource(NULL);
            return;
        }
        else
        {
            SetSource(videoSource);
	        m_videoSource->First();
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::fileConnectToCameraActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::fileCloseActionExecute(TObject *Sender)
{
    PhImage1->Close();
    PhImage1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    if (m_videoSource != NULL)
        delete m_videoSource;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::PhImage1AfterOpen(TObject *Sender)
{
    PhImage1->BestFit();
}
//---------------------------------------------------------------------------
#define _CHECK_SOURCE_     \
if (m_videoSource == NULL) \
    return;                \

#define _NAV_ENABLED_(v) \
    v->Enabled = m_videoSource != NULL && m_videoSource->NumFrames > 1 && !this->m_videoSource->IsPlaying;

void __fastcall TMainForm::viewFirstActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->First();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewFirstActionUpdate(TObject *Sender)
{
    _NAV_ENABLED_(viewFirstAction)
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewPrevActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Prev();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewPrevActionUpdate(TObject *Sender)
{
    _NAV_ENABLED_(viewPrevAction)
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewNextActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Next();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewNextActionUpdate(TObject *Sender)
{
    _NAV_ENABLED_(viewNextAction)
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewLastActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Last();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewLastActionUpdate(TObject *Sender)
{
    _NAV_ENABLED_(viewLastAction)
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewPlayActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    if (!m_videoSource->IsPlaying)
    {
	    m_videoSource->Play();
        viewPlayAction->Caption = L"Стоп";
        SpeedButton9->Down = true;
    }
    else
    {
        m_videoSource->Stop();
        viewPlayAction->Caption = L"Воспроизвести";
        SpeedButton9->Down = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewPlayActionUpdate(TObject *Sender)
{
    viewPlayAction->Enabled = m_videoSource != NULL && m_videoSource->NumFrames > 1;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetMode(TAction* action)
{
   m_modeAction = action;
   action->Checked = true;
   StatusBar1->Panels->Items[0]->Text = L"Режим: " + action->Caption;

   Label6->Enabled  = m_modeAction != modeHandAction;
   Label7->Enabled  = m_modeAction != modeHandAction;
   Label8->Enabled  = m_modeAction != modeHandAction;
   Label10->Enabled = m_modeAction != modeHandAction;

   Label12->Enabled = m_modeAction == modeHandAction && m_videoSource != NULL;
   Label13->Enabled = m_modeAction == modeHandAction && m_videoSource != NULL;
   Label14->Enabled = m_modeAction == modeHandAction && m_videoSource != NULL;
   Edit1->Enabled = m_modeAction == modeHandAction && m_videoSource != NULL;


   if (m_modeAction == modeHandAction)
   {
      PhImage1->SelectPhTool(PhRulerTool1);
   }
   else
   {
    	PhImage1->SelectPhTool(PhPaneTool1);
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	SetMode(modeHandAction);
    SetSource(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::SetSource(TPhMediaSource* source)
{
   if (m_videoSource != NULL)
   {
      delete m_videoSource;
      m_videoSource = NULL;
   }

   m_videoSource = source;
   if (m_videoSource  != NULL)
	   StatusBar1->Panels->Items[2]->Text = L"Источник данных: " + m_videoSource->Source;
   else
   {
	   StatusBar1->Panels->Items[1]->Text = L"";
	   StatusBar1->Panels->Items[2]->Text = L"Источник данных: NULL";
   }
}

void __fastcall TMainForm::PhImage1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
   if (m_modeAction == modeHandAction)
   {
     Label13->Caption = FormatFloat(L"####.##",this->PhRulerTool1->Lendth);
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PhImage1FrameData(TObject *Sender, int w, int h, int c,
          BYTE *data)
{
    if (m_videoSource != NULL)
		StatusBar1->Panels->Items[1]->Text = L"Кадр "  + IntToStr( m_videoSource->CurrentFrame) +
   		" of " + IntToStr(m_videoSource->NumFrames);
    else
		StatusBar1->Panels->Items[1]->Text = L" ";

    if (w > 0 && h > 0 && c > 0 && data != NULL)
    {
       awpImage img;
       img.nMagic = AWP_MAGIC2;
       img.bChannels = c;
       img.sSizeX =  w;
       img.sSizeY = h;
       img.dwType = AWP_BYTE;
       img.pPixels = data;

       m_engine.Process(&img);
       RenderScene(&img);
       ShowResult();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RenderScene(awpImage* img)
{
   DrawSource(img);
   DrawMask(img);
   DrawCenter(img);
   DrawObject(img);
   DrawEllipce(img);
   DrawRuler(img);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawSource(awpImage* img)
{
    if (!viewSourceImageAction->Checked)
	    awpZeroImage(img)
/*    else
    {
        if (m_engine.process != NULL)
        {
            AWPBYTE* p = (AWPBYTE*)m_engine.process->pPixels;
            AWPBYTE* b = (AWPBYTE*)img->pPixels;
            for (int i = 0; i < m_engine.process->sSizeX*m_engine.process->sSizeY; i++)
            {
               b[3*i] = p[i];
               b[3*i+1] = p[i];
               b[3*i+2] = p[i];
            }
        }
    }
*/
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawCenter(awpImage* img)
{
    if (!viewCenterAction->Checked)
        return;

    awpPoint p;
    awpRect  r;

    int delta = 20;

    p.X = m_engine.center.X;
    p.Y = m_engine.center.Y;

    r.left = p.X - delta;
    r.right = p.X + delta;
    r.top = p.Y - delta;
    r.bottom = p.Y + delta;

    awpDrawCCross(img, &r, 0,0, 255, 3);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawObject(awpImage* img)
{
    if (!viewObjectContourAction->Checked)
        return;

    awpPoint p;

    AWPSHORT r = m_engine.diam / 2;
    p.X = m_engine.center.X;
    p.Y = m_engine.center.Y;

    awpDrawCEllipse(img, p, r, r, 0, 0,0,255, 3);
}

void __fastcall TMainForm::DrawEllipce(awpImage* img)
{
    if (!viewEllipseAction->Checked)
        return;

    awpPoint p;

    m_engine.minor;
    p.X = m_engine.center.X;
    p.Y = m_engine.center.Y;

    awpDrawCEllipse(img, p, m_engine.major/2, m_engine.minor/2, m_engine.angle, 255,0,255, 3);

}

void __fastcall TMainForm::DrawAxis(awpImage* img)
{

}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawMask(awpImage* img)
{
    if (!viewAnalysisAreaAction->Checked)
        return;
    if (m_engine.mask == NULL)
        return;

    AWPBYTE* m = (AWPBYTE*)m_engine.mask->pPixels;
    AWPBYTE* b = (AWPBYTE*)img->pPixels;
    for (int i = 0; i < img->sSizeX*img->sSizeY; i++)
    {
        if (m[i] != 0)
        {
	        b[3*i] = 255;
	        b[3*i + 1] /= 2;
	        b[3*i + 2] /= 2;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawRuler(awpImage* img)
{
    int w = img->sSizeX;
    int h = img->sSizeY;

    const int sx = 40;
    const int sy = 40;

    awpPoint p1;
    awpPoint p2;

    p1.X = sx;
    p1.Y = h - sy;
    p2.X = p1.X + 140;
    p2.Y = p1.Y;
    awpDrawCLine(img, p1, p2, 0,255,0, 3);

    p1.X = sx;
    p1.Y = h - sy - 10;
    p2.X = p1.X;
    p2.Y = h - sy + 10;
    awpDrawCLine(img, p1, p2, 0,255,0, 3);

    p1.X = sx + 140;
    p1.Y = h - sy - 10;
    p2.X = p1.X;
    p2.Y = h - sy + 10;
    awpDrawCLine(img, p1, p2, 0,255,0, 3);
}
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    this->PhImage1->BestFit();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowResult()
{
    Label5->Caption = FormatFloat("000.00", m_c.Value(m_engine.diam));
    Label6->Caption = FormatFloat("000.00", m_c.Value(m_engine.major));
    Label7->Caption = FormatFloat("000.00", m_c.Value(m_engine.minor));
    Label8->Caption = FormatFloat("000.00", m_c.Value(m_engine.angle));
    Label10->Caption = FormatFloat("000.00", m_c.Value(m_engine.center.X)) + L":" + FormatFloat("000.00", m_c.Value(m_engine.center.Y));
}

void __fastcall TMainForm::viewSourceImageActionExecute(TObject *Sender)
{
    viewSourceImageAction->Checked = !viewSourceImageAction->Checked;
}
//---------------------------------------------------------------------------

