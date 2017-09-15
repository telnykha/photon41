//---------------------------------------------------------------------------

#ifndef FFMPEGcoreH
#define FFMPEGcoreH
//---------------------------------------------------------------------------
extern "C"
{
    #include <libavcodec\avcodec.h>
    #include <libavformat\avformat.h>
    #include <libavfilter\avfiltergraph.h>
    #include <libavfilter\avcodec.h>
    #include <libavfilter\buffersink.h>
    #include <libavfilter\buffersrc.h>
    #include <libswscale\swscale.h>
    #include "libavutil\opt.h"
    #include  "awpipl.h"
}

//#define _SDL_config_win32_h
#include "SDL.h"
#define __STDLIB_OVERLOADS__
#include <vector>
#include <list>
#include <deque>
#include <algorithm>


#define VIDEO_PICTURE_QUEUE_SIZE 1
using namespace std;

/*major error codes
*/
#define FFMPEG_PLAYER_OK 0
#define FFMPEG_PLAYER_CANNOT_OPEN_MEDIA -1
#define FFMPEG_PLAYER_CANNOT_SAVE_MEDIA -2
#define FFMPEG_PLAYER_ERROR_DECODING   -3
/*������ �����������
*/
#define FFMPEG_TRANCODER_UNSUPPORTED_FORMAT			-4
#define FFMPEG_TRANCODER_CANNOTOPEN_FILE			-5
#define FFMPEG_TRANCODER_CANNOT_WRITE_HDR			-6
#define FFMPEG_TRANCODER_TRANSCODE_ERROE			-7
#define FFMPEG_TRANCODER_CANNOT_WRITE_TRAILER		-8
/*minor error codes
*/
#define FFMPEG_PLAYER_CANNOT_INIT_SDL   -1
#define FFMPEG_PLAYER_CANNOT_OPEN_FILE  -2
#define FFMPEG_PLAYER_CANNOT_FIND_STREAMS -3
#define FFMPEG_PLAYER_HASNOT_VIDEO -4
#define FFMPEG_PLAYER_CANNOT_OPEN_AUDIO -5
#define FFMPEG_PLAYER_CANNOT_OPEN_VIDEO -6
#define FFMPEG_PLAYER_USUPPORTED_FORMAT -7



class CFFMPEGPlayer;
// video picture
typedef struct VideoPicture
{
    awpImage*    image;
    int			 width, height;
    int allocated;
    double pts;
} VideoPicture;

class CVideoPicture
{
private:
	awpImage* m_pImage;
	AVPicture m_Picture;
public:
	CVideoPicture();
	~CVideoPicture();

	awpImage* SetAVFrame(AVFrame* pFrame);
	awpImage* GetImage();
};

typedef  void (__stdcall *FrameCallback)(awpImage* pict, void* UserData);
typedef  void (__stdcall *SaveFihishCallback)(int status, void* UserData);
typedef  void (__stdcall *SaveProgressCallback)(int* progress, void* UserData);

enum EFFMPEGPlayerScreenMode {smNormal, smProcessor, smAudio};
/*EFFMPEGPlayerProcessorMode
������ ��������� ����������� �����������
*/
enum EFFMPEGPlayerProcessorMode {pmNothing = 0,
    pmFlipLeft ,
    pmFlipRight,
    pmFlipHorizontal,
    pmFlipVertical,
    pmRotate180,
    pmRotateMirror90,
    pmRotateMirror270
};
/*CFrameSize
���������, �������� ������� �����������
������������ ��� ��������� ����������
�������� ����������� ����� ���������
*/
struct CFrameSize
{
    int width;
    int height;
};
/*CFrameProcessor
����� ����������� �������������� �����������.
������������ ��� Flip And Rotate
*/
class CFrameProcessor
{
private:
    EFFMPEGPlayerProcessorMode m_Mode;
public:
    CFrameProcessor();

    EFFMPEGPlayerProcessorMode GetMode();
    void SetMode(EFFMPEGPlayerProcessorMode Value);
    awpImage* ProcessFrame(awpImage* source);

    CFrameSize GetProcessedSize(CFrameSize src);
};

/*time segment class
*/
class CTimeSegment
    {
private:
    int64_t m_sp;       // start position of time segment
    int64_t m_duration; // duration of the segment
    int64_t m_ep;
    int     m_index;    // cluster number, which belongs to this segment
    bool    m_erased;   //
public:
    CTimeSegment();
    CTimeSegment(int64_t s, int64_t d);
    CTimeSegment(const CTimeSegment& ts);
    ~CTimeSegment();
    //props
    void SetStratTime(int64_t s);
    int64_t GetStartTime() const ;
    void SetDuration(int64_t d);
    const int64_t GetDuration()const ;
    int64_t GetEndTime();
    void SetIndex(int Value);
    int GetIndex()const ;
    bool GetErased() const;
    void SetErased(bool Value);
};

