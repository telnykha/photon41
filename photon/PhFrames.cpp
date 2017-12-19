//---------------------------------------------------------------------------
#include <Vcl.Dialogs.hpp>
#pragma hdrstop
#include "PhFrames.h"
#include "FImage41.h"
#include "PhReadImagesThread.h"
#include "DIBImage41.h"

#define _FRAME_ITEM_(a) ((SFrameItem*)(m_items->Items[a]))

// Frame Items List. Service class to support automatic
// deletion of the SFrameItem
class TFramesList : public TList
{
public:
virtual void __fastcall Notify(void * Ptr, TListNotification Action)
{
    if (Action == lnDeleted)
    {
        SFrameItem* item = (SFrameItem*)Ptr;
        delete item;
    }
}
};

//---------------------------------------------------------------------------
TPhFrames::TPhFrames(TPhCustomImage* display)
{
    m_items = new TFramesList();
	m_pDisplay = display;
    m_current = 0;
    m_pMosaic = new TDIBImage();
    m_pReader = NULL;
    m_pCopier = NULL;
}
__fastcall TPhFrames::~TPhFrames()
{
   delete m_pMosaic;
   delete m_items;
   if (m_pReader != NULL)
	   delete m_pReader;
   if (m_pCopier != NULL)
	   delete m_pCopier;
}

bool TPhFrames::Init(TStrings* names)
{
    if (names == NULL)
        return false;
    Close();
    //
    for (int i = 0; i < names->Count; i++)
    {
      SFrameItem* item = new SFrameItem();
      item->strFileName = names->Strings[i];
      item->selected = false;
      m_items->Add(item);
    }

	if (names->Count > 0)
    {
		First();
        StartReadJobHelper();
    }
    else
        return false;
}
void TPhFrames::Close()
{
    m_items->Clear();
    Cancel();
    m_current = 0;
    m_pMosaic->Assign(NULL);
}

void TPhFrames::StartReadJobHelper()
{
    if (m_items->Count >= _FRAME_MIN_COUNT_  )
    {
        if (m_pReader != NULL)
        {
            m_pReader->Cancel();
            m_pReader->WaitFor();
        }

        m_pReader = new TPhReadImagesThread(m_items);
        m_pReader->FreeOnTerminate = true;
        m_pReader->OnTerminate = OnTerminateHelper;

        m_pReader->tmbWidth  = m_pDisplay->ThumbWidht;
        m_pReader->tmbHeight = m_pDisplay->ThumbHeight;
        m_pReader->OnProgress = m_pDisplay->OnProgress;
        m_pReader->OnFinish  = m_pDisplay->OnFinish;
        if (m_pDisplay->OnStart)
            m_pDisplay->OnStart(this);
        m_pReader->Start();
    }
}


