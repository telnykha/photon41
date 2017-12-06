//---------------------------------------------------------------------------
#ifndef PhFramesH
#define PhFramesH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TPhCustomImage;
class TDIBImage;
class TPhReadImagesThread;
struct SFrameItem
{
    UnicodeString strFileName;
    bool          selected;
};
class PACKAGE TPhFrames : public TObject
{
private:
	TPhCustomImage* 		m_pDisplay;
	TStrings* 				m_names;
    TList*                  m_items;
    TGraphic*               m_pMosaic;
	TPhReadImagesThread* 	m_pReader;
    int       				m_current;
    void __fastcall OnTerminateHelper(TObject *Sender);
protected:
    int __fastcall GetCount();
public:
    TPhFrames(TPhCustomImage* display);
    __fastcall virtual~TPhFrames();

    // init
    bool Init(TStrings* names);
    void Close();

    // navigation
    void __fastcall First();
    void __fastcall Next();
    void __fastcall Prev();
    void __fastcall Last();
    void __fastcall Frame(long num);

    __property int Count = {read = GetCount};
    __property int CurrentFrame = {read = m_current};
    __property TGraphic* Mosaic = {read = m_pMosaic};
};
#endif