/*timeline class
*/
class CFFMPEGTimeLine
{
private:
    int64_t m_GlobalDuration;
    deque<CTimeSegment>    m_DelItems;        // user input
    vector<CTimeSegment>   m_VisibleItems;    // Visible segments
    vector<CTimeSegment>   m_InvisibleItems;  // Invisible segments
    deque<CTimeSegment>    m_RedoItems;
    void Calc();
    void _debug_dump_del_items();
public:
    CFFMPEGTimeLine();
    ~CFFMPEGTimeLine();
    void Init(int64_t Duration);
    void Close();
    void Add(int64_t StartPos, int64_t duration);
    //Undo-Redo support
    void Undo();
    void Redo();
    int UndoCount();
    int RedoCount();

    int64_t GetLocalDuration();
	int64_t GetGlobalDuration();
    int64_t GlobalToLocalTime(int64_t GlobalTime);
    int64_t LocalToGlobalTime(int64_t LocalTime);
    bool IsVisibleTime(int64_t t);
    int64_t GetNextVisibleTime(int64_t t);
    int64_t GetPrevVisibleTime(int64_t t);
};

enum EFFMpegEncoderMode
{
    emTimeRecoding,		/*����� ������������� �������, ������������ ��� ��������� ����������� ����� �� �������� ������*/
    emVideoProcessing   /*����� ������������� ����� � �������, ������������ ��� �������������� ����������� �
                          ��������� ���������� �� ������������ ������*/
};
/*CFFMpegEncoder
����� ��������� ����������� � ������ ������ �� ����.
*/
class CFFMpegEncoder
{
private:
    AVFormatContext* m_pInFormat;
    AVFormatContext* m_pOutFormat;
    CFFMPEGPlayer*   m_pPlayer;
    EFFMpegEncoderMode m_EncodingMode;
    std::vector<int> m_mapInout;
    int              m_InVideoStreamIndex;
    int              m_OutVideoStreamIndex;
    int              m_InAudioStreamIndex;
    int              m_OutAudioStreamIndex;
    AVFrame*         m_pFrame;
    AVFrame*         m_pAFrame;
    AVFrame*         m_pFilteredAFrame;

    AVFilterContext* m_buffersrc_ctx;
    AVFilterContext* m_buffersink_ctx;
    AVFilterGraph *  m_filter_graph;


    uint8_t*        m_pOutBuf;
    int              m_OutBufSize;
    bool             m_needProcessAudio;
    int             m_FrameCounter;

    int64_t         m_last_pkt_pts;
    int64_t         m_last_pkt_dts;
protected:
    int AddCopyStream(AVFormatContext* pOutFormat, AVStream* pInStream);
    int AddVideoStream(AVFormatContext* pOutFormat, AVStream* pInStream);
    int AddAudioStream(AVFormatContext* pOutFormat, AVStream* pInStream);

    int InitFilters();
    int DecodeAudio(AVPacket* pkt, bool& got_output);
    bool DoAudioOut();

    bool WritePaket(AVPacket* pPkt);
    bool PreparePacketTime(AVPacket* pPkt);
    bool ConvertPacket(AVPacket* pPkt);
    bool ConvertAudio(AVPacket* pPkt);

    AVFrame* PorcessFrame ();
public:
    CFFMpegEncoder(CFFMPEGPlayer* player, EFFMpegEncoderMode mode);
    ~CFFMpegEncoder();

    bool Init(AVFormatContext* pFormat, const char* lpFileName);
    bool Close();

    bool SavePacket(AVPacket* pPkt);
	bool CompleteTranscode();
    bool BeginTranscode( void );

private:
    std::string         m_filename;
};


/* ����� ��� ���������� ������
*/
struct STranscoderOptions
{
	char* m_pInputFileName; //��� �������� �����
	char* m_pOutFileName;   //��� ��������� �����
	CFFMPEGTimeLine* m_pTimeLine; //������� ������� �� ������� �����
	SaveProgressCallback* m_pProgressCallback;//������� ���������
	SaveFihishCallback*   m_pSaveFinishCallback;//������� ���������� ��������
	EFFMPEGPlayerProcessorMode m_ProcessigMode;
};

