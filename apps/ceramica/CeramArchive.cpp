//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#include "awpipl.h"
#include "_LF.h"
#include "CeramArchive.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)

TCeramArchive::TCeramArchive(const char* path)
{
    this->m_path = path;
    m_pLog       = NULL;
	m_archive    = "";
	m_counter = 0;
}

TCeramArchive::~TCeramArchive()
{
}

bool TCeramArchive::Create(TCeramArchiveHeader& header)
{
    UnicodeString str = m_path.c_str();
    str += L"\\";
    str += DateToStr(Now());
    str += L"\\";

    if (!DirectoryExists(str))
        CreateDir(str);
    UnicodeString t = TimeToStr(Now());
    AnsiString _ansi = t;
    std::string _s = _ansi.c_str();
    std::replace(_s.begin(), _s.end(), ':', '-');
    _ansi = _s.c_str();


    str += _ansi;
    if (!CreateDir(str))
        return false;
    _ansi = str;
    m_archive = _ansi.c_str();
    _ansi += "\\results.log";

    m_pLog = fopen(_ansi.c_str(), "w+t");
    if (m_pLog == NULL)
    	return false;

    fprintf(m_pLog, "%s\n", "ceram01");
    fprintf(m_pLog, "%f\n", header.alfa);
    fprintf(m_pLog, "%i\n", header.bufferSize);
    fprintf(m_pLog, "%i\n", header.dutyRatio);
    fprintf(m_pLog, "%i\n", header.exposure);


   fprintf(m_pLog, "%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",
    "Date-time",
    "Accept",
    "Diam",
    "x-pos",
    "y-pos",
    "minor",
    "major",
    "angle",
    "image"
    );
	fprintf(m_pLog, "%s\n", "=========");
	m_counter = 0;
	return true;
}

void TCeramArchive::Close()
{
   if (m_pLog != NULL)
    fclose(m_pLog);
}

bool TCeramArchive::AddRecord(TCeramArchiveRecord& record)
{
    if (m_pLog == NULL)
		return false;
	m_counter++;
    UnicodeString s = DateTimeToStr(Now());
    AnsiString _ansi = s;
 //   UUID _id;
 //   LF_UUID_CREATE(_id)
	char buf[32];
	sprintf(buf, "%06d", m_counter);
	std::string _fn =  buf;//LFGUIDToString(&_id);
    _fn += ".jpg";
    std::string _ifn = m_archive.c_str();
    _ifn += "\\";
    _ifn += _fn;
	// запись в файл архива
    fprintf(m_pLog, "%s\t%i\t%f\t%f\t%f\t%f\t%f\t%f\t%s\n",
    _ansi.c_str(),
    record.acceptable,
    record.diam,
    record.xpos,
    record.ypos,
    record.mi,
    record.ma,
    record.angle,
    _fn.c_str()
    );
    awpSaveImage(_ifn.c_str(), record.img);
    return true;
}
