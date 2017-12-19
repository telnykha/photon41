//---------------------------------------------------------------------------

#ifndef PhReadImagesThreadH
#define PhReadImagesThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "awpipl.h"
#include "FImage41.h"
//---------------------------------------------------------------------------
// this is abstract PhThread to deal with items list.
class IPthThread : public TThread
{
protected:
    TList*    			m_items;
    UnicodeString 		m_msg;
    int       			m_progress;
    bool      			m_cancel;
    TPhProgressEvent    m_OnProgress;
    void __fastcall ProgressHelper();

public:
    __fastcall IPthThread(TList* items);
	void __fastcall Cancel();

	__property bool Canceled = {read = m_cancel};
    __property TPhProgressEvent OnProgress = {read = m_OnProgress, write = m_OnProgress};
};


//---------------------------------------------------------------------------
// This thread reads the images from TList and creates mosaic
// with tmbWidth and  tmbHeight for each image
class TPhReadImagesThread : public IPthThread
{
private:
    TPhJobEvent  m_FihishEvent;
    awpImage* m_mosaic;
    int       m_tmbWidth;
    int       m_tmbHeight;
protected:
	void __fastcall Execute();
    virtual void __fastcall BeforeDestruction(void);
public:
	__fastcall TPhReadImagesThread(TList* items);
    virtual __fastcall ~TPhReadImagesThread();
    __property awpImage* Mosaic = {read = m_mosaic};
    __property int tmbWidth 	= {read = m_tmbWidth, write = m_tmbWidth};
    __property int tmbHeight    = {read = m_tmbHeight, write = m_tmbHeight};
    __property TPhJobEvent  OnFinish = {read = m_FihishEvent, write =m_FihishEvent};
};
//---------------------------------------------------------------------------
// this thread performs copy, move and delete operations
class TPhCopyImagesThread : public IPthThread
{
private:
    TPhJobEvent  m_FihishEvent;
    EPhJobReason m_reason;
    UnicodeString m_FolderName;
    virtual void __fastcall BeforeDestruction(void);
protected:
	void __fastcall Execute();
public:
	__fastcall TPhCopyImagesThread(TList* names,const LPWSTR lpwFolderName, EPhJobReason reason = copyJob);
 //   __property EPhCopyThreadOperations operation = {read = m_operatoin};
    __property EPhJobReason reason = {read = m_reason};
    __property TPhJobEvent  OnFinish = {read = m_FihishEvent, write =m_FihishEvent};
};
#endif
