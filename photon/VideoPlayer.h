#ifndef _video_player_h_
#define _video_player_h_

#ifdef VIDEOPLAYER_EXPORTS
#define VIDEOPLAYER_API  __declspec(dllexport)   
#else
#define VIDEOPLAYER_API  __declspec(dllimport) 
#endif


#include "Image.h"

#define EXPORT_INFO_FORMAT_DEFAULT 0
#define EXPORT_INFO_FORMAT_COMPACT 1
#define EXPORT_INFO_FORMAT_CSV 2
#define EXPORT_INFO_FORMAT_FLAT 3
#define EXPORT_INFO_FORMAT_INI 4
#define EXPORT_INFO_FORMAT_JSON 5
#define EXPORT_INFO_FORMAT_XML 6

#define EXPORT_INFO_MEDIA 0
#define EXPORT_INFO_META  1


// идентифицирует плеер в памяти
DECLARE_HANDLE(HVIDEOPLAYER);
DECLARE_HANDLE(HFILTERLIST);
DECLARE_HANDLE(HSTREAM);
DECLARE_HANDLE(HDETECTOR);


typedef  void (__stdcall *ExportCallback)(int* ct);
typedef  void (__stdcall *FDetectorCallback)(void* ct);
typedef  void (__stdcall *CancelCallback)(bool* calncel);
typedef  void (__stdcall *ErrorCallback)(LPWSTR lpMessage);
typedef  void (__stdcall *FinishCallback)();
typedef  void (__stdcall *FinishInfoCallback)(LPCWSTR lpFileName);

typedef struct
{
	HWND		hWnd;
	ExportCallback OnProgress;
	//CancelCallback OnCancel;
	ErrorCallback  OnError;
	FinishCallback OnFinish;
	FinishInfoCallback OnFinishInfo;
}SExportSettings;

