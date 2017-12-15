//---------------------------------------------------------------------------
#ifndef PhFramesH
#define PhFramesH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------

#define _FRAME_MIN_COUNT_ 3

class TPhCustomImage;
//class TDIBImage;
class TPhReadImagesThread;
class TPhCopyImagesThread;
struct SFrameItem
{
    UnicodeString strFileName;
    int           width;
    int           height;
    bool          selected;
};
class PACKAGE TPhFrames : public TObject
{
private:
	TPhCustomImage* 		m_pDisplay;
    TList*                  m_items;
    TGraphic*               m_pMosaic;
	TPhReadImagesThread* 	m_pReader;
    TPhCopyImagesThread*    m_pCopier;
    int       				m_current;
    void __fastcall OnTerminateHelper(TObject *Sender);
    void __fastcall OnCopyTerminateHelper(TObject *Sender);
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
    void __fastcall GoFrame(long num);

    // operations
    bool __fastcall DeleteImage(long num);
    bool __fastcall DeleteSelected();

    bool __fastcall CopySelected(const LPWSTR lpDirName);
    bool __fastcall MoveSelected(const LPWSTR lpDirName);

	// selectiom
	void __fastcall SelectAll();
	void __fastcall InvertSelection();
	void __fastcall ClearSelection();

    SFrameItem* GetFrameItem(long num);
    __property SFrameItem* Frame[long index] = {read = GetFrameItem};
    __property int Count = {read = GetCount};
    __property int CurrentFrame = {read = m_current};
    __property TGraphic* Mosaic = {read = m_pMosaic};

};
#endif
