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
	m_videoSource = vsNone;
    SetDefaultZones();
    num_cross = 0;
//todo:    m_trains = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::CloseActionExecute(TObject *Sender)
{
//todo:    if (m_trains != NULL)
//        delete m_trains;
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::OpneImageActionExecute(TObject *Sender)
{
	this->m_videoSource = vsImage;
    OpenDialog1->Options >> ofAllowMultiSelect;
	OpenDialog1->Filter = cstrImages;
    if (OpenDialog1->Execute())
    {
        FImage1->Init(OpenDialog1->FileName, NULL);
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
	SetZones();
    FImage1->CurrentTool = ftPane;
    FImage1->Frame(FImage1->CurrentFrame);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModePaneActionUpdate(TObject *Sender)
{
    ModePaneAction->Checked =  FImage1->CurrentTool == ftPane;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionExecute(TObject *Sender)
{
	FImage1->CurrentTool = ftZones;
    TZonesTool* tool = (TZonesTool*)FImage1->Tool;
    tool->OnDelete = ToolDelete;
    //todo:
    awpImage* img = m_copy.GetImage();
    FImage1->Bitmap->SetAWPImage(img);
    tool->InitZones(&this->m_zones);
    tool->Selected = 0;
    FImage1->Paint();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ModeSelRectActionUpdate(TObject *Sender)
{
    ModeSelRectAction->Checked =  FImage1->CurrentTool == ftZones;
    ModeSelRectAction->Enabled = !FImage1->Bitmap->Empty;
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
   FImage1->Uninitialize();
   StatusBar1->Panels->Items[0]->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::CloseVideoActionUpdate(TObject *Sender)
{
 // обновление состояния команды. источник закрывается, если
 // он открыт. анализируется IsInitialized
 CloseVideoAction->Enabled = FImage1->IsInitialized;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenSlideShowActionExecute(TObject *Sender)
{
    //Открывает слайд шоу
    this->m_videoSource = vsSlideShow;
    OpenDialog1->Options << ofAllowMultiSelect;
    OpenDialog1->Filter = cstrImages;
    if (OpenDialog1->Execute())
    {
        if (!this->FImage1->Init("", OpenDialog1->Files))
        {
            ShowMessage("Не могу открыть слайд-шоу.");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1BeforeOpen(TObject *Sender)
{
    //устанавливает тип открываемого видеоисточника.
    FImage1->SourceType = this->m_videoSource;
    ModePaneActionExecute(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenVideoActionExecute(TObject *Sender)
{
    this->m_videoSource = vsVideo;
    OpenDialog1->Filter = cstrVideos;
    if (OpenDialog1->Execute())
    {
        if (!this->FImage1->Init(OpenDialog1->FileName, NULL))
        {
            ShowMessage("Не могу открыть видеоклип ." + OpenDialog1->FileName);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenUSBCameraActionExecute(TObject *Sender)
{
     this->m_videoSource = vsUSBCam;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OpenIPCameraActionExecute(TObject *Sender)
{
//      this->FImage1->Init("http://83.64.164.6//mjpg//video.mjpg", NULL);


   this->m_videoSource = vsIPCam;
   AnsiString str = "http://root:1@192.168.100.18//mjpg//video.mjpg";
/*   if (InputQuery("IP connection", "Host name", str))
   {
	if (!FImage1->Init(str, NULL))
	{
		ShowMessage("Не могу подключиться к адресу: " + str);
	}
   }
   */

}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PlayActionExecute(TObject *Sender)
{
  if (FImage1->IsPaused && this->CheckBox5->Checked)
  {
	ListView1->Clear();
    FImage1->ClearEvents();
    Button1Click(NULL);
  }
  FImage1->IsPaused  = !FImage1->IsPaused;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PlayActionUpdate(TObject *Sender)
{

    PlayAction->Enabled = FImage1->IsInitialized;
    PlayAction->Checked   = !FImage1->IsPaused ;
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
    FImage1->First();
    FImage1->First();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FirstFrameActionUpdate(TObject *Sender)
{
//
    FirstFrameAction->Enabled =  FImage1->IsInitialized;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PrevFrameActionExecute(TObject *Sender)
{
//
    FImage1->Prev();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PrevFrameActionUpdate(TObject *Sender)
{
//
    PrevFrameAction->Enabled= FImage1->IsInitialized;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionExecute(TObject *Sender)
{
  FImage1->Next();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::NextFrameActionUpdate(TObject *Sender)
{
//
    NextFrameAction->Enabled = FImage1->IsInitialized;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionExecute(TObject *Sender)
{
//
    FImage1->Last();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::LastFrameActionUpdate(TObject *Sender)
{
//
    LastFrameAction->Enabled = FImage1->IsInitialized;
}
//---------------------------------------------------------------------------
static void awp2DLineSegmentToStraightLine(awp2DLineSegment s, double& A, double& B, double& C)
{
    A = s.end.Y - s.strat.Y;
    B = s.strat.X - s.end.X;
    C = s.end.X*s.strat.Y - s.strat.X*s.end.Y;
}
//---------------------------------------------------------------------------
static awp2DPoint awp2DLineSegmentMiddlePoint(awp2DLineSegment s)
{
	awp2DPoint res;
    res.X = 0.5*(s.strat.X + s.end.X);
    res.Y = 0.5*(s.strat.Y + s.end.Y);
    return res;
}
//---------------------------------------------------------------------------
static awp2DPoint awp2DNormVector(awp2DPoint p, double l = 1)
{
	awp2DPoint res;
    res.X = 0;
    res.Y = 0;
	double L = sqrt(p.X*p.X + p.Y*p.Y);
    if (L == 0)
    	return res;
    res.X = l*p.X / L;
	res.Y = l*p.Y / L;
    return res;
}

//---------------------------------------------------------------------------
static awp2DPoint FindCrossPoint(awp2DLineSegment s1, awp2DLineSegment s2)
{
    double A1, B1, C1, A2, B2, C2, d;

    A1 = s1.end.Y - s1.strat.Y;
    B1 = s1.strat.X - s1.end.X;
    C1 = s1.end.X*s1.strat.Y - s1.strat.X*s1.end.Y;

    A2 = s2.end.Y - s2.strat.Y;
    B2 = s2.strat.X - s2.end.X;
    C2 = s2.end.X*s2.strat.Y - s2.strat.X*s2.end.Y;

    awp2DPoint result;
    result.X = 0;
    result.Y = 0;

    double det = (A1*B2 - A2*B1);
    if (det == 0)
		return result;
	double detx = (-C1)*B2 - (-C2)*B1;
    double dety = A1*(-C2) - A2*(-C1);

    result.X = detx / det;
    result.Y = dety / det;

	return result;

}

static double LineSegmentLength(awp2DLineSegment s)
{
	return sqrt((s.strat.X - s.end.X)*(s.strat.X - s.end.X)+(s.strat.Y - s.end.Y)*(s.strat.Y - s.end.Y));
}


double _awpL2Distance(awp2DPoint p1, awp2DPoint p2)
{
    return sqrt((p1.X -p2.X)*(p1.X - p2.X) + (p1.Y - p2.Y)*(p1.Y - p2.Y));
}

static double awp2DSegmentsAngle(awp2DLineSegment s1, awp2DLineSegment s2)
{
    double norm1 = LineSegmentLength(s1);
    double norm2 = LineSegmentLength(s2);
    double norm = norm1*norm2;
    if (norm == 0)
    	return 0;

    awp2DPoint p1,p2;
    p1.X = s1.end.X - s1.strat.X;
    p1.Y = s1.end.Y - s1.strat.Y;

    p2.X = s2.end.X - s2.strat.X;
    p2.Y = s2.end.Y - s2.strat.Y;

	double scalar = (p1.X*p2.X + p1.Y*p2.Y) / norm;
	double res;
    if (p1.X*p2.Y - p2.X*p1.Y >= 0)
    	res = -180*acos(scalar)/ AWP_PI;
    else
    	res =  180*acos(scalar)/ AWP_PI;
    return res;
}

static bool CheckCrossPoint(awp2DLineSegment s1, awp2DLineSegment s2, awp2DPoint p)
{
	double sd1 =  LineSegmentLength(s1);
    double sd2 =  LineSegmentLength(s2);
    double d1 =  _awpL2Distance(p, s1.strat);
    double d2 =  _awpL2Distance(p, s1.end);
    if (d1 + d2 - sd1 > 0.1)
    	return false;
    d1 =  _awpL2Distance(p, s2.strat);
    d2 =  _awpL2Distance(p, s2.end);
    if (d1 + d2 - sd2 > 0.1)
    	return false;
	return true;
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


   if (CheckBox1->Checked)
   {
     RenderZones(&img);
   }

   awpReleaseImage(&tmp);
   TrackBarEx1->Position =  FImage1->CurrentFrame;

   StatusBar1->Panels->Items[0]->Text = L"Frame "  + IntToStr(FImage1->CurrentFrame) +
   " of " + IntToStr(FImage1->TotalFrames);

   StatusBar1->Panels->Items[1]->Text = L"Time "  + FImage1->strCurrentTime +
   " of " + FImage1->strDuration;

   StatusBar1->Panels->Items[2]->Text = IntToStr(widht) + ":" + IntToStr(height) + ":" + IntToStr(bpp);
}
//---------------------------------------------------------------------------
 void __fastcall TmainForm::TrackBarEx1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	FImage1->Frame(TrackBarEx1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1AfterOpen(TObject *Sender)
{
	this->TrackBarEx1->Max = FImage1->TotalFrames;
	this->TrackBarEx1->Frequency = FImage1->TotalFrames / 10;
   	UnicodeString str = FImage1->AFileName;
    str = ChangeFileExt(str, ".trains");
    if (FileExists(str, true))
    {
    	AnsiString _ansi = str;
        m_zones.Clear();
        m_zones.Load(_ansi.c_str());
       // CreateMask();
    }
    else
    {
    	SetDefaultZones();
    }
//todo:    if (m_trains != NULL)
//        delete m_trains;
//	m_trains = new TLFTrains(m_zones);
//    TLFDetectEngine* engine = m_trains->GetDetector();

    // Load Engine
	UnicodeString strExeName = Application->ExeName;
	UnicodeString strExePath = ExtractFilePath(strExeName);
	strExePath += L"\\trains\\";

	AnsiString _ansi = strExePath;
//	m_trains->InitOCR(_ansi.c_str());

//    m_trains->GetDetector()->SetResize(true);
//	m_trains->GetDetector()->SetBaseImageWidth(640);

    ListView1->Items->Clear();
    for (int i = 0; i < FImage1->NumVideoEvents; i++)
    {
       TVideoEvent* e = FImage1->VideoEvent[i];
       if (e != NULL)
       {
          TListItem* item = ListView1->Items->Add();
          item->Caption = IntToStr(i);
          item->SubItems->Add(FImage1->TimeMsToString(e->Frame));
          item->SubItems->Add(FloatToStr(e->Value));
          item->SubItems->Add(FloatToStr(e->ExtValue));
       }
    }


    TVersionInfo* vi = new TVersionInfo(NULL);
    Caption = L"Обнаружение и распознавание номеров вагонов.  v " + vi->FileVersion + L" [" + FImage1->AFileName + L" ]";
    delete vi;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ListBox1Click(TObject *Sender)
{
  if (FImage1->CurrentTool == ftZones)
  {
      TZonesTool* tool = (TZonesTool*)mainForm->FImage1->Tool;
      tool->Selected = 0;
  }
  else
      FImage1->Frame(FImage1->CurrentFrame);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ToolDelete(TObject *Sender)
{
    SetZones();
}
void __fastcall TmainForm::SetZones()
{
    TImageTool* t = FImage1->Tool;
    TZonesTool* zones_tool = dynamic_cast<TZonesTool* >(t);
    if (zones_tool == NULL)
        return;

    TZonesTool* tool = (TZonesTool*)FImage1->Tool;

    this->m_zones.Clear();
    this->m_zones =  *tool->Zones;
    // todo: set zones
    TLF2DRect* r = m_zones.GetZone(0)->GetRect();


    if (FImage1->AFileName != "")
    {
    	UnicodeString str = FImage1->AFileName;
        str = ChangeFileExt(str, ".trains");
        AnsiString _ansi = str;
        tool->SaveZones(_ansi.c_str());
    }
    if (this->CheckBox1->Checked)
    {
    	DrawZones();
    }
    else
    	FImage1->Paint();
}

void __fastcall TmainForm::SetDefaultZones()
{
    TLFZone* rect    = new TLFZone(ZTRect);

    TLF2DRect* r = rect->GetRect();
    r->SetVertexes(30,70,30,70);

    m_zones.Clear();
    m_zones.AddZone(rect);

    //todo: set zones
    /*
    if (m_counter != NULL)
    {
		m_counter->SetZones(m_zones, FImage1->Bitmap->Width, FImage1->Bitmap->Height);
    }
    */
}

void __fastcall TmainForm::RenderZones(awpImage* image)
{
    if (image == NULL)
        return;

    if (CheckBox1->Checked)
    {
        for (int i = 0; i < this->m_zones.GetCount(); i++)
        {
            TLFZone* z = m_zones.GetZone(i);
              m_color.bRed = 0;
              m_color.bGreen = 0;
              m_color.bBlue  = 255;
            RenderZone(image, z);
        }
    }
}

void __fastcall TmainForm::RenderZone(awpImage* image, TLFZone* z)
{
	if (image == NULL || z == NULL || z->GetZoneType() == ZTUnknown)
    	return;
    if (z->GetZoneType() == ZTRect)
    {
      	RenderRect(image, z);
	}
    else if (z->GetZoneType() == ZTContour)
    {
       RenderContour(image, z);
    }
    else if (z->GetZoneType() == ZTLineSegment)
    {
       RenderLineSegment(image, z);
    }
    else if (z->GetZoneType() == ZTOpenPolygon)
    {
       RenderOpenPolygon(image, z);
    }
}
void __fastcall TmainForm::RenderOpenPolygon(awpImage* image,TLFZone* z)
{
    if (image == NULL || z == NULL || z->GetZoneType() != ZTOpenPolygon)
    	return;
    int w, h;

    w = image->sSizeX;
    h = image->sSizeY;

	TLF2DOpenPolygon* op = z->GetOpenPolygon();
    if (op == NULL)
    	return;
    for (int i = 0; i < op->GetCount(); i++)
    {
    	TLF2DLineSegment* ls = op->GetSegment(i);
        if (ls != NULL)
		{
        	int x1,x2,y1,y2;
            x1 = ls->GetStart().X*w / 100.;
            y1 = ls->GetStart().Y*h / 100.;
            x2 = ls->GetFinish().X*w / 100.;
            y2 = ls->GetFinish().Y*h / 100.;
            awpPoint p1;
            awpPoint p2;
            p1.X = x1;
            p1.Y = y1;
            p2.X = x2;
            p2.Y = y2;
            awpDrawCLine(image, p1,p2,m_color.bRed, m_color.bGreen, m_color.bBlue, 2);
        }
    }
}
void __fastcall TmainForm::RenderLineSegment(awpImage* image,TLFZone* z)
{
    if (image == NULL || z == NULL || z->GetZoneType() != ZTLineSegment)
    	return;
    int w, h;

    w = image->sSizeX;
    h = image->sSizeY;

	TLF2DLineSegment* ls = z->GetLineSegmnet();
    if (ls != NULL)
    {
        int x1,x2,y1,y2;
        x1 = ls->GetStart().X*w / 100.;
		y1 = ls->GetStart().Y*h / 100.;
        x2 = ls->GetFinish().X*w / 100.;
        y2 = ls->GetFinish().Y*h / 100.;
        awpPoint p1;
        awpPoint p2;
        p1.X = x1;
        p1.Y = y1;
        p2.X = x2;
        p2.Y = y2;
        awpDrawCLine(image, p1,p2,m_color.bRed, m_color.bGreen, m_color.bBlue, 2);

        awp2DPoint mp = awp2DLineSegmentMiddlePoint(ls->GetSegment());
        //
        awpRect rect;
        rect.left = mp.X*w/100. - 3;
        rect.top  = mp.Y*h/100. - 3;
        rect.right = mp.X* w/ 100.+ 3;
        rect.bottom = mp.Y*h/100. + 3;
      //  awpDrawCRect(image, &rect, m_color.bRed, m_color.bGreen, m_color.bBlue, 2);
        double A, B, C;
        awp2DLineSegmentToStraightLine(ls->GetSegment(), A, B, C);
        awp2DPoint norm;
        norm.X = A;
        norm.Y = B;
        norm = awp2DNormVector(norm,5);
        norm.X += mp.X;
        norm.Y += mp.Y;

        p1.X = mp.X*w / 100.;
        p1.Y = mp.Y*h / 100.;
		p2.X = norm.X*w / 100.;
        p2.Y = norm.Y*h / 100.;
        awpDrawCLine(image, p1,p2,m_color.bRed, m_color.bGreen, m_color.bBlue, 2);
    }
}
void __fastcall TmainForm::RenderContour(awpImage* image,TLFZone* z)
{
    if (image == NULL || z == NULL || z->GetZoneType() != ZTContour)
    	return;
    int w, h;

    w = image->sSizeX;
    h = image->sSizeY;

    TLF2DContour* c = z->GetContour();
    if (c == NULL)
        return;
    awp2DPoint _p1;
    awp2DPoint _p2;
    awpPoint   p1;
    awpPoint   p2;
    for (int i = 1; i < c->GetNumPoints(); i++)
    {
       _p1 = c->GetPoint(i-1);
       _p2 = c->GetPoint(i);

       p1.X = _p1.X*w / 100.;
       p1.Y = _p1.Y*h / 100.;
       p2.X = _p2.X*w / 100.;
       p2.Y = _p2.Y*h / 100.;
	   awpDrawCLine(image, p1,p2,m_color.bRed, m_color.bGreen, m_color.bBlue, 2);
    }

   _p1 = c->GetPoint(c->GetNumPoints() - 1);
   _p2 = c->GetPoint(0);

   p1.X = _p1.X*w / 100.;
   p1.Y = _p1.Y*h / 100.;
   p2.X = _p2.X*w / 100.;
   p2.Y = _p2.Y*h / 100.;
   awpDrawCLine(image, p1,p2,m_color.bRed, m_color.bGreen, m_color.bBlue, 2);

}
void __fastcall TmainForm::RenderRect(awpImage* image,TLFZone* z)
{
    if (image == NULL || z == NULL || z->GetZoneType() != ZTRect)
    	return;
    int w, h;

    w = image->sSizeX;
    h = image->sSizeY;

    TLF2DRect* _r = z->GetRect();
    if (_r == NULL)
        return;

    awpRect r;

    r.left = _r->GetLeftTop().X*w/100.;
    r.top  = _r->GetLeftTop().Y*h/100.;
	r.right = _r->GetRightBottom().X*w/100.;
    r.bottom = _r->GetRightBottom().Y*h/100.;

    awpDrawCRect(image, &r, m_color.bRed, m_color.bGreen, m_color.bBlue, 2);
}

void __fastcall TmainForm::DrawZones()
{
   if (FImage1->CurrentTool != ftZones && m_copy.GetImage() != NULL)
   {
        awpImage* img = NULL;
        awpCopyImage(m_copy.GetImage(), &img);
		RenderZones(img);
        //todo:

        FImage1->Bitmap->SetAWPImage(img);
        FImage1->Paint();
   }
}

static double DistFrom2DPointTo2DSegment(awp2DLineSegment s, awp2DPoint p)
{
    double A, B, C;

    A = s.end.Y - s.strat.Y;
    B = s.strat.X - s.end.X;
    C = s.end.X*s.strat.Y - s.strat.X*s.end.Y;

    if (A*A + B*B == 0)
    	return 0;

    return fabs(A*p.X + B*p.Y + C) / sqrt(A*A + B*B);
}


void __fastcall TmainForm::CheckBox1Click(TObject *Sender)
{
	this->DrawZones();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::CheckBox2Click(TObject *Sender)
{
	this->DrawZones();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::Button1Click(TObject *Sender)
{
    num_cross = 0;
    Label1->Caption = L"Число событий: " + IntToStr(num_cross);
    FImage1->ClearEvents();
    ListView1->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormShow(TObject *Sender)
{
	Button1Click(NULL);
    GroupBox2->Caption = "Чувствительность = " + FormatFloat("0.00", (double)TrackBar1->Position/100.);
    TVersionInfo* vi = new TVersionInfo(NULL);
	Caption = L"Обнаружение и распознавание номеров вагонов.  v " + vi->FileVersion;
    delete vi;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::OptionsActionExecute(TObject *Sender)
{
  UnicodeString InputString = InputBox(L"CF Counter demo", L"Переход на кадр", IntToStr(FImage1->CurrentFrame));
  if (InputString != IntToStr(FImage1->CurrentFrame))
  {
  	 try
     {
     	int f = StrToInt(InputString);
        if (f < 0 || f > FImage1->TotalFrames)
        {
        	ShowMessage("Недопустимый номер кадра.");
            return;
        }
        FImage1->Frame(f);
     }
     catch(EConvertError& e)
     {

     }
  }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::OptionsActionUpdate(TObject *Sender)
{
  OptionsAction->Enabled = FImage1->TotalFrames > 0;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FImage1ToolChange(TObject *Sender)
{
	TZonesTool* tool = dynamic_cast<TZonesTool* >(FImage1->Tool);

    if (tool == NULL)
    	return;

    this->m_zones.Clear();
    this->m_zones =  *tool->Zones;
    //todo: create mask
    //m_counter->CreateMask(FImage1->Bitmap->Width, FImage1->Bitmap->Height);

    TLF2DRect* r = m_zones.GetZone(0)->GetRect();

    if (FImage1->AFileName != "")
    {
    	UnicodeString str = FImage1->AFileName;
        str = ChangeFileExt(str, ".trains");
        AnsiString _ansi = str;
        tool->SaveZones(_ansi.c_str());
    }
    if (this->CheckBox1->Checked)
    {
    	DrawZones();
    }
    else
    	FImage1->Paint();

}
//---------------------------------------------------------------------------
void __fastcall TmainForm::TrackBarEx1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	FImage1->Frame(TrackBarEx1->Position);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoSourceSizeActionExecute(TObject *Sender)
{
	FImage1->Rescale = 1;
	FImage1->Frame(FImage1->CurrentFrame);
    //todo: create mask
    //m_counter->CreateMask(FImage1->Bitmap->Width, FImage1->Bitmap->Height);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoSourceSizeActionUpdate(TObject *Sender)
{
        videoSourceSizeAction->Checked = FImage1->Rescale == 1;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoHalfSizeActionExecute(TObject *Sender)
{
	FImage1->Rescale = 2;
	FImage1->Frame(FImage1->CurrentFrame);
    //todo: create mask
	//m_counter->CreateMask(FImage1->Bitmap->Width, FImage1->Bitmap->Height);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoHalfSizeActionUpdate(TObject *Sender)
{
        videoHalfSizeAction->Checked = FImage1->Rescale == 2;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoQuarterSizeActionExecute(TObject *Sender)
{
        FImage1->Rescale = 4;
		FImage1->Frame(FImage1->CurrentFrame);
        //todo: create mask
   		//m_counter->CreateMask(FImage1->Bitmap->Width, FImage1->Bitmap->Height);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::videoQuarterSizeActionUpdate(TObject *Sender)
{
        videoQuarterSizeAction->Checked = FImage1->Rescale == 4;
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected)

{
        if (!FImage1->IsPaused)
        	return;

		if (ListView1->Selected != NULL)
        {
            int idx = ListView1->Selected->Index;
            TVideoEvent* e = FImage1->VideoEvent[idx];
            if (e != NULL)
            {
                int num = e->Frame / 50000;
                FImage1->Frame(num);
                FImage1->Paint();
            }
        }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::TrackBar1Change(TObject *Sender)
{
	GroupBox2->Caption = "Чувствительность = " + FormatFloat("0.00", (double)TrackBar1->Position/100.);
    double t = (double)TrackBar1->Position/100.;
    //todo: set threshold
/*    if (m_counter != NULL)
    {
    	m_counter->SetThreshold(t);
    }*/
}
//---------------------------------------------------------------------------

bool __fastcall TmainForm::SaveEventsToXmlFile(UnicodeString& FileName)
{
    AnsiString _ansi = FileName;
	CEventLog log(_ansi.c_str());

    for (int i = 0; i < FImage1->NumVideoEvents; i++)
    {
        TVideoEvent* e = FImage1->VideoEvent[i];
        log.AddEvent(e);
    }

	return true;
}
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



bool __fastcall TmainForm::SaveEventsToTxtFile(UnicodeString& FileName)
{
	AnsiString _ansi = FileName;
    FILE* f = fopen(_ansi.c_str(), "w+t");
    if (f == NULL)
    	return false;
    fprintf(f, "time\t\t in\t out\n");

    for (int i = 0; i < FImage1->NumVideoEvents; i++)
    {
        TVideoEvent* e = FImage1->VideoEvent[i];
    	AnsiString str = TimeMsToTimeStr(e->Frame);
        int in  = e->Value > 0 ?  (int)e->Value : 0;
        int out  = e->Value < 0 ?  (int)fabs(e->Value) : 0;
        fprintf(f, "%s\t %d\t %d\t %f\n", str.c_str(),  in, out, e->ExtValue);
    }

	fclose(f);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TmainForm::LoadEventsFromXmlFile(UnicodeString& FileName)
{
 	AnsiString _ansi = FileName;
    FImage1->ReadEvents(_ansi);
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TmainForm::LoadEventsFromTxtFile(UnicodeString& FileName)
{
 	AnsiString _ansi = FileName;
	FILE* f = fopen(_ansi.c_str(), "r+t");
	if (f == NULL)
    	return false;
    double  h,m,s;
    int i,o;
    char buf[32];
    char buf1[32];
    char buf2[32];
    double sq = 0;
    fscanf(f, "%s\t%s\t%s\n", buf, buf1, buf2);
	while(fscanf(f, "%s\t%d\t%d\\n", buf, &i, &o) != EOF)
    {
        AnsiString str = buf;
        int p = str.Pos(":");
        AnsiString str1 = str.SubString(0,p-1);
		h = atoi(str1.c_str());
        str = str.SubString(p+1, str.Length());
        p = str.Pos(":");
        str1 = str.SubString(0,p-1);
        m = atoi(str1.c_str());
		str = str.SubString(p+1, str.Length());
		s = atoi(str.c_str());
        TVideoEvent* video_event = new  TVideoEvent();
        video_event->Frame = 1000000*(s + m*60 + h*60*60);
        video_event->Duration = 1000;
        video_event->Value = i == 0? -o : i;
        video_event->ExtValue = sq;
        FImage1->AddVideoEvent(video_event, false);
        delete video_event;
    }
	fclose(f);

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TmainForm::DeleteSelectedEvent()
{
    int index = 0;
    if (ListView1->Selected != NULL)
    {
    	index = ListView1->Selected->Index;
        ListView1->DeleteSelected();
        FImage1->DeleteVideoEvent(index, true);
        return true;
    }
	return false;
}
//---------------------------------------------------------------------------
bool __fastcall TmainForm::AddNewEvent(TVideoEvent* e)
{
    FImage1->AddVideoEvent(e);

    e = FImage1->VideoEvent[FImage1->NumVideoEvents-1];
    TListItem* item = ListView1->Items->Add();
    item->Caption = IntToStr(FImage1->NumVideoEvents);
    item->SubItems->Add(FImage1->TimeMsToString(e->Frame));
    item->SubItems->Add(IntToStr((int)e->Value));
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ListView1Change(TObject *Sender, TListItem *Item, TItemChange Change)

{
	Label1->Caption = L"Число событий: " + IntToStr(FImage1->NumVideoEvents);
}
//---------------------------------------------------------------------------


void __fastcall TmainForm::CheckBox5Click(TObject *Sender)
{
	if (CheckBox5->Checked)
    {
    	CheckBox5->Caption = L"Выключить счетчик";
    }
    else
    {
    	CheckBox5->Caption = L"Включить счетчик";
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logOpenActionExecute(TObject *Sender)
{
    OpenDialog1->Filter =  cstrEventsFilter;
    if (OpenDialog1->Execute())
    {
        bool res = false;
        UnicodeString strFileName = OpenDialog1->FileName;
        FImage1->ClearEvents();
		switch(OpenDialog1->FilterIndex)
		{
        	case 1:
            	res = LoadEventsFromXmlFile(strFileName);
            break;
            case 2:
            	res = LoadEventsFromTxtFile(strFileName);
            break;
        }

        if (!res)
        {
        	ShowMessage(L"Не могу загрузить список событий из файла: " + strFileName);
            return;
        }

        ListView1->Clear();
        for (int i = 0; i < FImage1->NumVideoEvents; i++)
        {
           TVideoEvent* e = FImage1->VideoEvent[i];
           if (e != NULL)
           {
              TListItem* item = ListView1->Items->Add();
              item->Caption = IntToStr(i);
              item->SubItems->Add(FImage1->TimeMsToString(e->Frame));
              item->SubItems->Add(FloatToStr(e->Value));
           }
        }
        EventsIndicator1->InitEvents(FImage1->VideoEvents, FImage1->Duration);
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logOpenActionUpdate(TObject *Sender)
{
	logOpenAction->Enabled = FImage1->TotalFrames > 1 && FImage1->IsPaused;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logSaveActionExecute(TObject *Sender)
{
	// save log
    SaveDialog1->Filter =  cstrEventsFilter;
    if (SaveDialog1->Execute())
    {
        bool res = false;
        UnicodeString FileName = SaveDialog1->FileName;
        UnicodeString strExt = ExtractFileExt(FileName);
        if (strExt == L"")
        {
            switch(SaveDialog1->FilterIndex)
            {
                case 1:
                	FileName += L".events";
                break;
                case 2:
                	FileName += L".txt";
                break;
            }
        }
		switch(SaveDialog1->FilterIndex)
		{
        	case 1:
            	res = SaveEventsToXmlFile(FileName);
            break;
            case 2:
            	res = SaveEventsToTxtFile(FileName);
            break;
        }
        if (!res)
        {
        	ShowMessage(L"Не могу сохранить список событий в файл: " + FileName);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logSaveActionUpdate(TObject *Sender)
{
	logSaveAction->Enabled = FImage1->TotalFrames > 1 && FImage1->NumVideoEvents > 0 && FImage1->IsPaused;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logDeleteActionExecute(TObject *Sender)
{
	if (!this->DeleteSelectedEvent())
    {
		ShowMessage("Не могу удалить событие.");
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logDeleteActionUpdate(TObject *Sender)
{
	logDeleteAction->Enabled = FImage1->TotalFrames > 1 && FImage1->NumVideoEvents > 0 &&
    ListView1->Selected != NULL  && FImage1->IsPaused;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logInsertActionExecute(TObject *Sender)
{
    NewEventDlg->Label2->Caption = FImage1->strCurrentTime;
	if (NewEventDlg->ShowModal() == mrOk)
    {
        TVideoEvent e;
        e.Frame = FImage1->CurrentTime;
        e.Duration = 1000;
        e.Value = NewEventDlg->SpinEdit1->Value;
    	if (!AddNewEvent(&e))
        {
			ShowMessage("Не могу добавить новое событие.");
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logInsertActionUpdate(TObject *Sender)
{
	logInsertAction->Enabled = FImage1->TotalFrames > 1  && FImage1->IsPaused;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::logClearActionExecute(TObject *Sender)
{
	ListView1->Clear();
    FImage1->ClearEvents();
    Button1Click(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::logClearActionUpdate(TObject *Sender)
{
	logClearAction->Enabled = FImage1->TotalFrames > 1 && FImage1->NumVideoEvents > 0 && FImage1->IsPaused;
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
	this->FImage1->Paint();
}
//---------------------------------------------------------------------------


