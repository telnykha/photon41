//---------------------------------------------------------------------------
#pragma hdrstop
#include "BloodUtils.h"


#pragma link "awplflibb.lib"

//---------------------------------------------------------------------------
bool bloodCheckFolder(UnicodeString& strPath, TStringList* fileNames)
{
	TSearchRec sr;
    UnicodeString strPath0 = strPath;
	strPath0 += "\\*.png";
	int iAttr =0;
	iAttr |= faAnyFile;
    int count = 0;
	if (FindFirst(strPath0, iAttr, sr) == 0)
	{
		do
		{
		  UnicodeString strName =  strPath + "\\" + sr.Name;
          fileNames->Add(strName);
          count++;
		}while(FindNext(sr) == 0);
		FindClose(sr);
	}

    return count > 0 && count <= MAX_FILE_COUNT;
}
/*
    Поиск области анализа. Область анализа возвращается в виде контура
    объекта с максимальной площадью
*/
bool bloodFindVisibleArea(awpImage* image, awpContour** c, double& radius, double& error)
{
	bool result = false;
    awpStrokeObj* obj = NULL;
    int Num = 0;
    awpImage* img2 = NULL;
    awpCopyImage(image, &img2);
    if (awpGetStrokes(img2, &Num, &obj, 160, NULL) != AWP_OK)
        return result;
    if (Num > 0)
    {
        int MaxS = 0;
        int MaxIdx = -1;
        for (int i = 0; i < Num; i++)
        {
            int S = 0;
            awpStrObjSquare(&obj[i], &S);
            if (S > MaxS)
            {
                MaxS = S;
                MaxIdx = i;
            }
        }
        if (MaxIdx >= 0)
        {
            awpCreateContour(c, 2*obj[MaxIdx].Num, true);
		    awpGetObjCountour(&obj[MaxIdx], *c);
            result = true;
        }
    }
    awpReleaseImage(&img2);
    awpFreeStrokes(Num, &obj);
    return bloodVisisbleAreaRadiusError(*c, radius, error);
}
/*
    оценка ошибки поиска контура и радиуса круга, который
    наилучшим образом подходит под найденный контур.
*/
bool bloodVisisbleAreaRadiusError(awpContour* c, double& radius, double& error)
{
    bool result = false;
    if (c == NULL || c->NumPoints == NULL)
        return result;
    awpPoint center;
    center.X = IMAGE_WIDTH / 2;
    center.Y = IMAGE_HEIGHT/ 2;
    double average = 0;
    for (int i = 0; i < c->NumPoints; i++)
    {
        AWPDOUBLE dist = 0;
        awpDistancePoints(center, c->Points[i], &dist);
        average += dist;
    }
    radius = average / c->NumPoints;

    error = 0;
    for (int i = 0; i < c->NumPoints; i++)
    {
        AWPDOUBLE dist = 0;
        awpDistancePoints(center, c->Points[i], &dist);
        error += sqrt((dist-radius)*(dist - radius));
    }
    error /= c->NumPoints;

    return result;
}
/*
    находит маску для изображения образца и вычисляет ее среднюю яркость.
    image - исходно изображение.
    c - контур объекта с максимальной площадью
    b[out] - среднее значение интенсивности внутри объекта.
*/
bool bloodBuildVisibleMask(awpImage* image, awpImage* mask,  awpContour* c, float& b)
{
  if (image == NULL || c == NULL)
    return false;
  AWPBYTE* data = (AWPBYTE*)image->pPixels;
  AWPBYTE* m = (AWPBYTE*)mask->pPixels;
  int count = 0;
  b = 0;
  for (int y = 0; y < image->sSizeY; y++)
  {
    for (int x = 0; x < image->sSizeX; x++)
    {
        awpPoint p;
        p.X = x;
        p.Y = y;
        AWPBOOL in = false;
        awpIsPointInContour(c, &p, &in);
        if (in == true)
        {
            b+= data[3*y*image->sSizeX + 3*x ];
            b+= data[3*y*image->sSizeX + 3*x +1];
            b+= data[3*y*image->sSizeX + 3*x +2];
            count+=3;
            m[y*image->sSizeX + x] = 1;
        }
        else
        {
            data[3*y*image->sSizeX + 3*x ] = 0;
            data[3*y*image->sSizeX + 3*x +1] = 0;
            data[3*y*image->sSizeX + 3*x +2] = 0;
            m[y*image->sSizeX + x] = 0;
        }
    }
  }
  b /= count;

  return true;
}

