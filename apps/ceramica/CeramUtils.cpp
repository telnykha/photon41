//---------------------------------------------------------------------------
#include <windows.h>
#pragma hdrstop
#include "CeramUtils.h"
#include "awpcvvideo.h"
#include <math.h>
extern "C"
{
	#include "pgf_wrapper.h"
}

#pragma link "pgf_wrapper.lib"
const     double    coef = 4;

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

// возвращает число mm в отрезке длиной value pix
double __fastcall TCeramCalibration::ValueMM(double value)
{
    return value*this->m_alfa;
}
// возвращает число pix в отрезке длиной value_mm миллиметров
int __fastcall TCeramCalibration::ValuePix(double value_mm)
{
    return int(value_mm/this->m_alfa);
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
    m_useBuffer = true;
    m_bufferSize = 10;
    m_bx = new TLFBuffer(m_bufferSize, 0);
    m_by = new TLFBuffer(m_bufferSize, 0);
    m_bd = new TLFBuffer(m_bufferSize, 0);
    m_count = 0;
    m_contour = NULL;
    m_useAprox = false;
}

TCeramImageProcessor::~TCeramImageProcessor()
{
    _AWP_SAFE_RELEASE_(this->m_copy)
    _AWP_SAFE_RELEASE_(this->m_mask)
    _AWP_SAFE_RELEASE_(this->m_process)

     if (m_contour != NULL)
        awpFreeContour(&m_contour);

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

    if (this->m_contour != NULL)
    {
        for (int i = 0; i < this->m_contour->NumPoints; i++)
        {
            this->m_contour->Points[i].X *= coef;
            this->m_contour->Points[i].Y *= coef;
        }
    }
    awpPoint p;
    if (!m_useAprox)
        return true;
	awp2DPoint points[250];
	awp2DPoint c;
	double r = m_diam / 2;
    int count = 0;
    for (int alfa = 30; alfa <= 150; alfa += 1)
    {
        p.X = center.X - r*cos(AWP_PI*alfa/180.);
        p.Y = center.Y - r*sin(AWP_PI*alfa/180.);
        if (contour != NULL)
        {
            double min_dist = 10*m_diam;
            int    min_idx = -1;
            for (int i = 0; i < contour->NumPoints; i++)
            {
                double d;
                awpDistancePoints(p, contour->Points[i], &d);
                if (d < min_dist)
                {
                    min_dist = d;
                    min_idx = i;
                }
            }

            if (min_idx >=0 )
    	    {
                points[count].X = contour->Points[min_idx].X;
                points[count].Y = contour->Points[min_idx].Y;
                count++;
            }
        }
    }
    if (count > 0)
    {
		pgfGetCircle(points, count, &c, &r, 2);
	    this->m_center.X = c.X;
    	this->m_center.Y = c.Y;
        this->m_diam = 2*r;
    }


  //  if (m_mask != NULL)
  //      awpResize(m_mask, coef*m_mask->sSizeX, coef*m_mask->sSizeY);
 //   if (m_process != NULL)
  //      awpResize(m_process, coef*m_process->sSizeX, coef*m_process->sSizeY);

}

bool __fastcall TCeramImageProcessor::FindCircle(awpImage* img, int &r, awpPoint &p)
{
    awpImage* crls = NULL;
    int 	  num = 0;
    bool result = false;
    double thr = 2*img->sSizeX /  100.;
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
                else if (fabs((double)r - (double)m_oldr) < thr)
	                result = true;
                else
                    result = false;
            }
	}
	awp2DPoint points[4];
	awp2DPoint c;
	double r0;
	points[0].X = 1;
	points[0].Y = 0;

	points[1].X = 0;
	points[1].Y = 1;

	points[2].X = -1;
	points[2].Y = 0;

	points[3].X = 0;
	points[3].Y = -1;

	pgfGetCircle(points, 4, &c, &r0, 1);

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

    if (this->m_mask_radius == 0)
    {
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
    }
    else
    {
        p.X = this->m_mask_center.X /coef;
        p.Y = this->m_mask_center.Y /coef;
        r = this->m_mask_radius / coef;
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

         // анализируем самый большой объект.
         // вычисл€ютс€ характеристики объекта.
         // центр масс и его полуоси.
         awpGetObjCentroid(m_process, &obj[maxIdx], &c);
         awpGetObjOrientation(m_process, &obj[maxIdx], &theta, &mi, &ma);

         if (m_contour != NULL)
            awpFreeContour(&m_contour);

        awpCreateContour(&m_contour, 2*obj[maxIdx].Num, true);
        awpGetObjCountour(&obj[maxIdx], m_contour);



         m_bx->Push(c.X);
         m_by->Push(c.Y);

         m_bd->Push(2*sqrt(double(maxS) / AWP_PI));
         m_count++;
         if (m_count <= this->bufferSize)
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

void __fastcall TCeramImageProcessor::Reset()
{
    _AWP_SAFE_RELEASE_(this->m_copy)
    _AWP_SAFE_RELEASE_(this->m_mask)
    _AWP_SAFE_RELEASE_(this->m_process)
    delete m_bx;
    delete m_by;
    delete m_bd;
    m_count = 0;
    int size = this->bufferSize;
    m_bx = new TLFBuffer(size, 0);
    m_by = new TLFBuffer(size, 0);
    m_bd = new TLFBuffer(size, 0);

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
    m_useBuffer = true;
    m_count = 0;
    m_contour = NULL;

}

void __fastcall TCeramImageProcessor::SetUseBuffer(bool value)
{
	this->m_useBuffer = value;
	this->Reset();

}
void __fastcall TCeramImageProcessor::SetBufferSize(int value)
{
	this->m_bufferSize = value;
	this->Reset();
}

int  __fastcall TCeramImageProcessor::GetBufferSize()
{
	return m_useBuffer ? m_bufferSize:1;
}