/*���������, ����������� ����� ������
*/
struct FrameBuffer
{
	uint8_t* base[4];
	uint8_t* data[4];
	int linesize[4];
	int h,w;
	enum PixelFormat pix_fmt;
	int refcount;
	struct InputStream* ist;
	struct FrameBuffer* next;
};
/* ���������, ����������� ������� ����
*/
struct InputFile
{
	AVFormatContext* m_ctx;
	int				 m_eof_reached;
};
/* ��������� ����������� �������� ����
*/
struct OutputFile
{
	AVFormatContext m_ctx;
	int64_t			m_recording_time;
	int64_t			m_start_time;
	uint64_t		m_limit_filesize;
};
/* ��������� ����������� ������� �����
*/
struct InputStream
{
	AVStream* st;
	bool	  discard;
	bool	  decoding_needed;
	AVCodec*  dec; // �������
	AVFrame*  decoded_frame;
	int64_t   start; // ����� ������ ����������
	int64_t   next_dts; // �������������� pts ��� ���������� ��������������� ������
	int64_t   pts; // ������� pts ��� ��������������� ������
	double    ts_scale;
	bool	  is_start;
	int       saw_first_ts;
	/*video resampling*/
	int		  resample_height;
	int		  resample_width;
	int		  resample_pix_fmt;
	/*audio resampling*/
	int       resample_sample_fmt;
	int       resample_sample_rate;
	int		  resample_channels;
	uint64_t  resample_channel_layout;
	FrameBuffer* buffer_pool;
	int dr1;
};

/* �����, ����������� ����������� � �������������� �����������.
*/
class CFFMpegTranscoder
{
private:
	/* ��������� ��������������
	*/
	STranscoderOptions m_Options;
	InputFile m_InputFile;
	OutputFile m_OutputFile;

	InputStream** input_streams;
	int nb_input_streams;
protected:
	bool open_input_file();
	bool add_input_streams(AVFormatContext* ic);
	void close_transcoder();
public:
	CFFMpegTranscoder();
	~CFFMpegTranscoder();
	int Init(STranscoderOptions* pOptions);
	int Transcode();
	void Cancel();
};
/*SAudioData

*/
struct SAudioData
{
	float m_minValue;
	float m_maxValue;
	float m_averageValue;
};
/*CAudioSegmet
����� ��� �������� ����������� �����������
*/
class CAudioSegment
{
private:
	int			m_numChannels;
	SAudioData	m_data[2];
	uint64_t    m_startTime;
	uint64_t    m_duration;
	bool		m_visible;
	bool        m_selected;
public:
	CAudioSegment();
	CAudioSegment( const CAudioSegment& segment);
	CAudioSegment(int NumChannels, uint64_t startTime, uint64_t duration, bool visible, bool selected, SAudioData* data);

	const bool IsSelected();
	const bool IsVisible();
	const uint64_t Duration();
	const uint64_t StartTime();
	const int NumChannels();
	const SAudioData* AudioData();

	void SetVisible(bool value);
	void SetSelected(bool value);
};

class CSafeBool
{
private:
	bool m_Value;
      SDL_mutex *m_mutex;
public:
	CSafeBool();
	~CSafeBool();
	void SetValue(bool Value);
	bool GetValue();
};

/*CFFMPEGPlayer
����� ����������� ��������������� ����� � ��� ��������������
*/
class CFFMPEGPlayer
{
private:

     EFFMPEGPlayerScreenMode m_ScreenMode;
     /* processing mode
     */
     EFFMPEGPlayerProcessorMode m_ProcessingMode;
     int m_LastErrorMajor;
     int m_LastErrorMinor;
public:
    class CImageCompare
    {
    private:
#ifdef _DEBUG
        FILE* f;
#endif
        awpImage* m_image;
        bool      first_time;
        bool      InternalCompare(awpImage* pImage, double threshold);
    public:
        CImageCompare();
        ~CImageCompare();
        bool Compare(AVPicture* frame, int height,  int width, double threshold);
        bool Compare(awpImage* frame, double threshold);
        void Reset() {first_time = true;};
    };

private:
	awpImage* m_AudioImage;
	awpImage* m_AudioImageBkg;
	std::vector<CAudioSegment> m_audioArray;
	void SetUpAudioImage();
	void UpdateAudioImage();
	void PrepareAudioSegments();
	void OnAudioDone();

    CFFMPEGTimeLine m_TimeLine;
    // packed quene support
    // TODO: make a calss to support this queue
    typedef struct PacketQueue
    {
      AVPacketList *first_pkt, *last_pkt;
      int nb_packets;
      int size;
      int abort_request;
      SDL_mutex *mutex;
      SDL_cond *cond;
    }PacketQueue;