bool bloodBinary(awpImage* image, awpImage* mask,  float b, float t, double r, double rt)
{
    awpPoint center;
    center.X = IMAGE_WIDTH / 2;
    center.Y = IMAGE_HEIGHT/ 2;


  AWPBYTE* data = (AWPBYTE*)image->pPixels;
  AWPBYTE* mdata = (AWPBYTE*)mask->pPixels;
  for (int y = 0; y < image->sSizeY; y++)
  {
    for (int x = 0; x < image->sSizeX; x++)
    {
        float v1  = mdata[y*image->sSizeX + x];
        float v2  = data[3*y*image->sSizeX + 3*x ];
        if ( v1 == 0)
        {
           data[3*y*image->sSizeX + 3*x] = 0;
           data[3*y*image->sSizeX + 3*x + 1] = 0;
           data[3*y*image->sSizeX + 3*x + 2] = 0;
           continue;
        }
        awpPoint p;
        p.X = x;
        p.Y = y;
        double dist = 0;
        awpDistancePoints(center, p, &dist);
        if (dist > rt*r)
        {
              data[3*y*image->sSizeX + 3*x] = 0;
              data[3*y*image->sSizeX + 3*x + 1] = 0;
              data[3*y*image->sSizeX + 3*x + 2] = 0;
              continue;
        }
        if (v2 < b *t)
        {
              data[3*y*image->sSizeX + 3*x + 2] = 255;
        }
        else
        {
              data[3*y*image->sSizeX + 3*x] = 0;
              data[3*y*image->sSizeX + 3*x + 1] = 0;
              data[3*y*image->sSizeX + 3*x + 2] = 0;
        }
    }
  }
  return true;
}
bool bloodApplyMask(awpImage* src, awpImage* mask, awpImage* mask1)
{
    if (src == NULL || mask == NULL || mask1 == NULL)
        return false;
    if (src->sSizeX != mask->sSizeX || src->sSizeY != mask->sSizeY)
        return false;
    if (src->sSizeX != mask1->sSizeX || src->sSizeY != mask1->sSizeY)
        return false;
    AWPBYTE* s = (AWPBYTE*)src->pPixels;
    AWPBYTE* m = (AWPBYTE*)mask->pPixels;
    AWPBYTE* m1 = (AWPBYTE*)mask1->pPixels;

    for (int i = 0; i < src->sSizeX*src->sSizeY; i++)
    {
        if (m1[i] == 0)
            continue;
        if (m[i] > 0)
            s[3*i + 2] = 255;
    }
    return true;
}

bool bloodMaskAverage(awpImage* img, awpImage* mask, double& b)
{
    if (img == NULL || mask == NULL)
        return false;
    b = 0;
    int count = 0;
    AWPBYTE* m = (AWPBYTE*)mask->pPixels;
    AWPBYTE* d = (AWPBYTE*)img->pPixels;
    for (int i = 0; i < img->sSizeX*img->sSizeY; i++)
    {
       if (m[i] == 0)
        continue;
       count++;
       b += d[3*i];
    }
    b /= count;
}


bool bloodGetObjects(awpImage* binary, awpImage* img, double mw, double mh, TLFObjectList& list)
{
    list.Clear();
    awpStrokeObj* obj = NULL;
    int Num = 0;
    if (awpGetStrokes(binary, &Num,  &obj, 128,  NULL) != AWP_OK)
        return false;
    for (int i = 0; i < Num; i++)
    {
        awpRect r;
        awpCalcObjRect(&obj[i], &r);
        int w = r.right - r.left;
        int h = r.bottom - r.top;
        if (w >= mw && h >= mh)
        {
           int s = 0;
           double d = 0;
           double p = 0;
           awpContour* c = NULL;
           awpStrObjSquare(&obj[i], &s);
           awpGetObjIntensity(img, &obj[i], &d);
           awpCreateContour(&c, 2*obj[i].Num, true);
           awpGetObjCountour(&obj[i], c);
           awpContAddPoint(c, &c->Points[0]);
           awpGetContPerim(c, &p);
           TLFBloodItem* item = new TLFBloodItem(d,s,p, c);
           list.Add(item);
           awpFreeContour(&c);
        }
        else
        {
            awpDrawStrokeObj(binary, &obj[i], 0);
        }
    }
    awpFreeStrokes(Num, &obj);
    return true;
}


TLFBloodItem::TLFBloodItem(double d, double s, double p, awpContour* c, int num)
{
      this->m_density = d;
      this->m_square  = s;
      this->m_num = num;
      this->m_perimeter = p;
      if (c != NULL)
      {
          awpCreateContour(&m_c, c->NumPoints, true);
          for (int i = 0; i < c->NumPoints; i++)
          {
            m_c->Points[i] = c->Points[i];
          }
      }
      else
        m_c = NULL;
}
TLFBloodItem::~TLFBloodItem()
{
    if (m_c != NULL)
        awpFreeContour(&m_c);
}
void TLFBloodItem::Draw(awpImage* img, AWPBYTE Value)
{
    double v = Value == 255?1:0;
    awpDrawPolygon (img, m_c, v, 255, 1);
}

double TLFBloodItem::GetDensity()
{
    return this->m_density;
}
double TLFBloodItem::GetSquare()
{
    return this->m_square;
}
double TLFBloodItem::GetPerimeter()
{
    return this->m_perimeter;
}
int    TLFBloodItem::GetNum()
{
    return this->m_num;
}

#pragma package(smart_init)
