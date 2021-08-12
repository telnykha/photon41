//---------------------------------------------------------------------------

#ifndef PhLandmarksToolH
#define PhLandmarksToolH
//---------------------------------------------------------------------------
#include "PhImageTool.h"
#include "_LF.h"
class PACKAGE TPhLandmarksTool : public TPhImageTool
{
private:
	bool   m_down;
	TLFDBLandmarks m_db;
	TLFLandmarkFile* m_file;
    int    m_selected;
protected:
	bool __fastcall IsNearPoint(int x, int y, int& idx);
	bool __fastcall GetConnected();
	TLFDBLandmarks* __fastcall GetDatabase();
public:
	__fastcall TPhLandmarksTool(TComponent* Owner);
   virtual __fastcall ~TPhLandmarksTool();

	virtual void Draw(TCanvas* Canvas);
	virtual void MouseDown(int X, int Y, TMouseButton Button = mbLeft);
	virtual void MouseUp(int X, int Y, TMouseButton Button = mbLeft);
	virtual void MouseMove(int X, int Y, TShiftState Shift);
	virtual void Reset();

	// database wrapper
	bool __fastcall Connect(const UnicodeString& fileName);
	void __fastcall Close();
	bool __fastcall SelectFile(const UnicodeString& fileName);

	__property bool Connected = {read = GetConnected};
	__property TLFDBLandmarks* db = {read = GetDatabase};
};
#endif