    void packet_queue_init(CFFMPEGPlayer::PacketQueue *q);
    int  packet_queue_put(PacketQueue *q, AVPacket *pkt);
    int  packet_queue_get(PacketQueue *q, AVPacket *pkt, int block);
    void packet_queue_end(PacketQueue *q);
    void packet_queue_abort(PacketQueue *q);
    void packet_queue_flush(PacketQueue *q);
    void _flush_pakets_helper();
    AVPacket flush_pkt;

	int queue_picture(double pts);
    void schedule_refresh(int delay);

private:
    // SDL context
    SDL_Thread  *m_decode_tid; // ���� ���������� ������ ������� �� �����
    SDL_Thread  *m_video_tid;  // ���� ������������� �����������
    SDL_Thread  *m_event_tid;  // ���� ��������� �������
    SDL_Thread  *m_save_tid;   // ���� ����������

    SDL_mutex   *m_pictq_mutex;
    SDL_cond    *m_pictq_cond;

    // ffmpeg context
    AVFormatContext *m_pFormatCtx;// �������� �����-�����
    AVStream        *m_audio_st;  // �������� ����������
    AVStream        *m_video_st;  // �������� ����������

	int m_audioStream;			  // ������ ����������� � ��������� �����-�����
    int m_videoStream;			  // ������ ����������� � ��������� �����-�����

    // quenes
    PacketQueue m_audioq;		  //������� �����-�������
    PacketQueue m_videoq;		  //������� �����-�������

    //playback control
    bool m_quit;			// true �������� ���������� ������ � ����� �� ���� �������.
    bool m_stop_playback;   // true �������� ��� ������������� ��������� �� �����
    bool m_mute;			// true ��������, ��� ���� ��������

    //pakets
    AVPacket        m_audio_pkt;		// ������� ����� � �����-�������
    AVPacket        m_audio_pkt_temp;   // ����� � �����-�������, ������������ ��� �� ����������

	AVPacket pkt1;//
    AVPacket* packet;
    bool stream_component_open(unsigned int stream_index);

    AVFrame  *m_pFrame;  // ��������� ��� ������� avcodec_decode_video2
	CVideoPicture m_VideoPicture;  // ��������� ��� �����������

    int m_pictq_size;   // ������� ������ ������� �����������
    int m_pictq_rindex; // ������ ������ ������� ��� ������
    int m_pictq_windex; // ������ ������ ������� ��� ������
    VideoPicture    m_pictq[VIDEO_PICTURE_QUEUE_SIZE];

    // sync support
    /*keeps track of
    how much time has passed according to the video*/
    int   m_av_sync_type;


    uint64_t m_global_video_pkt_pts;
    int64_t m_frame_last_pts;
    int64_t m_frame_last_delay;
    int64_t m_frame_timer;

	/* CLOCKS
    */
    double m_audio_clock;
    double m_video_clock;

    double get_audio_clock();
    double get_video_clock();
    double get_external_clock();
    double get_master_clock();

    uint64_t m_video_current_pts;
    uint64_t m_video_current_pts_drift;

    int64_t m_first_video_pts;
    uint64_t m_video_current_pts_time;

    double          m_audio_diff_cum; /* used for AV difference average computation */
    double          m_audio_diff_avg_coef;
    double          m_audio_diff_threshold;
    int             m_audio_diff_avg_count;



    double synchronize_video(AVFrame *src_frame, double pts);
    /*close support
    */
    void stream_close();
    void stream_component_close(unsigned int stream_index);
    /* General properties
    */
    int64_t m_duration;
    int64_t m_current_time;
    double m_frame_per_sec;
    /*seek variables
    */
    int m_seek_req;					//true ��������, ��� ���� ��������� ������ �� m_seek_pos
    int m_seek_flags;				//����� ��� ������� av_seek_frame
    int64_t m_seek_pos;				//�������������� � �����, ���� ���� ��������� ������
    bool m_seek_forward;			//true ��������, ��� ����� ����� ������ �����, false - �����
    bool m_seek_in_progress;		//true ��������, ��� ����������� ����� ����� �����
    bool m_seek_by_keyframes;		//true ��������, ��� ���� ��������� ����� ����� ����� �� �������� ������
    bool m_eof;						//������ ������ ����� �����

	CSafeBool m_need_frame;			// true ��������, ��� ������� ������ ����������� �����������
	CSafeBool m_is_paused;			// true ��������, ��� ����� ����� �� �����
	CSafeBool m_need_seek;			// true ��������, ��� ��������� ������� �� ����� ����
	CSafeBool m_need_last_frame;    // ��� �������� �� ��������� ����, ����� ����� ������ �� ������� ���������
									// ������ �������� ���� �� ���������� �����.

