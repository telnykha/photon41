//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "MainUnit.h"
#include "BloodUtils.h"
#include "DIBImage41.h"
#include "AboutUnit.h"
#include "VerInfoUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "FImage41"
extern "C"
{
    #pragma link "awpipl2b.lib"
    #pragma link "JPEGLIB.lib"
    #pragma link "libpng.lib"
    #pragma link "tifflib.lib"
    #pragma link "zlib.lib"
}
#pragma resource "*.dfm"
TmainForm *mainForm;
//---------------------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
	: TForm(Owner)
{
    m_image = NULL;
    m_mask  = NULL;
    m_binary = NULL;
    m_first = NULL;
}
//---------------------------------------------------------------------------
// Формирует список файлов, проверяет его, а затем вызывает PhImage->Init
// количество файлов не должно превышать 20, размер каждого файла должен быть
// 320х240 пикселей.
// открывается с использованием OpenFileDialog, путем выбора любого файла
// из заданной папки. Формат файла - png
void __fastcall TmainForm::fileOpenActionExecute(TObject *Sender)
{
    CloseHelper();

    if (OpenDialog1->Execute())
    {
       UnicodeString strPath = ExtractFilePath(OpenDialog1->FileName);
       TStringList* list = new TStringList();
       if (bloodCheckFolder(strPath, list))
       {
            if (this->PhImage1->Init(list))
                this->PhImage1->BestFit();
       }
       else
       {
         UnicodeString strMsg = L"Не могу окрыть изображения в папке: ";
         strMsg +=  strPath;
         ShowMessage(strMsg);
       }
       delete list;
    }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewMosaicActionUpdate(TObject *Sender)
{
   viewMosaicAction->Enabled = !this->PhImage1->Frames->Mosaic->Empty;
   viewMosaicAction->Checked =  this->PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewMosaicActionExecute(TObject *Sender)
{
    PhImage1->Mosaic = !PhImage1->Mosaic;
    this->UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewFirstActionExecute(TObject *Sender)
{
	PhImage1->Frames->First();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewFirstActionUpdate(TObject *Sender)
{
	viewFirstAction->Enabled = PhImage1->Mosaic == false && (PhImage1->Frames != NULL && PhImage1->Frames->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewPrevActionExecute(TObject *Sender)
{
 	PhImage1->Frames->Prev();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewPrevActionUpdate(TObject *Sender)
{
	viewPrevAction->Enabled = PhImage1->Mosaic == false && (PhImage1->Frames != NULL && PhImage1->Frames->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewNextActionExecute(TObject *Sender)
{
    PhImage1->Frames->Next();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewNextActionUpdate(TObject *Sender)
{
	viewNextAction->Enabled = PhImage1->Mosaic == false && (PhImage1->Frames != NULL && PhImage1->Frames->Count > 0);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewFinishActionExecute(TObject *Sender)
{
	PhImage1->Frames->Last();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewFinishActionUpdate(TObject *Sender)
{
	viewFinishAction->Enabled = PhImage1->Mosaic == false && (PhImage1->Frames != NULL && PhImage1->Frames->Count > 0);
}
//---------------------------------------------------------------------------
// После открытия показываем первое изображение
void __fastcall TmainForm::PhImage1AfterOpen(TObject *Sender)
{
    PhImage1->BestFit();
    if (PhImage1->Frames != NULL && PhImage1->Mosaic == false)
    {
        int idx = PhImage1->Frames->CurrentFrame + 1;
        StatusBar1->Panels->Items[1]->Text = L"Изобр. " + IntToStr(idx) + L" из " + IntToStr(PhImage1->Frames->Count);
    }
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::FormResize(TObject *Sender)
{
     PhImage1->BestFit();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewAnalysisAreaActionExecute(TObject *Sender)
{
	viewAnalysisAreaAction->Checked = !viewAnalysisAreaAction->Checked;
    UpdatePicture();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewAnalysisAreaActionUpdate(TObject *Sender)
{
	viewAnalysisAreaAction->Enabled = PhImage1->Mosaic == false && (PhImage1->Frames != NULL && PhImage1->Frames->Count > 0);
}
//---------------------------------------------------------------------------
// Обработка изображения.
void __fastcall TmainForm::PhImage1Frame(TObject *Sender, TGraphic *data)
{
    if (data != NULL)
    {
        //
        TDIBImage* dib = (TDIBImage*)(data);
        if (dib != NULL)
        {
            awpImage* img = NULL;
            dib->GetAWPImage(&img);
            _AWP_SAFE_RELEASE_(m_image)
            awpCopyImage(img, &m_image);
            awpImage* to_display = ProcessFrame(img, PhImage1->Frames->CurrentFrame);
            if (to_display != NULL)
            {
                PrintObjects();
                BuildHistogramms();
                UpdateChart();
                if ( PhImage1->Frames->CurrentFrame != 0)
                {
                    if (viewAnalysisAreaAction->Checked)
                        bloodApplyMask(to_display, m_binary, m_mask);
                    DrawObjects(to_display, 0);
                    DrawAnalysisArea(to_display);
                }

                dib->SetAWPImage(to_display);
               _AWP_SAFE_RELEASE_(to_display)
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhImage1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
    if (m_image == NULL || PhImage1->Mosaic == true)
        return;
    int x = PhImage1->GetImageX(X);
    int y = PhImage1->GetImageY(Y);
    if (x < 0 || y < 0)
        return;
     AWPBYTE* pix = (AWPBYTE*)m_image->pPixels;
     BYTE v = pix[m_image->bChannels*(y*m_image->sSizeX + x)];
     StatusBar1->Panels->Items[3]->Text = L"X=" + IntToStr(x) + L":Y=" + IntToStr(y) + L":V=" + IntToStr(v);
}

//---------------------------------------------------------------------------
awpImage* __fastcall TmainForm::ProcessFrame(awpImage* img, int frame)
{
    awpContour* c = NULL;
    m_objects.Clear();
    if (img != NULL)
    {
        float  b = 0;
        double r = 0;
        double e = 0;
        awpImage* norm = NULL;
        awpNormalize(m_image, &norm, AWP_NORM_L2);

        if (frame == 0)
        {
            _AWP_SAFE_RELEASE_(m_first)
            awpCopyImage(norm, &m_first);
            _AWP_SAFE_RELEASE_(m_mask);
            awpCreateImage(&m_mask, img->sSizeX, img->sSizeY, 1, AWP_BYTE);

            bloodFindVisibleArea(img, &c, r, e);
            bloodBuildVisibleMask(img, m_mask, c, b);// -- маска находится в изображении img
            m_average = b;
            m_radius = r;
            awpFreeContour(&c);
        }
        else
        {
          double threshold = 0.95;
          threshold = 0.85 + (double)this->SpinEdit1->Value / 1000.;
          double rt = (double)this->SpinEdit4->Value / 100;
          awpImage* resd = NULL;
          awpImage* resm = NULL;
          awpImage* mask = NULL;
          awpCreateImage(&mask, m_mask->sSizeX, m_mask->sSizeY, 3, AWP_BYTE);

          awpPutChannel(mask, m_mask, 0);
          awpPutChannel(mask, m_mask, 1);
          awpPutChannel(mask, m_mask, 2);

          awpCalcImage(norm, m_first, &resd, AWP_CALC_DIVIMAGES, AWP_CALC_OUTPLACE);
          awpConvert(resd, AWP_CONVERT_TO_BYTE_WITH_NORM);
          awpCalcImage(resd, mask, &resm,  AWP_CALC_MLTIMAGES, AWP_CALC_OUTPLACE);
          awpConvert(resm, AWP_CONVERT_TO_BYTE_WITH_NORM);
          double a = 0;
          bloodMaskAverage(resm, m_mask, a);
          bloodBinary(resm, m_mask, a, threshold, m_radius, rt);

          _AWP_SAFE_RELEASE_(mask)
          _AWP_SAFE_RELEASE_(img)
          awpCopyImage(resm, &img);
          _AWP_SAFE_RELEASE_(resm)
          _AWP_SAFE_RELEASE_(resd)
        }

        bloodMaskAverage(m_image, m_mask, m_average);
        //
        awpImage* to_display = NULL;
        awpImage* channel = NULL;
        awpImage* channel0 = NULL;
        awpCopyImage(m_image, &to_display);
        if (frame != 0)
        {
            awpGetChannel(img, &channel, 2);
            awpGetChannel(m_image, &channel0, 1);
            _AWP_SAFE_RELEASE_(m_binary)

            // анализ бинарного изображения.
            bloodGetObjects(channel, channel0, SpinEdit2->Value, SpinEdit3->Value, m_objects);
            awpCopyImage(channel, &m_binary);
            awpReleaseImage(&channel);
        }
        return to_display;
    }
    else
        return NULL;
}

void __fastcall TmainForm::SpinEdit2Change(TObject *Sender)
{
    this->Processhelper();
    SaveParams();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::SpinEdit3Change(TObject *Sender)
{
    this->Processhelper();
    SaveParams();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::SpinEdit1Change(TObject *Sender)
{
 	this->Processhelper();
    SaveParams();
}
//---------------------------------------------------------------------------
void  __fastcall TmainForm::Processhelper()
{
    if (PhImage1->Mosaic == false)
    {
        TDIBImage* dib = (TDIBImage*)PhImage1->Bitmap;
        if (dib != NULL)
        {
            awpImage* img = NULL;
            awpCopyImage(m_image, &img);
            awpImage* to_display = ProcessFrame(img, PhImage1->Frames->CurrentFrame);
            if (to_display != NULL)
            {
                PrintObjects();
                BuildHistogramms();
                UpdateChart();
                if (viewAnalysisAreaAction->Checked)
                    bloodApplyMask(to_display, m_binary, m_mask);
                DrawObjects(to_display, 0);
                DrawAnalysisArea(to_display);
                dib->SetAWPImage(to_display);
                StatusBar1->Panels->Items[2]->Text = L"Яркость = " + FormatFloat("###.##",m_average);
                PhImage1->Paint();
               _AWP_SAFE_RELEASE_(to_display)
            }
            _AWP_SAFE_RELEASE_(img)
        }
    }
    else
        this->DoAnalysis();
}

void  __fastcall TmainForm::DrawObjects(awpImage* img, int selected)
{
    if (!viewContoursAction->Checked)
        return;
    for (int i = 0; i < m_objects.GetCount(); i++)
    {
        int value = 128;
        TLFBloodItem* bi = (TLFBloodItem*)m_objects.Get(i);
        if (i == selected)
            value = 255;
        bi->Draw(img, value);
    }
}

void  __fastcall TmainForm::PrintObjects()
{
    ListView1->Clear();
    double sum_d = 0;
    double sum_s = 0;
    double sum_p = 0;
    for (int i = 0; i < m_objects.GetCount(); i++)
    {
        TLFBloodItem* bi = (TLFBloodItem*)m_objects.Get(i);
        TListItem* item = ListView1->Items->Add();
        item->Caption = IntToStr(i);
        item->SubItems->Add(FormatFloat("####.##", bi->GetDensity()));
        item->SubItems->Add(FormatFloat("####.##", bi->GetSquare()));
        item->SubItems->Add(FormatFloat("####.##", bi->GetPerimeter()));

        sum_d += bi->GetDensity();
        sum_s += bi->GetSquare();
        sum_p += bi->GetPerimeter();
    }
    Label7->Caption = IntToStr(m_objects.GetCount());
    Label8->Caption = FormatFloat("####.##", sum_d);
    Label9->Caption = FormatFloat("####.##", sum_s);
}

void  __fastcall TmainForm::UpdateChart()
{
    Series1->Clear();
    Chart1->Title->Text->Clear();

    if (PhImage1->Mosaic)
    {
        Chart1->BottomAxis->Title->Text = "Время";
        if (chartViewNumberAnalysisAction->Checked)
        {
            Chart1->Title->Text->Add(L"Число объектов");
            for (int i = 0; i < m_analysis.GetCount(); i++)
            {
                TLFBloodItem* d = (TLFBloodItem*)m_analysis.Get(i);
                Series1->AddXY(i, d->GetNum());
            }
        }
        else if (chartViewDensityAnalysisAction->Checked)
        {
            Chart1->Title->Text->Add(L"Оптическая плотность");
            for (int i = 0; i < m_analysis.GetCount(); i++)
            {
                TLFBloodItem* d = (TLFBloodItem*)m_analysis.Get(i);
                Series1->AddXY(i, d->GetDensity());
            }
        }
        else if (chartViewSquareAnalysisAction->Checked)
        {
            Chart1->Title->Text->Add(L"Площадь объектов");
            for (int i = 0; i < m_analysis.GetCount(); i++)
            {
                TLFBloodItem* d = (TLFBloodItem*)m_analysis.Get(i);
                Series1->AddXY(i, d->GetSquare());
            }
        }
        else if (chartViewPerimeterAnalysisAction->Checked)
        {
            Chart1->Title->Text->Add(L"Периметр объектов");
            for (int i = 0; i < m_analysis.GetCount(); i++)
            {
                TLFBloodItem* d = (TLFBloodItem*)m_analysis.Get(i);
                Series1->AddXY(i, d->GetPerimeter());
            }
        }
    }
    else
    {
        TLFHistogramm* h = NULL;
        double step = 1;

        if (chartViewDensityAction->Checked)
        {
            Chart1->Title->Text->Add(L"Распределение оптической плотности");
            Chart1->BottomAxis->Title->Text = "Плотность";
            step = 12.75;
            h = &m_hd;
        }
        else if (chartViewSquareAction->Checked)
        {
            Chart1->Title->Text->Add(L"Распределение площади");
            Chart1->BottomAxis->Title->Text = "Площадь (пикс)";
            step = 50;
            h = &m_hs;
        }
        else if (chartViewPerimeterAction->Checked)
        {
            Chart1->Title->Text->Add(L"Распределение периметра");
            Chart1->BottomAxis->Title->Text = "Периметр (пикс)";
            step = 10;
            h = &m_hp;
        }
        for (int i = 0; i < h->GetNumBins(); i++)
            Series1->AddXY(i*step, h->GetBin(i));
    }
}

void  __fastcall TmainForm::BuildHistogramms()
{
    m_hd.Setup(20, 0, 255);
    m_hs.Setup(20, 0, 1000);
    m_hp.Setup(20, 0, 200);

    for (int i = 0; i < m_objects.GetCount(); i++)
    {
        TLFBloodItem* bi = (TLFBloodItem*)m_objects.Get(i);
        m_hd.AddElememt(bi->GetDensity());
        m_hs.AddElememt(bi->GetSquare());
        m_hp.AddElememt(bi->GetPerimeter());
    }
}

void __fastcall TmainForm::chartViewDensityActionExecute(TObject *Sender)
{
	chartViewDensityAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewDensityActionUpdate(TObject *Sender)
{
    chartViewDensityAction->Enabled = PhImage1->Frames->Count > 0 && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewSquareActionExecute(TObject *Sender)
{
	chartViewSquareAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewSquareActionUpdate(TObject *Sender)
{
    chartViewSquareAction->Enabled = PhImage1->Frames->Count > 0 && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewPerimeterActionExecute(TObject *Sender)
{
    chartViewPerimeterAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewPerimeterActionUpdate(TObject *Sender)
{
    chartViewPerimeterAction->Enabled = PhImage1->Frames->Count > 0 && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::ListView1SelectItem(TObject *Sender, TListItem *Item, bool Selected)

{
    if (ListView1->Selected != NULL)
    {
     	m_selected = ListView1->Selected->Index;
        if (PhImage1->Mosaic == false)
	        UpdatePicture();
        else
            PhImage1->MosaicSelected = m_selected;
    }

}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	CloseHelper();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewContoursActionExecute(TObject *Sender)
{
    viewContoursAction->Checked = !viewContoursAction->Checked;
    UpdatePicture();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewContoursActionUpdate(TObject *Sender)
{
    viewContoursAction->Enabled = PhImage1->Frames->Count > 0 && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------
void  __fastcall TmainForm::UpdatePicture()
{
    TDIBImage* dib = (TDIBImage*)PhImage1->Bitmap;
    if (dib != NULL)
    {

        awpImage* img = NULL;
        awpCopyImage(m_image, &img);
        if (img != NULL)
        {
            if (viewAnalysisAreaAction->Checked)
            	bloodApplyMask(img, m_binary, m_mask);
            DrawObjects(img, m_selected);
            DrawAnalysisArea(img);
            dib->SetAWPImage(img);
            PhImage1->Paint();
           _AWP_SAFE_RELEASE_(img)
        }
    }
}
void  __fastcall TmainForm::DoAnalysis()
{
    this->m_analysis.Clear();
	ListView1->Clear();
    _AWP_SAFE_RELEASE_(m_image)
    _AWP_SAFE_RELEASE_(m_mask)
    _AWP_SAFE_RELEASE_(m_binary)
    _AWP_SAFE_RELEASE_(m_first)

    for (int i = 0; i < PhImage1->Frames->Count; i++)
    {
        SFrameItem* item = PhImage1->Frames->GetFrameItem(i);
        if (item != NULL)
        {
            TGraphic* gr = item->image;
            TDIBImage* dib = (TDIBImage*)gr;
            if (dib != NULL)
            {
                awpImage* img = NULL;
                dib->GetAWPImage(&img);
		        awpCopyImage(img, &m_image);
                // process frame
                awpImage* result = ProcessFrame(img, i);

                int Num = 0;
                double d = 0;
                double s = 0;
                double p = 0;
                GetSampelSums(Num, d, s, p);
                TLFBloodItem* itm = new TLFBloodItem(d, s, p, NULL, Num);
                m_analysis.Add(itm);

		        TListItem* l_item = ListView1->Items->Add();

                // to list view
                l_item->Caption = ExtractFileName(item->strFileName);
                l_item->SubItems->Add(FormatFloat("0000.00", d));
                l_item->SubItems->Add(FormatFloat("0000.00", s));
                l_item->SubItems->Add(FormatFloat("0000.00", p));

                _AWP_SAFE_RELEASE_(result)
                _AWP_SAFE_RELEASE_(img)
            }
        }
    }

    Label7->Caption = IntToStr(m_analysis.GetCount());
    Label8->Caption = DateToStr(Now());
    Label9->Caption = TimeToStr(Now());
    m_objects.Clear();
    UpdateChart();
    SaveReport();
}

void  __fastcall TmainForm::GetSampelSums(int& num, double& density, double& square, double& perim)
{
    num = m_objects.GetCount();
    density = 0;
    square = 0;
    perim = 0;
    for (int i = 0; i < m_objects.GetCount(); i++)
    {
        TLFBloodItem* bi = (TLFBloodItem*)m_objects.Get(i);
        density += bi->GetDensity();
        square += bi->GetSquare();
        perim += bi->GetPerimeter();
    }

}
void __fastcall TmainForm::chartViewDensityAnalysisActionExecute(TObject *Sender)
{
    chartViewDensityAnalysisAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewDensityAnalysisActionUpdate(TObject *Sender)
{
    chartViewDensityAnalysisAction->Enabled = PhImage1->Frames->Count > 0 && PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewNumberAnalysisActionExecute(TObject *Sender)
{
    chartViewNumberAnalysisAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewNumberAnalysisActionUpdate(TObject *Sender)
{
    chartViewNumberAnalysisAction->Enabled = PhImage1->Frames->Count > 0 && PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewSquareAnalysisActionExecute(TObject *Sender)
{
    chartViewSquareAnalysisAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewSquareAnalysisActionUpdate(TObject *Sender)
{
    chartViewSquareAnalysisAction->Enabled = PhImage1->Frames->Count > 0 && PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewPerimeterAnalysisActionExecute(TObject *Sender)
{
    chartViewPerimeterAnalysisAction->Checked = true;
    UpdateChart();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::chartViewPerimeterAnalysisActionUpdate(TObject *Sender)

{
    chartViewPerimeterAnalysisAction->Enabled = PhImage1->Frames->Count > 0 && PhImage1->Mosaic;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::FormCreate(TObject *Sender)
{
        CloseHelper();
        LoadParams();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::PhImage1Mosaic(TObject *Sender)
{
    if (PhImage1->Mosaic)
    {
        Label6->Caption = L"Число файлов:";
        Label4->Caption = L"Дата:";
        Label5->Caption = L"Время:";
        StatusBar1->Panels->Items[1]->Text = L"Анализ";
        StatusBar1->Panels->Items[2]->Text = L"";
        StatusBar1->Panels->Items[3]->Text = L"";
        Panel6->Visible = false;
        GroupBox1->Enabled = false;
        // обработка изображений
        this->DoAnalysis();
    }
    else
    {
        Label6->Caption = L"Число объектов:";
        Label4->Caption = L"Опт. плотность:";
        Label5->Caption = L"Площадь:";
        Panel6->Visible = true;
        PhImage1->Frames->First();
        int idx = PhImage1->Frames->CurrentFrame + 1;
        StatusBar1->Panels->Items[1]->Text = L"Изобр. " + IntToStr(idx) + L" из " + IntToStr(PhImage1->Frames->Count);
        GroupBox1->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editCopyImageActionExecute(TObject *Sender)
{
    PhImage1->SaveToClipBoard();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editCopyImageActionUpdate(TObject *Sender)
{
    editCopyImageAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editCopyChartActionExecute(TObject *Sender)
{
    Chart1->CopyToClipboardBitmap();
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::editCopyChartActionUpdate(TObject *Sender)
{
     editCopyChartAction->Enabled = !PhImage1->Empty;
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::viewAreaActionExecute(TObject *Sender)
{
    viewAreaAction->Checked = !viewAreaAction->Checked;
    UpdatePicture();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::viewAreaActionUpdate(TObject *Sender)
{
    viewAreaAction->Enabled = PhImage1->Frames->Count > 0 && !PhImage1->Mosaic;
}
//---------------------------------------------------------------------------
void  __fastcall TmainForm::DrawAnalysisArea(awpImage* img)
{
    if (img == NULL || !viewAreaAction->Checked)
        return;

    awpPoint c;
    c.X = IMAGE_WIDTH / 2;
    c.Y = IMAGE_HEIGHT / 2;

    double tr = (double)SpinEdit4->Value / 100.;
    AWPBYTE* data = (AWPBYTE*)img->pPixels;

    for (int y = 0; y < img->sSizeY; y++)
    {
        for (int x = 0; x < img->sSizeX; x++)
        {
            awpPoint p;
            p.X = x;
            p.Y = y;
            double d = 0;
            awpDistancePoints(c, p, &d);
            if (d > tr*m_radius)
            {
                data[3*img->sSizeX*y + 3*x] /= 2;
                data[3*img->sSizeX*y + 3*x+2] /= 2;
            }
        }
    }
}

bool  __fastcall TmainForm::SaveReport()
{
    FILE* f = NULL;
    SFrameItem* item = PhImage1->Frames->GetFrameItem(0);
    UnicodeString str = ExtractFilePath(item->strFileName);
    AnsiString _ansi = str;
    _ansi += "\\report.txt";
    f = fopen(_ansi.c_str(), "w+t");
    if (f == NULL)
        return false;
    // печатаетм заголовок
    _ansi = str;

    fprintf(f,"Отчет\n");
    fprintf(f,"-----\n");

    fprintf(f,"Данные: %s\n", _ansi.c_str());
    _ansi = DateToStr(Now());
    fprintf(f,"Дата: %s\n", _ansi.c_str());
    _ansi = TimeToStr(Now());
    fprintf(f,"Время: %s\n", _ansi.c_str());
    fprintf(f,"Число файлов: %i\n", m_analysis.GetCount());

    fprintf(f,"Параметры измерений\n");
    fprintf(f,"-------------------\n");
    fprintf(f,"Чувствительность: %i %\n", SpinEdit1->Value);
    fprintf(f,"Минимальная ширина: %i\n", SpinEdit2->Value);
    fprintf(f,"Минимальная высота: %i\n", SpinEdit3->Value);
    fprintf(f,"Радиус препарата: %i %\n", SpinEdit4->Value);


    fprintf(f,"------------------------------------------\n");
    fprintf(f,"Файл\t\tЧисло\tПлотность\tПлощадь\t\tПериметр\n");
    for (int i = 0; i < m_analysis.GetCount(); i++)
    {
       TLFBloodItem* item = (TLFBloodItem*)m_analysis.Get(i);
	   SFrameItem*   fitem = PhImage1->Frames->GetFrameItem(i);
       float d = (float)item->GetDensity();
       float s = (float)item->GetSquare();
       float p = (float)item->GetPerimeter();
       _ansi = ExtractFileName(fitem->strFileName);
       fprintf(f, "%s\t%i\t%f\t\%f\t%f\n", _ansi.c_str(), item->GetNum(), d,s,p);
    }

    fclose(f);
}

void __fastcall TmainForm::fileReportActionExecute(TObject *Sender)
{
    SFrameItem* item = PhImage1->Frames->GetFrameItem(0);
    UnicodeString str = ExtractFilePath(item->strFileName);
    AnsiString _ansi = str;
    _ansi += "\\report.txt";

    AnsiString cmd = "notepad.exe ";
    cmd += _ansi;

    WinExec(cmd.c_str(), SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::fileReportActionUpdate(TObject *Sender)
{
    fileReportAction->Enabled = PhImage1->Mosaic;
}
//---------------------------------------------------------------------------
void  __fastcall TmainForm::SaveParams()
{
	UnicodeString str = GetEnvironmentVariable(L"APPDATA");
    str += L"\\blood41\\";
    if (!DirectoryExists(str))
        CreateDir(str);
    str += L"blood41.ini";
    AnsiString _ansi = str;
    FILE* f = fopen(_ansi.c_str(), "w+t");
    int value = SpinEdit1->Value;
    fprintf(f, "%i\n", value);
    value = SpinEdit2->Value;
    fprintf(f, "%i\n", value);
    value = SpinEdit3->Value;
    fprintf(f, "%i\n", value);
    value = SpinEdit4->Value;
    fprintf(f, "%i\n", value);
    fclose(f);
}

void  __fastcall TmainForm::LoadParams()
{
	UnicodeString str = GetEnvironmentVariable(L"APPDATA");
    str += L"\\blood41\\";
    UnicodeString FileName = str;
    FileName += L"blood41.ini";
    if (DirectoryExists(str))
    {
        if (FileExists(FileName))
        {
            AnsiString _ansi = FileName;
            FILE* f = fopen(_ansi.c_str(), "r+t");
            int value = 0;
            fscanf(f, "%i\n", &value);
            SpinEdit1->Value = value;
            fscanf(f, "%i\n", &value);
            SpinEdit2->Value = value;
            fscanf(f, "%i\n", &value);
            SpinEdit3->Value = value;
            fscanf(f, "%i\n", &value);
            SpinEdit4->Value = value;
            fclose(f);
        }
        else
            SaveParams();
    }
    else
        SaveParams();
}

void __fastcall TmainForm::helpCallActionExecute(TObject *Sender)
{
    UnicodeString adr = L"https://telnykha.wixsite.com/blood41";//ExtractFilePath(Application->ExeName);
//    adr+= "\\Blood41.html";
	ShellExecute(this->WindowHandle,L"open",adr.c_str() ,NULL,NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TmainForm::helpAboutActionExecute(TObject *Sender)
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
void __fastcall TmainForm::fileCloseActionExecute(TObject *Sender)
{
	CloseHelper();
}
//---------------------------------------------------------------------------
void __fastcall TmainForm::fileCloseActionUpdate(TObject *Sender)
{
    fileCloseAction->Enabled = PhImage1->Frames->Count > 0;
}
//---------------------------------------------------------------------------
void  __fastcall TmainForm::CloseHelper()
{
    Series1->Clear();
    Chart1->Title->Text->Clear();
    Chart1->Title->Text->Add(L"");
    Chart1->BottomAxis->Title->Text = "";


    ListView1->Clear();
    StatusBar1->Panels->Items[1]->Text = L"";
    StatusBar1->Panels->Items[2]->Text = L"";
    StatusBar1->Panels->Items[3]->Text = L"";
    PhImage1->Close();
    PhImage1->Paint();
    m_objects.Clear();
    m_analysis.Clear();

    Label7->Caption = L"000.00";
    Label8->Caption = L"000.00";
    Label9->Caption = L"000.00";

    Label6->Caption = L"Число объектов:";
    Label4->Caption = L"Опт. плотность:";
    Label5->Caption = L"Площадь:";

    _AWP_SAFE_RELEASE_(m_image)
    _AWP_SAFE_RELEASE_(m_mask)
    _AWP_SAFE_RELEASE_(m_binary)
    _AWP_SAFE_RELEASE_(m_first)
}

