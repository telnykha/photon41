//---------------------------------------------------------------------------
#include <windows.h>
#pragma hdrstop
#include "CeramUtils.h"
#include "awpcvvideo.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
TCeramCalibration::TCeramCalibration()
{
    m_alfa = 1 / 70.;
}
TCeramCalibration::TCeramCalibration(double alfa)
{
    m_alfa = alfa;
}

TCeramCalibration::TCeramCalibration(double lenght_pix, double lenght_mm)
{
    m_alfa =  lenght_mm / lenght_pix;
}


TCeramCalibration::~TCeramCalibration()
{

}

void __fastcall TCeramCalibration::Init(double lenght_pix, double lenght_mm)
{
    m_alfa =  lenght_mm / lenght_pix;
}


double __fastcall TCeramCalibration::Value(double value)
{
    return value*this->m_alfa;
}



TCeramImageProcessor::TCeramImageProcessor()
{
    this->m_copy = NULL;
    m_center;
    m_angle = 0;
    m_diam = 0;
    m_major = 0;
    m_minor = 0;
    m_mask = NULL;
    m_process = NULL;
    m_oldc.X = 0;
    m_oldc.Y = 0;
    m_oldr = 0;
    m_bx = new TLFBuffer(20, 0);
    m_by = new TLFBuffer(20, 0);
    m_bd = new TLFBuffer(20, 0);
    m_count = 0;
}

TCeramImageProcessor::~TCeramImageProcessor()
{
    _AWP_SAFE_RELEASE_(this->m_copy)
    _AWP_SAFE_RELEASE_(this->m_mask)
    _AWP_SAFE_RELEASE_(this->m_process)
    delete m_bx;
    delete m_by;
    delete m_bd;
}

bool __fastcall TCeramImageProcessor::Process(awpImage* img)
{
    if (img == NULL)
        return false;

    _AWP_SAFE_RELEASE_(this->m_copy)
    _AWP_SAFE_RELEASE_(this->m_process)

    if (awpCopyImage(img, &m_copy) != AWP_OK)
        return false;

    double    coef = 4;
    awpCopyImage(m_copy, &m_process);
    awpResize(m_process, m_process->sSizeX / coef, m_process->sSizeY / coef);
 	awpConvert(m_process, AWP_CONVERT_3TO1_BYTE);

    // process on copy image
    MakeMaskImage();
    ProcessHelper();
    Analysis();

    this->m_center.X *= coef;
    this->m_center.Y *= coef;

    this->m_diam *= coef;
    this->m_major *= coef;
    this->m_minor *= coef;

    if (m_mask != NULL)
        awpResize(m_mask, coef*m_mask->sSizeX, coef*m_mask->sSizeY);
    if (m_process != NULL)
        awpResize(m_process, coef*m_process->sSizeX, coef*m_process->sSizeY);

}

bool __fastcall TCeramImageProcessor::FindCircle(awpImage* img, int &r, awpPoint &p)
{
    awpImage* crls = NULL;
    int 	  num = 0;
    bool result = false;
 	awpCreateImage(&crls, 100, 3, 1, AWP_DOUBLE);
    if (awpcvHoughCircles(m_process, crls, &num) == S_OK)
    {
            double min = m_process->sSizeX;
            int min_idx = -1;
            AWPDOUBLE* data = (AWPDOUBLE*)crls->pPixels;
			for (int i = 0; i < num; i++)
            {
                int w;
				w = data[2*crls->sSizeX + i];
                if (w < min)
                {
                	min = w;
                    min_idx = i;
                }
            }
            if (min_idx >=0)
            {
                p.X = data[min_idx ];
                p.Y = data[crls->sSizeX + min_idx ];
                r = (data[2*crls->sSizeX + min_idx ]);
                if (this->m_oldr == 0)
                    result = true;
                else if (fabs((double)r - (double)m_oldr) < 10)
	                result = true;
                else
                    result = false;
            }
    }
    _AWP_SAFE_RELEASE_(crls)
    return result;
}



void __fastcall TCeramImageProcessor::MakeMaskImage()
{
    if (m_copy == NULL)
        return;

    _AWP_SAFE_RELEASE_(this->m_mask)
    awpPoint p;
    int      r = 0;
    if (FindCircle(m_process,r , p))
    {
        this->m_oldr = r;
        this->m_oldc = p;
    }
    else
    {
        r = m_oldr;
        p = m_oldc;
    }
    CreateMask(p, 1.05*r, m_process->sSizeX, m_process->sSizeY);
}
void __fastcall TCeramImageProcessor::CreateMask(awpPoint p, double r, int w, int h)
{
    awpCreateImage(&m_mask, w,h,1, AWP_BYTE);
    AWPBYTE* b = (AWPBYTE*)m_mask->pPixels;
    double r2 = (double)r*(double)r;
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            double d = (p.X - x)*(p.X - x)+(p.Y - y)*(p.Y - y);
            if (d < r2)
                b[y*w+x] = 1;
        }
    }
}

void __fastcall TCeramImageProcessor::ProcessHelper()
{
    if (m_mask == NULL || m_process == NULL)
        return;
    AWPBYTE* m = (AWPBYTE*)m_mask->pPixels;
    AWPBYTE* p = (AWPBYTE*)m_process->pPixels;
    double a = 0;
    for (int i = 0; i < m_mask->sSizeX*m_mask->sSizeY; i++)
    {
        p[i] *= m[i];
        if (m[i] > 0)
            a += p[i];
    }
    a /= (double)m_mask->sSizeX*(double)m_mask->sSizeY;
    for (int i = 0; i < m_mask->sSizeX*m_mask->sSizeY; i++)
    {
        if (p[i] > 2*a)
            p[i] = 255;
        else
        	p[i] = 0;
    }
}

void __fastcall TCeramImageProcessor::Analysis()
{
    if (this->m_process == NULL)
        return;

    awpStrokeObj* obj = NULL;
    int Num = 0;
    if (awpGetStrokes(m_process, &Num,  &obj, 128,  NULL) != AWP_OK)
        return;
    if (Num == 0)
        return;
    int maxS = 0;
    int maxIdx = -1;
    for (int i = 0; i < Num; i++)
    {
        int s = 0;
        awpStrObjSquare(&obj[i], &s);
        if (s > maxS)
        {
            maxS = s;
            maxIdx = i;
        }
    }

    if (maxIdx >= 0)
    {
         awpPoint c;
         AWPDOUBLE theta = 0;
         AWPDOUBLE mi = 0;
         AWPDOUBLE ma = 0;
         // ����� ������� ������
         awpGetObjCentroid(m_process, &obj[maxIdx], &c);
         awpGetObjOrientation(m_process, &obj[maxIdx], &theta, &mi, &ma);

         m_bx->Push(c.X);
         m_by->Push(c.Y);
         m_bd->Push(2*sqrt(double(maxS) / AWP_PI));
         m_count++;
         if (m_count <= 20)
         {
             this->m_center.X = c.X;
             this->m_center.Y = c.Y;
             this->m_diam = 2*sqrt(double(maxS) / AWP_PI);
         }
         else
         {
             this->m_center.X = m_bx->GetAvg();
             this->m_center.Y = m_by->GetAvg();
             this->m_diam = m_bd->GetAvg();
         }
         this->m_major = ma;
         this->m_minor = mi;
         this->m_angle = theta;
    }
    awpFreeStrokes(Num, &obj);
}