	void		seekHelper();
	void		readPacketHelper();
	bool		checkEof(int ret);
	int64_t		getPacketTimeStamp(AVPacket* pPacket);
	void		putPacketToQueue(AVPacket* pPacket);
	void		decodeHelper();
	void		displayHelper(awpImage* pImage);

    void    SetCurrentTime(uint64_t cur_pts = AV_NOPTS_VALUE);
	int64_t GetDelay(uint64_t cur_pts = AV_NOPTS_VALUE);
	void    ResetTime();

    /*compare support
    */
    double m_search_threshold;
    CImageCompare m_ImageCompare;

    /* save support
    */
    bool    m_save_in_progress;
    float   m_save_progress;
    bool    m_user_cancel;
	/*selection
	*/
    int64_t m_save_start;
    int64_t m_save_finish;

    bool m_is_closed;
    CFFMpegEncoder* m_Encoder;
    /* Frame callback support
    */
    FrameCallback m_FrameCallBack;
    void* m_UserData;
    /*frame processor
    */
    CFrameProcessor* m_pFrameProcessor;

    /* save finish callback
    */
    SaveFihishCallback m_SaveFihishCallback;
    void* m_SaveFihishUserData;
public:
     CFFMPEGPlayer();
    ~CFFMPEGPlayer();
    /*Open and close media file
    */
    bool Open(const char* lpFileName);
    void Close();
    /*Playback support
    */
    void StartPlayback();
    void StopPlayback();
    void display_image();


    /* seek support
    */
    void Seek(int64_t SeekPos);
    bool NextFrame();
    bool PrevFrame();
    bool FirstFrame();
    bool LastFrame();

	/*scene search support
    */
    void SearchForward();
    void SearchBackward();
    double GetSearchThreshold();
    void SetSearchThreshold(double Value);

    bool IsPaused();
    bool IsSearch();
    bool IsPlayback();
    bool IsSave();
    bool IsClosed();

	/*general properties
    */
    int64_t Duration();
    double FramePerSec();
    int64_t CurrentTime();

    bool GetMute();
    void SetMute(bool Value);

    EFFMPEGPlayerScreenMode GetScreenMode();
    void SetScreenMode(EFFMPEGPlayerScreenMode Value);

    /*Delete-Undo-Redo support
    */
    void Delete(int64_t Start, int64_t Finish);
    void Undo();
    void Redo();
    int  GetUndoCount();
    int  GetRedoCount();
    /*Thread functions
    */
    int EventLoop();
    int DecompressLoop();
    int ReadPacketsLoop();
    int SeekLoop();
    int SaveLoop();
    int TranscodeLoop();
	int PrepareAudioLoop();

	/*Save functions
    */
    bool   Save(const char* lpFileName, int64_t StartTime, int64_t Duration);
    float  GetSaveProgress();
    void   StopSave();
    int64_t GetSaveStartTime();
	/* audio support
	*/
	void GetAudioBuffer(Uint8 *stream, int len);

    /*this variables are special for audio_callback which calls
    from SDL when audio data is needed*/
    unsigned int m_audio_buf_size;
    unsigned int m_audio_buf_index;
    DECLARE_ALIGNED(16,uint8_t,m_audio_buf)[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3)];
    int    synchronize_audio(short *samples, int samples_size, double pts);

    /*utils*/
    /*audio_decode_frame*/
    int audio_decode_frame(uint8_t *audio_buf, double *pts_ptr);
    /*global sync support function
    */
    uint64_t get_global_pts();
    void SetFrameCallback(FrameCallback func, void* UserData);
    void SetProcessingMode(int Mode);

    bool IsSeekBykeyFrames ();
    void SetSeekByKeyframes (bool value);

    /*frame processor
    */
    CFrameProcessor* GetFrameProcessor();
    void SetFrameProcessor(CFrameProcessor* processor);
    /* timeline
    */
    CFFMPEGTimeLine* GetTimeLine();
    /* error state
    */
    void GetLastError(int* minor, int* major);
    /* Save finish callback
    */
    void SetSaveFinishCallback(SaveFihishCallback func, void* UserData);
private:
    /*functions with prefix ' event_' is used fot event_thread function*/
    void event_alloc_picture();
    void event_video_refresh_timer();
    void event_fihish_save_video();
	/*presnting video and audio streams */
	bool has_video();
	bool has_audio();
};


#endif
