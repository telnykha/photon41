//---------------------------------------------------------------------------

#pragma hdrstop
#include "PhFrames.h"
#include "FImage41.h"
//---------------------------------------------------------------------------
TPhFrames::TPhFrames(TPhCustomImage* display)
{
    m_names = new TStringList();
    m_pDisplay = display;
    m_current = 0;
}
__fastcall TPhFrames::~TPhFrames()
{
   delete m_names;
}

bool TPhFrames::Init(TStrings* names)
{
    if (names == NULL)
        return false;

    Close();
    m_names->SetStrings(names);
    if (m_names->Count > 0)
    {
        First();
    }
    else
        return false;
}
void TPhFrames::Close()
{
    m_names->Clear();
    m_current = 0;
}

void __fastcall TPhFrames::First()
{
	if ( m_names->Count == 0 )
        return;

    m_current = 0;
    AnsiString strFileName = m_names->Strings[m_current];
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Next()
{
	if ( m_names->Count == 0 )
        return;

    m_current++;
    if (m_current >= m_names->Count)
        m_current = 0;
    AnsiString strFileName = m_names->Strings[m_current];
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Prev()
{
	if ( m_names->Count == 0 )
        return;

    m_current--;
    if (m_current < 0)
        m_current = m_names->Count - 1;
    AnsiString strFileName = m_names->Strings[m_current];
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Last()
{
	if ( m_names->Count == 0 )
        return;

    m_current = m_names->Count - 1;
    AnsiString strFileName = m_names->Strings[m_current];
    m_pDisplay->LoadFromFile(strFileName.c_str());
}
void __fastcall TPhFrames::Frame(long num)
{
    if (num >= 0 && num < m_names->Count)
    {
        m_current = num;
        AnsiString strFileName = m_names->Strings[m_current];
        m_pDisplay->LoadFromFile(strFileName.c_str());
    }
}

int __fastcall TPhFrames::GetCount()
{
    return this->m_names->Count;
}


#pragma package(smart_init)
