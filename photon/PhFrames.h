//---------------------------------------------------------------------------
#ifndef PhFramesH
#define PhFramesH
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TPhCustomImage;
class TPhReadImagesThread;
class PACKAGE TPhFrames : public TObject
{
private:
	TPhCustomImage* 		m_pDisplay;
	TPhReadImagesThread* 	m_pReader;
	TStrings* m_names;
    int       m_current;
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
};
#endif
