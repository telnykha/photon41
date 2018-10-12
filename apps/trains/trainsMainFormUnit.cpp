//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "trainsMainFormUnit.h"
#include "NewEventUnit.h"
#include "VerInfoUnit.h"
#include "aboutUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage"
#pragma link "TrackBarEx"
#pragma link "EventsIndicator"
#pragma link "FImage41"
#pragma resource "*.dfm"

#pragma link "awplflibb.lib"
#pragma link "TinyXML.lib"
#pragma link "awpipl2b.lib"
#pragma link "JPEGLIB.LIB"

const AnsiString cstrImages = "Jpeg images|*.jpeg;*.jpg|AWP images|*.awp";
const AnsiString cstrVideos = "Videos |*.avi;*.mp4;*.mpg;|Avi videos|*.avi;|MP4 videos|*.mp4|mpeg files|*.mpg";
const AnsiString cstrXml    = "Xml Files | *.xml";
const UnicodeString cstrEventsFilter = "Events files|*.events|Text files|*.txt";

TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::CloseActionExecute(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::OpneImageActionExecute(TObject *Sender)
{
    OpenDialog1->Options >> ofAllowMultiSelect;
	OpenDialog1->Filter = cstrImages;
    if (OpenDialog1->Execute())
    {
        FImage1->Init(OpenDialog1->Files);
        UpdateImage();
        StatusBar1->Panels->Items[0]->Text = "";
    }
}
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
   //
   StatusBar1->Panels->Items[0]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::CloseVideoActionUpdate(TObject *Sender)
{
 // обновление состояния команды. источник закрывается, если
 // он открыт. анализируется IsInitialized

}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenSlideShowActionExecute(TObject *Sender)
{
    //Открывает слайд шоу
    OpenDialog1->Options << ofAllowMultiSelect;
    OpenDialog1->Filter = cstrImages;
    if (OpenDialog1->Execute())
    {
        if (!this->FImage1->Init(OpenDialog1->Files))
        {
            ShowMessage("Не могу открыть слайд-шоу.");
        }
    }
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
    OpenDialog1->Filter = cstrVideos;
    //
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
	//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PlayActionUpdate(TObject *Sender)
{
    if (PlayAction->Checked)
    {
	   SpeedButton9->Caption = "пауза";
       SpeedButton9->Font->Color = clBlue;
    }
    else
    {
       SpeedButton9->Caption = "воспр.";
       SpeedButton9->Font->Color = clBlack;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FirstFrameActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FirstFrameActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PrevFrameActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::PrevFrameActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionExecute(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionUpdate(TObject *Sender)
{
//
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


    TVersionInfo* vi = new TVersionInfo(NULL);
    Caption = L"Обнаружение и распознавание номеров вагонов.  v " + vi->FileVersion + L" [" + FImage1->AFileName + L" ]";
    delete vi;
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
void __fastcall TmainForm::OptionsActionExecute(TObject *Sender)
{
  UnicodeString InputString = InputBox(L"CF Counter demo", L"Переход на кадр", IntToStr(FImage1->Frames->CurrentFrame));
  if (InputString != IntToStr(FImage1->Frames->CurrentFrame))
  {
  	 try
     {
     	int f = StrToInt(InputString);
        if (f < 0 || f > FImage1->Frames->Count)
        {
        	ShowMessage("Недопустимый номер кадра.");
            return;
        }
       //todo: FImage1->Frames->CurrentFrame = f;
     }
     catch(EConvertError& e)
     {

     }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OptionsActionUpdate(TObject *Sender)
{
//
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
    AboutBox->Version->Caption = vi->FileVersion;
	AboutBox->ShowModal();
    delete vi;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1Resize(TObject *Sender)
{
    //todo:
}
//---------------------------------------------------------------------------


