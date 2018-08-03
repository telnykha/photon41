//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainUnit.h"
#include "CeramUtils.h"
#include "PhVideo.h"
#include "PhSlideShow.h"
#include "SelDirUnit.h"
#include "IpAddress.h"
#include "Bitmap2Dib.h"
#include "VerInfoUnit.h"
#include "AboutUnit.h"

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
    m_buffer = new TLFBuffer(256, 0);
    m_archive = NULL;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::fileExitActionExecute(TObject *Sender)
{
    delete m_buffer;
    Close();
}
#define _MODE_ENABLED_(v) \
    v->Enabled = m_videoSource != NULL && m_videoSource->NumFrames > 0;

//---------------------------------------------------------------------------
void __fastcall TMainForm::modeExperimentActionExecute(TObject *Sender)
{
    if (m_modeAction != modeExperimentAction)
		SetMode(modeExperimentAction);
    else
        SetMode(modeAutoAnalysisAction);
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
			SetMode(modeHandAction);
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
    this->m_videoSource = NULL;
	SetMode(modeHandAction);
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
 //       Panel1->Visible = false;
//        PhImage1->BestFit();
    }
    else
    {
        m_videoSource->Stop();
        viewPlayAction->Caption = L"Воспроизвести";
        SpeedButton9->Down = false;
//        Panel1->Visible = true;
  //      PhImage1->BestFit();
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
   if (m_modeAction == modeExperimentAction)
    this->StopExperiment();

   m_modeAction = action;
   if (m_modeAction == modeExperimentAction)
    this->StartExperiment();


   action->Checked = true;
   StatusBar1->Panels->Items[0]->Text = L"Режим: " + action->Caption;

   Label6->Enabled  = m_modeAction != modeHandAction;
   Label7->Enabled  = m_modeAction != modeHandAction;
   Label8->Enabled  = m_modeAction != modeHandAction;
   Label10->Enabled = m_modeAction != modeHandAction;

    for (int i = 0; i < GroupBox2->ControlCount; i++)
    {
        TControl* c = GroupBox2->Controls[i];
        if (c != NULL)
            c->Enabled = m_modeAction == modeHandAction && m_videoSource != NULL;
    }

   if (m_modeAction == modeHandAction)
   {
      PhImage1->SelectPhTool(PhRulerTool1);
      IdTCPServer1->Active = false;
   }
   else
   {
      PhImage1->SelectPhTool(PhPaneTool1);
      IdTCPServer1->Active = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	SetMode(modeHandAction);
    SetSource(NULL);
    LoadParams();

    TStringList* l = new TStringList();
    GetMyIpAddressList(l);
    this->ComboBox1->Items->Clear();
    for (int i = 0; i < l->Count; i++)
        this->ComboBox1->Items->Add(l->Strings[i]);
    if (l->Count > 0)
	    this->ComboBox1->ItemIndex = 0;
    delete l;

  	IdTCPServer1->Bindings->Add()->IP =  this->ComboBox1->Items->Strings[0];
  	IdTCPServer1->Bindings->Add()->Port = this->SpinEdit3->Value;

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
     double mm = m_c.ValueMM(this->PhRulerTool1->Lendth);
     Edit1->Text = FormatFloat("###.##", mm);
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PhImage1FrameData(TObject *Sender, int w, int h, int c,
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



    if (w > 0 && h > 0 && c > 0 && data != NULL)
    {
       awpImage img;
       img.nMagic = AWP_MAGIC2;
       img.bChannels = c;
       img.sSizeX =  w;
       img.sSizeY = h;
       img.dwType = AWP_BYTE;
       img.pPixels = data;
       DrawRuler(&img);
       if (m_modeAction == modeHandAction)
         return;
       // перед тем, как начать обработку сделаем копию
       // изображения

       m_copy.SetImage(&img);
       // обработка изображения.
       m_engine.Process(&img);
       // отображение результатов обработки на
       // изображении
       RenderScene(&img);
       // отображение результатов обработки на
       // пользовательском интерфейсе

       ShowResult();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RenderScene(awpImage* img)
{
   DrawSource(img);
   DrawMask(img);
   DrawAxis(img);
   DrawCenter(img);
   DrawObject(img);
   DrawEllipce(img);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawSource(awpImage* img)
{
    if (!viewSourceImageAction->Checked)
	    this->DrawBinary(img);
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
    p.X = m_engine.center.X;
    p.Y = m_engine.center.Y;

    awpDrawCEllipse2(img, p, m_engine.major/2, m_engine.minor/2, -AWP_PI*m_engine.angle/180., 255,0,255, 1);
}

void __fastcall TMainForm::DrawAxis(awpImage* img)
{
    if (!viewAxisAction->Checked)
        return;

    awpPoint p;
    p.X = m_engine.center.X;
    p.Y = m_engine.center.Y;

	awpDrawCEllipseCross(img, p, m_engine.major, m_engine.minor, m_engine.angle, 255,0,0, 1);
}

void __fastcall TMainForm::DrawBinary(awpImage* img)
{
    if (!viewBinaryAction->Checked)
        return;

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

    int _length = this->m_c.ValuePix(2);
    int _delta  = 20;

    awpRect rect;
    rect.left = sx;
    rect.top  = h - sy - 20;
    rect.right = sx + _length;
    rect.bottom = h - sy;

    awpDrawCRect(img, &rect, 0,255,0, 1);
    rect.right = sx + _length / 2;
   	awpFillRect(img, &rect, 1, 255);

    awpRect r;
    r.left = 0;
    r.top  = 0;
    r.right = img->sSizeX;
    r.bottom = 40;
    AnsiString _str = DateToStr(Now());
    _str += " ";
    _str += TimeToStr(Now());
    _str += " d=";
    _str += FormatFloat("000.00  mm", m_c.ValueMM(m_engine.diam));
    awpwinDrawStatusText(img, _str.c_str(), r);

}
void __fastcall TMainForm::FormResize(TObject *Sender)
{
    this->PhImage1->BestFit();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::ShowResult()
{
    m_buffer->Push(m_c.ValueMM(m_engine.diam));

    Label5->Caption = FormatFloat("000.00  mm", m_c.ValueMM(m_engine.diam));
    Label6->Caption = FormatFloat("000.00  mm", m_c.ValueMM(m_engine.major));
    Label7->Caption = FormatFloat("000.00  mm", m_c.ValueMM(m_engine.minor));
    Label8->Caption = FormatFloat("000.00  grad",m_engine.angle);
    Label10->Caption = FormatFloat("000.00", m_c.ValueMM(m_engine.center.X)) + L":" + FormatFloat("000.00", m_c.ValueMM(m_engine.center.Y));
    Series1->Clear();
    for (int i = 0; i < m_buffer->GetSize(); i++)
        Series1->Add(m_buffer->GetValue(i));
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::viewSourceImageActionExecute(TObject *Sender)
{
    viewSourceImageAction->Checked = !viewSourceImageAction->Checked;
}
//---------------------------------------------------------------------------
void  __fastcall TMainForm::SaveParams()
{
	UnicodeString str = GetEnvironmentVariable(L"APPDATA");
    str += L"\\ceramica\\";
    if (!DirectoryExists(str))
        CreateDir(str);
    str += L"ceramica.ini";
    AnsiString _ansi = str;
    FILE* f = fopen(_ansi.c_str(), "w+t");
     // коэф. масштабирования
    float dv = m_c.alfa;
    fprintf(f, "%f\n", dv);
    // использовать ли буферизацию
    int  iv = (int)CheckBox1->Checked;
    fprintf(f, "%i\n", iv);
    // размер буфера
    iv = SpinEdit1->Value;
    fprintf(f, "%i\n", iv);
    // путь для записи архива
    _ansi = Edit2->Text;
    fprintf(f, "%s\n", _ansi.c_str());
    // скважность записи
    iv = SpinEdit2->Value;
    fprintf(f, "%i\n", iv);
    // время экспозиции
    iv = StrToInt(Edit3->Text);
    fprintf(f, "%i\n", iv);

    fclose(f);
    LoadParams();
}
//---------------------------------------------------------------------------
void  __fastcall TMainForm::LoadParams()
{
	UnicodeString str = GetEnvironmentVariable(L"APPDATA");
    str += L"\\ceramica\\";
    UnicodeString FileName = str;
    FileName += L"ceramica.ini";
    if (DirectoryExists(str))
    {
        if (FileExists(FileName))
        {
            AnsiString _ansi = FileName;
            FILE* f = fopen(_ansi.c_str(), "r+t");
            float dv = 0;
            int   iv = 0;
            // калибровка
            fscanf(f, "%f\n", &dv);
            m_c.alfa = dv;
            Label15->Caption = L"В одном мм " + IntToStr(m_c.ValuePix(1)) + L" пискелей";
            // использование буферизации
            fscanf(f, "%i\n",&iv);
            CheckBox1->Checked = (bool)iv;
            // размер буфера
            fscanf(f, "%i\n", &iv);
            SpinEdit1->Value = iv;
            // путь к архиву
            char buf[1024];
            fscanf(f, "%s\n", buf);
            _ansi = buf;
            Edit2->Text = _ansi;
            // скважность записи
            fscanf(f, "%i\n", &iv);
            SpinEdit2->Value = iv;
            // время экспозиции
            fscanf(f, "%i\n", &iv);
            Edit3->Text = IntToStr(iv);
            fclose(f);
        }
        else
            SaveParams();
    }
    else
        SaveParams();
}


void __fastcall TMainForm::CheckBox1Click(TObject *Sender)
{
    SaveParams();
    this->m_engine.useBuffer = CheckBox1->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpinEdit1Change(TObject *Sender)
{
    SaveParams();
    this->m_engine.bufferSize = SpinEdit1->Value;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit2Change(TObject *Sender)
{
	SaveParams();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpinEdit2Change(TObject *Sender)
{
	SaveParams();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit3Change(TObject *Sender)
{
    int v;
    if (TryStrToInt(Edit3->Text, v))
	    SaveParams();
    else
        Edit3->Text = m_e3ov;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit3Enter(TObject *Sender)
{
    m_e3ov = StrToInt(Edit3->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewBinaryActionExecute(TObject *Sender)
{
    viewBinaryAction->Checked = !viewBinaryAction->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::viewBinaryActionUpdate(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit1Change(TObject *Sender)
{
    if (this->m_videoSource == NULL)
        return;

    float v = 10;
    if (TryStrToFloat(Edit1->Text, v))
    {
        m_c.Init(this->PhRulerTool1->Lendth, v);
	    SaveParams();
    }
    else
        Edit1->Text = m_e1ov;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit1Enter(TObject *Sender)
{
    m_e1ov = StrToFloat(Edit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
    if (this->m_videoSource == NULL || !this->m_videoSource->IsPlaying)
        return;
 	// Сохранение в архив
    if (m_archive != NULL)
    {
        TCeramArchiveRecord r;
        r.diam = m_c.ValueMM(m_engine.diam);
        r.xpos = m_c.ValueMM(m_engine.center.X);
        r.ypos = m_c.ValueMM(m_engine.center.Y);
        r.mi = m_c.ValueMM(m_engine.minor);
        r.ma = m_c.ValueMM(m_engine.major);
        r.angle = m_engine.angle;
        r.img = m_copy.GetImage();
        m_archive->AddRecord(r);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::UpdateRuler()
{

}

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
    String DirName;
	if (GetDirNamePreview(DirName))
    {
        Edit2->Text = DirName;
	    SaveParams();
    }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Panel4Click(TObject *Sender)
{
    Panel1->Visible = !Panel1->Visible;
    PhImage1->BestFit();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::StartExperiment()
{
    if (this->m_archive != NULL)
        delete m_archive;
    AnsiString _ansi = Edit2->Text;
    m_archive = new TCeramArchive(_ansi.c_str());

    TCeramArchiveHeader header;
    header.alfa = m_c.alfa;
    header.bufferSize = m_engine.bufferSize;
    header.dutyRatio  = SpinEdit2->Value;
    header.exposure   = StrToInt(Edit3->Text);

    if (!m_archive->Create(header))
    {
        ShowMessage("Не могу создать архив: " + Edit2->Text);
        return;
    }
    this->Timer1->Interval = SpinEdit2->Value;
    this->Timer1->Enabled  = true;
}
void __fastcall TMainForm::StopExperiment()
{
    this->Timer1->Enabled  = false;
    m_archive->Close();
}

void __fastcall TMainForm::IdTCPServer1Execute(TIdContext *AContext)
{
  UnicodeString LLine = AContext->Connection->IOHandler->ReadLn();
  Memo1->Lines->Add(LLine);
  TDateTime dt = Now();
  unsigned short year, month, day;
  dt.DecodeDate(&year, &month, &day);
  unsigned short hour, min, sec, msec;
  dt.DecodeTime(&hour, &min, &sec, &msec);

    TCeramArchiveRecord r;
    r.diam = m_c.ValueMM(m_engine.diam);
    r.xpos = m_c.ValueMM(m_engine.center.X);
    r.ypos = m_c.ValueMM(m_engine.center.Y);
    r.mi = m_c.ValueMM(m_engine.minor);
    r.ma = m_c.ValueMM(m_engine.major);
    r.angle = m_engine.angle;


  AContext->Connection->IOHandler->WriteLn(IntToStr(1945) + " : " +
  IntToStr(year) + " : " +
  IntToStr(month) + " : " +
  IntToStr(day) + " : " +
  IntToStr(hour) + " : " +
  IntToStr(min) + " : " +
  IntToStr(sec) + " : " +
  FormatFloat("000.00  mm", r.diam) + " : " +
  FormatFloat("000.00  mm", r.ma) + " : " +
  FormatFloat("000.00  mm", r.mi) + " : " +
  FormatFloat("000.00  mm", r.xpos) + " : " +
  FormatFloat("000.00  mm", r.ypos) + " : " +
  FormatFloat("000.00  grad", r.angle)
  );
  float array[14];
  // упаковка данных
  TByteDynArray a;
  a.set_length(66);
  unsigned char* byte = &a[0];
  int* tmp = (int*)byte;
  tmp[0] = 1945;
  tmp[1] = year;
  tmp[2] = month;
  tmp[3] = day;
  tmp[4] = hour;
  tmp[5] = min;
  tmp[6] = sec;
  float* f = (float*)&tmp[7];
  f[0] = r.diam;
  f[1] = r.ma;
  f[2] = r.mi;
  f[3] = r.xpos;
  f[4] = r.ypos;
  f[5] = r.angle;

  AContext->Connection->IOHandler->WriteDirect(a);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IdTCPServer1Connect(TIdContext *AContext)
{
    Memo1->Lines->Add("подключение клиента. ");
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IdTCPServer1Disconnect(TIdContext *AContext)
{
    Memo1->Lines->Add("отключение клиента. ");
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::fileClientActionExecute(TObject *Sender)
{
   WinExec("CeramClient.exe", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::helpAboutActionExecute(TObject *Sender)
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

