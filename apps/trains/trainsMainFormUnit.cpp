//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "trainsMainFormUnit.h"
#include "VerInfoUnit.h"
#include "aboutUnit.h"
#include "PhVideo.h"
#include "TuningUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage41"
#pragma resource "*.dfm"

#pragma link "awplflibb.lib"
#pragma link "TinyXML.lib"
#pragma link "awpipl2b.lib"
#pragma link "JPEGLIB.LIB"
#pragma link "trains.lib"

TmainForm *mainForm;

#define _CHECK_SOURCE_     \
if (m_videoSource == NULL) \
    return;                \

#define _NAV_ENABLED_(v) \
    v->Enabled = m_videoSource != NULL && m_videoSource->NumFrames > 1 && !this->m_videoSource->IsPlaying;

#define _MODE_ENABLED_(v) \
    v->Enabled = m_videoSource != NULL && m_videoSource->NumFrames >= 0;

//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
    m_videoSource = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::CloseActionExecute(TObject *Sender)
{
    if (m_videoSource != NULL)
        delete m_videoSource;

    Close();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::UpdateImage()
{
        // установка размеров изображения.
        // если размер изображения больше размеров окна -
		// выполняем операцию BestFit
        // иначе выполняем операцию ActualSize

        int w = FImage1->Width;
        int h = FImage1->Height;
        int w1 = FImage1->Bitmap->Width;
        int h1 = FImage1->Bitmap->Height;

        if (w1 > w || h1 > h)
            FImage1->BestFit();
        else
            FImage1->ActualSize();

}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormResize(TObject *Sender)
{
    UpdateImage();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModePaneActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModePaneActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ActualSizeActionUpdate(TObject *Sender)
{
    ActualSizeAction->Enabled = !FImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ActualSizeActionExecute(TObject *Sender)
{
    FImage1->ActualSize();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::BestFitActionExecute(TObject *Sender)
{
    FImage1->BestFit();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::BestFitActionUpdate(TObject *Sender)
{
     BestFitAction->Enabled = !FImage1->Bitmap->Empty;
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::AboutActionExecute(TObject *Sender)
{
 // AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::CloseVideoActionExecute(TObject *Sender)
{
   // Закрыть видеоисточник
   if (m_videoSource != NULL)
   {
      delete m_videoSource;
      m_videoSource = NULL;
   }
   FImage1->Close();
   FImage1->Refresh();
   SetSource(NULL);
   this->SetMode(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::CloseVideoActionUpdate(TObject *Sender)
{
 // обновление состояния команды. источник закрывается, если
 // он открыт. анализируется IsInitialized

}
//---------------------------------------------------------------------------


void __fastcall TmainForm::FImage1BeforeOpen(TObject *Sender)
{
    //устанавливает тип открываемого видеоисточника.
    ModePaneActionExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenVideoActionExecute(TObject *Sender)
{
	AnsiString cstrVideos = "Videos |*.avi;*.mp4;*.mpg;|Avi videos|*.avi;|MP4 videos|*.mp4|mpeg files|*.mpg";
    OpenDialog1->Filter = cstrVideos;

    if (OpenDialog1->Execute())
    {
        TPhMediaSource* videoSource= new TPhVideoSource(FImage1);
        videoSource->Open(OpenDialog1->Files);
        if (videoSource->NumFrames == 0)
        {
            ShowMessage(L"Не могу открыть файл: " + OpenDialog1->FileName);
            return;
        }
        SetSource(videoSource);
        SetMode(modeTuningAction);
    }

}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenUSBCameraActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenIPCameraActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PlayActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    if (!m_videoSource->IsPlaying)
    {
	    m_videoSource->Play();
		SpeedButton9->Caption = "пауза";
        SpeedButton9->Font->Color = clBlue;
        SpeedButton9->Down = true;
    }
    else
    {
        m_videoSource->Stop();
       SpeedButton9->Caption = "воспр.";
       SpeedButton9->Font->Color = clBlack;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PlayActionUpdate(TObject *Sender)
{
 PlayAction->Enabled = m_videoSource != NULL && (m_videoSource->NumFrames > 1 || m_videoSource->NumFrames == 0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FirstFrameActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->First();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FirstFrameActionUpdate(TObject *Sender)
{
 	_NAV_ENABLED_(FirstFrameAction)
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PrevFrameActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Prev();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PrevFrameActionUpdate(TObject *Sender)
{
 	_NAV_ENABLED_(PrevFrameAction)
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Next();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionUpdate(TObject *Sender)
{
 	_NAV_ENABLED_(NextFrameAction)
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionExecute(TObject *Sender)
{
	_CHECK_SOURCE_
    m_videoSource->Last();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionUpdate(TObject *Sender)
{
	 _NAV_ENABLED_(LastFrameAction)
}


void __fastcall TmainForm::FImage1Frame(TObject *Sender, int widht,
      int height, int bpp, char *data)
{
   awpImage img;
   img.nMagic = AWP_MAGIC2;
   img.bChannels = bpp / 8;
   img.sSizeX =  widht;
   img.sSizeY = height;
   img.dwType = AWP_BYTE;
   img.pPixels = data;

   this->m_copy.SetImage(&img);


   awpImage* tmp = NULL;
   awpCopyImage(&img, &tmp);
//todo:   if (m_trains != NULL && tmp != NULL &&  this->CheckBox5->Checked)
/*   {
       awpRect result;
       char number[32];
       awpConvert(tmp, AWP_CONVERT_3TO1_BYTE);
       if (m_trains->ProcessImage(tmp, &result, number) > 0)
       {
            TVideoEvent ee;
            ee.Frame = FImage1->CurrentTime;
            ee.Duration = 1000;
            ee.Value = 1;
            ee.ExtValue = 1;

            awpDrawRect(&img,&result,2,255, 4);

            FImage1->AddVideoEvent(&ee);
            TVideoEvent*  e = FImage1->VideoEvent[FImage1->NumVideoEvents-1];
            ListView1->SetFocus();

			TListItem* item = ListView1->Items->Add();
            item->Caption = IntToStr(FImage1->NumVideoEvents);
            item->SubItems->Add(FImage1->TimeMsToString(e->Frame));
            item->SubItems->Add("1");
            item->SubItems->Add("1");
            item->Selected = true;
            item->MakeVisible(true);
            AnsiString str = number;
            Label1->Caption = str;
       }
   }*/
   awpReleaseImage(&tmp);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1AfterOpen(TObject *Sender)
{
   	UnicodeString str = FImage1->AFileName;
    str = ChangeFileExt(str, ".trains");
    if (FileExists(str, true))
    {
    	AnsiString _ansi = str;
    }
    else
    {
    }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::RenderZones(awpImage* image)
{
    if (image == NULL)
        return;
    //todo: render VAInitParams
}


void __fastcall TmainForm::DrawZones()
{
    //todo: draw zones
}

void __fastcall TmainForm::FormShow(TObject *Sender)
{
    TVersionInfo* vi = new TVersionInfo(NULL);
	Caption = L"Обнаружение и распознавание номеров вагонов.  v " + vi->FileVersion;
    delete vi;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

static AnsiString TimeMsToTimeStr(double _time)
{
    _time /= 1000;
    long sec  = _time / 1000;
    long min  = sec / 60;
    sec %= 60;
	double hour = min / 60;
	min %=60;
    long msec = _time - hour*60*60*1000 - min*60*1000 - sec*1000;

    UnicodeString result = FormatFloat("00",(double)hour) + ":" + FormatFloat("00", min) + ":" + FormatFloat("00", sec);
    AnsiString _ansi = result;
    return _ansi;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::N16Click(TObject *Sender)
{
  TVersionInfo* vi = new TVersionInfo(NULL);
  AboutBox->ProductName->Caption = vi->ProductName;
  AboutBox->Version->Caption = vi->FileVersion;
  AboutBox->Copyright->Caption = vi->LegalCopyright;
  AboutBox->Comments->Caption = vi->Comments;
  AboutBox->ShowModal();
  delete vi;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1Resize(TObject *Sender)
{
    //todo:
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::GotoFrameActionExecute(TObject *Sender)
{
  _CHECK_SOURCE_

  UnicodeString InputString = InputBox(L"Trains demo", L"Переход на кадр", IntToStr(FImage1->Frames->CurrentFrame));
  if (InputString != IntToStr(FImage1->Frames->CurrentFrame))
  {
  	 try
     {
     	int f = StrToInt(InputString);
        if (f < 0 || f > m_videoSource->NumFrames)
        {
        	ShowMessage("Недопустимый номер кадра.");
            return;
        }
       this->m_videoSource->CurrentFrame = f;

     }
     catch(EConvertError& e)
     {

     }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::GotoFrameActionUpdate(TObject *Sender)
{
	_NAV_ENABLED_(GotoFrameAction)
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1FrameData(TObject *Sender, int w, int h, int c,
          BYTE *data)
{
    if (m_videoSource != NULL)
    {
		StatusBar1->Panels->Items[1]->Text = L"Кадр "  + IntToStr( m_videoSource->CurrentFrame) +
   		" of " + IntToStr(m_videoSource->NumFrames);
	    StatusBar1->Panels->Items[3]->Text = L"Изображение: " + IntToStr(w) + L":" + IntToStr(h) + L":" + IntToStr(c);
    }
    else
		StatusBar1->Panels->Items[1]->Text = L" ";
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::SetSource(TPhMediaSource* source)
{
   if (m_videoSource != NULL)
   {
      delete m_videoSource;
      m_videoSource = NULL;
   }

   m_videoSource = source;
   if (m_videoSource  != NULL)
   {
        m_videoSource->First();
		StatusBar1->Panels->Items[1]->Text = L"Кадр "  + IntToStr( m_videoSource->CurrentFrame) +
   		" of " + IntToStr(m_videoSource->NumFrames);
	   StatusBar1->Panels->Items[2]->Text = L"Источник данных: " + m_videoSource->SourceName;
       //StatusBar1->Panels->Items[3]->Text = L"Изображение: " + IntToStr(w) + L":" + IntToStr(h) + L":" + IntToStr(c);
       UnicodeString cap = L"Обнаружение и распознавание номеров вагонов.  [";
       cap += m_videoSource->Source;
       cap  += L"]";
       this->Caption = cap;
   }
   else
   {
	   StatusBar1->Panels->Items[1]->Text = L"";
	   StatusBar1->Panels->Items[2]->Text = L"Источник данных: NULL";
       this->Caption = L"Обнаружение и распознавание номеров вагонов.";
  	   StatusBar1->Panels->Items[3]->Text = L"";

   }

}

void __fastcall TmainForm::SetMode(TAction* action)
{
	m_modeAction = action;
    if (m_modeAction != NULL)
    {
        action->Checked = true;
        StatusBar1->Panels->Items[0]->Text = L"Режим: " + action->Caption;
        TuningForm->Visible = m_modeAction == modeTuningAction;
        if (m_modeAction != modeTuningAction)
        {
            m_engine.Init(&m_trains_params, &m_target_params);
        }

    }
    else
    {
        StatusBar1->Panels->Items[0]->Text = L"Режим: ";
        TuningForm->Visible = false;
    }
}


void __fastcall TmainForm::modeAnalysisActionExecute(TObject *Sender)
{
    SetMode(modeAnalysisAction);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::modeAnalysisActionUpdate(TObject *Sender)
{
	_MODE_ENABLED_(modeAnalysisAction)
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::modeTuningActionExecute(TObject *Sender)
{
    SetMode(modeTuningAction);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::modeTuningActionUpdate(TObject *Sender)
{
	_MODE_ENABLED_(modeTuningAction)
}
//---------------------------------------------------------------------------

