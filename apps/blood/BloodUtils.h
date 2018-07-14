//---------------------------------------------------------------------------
#ifndef BloodUtilsH
#define BloodUtilsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "awpipl.h"
#include "_LF.h"


#define MAX_FILE_COUNT 30
#define IMAGE_WIDTH    320
#define IMAGE_HEIGHT   240

struct ImageItem
{
    double  delta;
    awpRect rect;
};

class TLFBloodItem : public TLFObject
{
private:
  double m_density;
  double m_square;
  double m_perimeter;
  awpContour* m_c;
  int m_num;
public:
    TLFBloodItem(double d, double s, double p, awpContour* c, int num = 0);
    virtual ~TLFBloodItem();
    void Draw(awpImage* img, AWPBYTE Value);

    double GetDensity();
    double GetSquare();
    double GetPerimeter();
    int    GetNum();
};

bool bloodCheckFolder(UnicodeString& strPath, TStringList* fileNames);
bool bloodFindVisibleArea(awpImage* image, awpContour** c, double& radius, double& error);
bool bloodVisisbleAreaRadiusError(awpContour* c, double& radius, double& error);
bool bloodBuildVisibleMask(awpImage* image, awpImage* mask, awpContour* c, float& b);
bool bloodMaskAverage(awpImage* img, awpImage* mask, double& b);
bool bloodBinary(awpImage* image, awpImage* mask, float b, float t, double r, double rt);
bool bloodApplyMask(awpImage* src, awpImage* mask, awpImage* mask1);
bool bloodGetObjects(awpImage* binary, awpImage* img, double mw, double mh,  TLFObjectList& list);
#endif