void __fastcall TPhFrames::First()
{
	if ( m_items->Count == 0 )
        return;

    m_current = 0;
    AnsiString strFileName = _FRAME_ITEM_(m_current)->strFileName;
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Next()
{
	if ( m_items->Count == 0 )
        return;

    m_current++;
    if (m_current >= m_items->Count)
        m_current = 0;
    AnsiString strFileName = _FRAME_ITEM_(m_current)->strFileName;
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Prev()
{
	if ( m_items->Count == 0 )
        return;

    m_current--;
    if (m_current < 0)
        m_current = m_items->Count - 1;
    AnsiString strFileName = _FRAME_ITEM_(m_current)->strFileName;
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Last()
{
	if ( m_items->Count == 0 )
        return;

    m_current = m_items->Count - 1;
    AnsiString strFileName =_FRAME_ITEM_(m_current)->strFileName;
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::GoFrame(long num)
{
    if (num >= 0 && num < m_items->Count)
    {
        m_current = num;
        AnsiString strFileName = _FRAME_ITEM_(m_current)->strFileName;
        m_pDisplay->LoadFromFile(strFileName.c_str());
    }
}

int __fastcall TPhFrames::GetCount()
{
    return m_items->Count;
}

void __fastcall TPhFrames::OnTerminateHelper(TObject *Sender)
{
#ifdef _DEBUG
    if (m_pReader != NULL && !m_pReader->Canceled)
	    ShowMessage("Job done.");
    else
        ShowMessage("Job canceled.");
#endif
	if (m_pReader != NULL && !m_pReader->Canceled)
    {
       TDIBImage* img = dynamic_cast< TDIBImage*>(m_pMosaic);
       if (img != NULL)
	       img->SetAWPImage(m_pReader->Mosaic);
       if (m_pDisplay->Mosaic)
       {
		m_pDisplay->Bitmap->Assign(img);
		m_pDisplay->Paint();
	   }
	}
	if (m_pReader != NULL && m_pReader->Canceled)
	{
		if (m_pDisplay->OnCancel)
            m_pDisplay->OnCancel(this);
	}
    m_pReader = NULL;
}

void __fastcall TPhFrames::OnCopyTerminateHelper(TObject *Sender)
{
	if (m_pCopier == NULL)
		return;
	if (m_pCopier->Canceled)
	{
		if (m_pDisplay->OnCancel)
            m_pDisplay->OnCancel(this);
	}
	if (m_items->Count == 0)
	{
		m_pDisplay->Bitmap->Assign(NULL);
        m_pDisplay->Paint();
	}
    if (m_pCopier->reason != copyJob  && m_items->Count >= _FRAME_MIN_COUNT_)
    {
		StartReadJobHelper();
    }
    m_pCopier = NULL;
}

bool __fastcall TPhFrames::DeleteImage(long num)
{
    if (num < 0 || num >= m_items->Count)
        return false;

    UnicodeString FileName = _FRAME_ITEM_(num)->strFileName;
    DeleteFile(FileName);
    m_items->Delete(num);

    m_pMosaic->Assign(NULL);

    if (m_items->Count >= _FRAME_MIN_COUNT_)
    {
		StartReadJobHelper();
    }
    return true;
}

bool __fastcall TPhFrames::DeleteSelected()
{
     if (this->m_pCopier != NULL)
    {
        m_pCopier->Terminate();
        m_pCopier->WaitFor();
    }

    m_pCopier = new TPhCopyImagesThread(m_items, L"", deleteJob);
    m_pCopier->FreeOnTerminate = true;
    m_pCopier->OnTerminate = OnCopyTerminateHelper;
    m_pCopier->OnFinish = m_pDisplay->OnFinish;
    m_pCopier->OnProgress = m_pDisplay->OnProgress;
    if (m_pDisplay->OnStart)
        m_pDisplay->OnStart(this);
    m_pCopier->Start();
	return true;
}

bool __fastcall TPhFrames::CopySelected(const LPWSTR lpDirName)
{
     if (this->m_pCopier != NULL)
    {
        m_pCopier->Terminate();
        m_pCopier->WaitFor();
    }

    m_pCopier = new TPhCopyImagesThread(m_items, lpDirName, copyJob);
    m_pCopier->FreeOnTerminate = true;
    m_pCopier->OnTerminate = OnCopyTerminateHelper;
    m_pCopier->OnFinish = m_pDisplay->OnFinish;
    m_pCopier->OnProgress = m_pDisplay->OnProgress;
    if (m_pDisplay->OnStart)
        m_pDisplay->OnStart(this);
    m_pCopier->Start();
    return true;
}

bool __fastcall TPhFrames::MoveSelected(const LPWSTR lpDirName)
{
    if (this->m_pCopier != NULL)
    {
        m_pCopier->Terminate();
        m_pCopier->WaitFor();
    }
    m_pCopier = new TPhCopyImagesThread(m_items, lpDirName, moveJob);
    m_pCopier->FreeOnTerminate = true;
    m_pCopier->OnTerminate = OnCopyTerminateHelper;
    m_pCopier->OnProgress = m_pDisplay->OnProgress;
    m_pCopier->OnFinish = m_pDisplay->OnFinish;
    if (m_pDisplay->OnStart)
        m_pDisplay->OnStart(this);
    m_pCopier->Start();
    return true;
}

SFrameItem* TPhFrames::GetFrameItem(long num)
{
    if (num >= 0 && num < m_items->Count)
    {
		return _FRAME_ITEM_(num);
	}
    else
        return NULL;
}

void __fastcall TPhFrames::SelectAll()
{
	if (m_pDisplay == NULL)
		return;
	if (!m_pDisplay->Mosaic)
		return;
	if (this->m_items == NULL)
		return;
	for(int i = 0; i < m_items->Count; i++)
	{
	   SFrameItem* item = _FRAME_ITEM_(i);
	   if (item)
	   {
		item->selected = true;
	   }
	}

	m_pDisplay->Paint();
}
void __fastcall TPhFrames::InvertSelection()
{
	if (m_pDisplay == NULL)
		return;
	if (!m_pDisplay->Mosaic)
		return;
	if (this->m_items == NULL)
		return;
	for(int i = 0; i < m_items->Count; i++)
	{
	   SFrameItem* item = _FRAME_ITEM_(i);
	   if (item)
	   {
		item->selected = !item->selected;
	   }
	}

	m_pDisplay->Paint();
}

void __fastcall TPhFrames::ClearSelection()
{
	if (m_pDisplay == NULL)
		return;
	if (!m_pDisplay->Mosaic)
		return;
	if (m_pDisplay == NULL)
		return;

	for(int i = 0; i < m_items->Count; i++)
	{
	   SFrameItem* item = _FRAME_ITEM_(i);
	   if (item)
	   {
		item->selected = false;
	   }
	}

    m_pDisplay->Paint();
}

void TPhFrames::Cancel()
{
    if (m_pReader != NULL)
    {
        m_pReader->Cancel();
        m_pReader->WaitFor();
    }

    if (this->m_pCopier != NULL)
    {
		m_pCopier->Cancel();
		m_pCopier->WaitFor();
    }
}
#pragma package(smart_init)