VIDEOPLAYER_API HVIDEOPLAYER __stdcall createMediaPlayer();
VIDEOPLAYER_API HRESULT __stdcall closeMediaPlayer(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall setMainWindowHandle(HVIDEOPLAYER hplayer, HANDLE handle);
VIDEOPLAYER_API HRESULT __stdcall refreshMainWindow(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall resizeMainWindow(HVIDEOPLAYER hplayer);

VIDEOPLAYER_API HRESULT __stdcall refreshFilterWindow(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall resizeFilterWindow(HVIDEOPLAYER hplayer);

VIDEOPLAYER_API HRESULT __stdcall setMainWindowEnabled(HVIDEOPLAYER hplayer, bool enabled);
VIDEOPLAYER_API HRESULT __stdcall isMainWindowEnabled(HVIDEOPLAYER hplayer, bool& result);
VIDEOPLAYER_API HRESULT __stdcall setFilteredWindowHandle(HVIDEOPLAYER hplayer, HANDLE handle);
VIDEOPLAYER_API HRESULT __stdcall setFilteredWindowEnabled(HVIDEOPLAYER hplayer, bool enabled);
VIDEOPLAYER_API HRESULT __stdcall isFilteredWindowEnabled(HVIDEOPLAYER hplayer, bool& result);

/*
	работа со списком фильтров
*/
VIDEOPLAYER_API HFILTERLIST __stdcall  getFilterList(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall      getNumFilters(HFILTERLIST hlist, int& value);
VIDEOPLAYER_API LPCWSTR	__stdcall      getFilterSource(HFILTERLIST hlist, int index);
VIDEOPLAYER_API HFILTER __stdcall      getFilter(HFILTERLIST hlist, int index);
VIDEOPLAYER_API HRESULT __stdcall      addFilter(HFILTERLIST hlist, LPCWSTR lpDllName);
VIDEOPLAYER_API HRESULT __stdcall      removeFilter(HFILTERLIST hlist, LPCWSTR lpDllName);

/*работа со списком фильтров независимо от HVIDEOPLAYER*/
VIDEOPLAYER_API HFILTERLIST __stdcall    createFilterList(LPCWSTR lpConfigName);
VIDEOPLAYER_API HRESULT     __stdcall    destroyFilterList(HFILTERLIST hlist);
VIDEOPLAYER_API HIMAGE      __stdcall    applyFilterList(HFILTERLIST hlist, HIMAGE hframe);

VIDEOPLAYER_API char* __stdcall   getLastErrorDescription(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall tryOpenMediaFile(HVIDEOPLAYER hplayer, LPWSTR FileName);
VIDEOPLAYER_API HRESULT __stdcall tryOpenMediaStream(HVIDEOPLAYER hplayer, HSTREAM stream, const char* fileName);
VIDEOPLAYER_API HRESULT __stdcall closeMedia(HVIDEOPLAYER hplayer );
VIDEOPLAYER_API HRESULT __stdcall isMediaOpened(HVIDEOPLAYER hplayer, bool& result);
VIDEOPLAYER_API HRESULT __stdcall startPlayback(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall stopPlayback(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall isPlaying(HVIDEOPLAYER hplayer, bool& result);
VIDEOPLAYER_API HRESULT __stdcall getCurrentTime(HVIDEOPLAYER hplayer, double& result);
VIDEOPLAYER_API HRESULT __stdcall getDuration(HVIDEOPLAYER hplayer, double& result);
VIDEOPLAYER_API HRESULT __stdcall getFps(HVIDEOPLAYER hplayer, double& result);
VIDEOPLAYER_API HRESULT __stdcall seekFrame(HVIDEOPLAYER hplayer, double frameTime);
VIDEOPLAYER_API HRESULT __stdcall keyFrameSeek(HVIDEOPLAYER hplayer, double frameTime, double& resultTime);
VIDEOPLAYER_API HRESULT __stdcall seekToNextFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall seekToPrevFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall seekToNextKeyFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall seekToPrevKeyFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall seekToStart(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall seekToEnd(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall setSoundMute(HVIDEOPLAYER hplayer, bool mute);
VIDEOPLAYER_API HRESULT __stdcall getSoundMute(HVIDEOPLAYER hplayer, bool& result);
VIDEOPLAYER_API HRESULT __stdcall setSoundLevel(HVIDEOPLAYER hplayer, double level);
VIDEOPLAYER_API HRESULT __stdcall getSoundLevel(HVIDEOPLAYER hplayer, double& result);
VIDEOPLAYER_API   HIMAGE __stdcall exportCurrentFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API   HIMAGE __stdcall exportSpecificFrame(HVIDEOPLAYER hplayer, double time);
VIDEOPLAYER_API   HIMAGE __stdcall exportCurrentFilteredFrame(HVIDEOPLAYER hplayer);
VIDEOPLAYER_API HRESULT __stdcall exportMediaToStream(HVIDEOPLAYER hplayer, double startTime, double duration, HSTREAM stream,
        SExportSettings& settings, ExportCallback callback);
VIDEOPLAYER_API HRESULT __stdcall exportMediaToFile(HVIDEOPLAYER hplayer, double startTime, double duration, LPCWSTR fileName,
        SExportSettings& settings);
VIDEOPLAYER_API HRESULT __stdcall exportFilteredMediaToStream(HVIDEOPLAYER hplayer, double startTime, double duration, LPCWSTR fileName,
        SExportSettings& settings);
VIDEOPLAYER_API HRESULT __stdcall exportFilteredMediaToFile(HVIDEOPLAYER hplayer, double startTime, double duration, LPCWSTR fileName,
        SExportSettings& settings);
VIDEOPLAYER_API HRESULT __stdcall applyDetector(HVIDEOPLAYER hplayer, HDETECTOR detector, double startTime, double duration,
        FDetectorCallback callback);
VIDEOPLAYER_API HRESULT __stdcall applyDetectorAfterFiltration(HVIDEOPLAYER hplayer, HDETECTOR detector, double startTime, double duration,
        FDetectorCallback callback);
VIDEOPLAYER_API   HRESULT __stdcall cancelExport(HVIDEOPLAYER hplayer);


VIDEOPLAYER_API HFILTER	  __stdcall createFilter(LPCWSTR lpDllName);
VIDEOPLAYER_API HRESULT	 __stdcall  destroyFilter(HFILTER hfilter);
VIDEOPLAYER_API HRESULT  __stdcall  getFilterID(HFILTER hfilter, int& id);
VIDEOPLAYER_API LPCWSTR  __stdcall  getFilterName(HFILTER hfilter);
VIDEOPLAYER_API LPCWSTR  __stdcall  getFilterDescription(HFILTER hfilter);
VIDEOPLAYER_API LPCWSTR  __stdcall  getFilterInitString(HFILTER hfilter);
VIDEOPLAYER_API HRESULT  __stdcall  setFilterInitString(HFILTER hfilter, LPCWSTR lpInitString);
VIDEOPLAYER_API HRESULT  __stdcall  getFilterMinimumAheadFrameNumber(HFILTER hfilter, int& num);
VIDEOPLAYER_API HIMAGE   __stdcall  applyFilter(HFILTER hfilter, HIMAGE hframe, double timestamp, bool isResultNeeded);
VIDEOPLAYER_API HRESULT  __stdcall  resetFilter(HFILTER hfilter);
VIDEOPLAYER_API HRESULT  __stdcall  getFilterEnabled(HFILTER hfilter, bool& enabled);
VIDEOPLAYER_API HRESULT  __stdcall  setFilterEnabled(HFILTER hfilter, bool value);
VIDEOPLAYER_API HRESULT  __stdcall  getFilterDefault(HFILTER hfilter, bool& value);
VIDEOPLAYER_API HRESULT	 __stdcall  getFilterNumParams(HFILTER hfilter, int& num);
VIDEOPLAYER_API LPCWSTR  __stdcall  getFilterParamName(HFILTER hfilter, int index);
VIDEOPLAYER_API HRESULT  __stdcall  getFilterParamValue(HFILTER hfilter, int index, double& value);
VIDEOPLAYER_API LPCWSTR  __stdcall  getFilterParamDescription(HFILTER hfilter, int index);
VIDEOPLAYER_API HRESULT	 __stdcall  setFilterParamValue(HFILTER hfilter, int index, double value);
VIDEOPLAYER_API HRESULT __stdcall   loadFilterConfig(HFILTER hfilter, LPCWSTR lpFileName);
VIDEOPLAYER_API HRESULT  __stdcall  saveFilterConfig(HFILTER hfilter, LPCWSTR lpFileName);

VIDEOPLAYER_API HRESULT  __stdcall  getFilterIndex(HFILTER hfilter, HFILTERLIST hlist, int& index);
VIDEOPLAYER_API HRESULT  __stdcall  setFilterIndex(HFILTER hfilter, HFILTERLIST hlist, int index);

/*
	работа с информацией о файле.
	- получении информации о формате файла
	- получение информации о потоках внутри файла
	- получение информации о метаданных

*/
VIDEOPLAYER_API HRESULT  __stdcall  getMediaInfo(HVIDEOPLAYER hplayer, int Options, int OutFormat, LPCWSTR lpOutFileName, 
	SExportSettings& settings);
#endif //_video_player_h_
