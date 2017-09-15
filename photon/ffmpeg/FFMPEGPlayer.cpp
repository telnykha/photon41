#include "stdafx.h"
#include "FFMPEGPlayer.h"
#include "time.h"
#include <algorithm>

#define LOG_FF_PREFIX   "<FFLIB>"
#define READ_PACKET_DELAY 10	 /*0.01 секунды*/	
#define SEEK_GRANULARITY  500000 /*0.5 секунды*/

#define _CLEAR_ERRORS_ {\
    m_LastErrorMajor = FFMPEG_PLAYER_OK;\
    m_LastErrorMinor = FFMPEG_PLAYER_OK;}

#define _ERROR_EXIT_(m1,m2) {\
    m_LastErrorMajor = m1;\
    m_LastErrorMinor = m2;\
    goto CLEANUP;}

#define _OPEN_FILE_ERROR_(m){\
    _ERROR_EXIT_(FFMPEG_PLAYER_CANNOT_OPEN_FILE, m)}


static AVFrame *alloc_picture(enum PixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = (uint8_t*)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    picture->width = width;
    picture->height = height;
    return picture;
}


static void* grow_array(void *array, int elem_size, int *size, int new_size)
{
     if (new_size >= INT_MAX / elem_size) {
         av_log(NULL, AV_LOG_ERROR, "Array too big.\n");
         return NULL;
     }
     if (*size < new_size) {
         uint8_t *tmp = (uint8_t*)av_realloc(array, new_size*elem_size);
         if (!tmp) {
             av_log(NULL, AV_LOG_ERROR, "Could not alloc buffer.\n");
             return NULL;
         }
         memset(tmp + *size*elem_size, 0, (new_size-*size) * elem_size);
         *size = new_size;
         return tmp;
     }
     return array;	
}

static void free_frame(AVFrame* pFrame)
{
    if (pFrame == NULL)
        return;
    if (pFrame->data[0] != NULL)
        av_free(pFrame->data[0]);
}

/*transforms the image from AVFrame into a format awpImage
*/
static bool AVFrame2AwpRGBImage(AVFrame* frame, awpImage** ppImage)
{
    bool res = false;
    if (frame == NULL || ppImage == NULL)
        return res;

    AVPicture picture;
    picture.data[0] = NULL;
    int line_size = frame->width*3;
    
    picture.data[0] = (uint8_t*)malloc(line_size*frame->height);
    if (picture.data[0] == NULL)
        goto cleanup;
    picture.linesize[0] = 3*frame->width;
    SwsContext* context = NULL;  

    context = sws_getContext(frame->width, frame->height, (PixelFormat)frame->format, 
        frame->width, frame->height, PIX_FMT_BGR24, 1, NULL, NULL, NULL);
    
    if (context == NULL)
        goto cleanup;

    int h = sws_scale(context, frame->data, frame->linesize, 0, frame->height, picture.data, picture.linesize);
    if (h != frame->height)
        goto cleanup;

    sws_freeContext(context);
    if (awpCreateImage(ppImage, frame->width, frame->height, 3, AWP_BYTE) != AWP_OK)
        goto cleanup;

    AWPBYTE* b = (AWPBYTE*)(*ppImage)->pPixels;
    memcpy(b, picture.data[0], line_size*frame->height);

    res = true;

cleanup:
    if (picture.data[0] != NULL)
        free(picture.data[0]);
    return res;
}

/* transofrms image form awpImage format to AVFrame
*/
static bool AwpRGBImage2AVFrame(awpImage* pImage, AVFrame** ppFrame)
{
    bool res = false;
    if (pImage == NULL || ppFrame == NULL)
        return false;

    // преобразование awpImage в AVPicture
    AVPicture picture;
    picture.data[0] = NULL;
    int line_size = pImage->sSizeX*3;

    picture.data[0] = (uint8_t*)malloc(line_size*pImage->sSizeY);
    if (picture.data[0] == NULL)
        goto cleanup;
    picture.linesize[0] = line_size;

    AWPBYTE* b = (AWPBYTE*)(pImage)->pPixels;
    memcpy(picture.data[0], b,  line_size*pImage->sSizeY);

    // преобразование AVPicture в AVFrame
    AVFrame* pFrame = alloc_picture(PIX_FMT_YUV420P, pImage->sSizeX, pImage->sSizeY);
    if (pFrame == NULL)
        goto cleanup;

    SwsContext* context = NULL; 
    context = sws_getContext(pImage->sSizeX, pImage->sSizeY, PIX_FMT_BGR24, 
        pImage->sSizeX, pImage->sSizeY, PIX_FMT_YUV420P, 1, NULL, NULL, NULL);

    if (context == NULL)
        goto cleanup;

    int h = sws_scale(context, picture.data, picture.linesize, 0, pFrame->height, pFrame->data, pFrame->linesize);

    if (h != pFrame->height)
        goto cleanup;

    sws_freeContext(context);

    *ppFrame = pFrame;
    res = true;
cleanup:
    if (picture.data[0] != NULL)
        free(picture.data[0]);
    return res;
}

/* SDL audio buffer size, in samples. Should be small to have precise
   A/V sync as SDL does not have hardware buffer fullness info. */
#define SDL_AUDIO_BUFFER_SIZE 1024
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)
#define FF_STOP_EVENT (SDL_USEREVENT + 3)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_FINISH_EVENT  (SDL_USEREVENT + 4)
#define FF_AUDIO_ANALYSIS_DONE_EVENT (SDL_USEREVENT +5)


#define MAX_AUDIOQ_SIZE (5 * 16 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 256 * 1024)

#define rint floor

#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0

#define SAMPLE_CORRECTION_PERCENT_MAX 10
#define AUDIO_DIFF_AVG_NB 20


#define INT64_MIN    ((int64_t)_I64_MIN)
#define INT64_MAX    _I64_MAX


enum {
    AV_SYNC_AUDIO_MASTER,
    AV_SYNC_VIDEO_MASTER,
    AV_SYNC_EXTERNAL_MASTER,
};

 #define DEFAULT_AV_SYNC_TYPE AV_SYNC_AUDIO_MASTER


/* our_get_buffer() function
These are calle d whenever we allocate a frame
 buffer. We use this to store the global_pts in
 a frame at the time it is allocated.
 */
int our_get_buffer(struct AVCodecContext *c, AVFrame *pic) 
{
  int ret = avcodec_default_get_buffer(c, pic);
  uint64_t *pts = (uint64_t *)av_malloc(sizeof(uint64_t));
  CFFMPEGPlayer* player = (CFFMPEGPlayer*)c->opaque;
  *pts = player->get_global_pts();
  pic->opaque = pts;
  return ret;
}
void our_release_buffer(struct AVCodecContext *c, AVFrame *pic) 
{
    if(pic != NULL && pic->opaque != NULL)
        av_freep(&pic->opaque);
  avcodec_default_release_buffer(c, pic);
}

#pragma region ThreadsAndCallbacks

/*audio_callback() function
The callback has to be of the form void callback(void *userdata, Uint8 *stream, int len), 
where user data of course is the pointer we gave to SDL, 
stream is the buffer we will be writing audio data to, and len is the size of that buffer. 
*/
void audio_callback(void *userdata, Uint8 *stream, int len)
{
 // XXXX: make audio callback function to send audio data to SDL 
    CFFMPEGPlayer *is = (CFFMPEGPlayer*)userdata;
    int audio_size, len1;
    double pts;
      while(len > 0) 
      {
        if(is->m_audio_buf_index >= is->m_audio_buf_size) 
        {
          /* We have already sent all our data; get more */

          audio_size = is->audio_decode_frame(is->m_audio_buf, &pts);
          if(audio_size < 0) {
	        /* If error, output silence */
	        is->m_audio_buf_size = 1024;
	        memset(is->m_audio_buf, 0, is->m_audio_buf_size);
          } 
          else 
          {
	        audio_size = is->synchronize_audio((int16_t *)is->m_audio_buf,
				                audio_size, pts);              
              is->m_audio_buf_size = audio_size;
          }
          is->m_audio_buf_index = 0;
        }
        len1 = is->m_audio_buf_size - is->m_audio_buf_index;
        if(len1 > len)
          len1 = len;
        if (is->GetMute())
            memset(stream, 0, len1);
        else
            memcpy(stream, (uint8_t *)is->m_audio_buf + is->m_audio_buf_index, len1);
        len -= len1;
        stream += len1;
        is->m_audio_buf_index += len1;
      }
}

void sdl_audio_callback(void *userdata, Uint8 *stream, int len)
{
	CFFMPEGPlayer *is = (CFFMPEGPlayer*)userdata;
	if (is != NULL)
		is->GetAudioBuffer(stream, len);
}

void FFDebugCallback( void* ptr, int level, const char* fmt, va_list vl )
{
#ifdef _DEBUG
	AVClass* avc= ptr ? *(AVClass**)ptr : NULL;
    char m_line[1024];
    m_line[0] = 0;

    strcpy_s( m_line, LOG_FF_PREFIX );
    if( avc) 
    {
        sprintf_s(m_line + strlen(m_line), sizeof(m_line) - strlen(m_line), "[%s @ %p] ", avc->item_name(ptr), ptr);
    }
    vsnprintf_s(m_line + strlen(m_line), sizeof(m_line) - strlen(m_line), 1023, fmt, vl);
    OutputDebugStringA(m_line);
#endif
}
/*
read_thread() function.
It's basically just a for loop that will read in a packet and put it on the
right queue
*/
int read_thread(void* arg)
{
    CFFMPEGPlayer* player = (CFFMPEGPlayer*)arg;
    if (player == NULL)
        return -1;
    /*main decode loop*/
    return player->ReadPacketsLoop();
}
/*This thread reads in packets from the video queue, decodes the video into frames, 
and then calls a queue_picture function to put the processed frame onto a picture queue
*/
int video_thread(void* arg)
{
    CFFMPEGPlayer* player = (CFFMPEGPlayer*)arg;
    if (player == NULL)
        return -1;
    /*main decompression loop while playback status*/
    return player->DecompressLoop();
}
/* this thread process SDL's events
*/
int event_loop(void* arg)
{
    CFFMPEGPlayer* player = (CFFMPEGPlayer*)arg;
    if (player == NULL)
        return -1;
    return player->EventLoop();
}
/* this thread save vodeo with decoding and processing 
*/
int transcode_thread(void* arg)
{
    CFFMPEGPlayer* player = (CFFMPEGPlayer*)arg;
    if (player == NULL)  
        return -1;
    return player->TranscodeLoop();
}


/* анализ аудиопотока
*/
int audio_analysis_thread(void* arg)
{
	CFFMPEGPlayer* player = (CFFMPEGPlayer*)arg;
	if (player == NULL)
		return -1;
	return player->PrepareAudioLoop();
}
#pragma endregion ThreadsAndCallbacks

#pragma region CFFMPEGPlayerArea
/*This is our player's constructor. Sets all variables to the default vlaue and init ffmpeg
*/
CFFMPEGPlayer::CFFMPEGPlayer()
{
    av_register_all();
	avcodec_register_all();

    av_log_set_level( AV_LOG_INFO );
    av_log_set_flags( AV_LOG_SKIP_REPEATED );
    av_log_set_callback( FFDebugCallback );

    /*fill SDL context with nulls*/
    m_decode_tid = NULL;
    m_video_tid = NULL;
    m_event_tid = NULL;
    m_save_tid  = NULL;
    m_pictq_mutex = NULL;
    m_pictq_cond = NULL;
    
    m_pFormatCtx = NULL;

    m_audio_st = NULL;
    m_video_st = NULL;

    m_audioStream = -1;
    m_videoStream = -1;

    m_quit = false;
    //m_stop_playback = true;

    m_audio_buf_size = 0;
    m_audio_buf_index = 0;     

    memset(&m_audio_pkt, 0, sizeof(m_audio_pkt));
    memset(&m_audio_pkt_temp, 0, sizeof(m_audio_pkt_temp));
    memset(m_audio_buf, 0, sizeof(m_audio_buf));

    m_pFrame = NULL;
    m_pictq_size = 0;
    m_pictq_windex  = 0;
    m_pictq_rindex = 0;
    memset(m_pictq, 0, sizeof(m_pictq));

    m_global_video_pkt_pts = AV_NOPTS_VALUE;
    m_video_clock = 0;
    m_frame_last_pts = 0;
    m_frame_last_delay = 40e-3;

    m_audio_clock  =0;
    m_av_sync_type = DEFAULT_AV_SYNC_TYPE;

    m_audio_diff_cum = 0;
    m_audio_diff_avg_coef =exp(log(0.01 / AUDIO_DIFF_AVG_NB));
    m_audio_diff_threshold = 0;
    m_audio_diff_avg_count = 0;

    m_video_current_pts_drift = 0;

    m_duration = 0;
    m_current_time = 0;
    m_frame_per_sec = 0;

    m_mute = false;
    /*With ffmpeg, you have to first initialize the library*/

    m_seek_req = 0; 
    m_seek_flags =0;
    m_seek_pos = 0;
    m_eof = false;
     
    av_init_packet(&flush_pkt);
    flush_pkt.data = (uint8_t*)"FLUSH";

    packet = &pkt1;
    m_seek_forward = true;
    m_seek_in_progress = false;
    m_seek_by_keyframes = true;
    m_search_threshold = 0.25;

    m_save_in_progress = false;
    m_save_progress = 0;
    m_save_start = 0;
    m_save_finish = 0;
    m_ScreenMode = smNormal;
    m_is_closed = true;
    m_FrameCallBack = NULL;
    m_UserData = NULL;
    m_ProcessingMode = pmNothing;
    m_pFrameProcessor = NULL;
    m_Encoder = NULL;
    m_SaveFihishCallback  = NULL;
    m_SaveFihishUserData = NULL;
    m_user_cancel = false;

	awpCreateImage(&m_AudioImage, 2000, 480, 3, AWP_BYTE);
	awpCreateImage(&m_AudioImageBkg, 2000, 480, 3, AWP_BYTE);

    m_first_video_pts = -1;
	m_is_paused.SetValue(true);
	m_need_seek.SetValue(false);
	this->m_need_last_frame.SetValue(false);
}
/* player destructor
*/
CFFMPEGPlayer::~CFFMPEGPlayer()
{
    
	Close();
	awpReleaseImage(&m_AudioImage);
	awpReleaseImage(&m_AudioImageBkg);
}
/* 
*/
bool CFFMPEGPlayer::Open(const char* lpFileName)
{

	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Open] Enter.\n");

    _CLEAR_ERRORS_

	this->m_TimeLine.Close();
    m_quit = false;
    m_pFormatCtx = NULL;
    // initialize SDL 
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) 
    {
        _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_INIT_SDL,0)
    }

    // Open media file
    m_pFormatCtx = NULL;
    if (avformat_open_input(&m_pFormatCtx, lpFileName, NULL, NULL) != 0)
    {
       _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_OPEN_FILE)
    }

    if (avformat_find_stream_info(m_pFormatCtx, NULL) < 0)
    {
        _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_FIND_STREAMS)
    }
    m_pictq_mutex = SDL_CreateMutex();
    m_pictq_cond  = SDL_CreateCond();
    // travel all streams and open them 
    for (unsigned int i = 0; i < m_pFormatCtx->nb_streams; i++)
    {
		if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && m_videoStream < 0)
            m_videoStream = i;
        if (m_pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && m_audioStream < 0)
            m_audioStream = i;
    }

    if (has_audio())
    {
        if (!stream_component_open(m_audioStream))
        {
            _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_OPEN_AUDIO)
        }
    }
    if (has_video())
    {
        if (!stream_component_open(m_videoStream))
            _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_OPEN_VIDEO)
    }
	/* инициализация временной шкалы
	*/
	if (has_audio() || has_video())
	{
		AVRational r; 
		r.num = 1;
		r.den = AV_TIME_BASE;

		/*имеется и аудио и видео*/
		if (has_audio() && has_video())
		{
			/*имеются оба потока видио и аудио*/
			if (m_video_st->duration != AV_NOPTS_VALUE)
			{
				m_duration = av_rescale_q(m_video_st->duration, m_video_st->time_base, r);
			}
			else if (m_audio_st->duration != AV_NOPTS_VALUE && m_video_st->duration == AV_NOPTS_VALUE)
			{
				m_duration = av_rescale_q(m_audio_st->duration, m_audio_st->time_base, r);
			}
			else 
			{
				m_duration = m_pFormatCtx->duration;
			}
		}
		else if (has_audio() && !has_video())
		{
			/*имеется только аудио поток*/
			if (m_audio_st->duration != AV_NOPTS_VALUE)
				m_duration = av_rescale_q(m_audio_st->duration, m_audio_st->time_base, r);
			else
				m_duration = m_pFormatCtx->duration;
		}
		else if (has_video() && !has_audio())
		{
			/*имеется только видео поток*/
			if (m_video_st->duration != AV_NOPTS_VALUE)
                m_duration = av_rescale_q(m_video_st->duration, m_video_st->time_base, r);
            else
                m_duration = m_pFormatCtx->duration;
		}
		else
		{
			/*у нас нет вообще потоков*/
	        _OPEN_FILE_ERROR_(FFMPEG_PLAYER_CANNOT_FIND_STREAMS)
		}
		m_TimeLine.Init(m_duration);
	}

    /* проверка допустимости аудио и видеокодеков
    */
    if (strcmp(m_pFormatCtx->iformat->name, "avi") == 0 && 
        (m_video_st->codec->codec_id == CODEC_ID_MJPEG || m_video_st->codec->codec_id == CODEC_ID_MJPEGB))
    	    _OPEN_FILE_ERROR_(FFMPEG_PLAYER_USUPPORTED_FORMAT)

    //if (has_video() && this->m_frame_per_sec == 0)
   	//    _OPEN_FILE_ERROR_(FFMPEG_PLAYER_USUPPORTED_FORMAT)

    if (strcmp(m_pFormatCtx->iformat->name, "mpeg") == 0 && 
        this->m_audio_st->codec->codec_id == CODEC_ID_AC3)
    	    _OPEN_FILE_ERROR_(FFMPEG_PLAYER_USUPPORTED_FORMAT)

	/* запуск потока обработки событий 
	   и переход на первый кадр.
	*/
    if (has_audio() || has_video())
        m_event_tid = SDL_CreateThread(event_loop, this);

	if (!has_video() && has_audio())
	{
		m_ScreenMode = smAudio;
		this->PrepareAudioSegments();
		av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Open] Only audio stream. Exit.\n");
		return true;
	}
	else
		m_ScreenMode = smNormal;

	m_decode_tid = SDL_CreateThread(read_thread, this);
    if (has_video())
		m_video_tid  = SDL_CreateThread(video_thread, this);

	m_is_closed = false;


	Seek(0);
	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Open] Done. Exit.\n");
    return true;

CLEANUP:
    m_duration = 0;
    m_TimeLine.Init(0);
    if(m_pictq_mutex != NULL)
    {
        SDL_DestroyMutex(m_pictq_mutex);
        m_pictq_mutex = NULL;
    }
    if (m_pictq_cond != NULL)
    {
        SDL_DestroyCond(m_pictq_cond);
        m_pictq_cond = NULL;
    }
    // todo: close opened streams 
    if (m_video_st != NULL && m_video_st->codec != NULL)
    {
        avcodec_close(m_video_st->codec);
        m_pFormatCtx->streams[m_videoStream]->discard = AVDISCARD_ALL;
        m_video_st = NULL;
    }
    if (m_audio_st != NULL && m_audio_st->codec != NULL)
    {
        avcodec_close(m_audio_st->codec);
        m_pFormatCtx->streams[m_audioStream]->discard = AVDISCARD_ALL;
        m_audio_st = NULL;
    }
    m_videoStream = -1;
    m_audioStream = -1;
    if (m_pFormatCtx != NULL)
        avformat_close_input(&m_pFormatCtx);

 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Open] Error. Exit.\n");
    return false;
}
/*
*/
void CFFMPEGPlayer::Close()
{
 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Enter.\n");
	m_quit = true;
	SDL_Event event;
    event.type = FF_QUIT_EVENT;
    event.user.data1 = this;
    SDL_PushEvent(&event);

	SDL_Delay(100);
    int cond = 0;
    if (m_decode_tid)
    {
        SDL_WaitThread(m_decode_tid, &cond);
        m_decode_tid = NULL;
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Decode thread done.\n");
        if (cond != 2)
        {
            //push quit event
        }
    }
    else
    {
        //push quit event
        SDL_Event event;
        event.type = FF_QUIT_EVENT;
        event.user.data1 = this;
        SDL_PushEvent(&event);
        SDL_Delay(100);
    }

    if (m_event_tid)
    {
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Wait Event thread.\n");
        SDL_WaitThread(m_event_tid, NULL);
        m_event_tid = NULL;
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Event thread done.\n");
    }
    if (m_video_tid)
    {
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Wait Video thread.\n");
        SDL_WaitThread(m_video_tid, NULL);
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Video thread done.\n");
        m_video_tid = NULL;
    }
    if (m_save_tid)
    {
        m_save_in_progress = false;
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Wait Save thread.\n");
        SDL_WaitThread(m_save_tid, NULL);
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Save thread done.\n");
        m_save_tid = NULL;
    }
    if (has_audio())
    {
        stream_component_close(m_audioStream);
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Audio stream close.\n");
        m_audioStream = -1;
    }
    if (has_video())
    {
        stream_component_close(m_videoStream);
	 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Video stream close.\n");
        m_videoStream = -1;
    }

    stream_close();
    if (m_pFormatCtx)
    {
        av_close_input_file(m_pFormatCtx);
        m_pFormatCtx = NULL;
    }
    SDL_Quit();
    m_first_video_pts  = -1;

	m_audioArray.clear();
	m_is_closed = true;

 	av_log(NULL, AV_LOG_INFO, "[CFFMPEGPlayer::Close] Exit.\n");
}

/*
The stream_component_open() function is where we will find our codec decoder, 
set up our audio options, save important information to our variables, 
and launch our audio and video threads. This is where we would also insert other options, 
such as forcing the codec instead of autodetecting it and so forth.
*/
bool CFFMPEGPlayer::stream_component_open(unsigned int stream_index)
{
    bool res = false;
    AVCodecContext *codecCtx;
    SDL_AudioSpec wanted_spec, spec;

    /*check the state*/
    if (m_pFormatCtx == NULL)
    {
     
        return res;
    }
    if (stream_index < 0 || stream_index >= m_pFormatCtx->nb_streams)
    {
        return res;
    }

    // Get a pointer to the codec context for the video stream
    codecCtx = m_pFormatCtx->streams[stream_index]->codec;

    // setup SDL audio support 
    if (codecCtx->codec_type == AVMEDIA_TYPE_AUDIO)
    {
      
        codecCtx->request_channels = FFMIN(2, codecCtx->channels);        
        // processing audio codec 
        wanted_spec.freq = codecCtx->sample_rate;
        wanted_spec.format = AUDIO_S16SYS;
        wanted_spec.silence = 0;
        wanted_spec.samples = SDL_AUDIO_BUFFER_SIZE;
        wanted_spec.channels = codecCtx->channels > 2 ? 2:codecCtx->channels;
        wanted_spec.userdata = this;
        wanted_spec.callback = audio_callback;

        if(SDL_OpenAudio(&wanted_spec, &spec) < 0) 
        {
            return res;
        }
    }
        

    // find the decoder 
    AVCodec *codec;
    codec = avcodec_find_decoder(codecCtx->codec_id);

    if(!codec || (avcodec_open(codecCtx, codec) < 0)) 
    {
        return res;
    }

    // run threads 
    switch(codecCtx->codec_type)
    {
    case AVMEDIA_TYPE_AUDIO:
        m_audioStream = stream_index; 
        m_audio_st = m_pFormatCtx->streams[stream_index];
        m_audio_buf_size = 0;
        m_audio_buf_index = 0;
        /* averaging filter for audio sync */
        m_audio_diff_avg_coef = exp(log(0.01 / AUDIO_DIFF_AVG_NB));
        m_audio_diff_avg_count = 0;
        /* Correct audio only if larger error than this */
        m_audio_diff_threshold = 2.0 * SDL_AUDIO_BUFFER_SIZE / codecCtx->sample_rate;
        // XXXX: implement quene init
        memset(&m_audio_pkt, 0, sizeof(m_audio_pkt));
        packet_queue_init(&m_audioq);

    break;
    case AVMEDIA_TYPE_VIDEO:
        // XXXX: implement video support 
        m_videoStream = stream_index;
        m_video_st = m_pFormatCtx->streams[stream_index];
        m_video_current_pts_time = av_gettime();
        packet_queue_init(&m_videoq);   
        // before start the thread alloc data 
        m_pFrame = avcodec_alloc_frame();
        codecCtx->opaque = this;
        codecCtx->get_buffer = our_get_buffer;
        codecCtx->release_buffer = our_release_buffer;
        m_frame_per_sec = m_video_st->avg_frame_rate.num;

    break;
    default:
        break;
    }
    return true;
}

void CFFMPEGPlayer::packet_queue_init(CFFMPEGPlayer::PacketQueue *q) 
{
    memset(q, 0, sizeof(CFFMPEGPlayer::PacketQueue));
    q->mutex = SDL_CreateMutex();
    q->cond  = SDL_CreateCond();
    q->size = 0;
    packet_queue_put(q, &flush_pkt);
} 

int CFFMPEGPlayer::packet_queue_put(PacketQueue *q, AVPacket *pkt)
{
  //av_log(NULL, AV_LOG_INFO, "[packet_queue_put] Enter put  packet.\n");
  AVPacketList *pkt1;
  if (pkt!=&flush_pkt && av_dup_packet(pkt) < 0)
    return -1;


  pkt1 = (AVPacketList *)av_malloc(sizeof(AVPacketList));
  if (!pkt1)
    return -1;
  pkt1->pkt = *pkt;
  pkt1->next = NULL;
  
  SDL_LockMutex(q->mutex);
  if (!q->last_pkt)
    q->first_pkt = pkt1;
  else
    q->last_pkt->next = pkt1;

  q->last_pkt = pkt1;
  q->nb_packets++;
  q->size += pkt1->pkt.size;

  SDL_CondSignal(q->cond);
  SDL_UnlockMutex(q->mutex);
  //av_log(NULL, AV_LOG_INFO, "[packet_queue_put] Exit put  packet.\n");
  return 0;
}

int CFFMPEGPlayer::packet_queue_get(PacketQueue *q, AVPacket *pkt, int block) 
{
 
  //av_log(NULL, AV_LOG_INFO, "[packet_queue_get] Enter get  packet.\n");
  AVPacketList *pkt1;
  int ret = 0;
  SDL_LockMutex(q->mutex);
  for(;;) 
  {
    if (q->abort_request) 
	{
        ret = -1;
        break;
    }    
    if(m_quit) 
	{
      ret = -1;
      break;
    }
	//
    pkt1 = q->first_pkt;
    if (pkt1) 
    {
      
	  q->first_pkt = pkt1->next;
      if (!q->first_pkt)
          q->last_pkt = NULL;
      
	  q->nb_packets--;
      q->size -= pkt1->pkt.size;
      *pkt = pkt1->pkt;
      av_free(pkt1);
      ret = 1;
      break;
    }
    else if (!block) 
    {
      ret = 0;
      break;
    } 
	else 
    {
        //TODO: это состояние вызывает остановку процесса и выход из 
        //потоков воспроизведения. Нужен новый, усточивый критерий 
        //остановки потоков в случае, если очередь пустая. 
		//av_log(NULL, AV_LOG_INFO, "[packet_queue_put] wait  packet.\n");
		//SDL_CondWait(q->cond, q->mutex);
        if (SDL_CondWaitTimeout(q->cond, q->mutex, 500) == SDL_MUTEX_TIMEDOUT)
        {
            ret = -1;
			this->m_is_paused.SetValue(true);
            break;
        }
		//else
		//	break;
    } 
  }
  SDL_UnlockMutex(q->mutex);
  //av_log(NULL, AV_LOG_INFO, "[packet_queue_get] Exit get  packet.\n");
  return ret;
}

void CFFMPEGPlayer::packet_queue_end(PacketQueue *q)
{
    SDL_DestroyMutex(q->mutex);
    SDL_DestroyCond(q->cond);
}

void CFFMPEGPlayer::packet_queue_abort(PacketQueue *q)
{
    SDL_LockMutex(q->mutex);
    q->abort_request = 1;
    SDL_CondSignal(q->cond);
    SDL_UnlockMutex(q->mutex);
}

void CFFMPEGPlayer::packet_queue_flush(PacketQueue *q)
{
    AVPacketList *pkt, *pkt1;

    SDL_LockMutex(q->mutex);
    for(pkt = q->first_pkt; pkt != NULL; pkt = pkt1) {
        pkt1 = pkt->next;
        av_free_packet(&pkt->pkt);
        av_freep(&pkt);
    }
    q->last_pkt = NULL;
    q->first_pkt = NULL;
    q->nb_packets = 0;
    q->size = 0;
    SDL_UnlockMutex(q->mutex);
}

/* decode one audio frame and returns its uncompressed size
calls from auido_callback function*/
int CFFMPEGPlayer::audio_decode_frame(uint8_t *audio_buf, double *pts_ptr)
{
  if (m_audio_st == NULL)
      return -1;

  int len1, data_size, n;
  double pts;
  for(;;) 
  {
      while(m_audio_pkt_temp.size > 0)
      {
          data_size = sizeof(m_audio_buf);
           len1 = avcodec_decode_audio3(m_audio_st->codec, (int16_t *)audio_buf, &data_size, &m_audio_pkt_temp);
          if(len1 < 0) 
          {
	        /* if error, skip frame */
	        m_audio_pkt_temp.size = 0;
            break;
          }

          m_audio_pkt_temp.data += len1;
          m_audio_pkt_temp.size -= len1;
          if(data_size <= 0) 
          {
              /* No data yet, get more frames */
              continue;
          }
          pts = m_audio_clock;
          *pts_ptr = pts;
          n = 2*m_audio_st->codec->channels;
          m_audio_clock += (double)data_size / (double) (n*m_audio_st->codec->sample_rate);
          /* We have data, return it and come back for more later */
          return data_size;
      }

        if(m_audio_pkt.data)
          av_free_packet(&m_audio_pkt);

        if(m_quit) 
        {
            /*exit if requred*/
            return -1;
        }
		if (this->m_is_paused.GetValue())

        {
            return -1;
        }
        /*read next packet*/
        if(packet_queue_get(&m_audioq, &m_audio_pkt, 1) < 0)
        {
            if (!has_video())
				this->m_is_paused.SetValue(true);
			return -1;
        }
        if(m_audio_pkt.data == flush_pkt.data) 
        {
          avcodec_flush_buffers(m_audio_st->codec);
          continue;
        } 

        memcpy(&m_audio_pkt_temp, &m_audio_pkt, sizeof(m_audio_pkt));
        if (m_audio_pkt.pts != AV_NOPTS_VALUE)
		{
            m_audio_clock = av_q2d(m_audio_st->time_base)*m_audio_pkt.pts;
			if (!has_video())
				SetCurrentTime(m_audio_pkt.pts);
		}
  }
}

void CFFMPEGPlayer::GetAudioBuffer(Uint8 *stream, int len)
{

}

/* CFFMPEGPlayer::decodeHelper(). Вызывается из треда decomperssLoop

   Преобразует информацию из сжатых и закодированных пакетов в изображение 
   AVFrame, c использованием функции avcodec_decode_video2. Полученное 
   изображение немедленно конвертируется в формат awpImage. 
   
   - В режиме проигрывателя записывает это изображение в очередь для синхронного отображения, 
     с использованием queue_picture. 

   - В режиме навигации по файлу вызывает функцию обновления экрана displayHelper
     и сбрасывает флаги need_frame или need_last_frame. 

   - В режиме поиска новой сцены вызывает функцию обновления экрана  displayHelper
     выполняет сравнение с предыдущей сценой и если сцены достаточно отличаются 
	 друг от друга останавливает поиск. 
*/
void CFFMPEGPlayer::decodeHelper()
{
	if (this->m_need_seek.GetValue()== true)
	{
		SDL_Delay(10);
		return;
	}
	AVPacket   thePacket;
	AVPacket*  pPacket = &thePacket;
	int frameFinished  = 0;
	/* получим пакета из очереди пакетов 	*/
	av_init_packet(pPacket);
	if (packet_queue_get(&m_videoq, pPacket, 1) < 0)
	{
		/*если ничего не полуилось, то выйдем, предварительно сбросив
		переменную need_frame и установив проигрыватель на паузу*/
		if (this->m_is_paused.GetValue() == false && this->m_eof)
			this->m_is_paused.SetValue(true);
		if (this->m_need_frame.GetValue() == true)
			this->m_need_frame.SetValue(false);
		SDL_Delay(READ_PACKET_DELAY);
        return;
	}
	/* содержит ли пакет актуальные данные или эт о flush-пакет	*/
    if(pPacket->data == flush_pkt.data) 
    {
        /*если это flush-пакет, то сбросим все внутренние переменные кодека
		и время*/
		avcodec_flush_buffers(m_video_st->codec);  
		this->ResetTime();
        return;
    }
    double pts = 0;
    m_global_video_pkt_pts = packet->pts;

	/* декодируем кадр */
	avcodec_decode_video2(m_video_st->codec, m_pFrame, &frameFinished, pPacket);

    if(packet->dts == AV_NOPTS_VALUE 
       && m_pFrame->opaque && *(uint64_t*)m_pFrame->opaque != AV_NOPTS_VALUE) 
    {
      pts = (double)(*(uint64_t *)m_pFrame->opaque);
    } 
    else if(packet->dts != AV_NOPTS_VALUE) 
    {
      pts = (double)packet->dts;
    } else 
    {
      pts = 0;
    }
    pts *= av_q2d(m_video_st->time_base);

	av_free_packet(pPacket);
	if (frameFinished)
	{
		if (m_pFrame->best_effort_timestamp == AV_NOPTS_VALUE)
			return;
		/* кадр декодирован, преобразуем его в изображение 
		пригодное для обработки и отображения на экране*/ 
		this->m_VideoPicture.SetAVFrame(m_pFrame);
		if (this->m_need_frame.GetValue() == true && this->m_need_last_frame.GetValue() == false)
		{
			/*отобразим его на экране или запишем в очередь для отображения. */
			displayHelper(this->m_VideoPicture.GetImage());
			/* если был нужен кадр (в режиме остановки), то сбросим этот 
			   флаг. кадр больше не нужен, т.к. он получен*/
			this->m_need_frame.SetValue(false);
		}
		else if (this->m_need_last_frame.GetValue() == true)
		{
			/*если нужне последний кадр, то мы должны проверить число доступных пакетов в очереди
			и флаг конца файла*/
			if (this->m_videoq.nb_packets == 0 && this->m_eof)
			{
				/*последний кадр нашелся, отобразим его и сбросим флаг поиска последнего кадра*/
				this->displayHelper(this->m_VideoPicture.GetImage());
				this->m_need_last_frame.SetValue(false);
			}
		}
		else if (m_seek_in_progress)
		{
			/*если мы ищем новую сцену, то отобразим изображение на экране и проверим 
			не нашлась ли она*/
			this->displayHelper(this->m_VideoPicture.GetImage());
			if (m_ImageCompare.Compare(this->m_VideoPicture.GetImage(), m_search_threshold))
				m_seek_in_progress = false;
			else
			{
				 /*сцена не нашлась, выставим необходимые значения переменных поиска*/ 
				 m_seek_flags = m_seek_forward ? 0 : AVSEEK_FLAG_BACKWARD;
				 int incr = m_seek_forward ? SEEK_GRANULARITY : -2*SEEK_GRANULARITY;
				 m_seek_pos = m_current_time + incr;
				 if (m_seek_pos < 0)
				 {
					m_seek_pos = 0;
					m_seek_in_progress = false;
				 }
				 if (m_seek_pos >= this->Duration())
					m_seek_in_progress = false;
				 
				 this->m_need_seek.SetValue(true);
			}
		}
		else
		{
			/*плеер находится в режиме воспроизведения видео, синхронизируем видеопоток и 
			обновим очередь картинок для отображения их на экране*/
			pts = synchronize_video(m_pFrame, pts);
			queue_picture(pts);
		}
	}
}
/* CFFMPEGPlayer::displayHelper()
   Выполянет отображение текущего изображения на экране, путем вызова 
   callback функции m_FrameCallBack. 
   Устанавливает текущее время с использованием SetCurrentTime
*/
void CFFMPEGPlayer::displayHelper(awpImage* pImage)
{
    if (m_pFrame == NULL && pImage == NULL)
		return;

	if (m_FrameCallBack && pImage && m_UserData)
      m_FrameCallBack(pImage, m_UserData);

	uint64_t CurrentTime = m_pFrame->best_effort_timestamp;
	if (this->m_need_last_frame.GetValue() == true)
		CurrentTime = this->Duration();
	this->SetCurrentTime(CurrentTime);
}

/*queue_picture() 
*/
int CFFMPEGPlayer::queue_picture(double pts)
{
    VideoPicture* vp;
    /*wait until we have space for a new pic*/
    SDL_LockMutex(m_pictq_mutex);
	while (m_pictq_size >= VIDEO_PICTURE_QUEUE_SIZE && !m_quit && !this->m_is_paused.GetValue())
    {
        SDL_CondWaitTimeout(m_pictq_cond, m_pictq_mutex, 10);
    }
     SDL_UnlockMutex(m_pictq_mutex);

    if (m_quit)
        return -1;

    vp = &m_pictq[m_pictq_windex];

    /*if need then allocate or resize the buffer*/
    
    if(!vp->allocated ||
        vp->width != m_video_st->codec->width ||
        vp->height != m_video_st->codec->height) 
    {

        SDL_Event event;
        vp->allocated = 0;
        /* we have to do it in the main thread */
        event.type = FF_ALLOC_EVENT;
        event.user.data1 = this;
        SDL_PushEvent(&event);

        /* wait until we have a picture allocated */
        SDL_LockMutex(m_pictq_mutex);
        while(!vp->allocated && !m_quit) {
            SDL_CondWait(m_pictq_cond, m_pictq_mutex);
        }
        SDL_UnlockMutex(m_pictq_mutex);
        if(m_quit) 
        {
            return -1;
        }
    }

  /* We have a place to put our picture on the queue */

  if(vp->allocated && this->m_VideoPicture.GetImage() != NULL) 
  {
    /* point pict at the queue */
	SDL_LockMutex(m_pictq_mutex);
	::awpFastCopyImage(this->m_VideoPicture.GetImage(), vp->image);
	 SDL_UnlockMutex(m_pictq_mutex);
    vp->pts = pts;
    /* now we inform our display thread that we have a pic ready */
    if(++m_pictq_windex == VIDEO_PICTURE_QUEUE_SIZE) {
      m_pictq_windex = 0;
    }
    SDL_LockMutex(m_pictq_mutex);
    m_pictq_size++;
    SDL_UnlockMutex(m_pictq_mutex);
  }
  return 0;
}

void CFFMPEGPlayer::event_alloc_picture()
{
  VideoPicture *vp = &m_pictq[m_pictq_windex];
  vp->width = m_video_st->codec->width;
  vp->height = m_video_st->codec->height;
  awpCreateImage(&vp->image, vp->width, vp->height, 3, AWP_BYTE);
  SDL_LockMutex(m_pictq_mutex);
  vp->allocated = 1;
  SDL_CondSignal(m_pictq_cond);
  SDL_UnlockMutex(m_pictq_mutex);
}

void CFFMPEGPlayer::event_fihish_save_video()
{
    if (m_Encoder = NULL)
        return;
    int status;
    if (m_save_tid != NULL)
    {
        SDL_WaitThread(m_save_tid, &status);
        m_save_tid = NULL;
        if (m_SaveFihishCallback != NULL)
            m_SaveFihishCallback(status, m_SaveFihishUserData);
    }
}


/*The event handler SDL REFRESH
  calculates the time after which the need to call the next REFRESH
  and displays the picture on the screen 
*/
void CFFMPEGPlayer::event_video_refresh_timer()
{
    if (has_video())
	{
		if (!this->m_is_paused.GetValue())
		{
			VideoPicture* vp;
			double actual_delay, delay, sync_threshold, ref_clock, diff;
			if (m_video_st != NULL)
			{
				if (m_pictq_size == 0)
				{
					schedule_refresh(10);
				}
				else
				{
					vp = &m_pictq[m_pictq_rindex];
					actual_delay = this->GetDelay();
					schedule_refresh(actual_delay);
					this->SetCurrentTime();	
					/*display the picture*/
					display_image();

					if (++m_pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE)
						m_pictq_rindex = 0;

					SDL_LockMutex(m_pictq_mutex);
					m_pictq_size--;
					if (m_pictq_size < 0 )
						m_pictq_size = 0;
					SDL_CondSignal(m_pictq_cond);
					SDL_UnlockMutex(m_pictq_mutex);
				}
			}
			else
			{
				schedule_refresh(100);
			}
		}
		else
		  display_image();
	}
	else if (has_audio())
	{
		UpdateAudioImage();
		if (m_FrameCallBack)
			m_FrameCallBack(m_AudioImage, m_UserData);
		int delay = this->IsPlayback() ? 200 : 0; 
		schedule_refresh(delay);
	}
}
/*По таймеру создается событие REFRESH для SDL и отправляется в очередь событий
*/
static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque) 
{
  SDL_Event event;
  event.type = FF_REFRESH_EVENT;
  event.user.data1 = opaque;
  SDL_PushEvent(&event);
  return 0; /* 0 means stop timer */
}
/*устанавливает таймер для отображения кадра. 
*/
void CFFMPEGPlayer::schedule_refresh(int delay)
{
    if (delay < 0)
		return;

	if (m_quit)
		return;

	if (m_need_frame.GetValue())	
	{
	    SDL_AddTimer(delay, sdl_refresh_timer_cb, this);
		return;
	}

	if (this->m_is_paused.GetValue() && this->has_video())
		return;

     SDL_AddTimer(delay, sdl_refresh_timer_cb, this);
}

/*display_image() function
отображает распакованный кадр на экране. 
*/
void CFFMPEGPlayer::display_image()
{
  SDL_Rect rect;
  VideoPicture *vp;

 // vp = &m_pictq[m_pictq_rindex];
  
  //if (m_need_frame.GetValue())
  //{
	 // SetCurrentTime();	
  //}
   SDL_LockMutex(m_pictq_mutex);
   if (m_FrameCallBack && this->m_VideoPicture.GetImage() && m_UserData)
      m_FrameCallBack(this->m_VideoPicture.GetImage(), m_UserData);
   SDL_UnlockMutex(m_pictq_mutex);

}

uint64_t CFFMPEGPlayer::get_global_pts()
{
    return m_global_video_pkt_pts;
}
/*synchronize_video() functon 
update the PTS to be in sync with
everything. This function will also finally deal with cases where we don't get
a PTS value for our frame. At the same time we need to keep track of when the
next frame is expected so we can set our refresh rate properly. We can
accomplish this by using an internal video_clock value which keeps track of
how much time has passed according to the video
*/
double CFFMPEGPlayer::synchronize_video(AVFrame *src_frame, double pts) 
{

  double frame_delay;

  if(pts != 0) 
  {
    /* if we have pts, set video clock to it */
    m_video_clock = pts;
  } else 
  {
    /* if we aren't given a pts, set it to the clock */
    pts = m_video_clock;
  }
  /* update the video clock */
  frame_delay = av_q2d(m_video_st->codec->time_base);
  /* if we are repeating a frame, adjust clock accordingly */
  frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
  m_video_clock += frame_delay;
  return pts;
}
/* Add or subtract samples to get a better sync, return new
   audio buffer size */
int CFFMPEGPlayer::synchronize_audio(short *samples, int samples_size, double pts)
{
  int n;
  double ref_clock;

  n = 2 * m_audio_st->codec->channels;
  
  if(m_av_sync_type != AV_SYNC_AUDIO_MASTER) 
  {
    double diff, avg_diff;
    int wanted_size, min_size, max_size;
    
    ref_clock = get_master_clock();
    diff = get_audio_clock() - ref_clock;

    if(diff < AV_NOSYNC_THRESHOLD) 
    {
      // accumulate the diffs
      m_audio_diff_cum = diff + m_audio_diff_avg_coef * m_audio_diff_cum;
      if(m_audio_diff_avg_count < AUDIO_DIFF_AVG_NB) 
      {
          m_audio_diff_avg_count++;
      } 
      else 
      {
          avg_diff = m_audio_diff_cum * (1.0 - m_audio_diff_avg_coef);
          if(fabs(avg_diff) >= m_audio_diff_threshold) 
          {
              wanted_size = samples_size + ((int)(diff * m_audio_st->codec->sample_rate) * n);
              min_size = samples_size * ((100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100);
              max_size = samples_size * ((100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100);
              if(wanted_size < min_size) 
              {
                  wanted_size = min_size;
              } 
              else if (wanted_size > max_size) 
              {
                  wanted_size = max_size;
              }
              if(wanted_size < samples_size) 
              {
                  /* remove samples */
                  samples_size = wanted_size;
              } 
              else if(wanted_size > samples_size) 
              {
                  uint8_t *samples_end, *q;
                  int nb;

                  /* add samples by copying final sample*/
                  nb = (samples_size - wanted_size);
                  samples_end = (uint8_t *)samples + samples_size - n;
                  q = samples_end + n;
                  while(nb > 0) 
                  {
                      memcpy(q, samples_end, n);
                      q += n;
                      nb -= n;
                  }
                  samples_size = wanted_size;
              }
          }
      }
    } 
    else 
    {
      /* difference is TOO big; reset diff stuff */
      m_audio_diff_avg_count = 0;
      m_audio_diff_cum = 0;
    }
  }
  return samples_size;
}

/* get_audio_clock() function
*/
double CFFMPEGPlayer::get_audio_clock()
{
    if (m_audio_st == NULL)
        return get_external_clock();
    double pts;
    int hw_buf_size, bytes_per_sec, n;
      
    pts = m_audio_clock; /* maintained in the audio thread */
    hw_buf_size = m_audio_buf_size - m_audio_buf_index;
    bytes_per_sec = 0;
    n = m_audio_st->codec->channels * 2;
    if(m_audio_st) 
    {
        bytes_per_sec = m_audio_st->codec->sample_rate * n;
    }
    if(bytes_per_sec) 
    {
    pts -= (double)hw_buf_size / bytes_per_sec;
    }
    return pts;
}

double CFFMPEGPlayer::get_video_clock()
{
	if (this->m_is_paused.GetValue())
    {
        return m_video_current_pts;
    }
    return m_video_current_pts_drift + av_gettime() / 1000000.0;
}

double CFFMPEGPlayer::get_external_clock()
{
    /*av_gettime() 
      Get the current time in microseconds. 
    */
    return av_gettime() / 1000000.0;
}

/*returns the current time in seconds
*/
double CFFMPEGPlayer::get_master_clock()
{
      if(m_av_sync_type == AV_SYNC_VIDEO_MASTER)
      {
        return get_video_clock();
      } 
      else if(m_av_sync_type == AV_SYNC_AUDIO_MASTER) 
      {
        return get_audio_clock();
      } 
      else 
      {
        return get_external_clock();
      }
}
/*
*/
bool CFFMPEGPlayer::IsPaused()
{
	return this->m_is_paused.GetValue() && !IsSearch() && !IsSave();
}
/*
*/
bool CFFMPEGPlayer::IsSearch()
{
    return m_seek_in_progress;
}
/*
*/
bool CFFMPEGPlayer::IsSave()
{
    return m_save_in_progress;
}

bool CFFMPEGPlayer::IsClosed()
{
    return this->m_is_closed;
}


void CFFMPEGPlayer::stream_close()
{
    VideoPicture *vp;
    int i;
    /* free all pictures */
    for(i=0;i<VIDEO_PICTURE_QUEUE_SIZE; i++) {
        vp = &m_pictq[i];
    }
    if(m_pictq_mutex)
    {
        SDL_DestroyMutex(m_pictq_mutex);
        m_pictq_mutex = NULL;
    }
    if (m_pictq_cond)
    {
        SDL_DestroyCond(m_pictq_cond);
        m_pictq_cond = NULL;
    }
}

void CFFMPEGPlayer::stream_component_close(unsigned int stream_index)
{
    AVFormatContext *ic = m_pFormatCtx;
    AVCodecContext *avctx;

    if (stream_index < 0 || stream_index >= ic->nb_streams)
        return;
    avctx = ic->streams[stream_index]->codec;

    switch(avctx->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        packet_queue_abort(&m_audioq);

        SDL_CloseAudio();

        packet_queue_end(&m_audioq);
        break;
    case AVMEDIA_TYPE_VIDEO:
        packet_queue_abort(&m_videoq);

        /* note: we also signal this mutex to make sure we deblock the
           video thread in all cases */
        SDL_LockMutex(m_pictq_mutex);
        SDL_CondSignal(m_pictq_cond);
        SDL_UnlockMutex(m_pictq_mutex);

        SDL_WaitThread(m_video_tid, NULL);

        packet_queue_end(&m_videoq);
        break;
    default:
        break;
    }

    ic->streams[stream_index]->discard = AVDISCARD_ALL;
    avcodec_close(avctx);
    switch(avctx->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        m_audio_st = NULL;
        m_audioStream = -1;
        break;
    case AVMEDIA_TYPE_VIDEO:
        m_video_st = NULL;
        m_videoStream = -1;
        break;
    default:
        break;
    }
}

/*returns the length of the clip, in milliseconds
*/
int64_t CFFMPEGPlayer::Duration()
{
    return m_TimeLine.GetLocalDuration();
}
double CFFMPEGPlayer::FramePerSec()
{
    return m_frame_per_sec;
}
/*returns the position of the current frame in milliseconds
*/
int64_t CFFMPEGPlayer::CurrentTime()
{
    return m_TimeLine.GlobalToLocalTime(m_current_time);
}

bool CFFMPEGPlayer::GetMute()
{
    return m_mute;
}
void CFFMPEGPlayer::SetMute(bool Value)
{
    m_mute = Value;
}

EFFMPEGPlayerScreenMode CFFMPEGPlayer::GetScreenMode()
{
    return m_ScreenMode;
}
void CFFMPEGPlayer::SetScreenMode(EFFMPEGPlayerScreenMode Value)
{
    m_ScreenMode = Value;
}

/* looking for a keyframe at the position  SeekPos - ms
*/
void CFFMPEGPlayer::Seek(int64_t SeekPos)
{

	if (this->m_need_seek.GetValue())
		return;
	if (this->m_need_frame.GetValue())
		return;

	if (m_seek_in_progress)
        return;

	if (this->m_is_paused.GetValue() == false) 
         StopPlayback();

	 if (SeekPos >= this->Duration())
	 {
		 /* проверим это поиск действительно последнего кадра
			или конец ролика был вырезан.
		 */
		 uint64_t globalPosition = this->m_TimeLine.LocalToGlobalTime(SeekPos);
		 if (globalPosition >= this->m_TimeLine.GetGlobalDuration())
		 {
			 /* установим позицию для поиска, на 10 
				единиц детализации. 
			 */
			 SeekPos -= 20*SEEK_GRANULARITY; 
			 this->m_need_last_frame.SetValue(true);
		 }
	 }

	/* преобразуем время в микросекунды. 
     */
     int64_t sp = SeekPos;
     int64_t gsp = m_TimeLine.LocalToGlobalTime(sp);
     int64_t incr= 0;
     incr = gsp - m_current_time;
     
	 m_seek_flags = incr < 0 ?  AVSEEK_FLAG_BACKWARD : 0;
	 if (!this->m_TimeLine.IsVisibleTime(gsp))
	 {
		if (incr < 0)
			m_seek_pos = this->m_TimeLine.GetPrevVisibleTime(gsp);
		else
			m_seek_pos = this->m_TimeLine.GetNextVisibleTime(gsp);
	 }
	 else
		 m_seek_pos = m_current_time + incr;

	 if (this->has_video())
		this->m_need_frame.SetValue(true);
	 else
	 {
		 this->UpdateAudioImage();
		if (m_FrameCallBack)
			m_FrameCallBack(m_AudioImage, m_UserData);
		 this->schedule_refresh(100);
	 }

	 this->m_need_seek.SetValue(true);
}
void  CFFMPEGPlayer::SetCurrentTime(uint64_t cur_pts)
{
    m_current_time = 0;
    if (has_video())
	{
		if (m_pFrame == NULL)
			return;
		int64_t pts = m_pFrame->best_effort_timestamp;
		if (pts == AV_NOPTS_VALUE)
			pts = 0;
		int64_t start_time = m_pFormatCtx->start_time;
		AVRational r;
		r.num = 1;
		r.den = AV_TIME_BASE;
		if (m_video_st != NULL && m_video_st->start_time != 0)
		{
			start_time = av_rescale_q(m_video_st->start_time, m_video_st->time_base,  r);
		}
		pts = av_rescale_q(pts, m_video_st->time_base,  r);
		if (m_first_video_pts < 0)
			m_first_video_pts = pts;
		m_current_time = pts - start_time/* - m_first_video_pts*/;
		if (m_current_time < 0)
			m_current_time = 0;
	}
	else if (has_audio())
	{
		if (cur_pts == AV_NOPTS_VALUE)
			return;
		int64_t pts = cur_pts;
		int64_t start_time = m_pFormatCtx->start_time;
		AVRational r;
		r.num = 1;
		r.den = AV_TIME_BASE;
		pts = av_rescale_q(pts, m_audio_st->time_base,  r);
		m_current_time = pts - start_time;
		if (m_current_time < 0)
			m_current_time = 0;
	}
}

void    CFFMPEGPlayer::ResetTime()
{
        m_frame_last_pts = 0;
        m_frame_last_delay = 0;
        m_frame_timer = av_gettime();
}


int64_t CFFMPEGPlayer::GetDelay(uint64_t cur_pts)
{
	if (this->has_video())
	{
		if (m_pFrame == NULL)
			return -1;

		int64_t pts = m_pFrame->best_effort_timestamp;
		AVRational r;
		r.num = 1;
		r.den = AV_TIME_BASE;
		m_video_current_pts = av_rescale_q(pts, m_video_st->time_base,  r);
		int64_t delay = m_video_current_pts - m_frame_last_pts;

		if (delay <= 0 || delay >= 1000000)
			delay = m_frame_last_delay;
		//if (m_av_sync_type != AV_SYNC_VIDEO_MASTER)
		//{
		//	ref_clock = get_master_clock();
		//	diff = vp->pts - ref_clock;
		//	int64_t  sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
		//	if(fabs(diff) < AV_NOSYNC_THRESHOLD) 
		//	{
		//		if(diff <= -sync_threshold) 
		//		{
		//			delay = 0;
		//		} 
		//		else if(diff >= sync_threshold) 
		//		{
		//			delay = 2 * delay;
		//		}
		//	}
		//}

		m_frame_last_delay = delay;
		m_frame_last_pts = m_video_current_pts;
		m_frame_timer += delay;

		int64_t adelay = m_frame_timer - av_gettime();
		if (adelay < 0)
			return 10;
		return adelay / 1000;


	}
	return -1;
}

void CFFMPEGPlayer::SearchForward()
{
    if (m_seek_in_progress)
        return;
    if (m_stop_playback == false)
        StopPlayback();
    m_ImageCompare.Reset();
	m_seek_forward = true;
	Seek(m_current_time);
	m_seek_in_progress = true;
}

void CFFMPEGPlayer::SearchBackward()
{
     if (m_seek_in_progress)
        return;
     if (m_stop_playback == false)
         StopPlayback();
 
	 m_ImageCompare.Reset();
     m_seek_forward = false;
     m_seek_in_progress = true;
}

double CFFMPEGPlayer::GetSearchThreshold()
{
    return m_search_threshold;
}

void CFFMPEGPlayer::SetSearchThreshold(double Value)
{
    if (Value > 0 && Value < 1)
        m_search_threshold = Value;
}

    /* начинает проигрывание видео
*/
void CFFMPEGPlayer::StartPlayback()
{
    if (m_seek_in_progress)
        return;

	if (this->m_is_paused.GetValue() == true)
    {
		this->ResetTime();
		this->m_is_paused.SetValue(false);
		m_seek_pos = m_current_time;
		m_eof = false;

		this->m_need_frame.SetValue(false);
		this->m_need_seek.SetValue(true);
		/* запустим воспроизведение видео
		*/
        schedule_refresh(10);
        SDL_PauseAudio(0);
    }
}
/*останавливает проигрывание видео
*/
void CFFMPEGPlayer::StopPlayback()
{
	if (this->m_is_paused.GetValue() == false)
    {
		this->m_is_paused.SetValue(true);
        schedule_refresh(-1);
        SDL_PauseAudio(1);
    }
   if (m_seek_in_progress)
       m_seek_in_progress = false;
}

bool CFFMPEGPlayer::IsPlayback()
{
	return !this->m_is_paused.GetValue();
}

int CFFMPEGPlayer::EventLoop()
{
    SDL_Event       event; 
     for(;;) 
     {
       if (m_quit)
		   return 0;
		SDL_WaitEvent(&event);
        switch(event.type) 
        {
            case FF_ALLOC_EVENT:
                    event_alloc_picture();
                break;
            case FF_REFRESH_EVENT :
                    event_video_refresh_timer();
                break;
            case FF_FINISH_EVENT:
                event_fihish_save_video();
                break;
			case FF_AUDIO_ANALYSIS_DONE_EVENT:
				OnAudioDone();
				break;
            case FF_QUIT_EVENT:
				m_quit = true;
              return 0;
              break;
            default:
              break;
        }
      }
     return 0;
}
/* CFFMPEGPlayer::DecompressLoop()
   функция декодирования изображения из пакета. 
*/
int CFFMPEGPlayer::DecompressLoop()
{
	av_log(NULL, AV_LOG_INFO, "[DecompressLoop] Start decompress.\n");
	for(;;)
    {
        if (m_quit)
            break;
		while ( this->m_is_paused.GetValue() && !m_need_frame.GetValue() && !m_quit && !this->m_seek_in_progress)
			SDL_Delay(10);
    	decodeHelper();
    }
	av_log(NULL, AV_LOG_INFO, "[DecompressLoop] Finish decompress.\n");
    return 0;
}
/*
*/ 
int CFFMPEGPlayer::SeekLoop()
{
    bool res = true;
    for(;;)
    {
        if (m_quit)
            break;
        if (!m_seek_in_progress)
            break;

        if (m_seek_forward)
        {
            m_seek_by_keyframes = false;
            res = NextFrame();
            m_seek_by_keyframes = true;
        }
        else
        {
            m_seek_by_keyframes = true;
            res = PrevFrame();
        }
        if (!res) 
            break;
    }
    m_seek_in_progress = false;
    m_seek_by_keyframes = true;
    return 0;
}

/*  CFFMPEGPlayer::seekHelper()
	выполняет прыжок на заданную позицию в файле. 
*/
void CFFMPEGPlayer::seekHelper()
{
	if (m_need_seek.GetValue() == true)
	{
		/* m_seek_pos - время на которое надо перейти в микросекундах 
		*/
		int64_t seek_target = m_seek_pos;
		int stream_index = -1;
		int ret = -1;
		/* установим индекс потока, для поиска требуемого фрейма
		*/
		if (m_videoStream >= 0)
			stream_index = m_videoStream;
		else if (m_audioStream >= 0)
			stream_index = m_audioStream;
		/* переконветируем время seek_target во временной масштаб потока.
		*/
		AVRational r; r.num = 1; r.den = AV_TIME_BASE;
		seek_target = av_rescale_q(seek_target+ m_pFormatCtx->start_time, r, m_pFormatCtx->streams[stream_index]->time_base);
		/* проверим seek_target
		*/
		ret = av_seek_frame(m_pFormatCtx, stream_index, seek_target, m_seek_flags);
		if (ret >= 0)
		{
			this->m_eof = false;
			if (m_audio_st != NULL) 
			{
				packet_queue_flush(&m_audioq);
				packet_queue_put(&m_audioq, &flush_pkt);
			}
			if (m_video_st != NULL) 
			{
				packet_queue_flush(&m_videoq);
				packet_queue_put(&m_videoq, &flush_pkt);
			}
		}
		/* выключаем флаг необходимости поиска.	*/
		m_need_seek.SetValue(false);
		/*проверим, имеется ли в медиа файле видео*/
		if (!this->has_video())
		{
			/*файл не содержит видео данных, потребуем 
			обновления экрана*/
			this->SetCurrentTime(seek_target);
			this->schedule_refresh(100);
		}
	}
}

/* проверка достигнут ли конец файла. 
*/
bool CFFMPEGPlayer::checkEof(int ret)
{
	return ret == AVERROR_EOF || url_feof(m_pFormatCtx->pb) || m_pFormatCtx->pb->eof_reached;
}
/* CFFMPEGPlayer::readPacketHelper()
   функция выполняет чтение пакета из файла и помещает его в соответствующую очередь 
   пакетов с использованием putPacketToQueue
*/
void CFFMPEGPlayer::readPacketHelper()
{
	int ret = -1; 
	int64_t  pts = AV_NOPTS_VALUE;
	/*выполяем цикл до тех пор, пока пакет не будет прочитан*/
	do
	{
		/* читаем пакет из файла*/
		ret = av_read_frame(m_pFormatCtx, packet);
		if (ret < 0)
		{
			/* не удалось прочитать пакет. проверим конец файла*/
			this->m_eof = checkEof(ret);
			if (m_eof)
			{
				/*достигнут конец файла и дальнейшее чтение не имеет смысла, 
				выходим из функции*/
				return;
			}
			/* по какой-то причине не удалось прочитать пакет, 
			задержка READ_PACKET_DELAY ms и попытаемся еще раз.
			todo: навереное стоит ограничить число попыток и установить 
			ошибочный статус, если их число превысит некоторый порог.*/
			SDL_Delay(READ_PACKET_DELAY);
			continue;
		}
		/* найдем занчение pts для данного пакета 
		   pts возвращается в микросекундах*/
		pts = getPacketTimeStamp(packet);
		if (pts == AV_NOPTS_VALUE)
		{
			/* пакет не содержит временных меток. 
			   Задержка READ_PACKET_DELAY ms.*/
			SDL_Delay(READ_PACKET_DELAY);
			continue;
		}
	}while(ret < 0);
	/*проверим, видим ли пакет*/
	if (this->m_TimeLine.IsVisibleTime(pts))
	{
		/*пакет видим, значит запишем его в очередь*/
		putPacketToQueue(packet);
	}
	else
	{
		/*пакет не видим, установим требование для поиска*/
		int64_t nt = this->m_TimeLine.GetNextVisibleTime(pts);
		this->m_need_seek.SetValue(true);
		m_seek_flags  = 0;
		m_seek_pos  = nt + SEEK_GRANULARITY;
	}
}
/* возарвщается значение времени для пакета pPacket в микросекундах 
*/
int64_t CFFMPEGPlayer::getPacketTimeStamp(AVPacket* pPacket)
{
	int64_t  pts = AV_NOPTS_VALUE;
	AVRational r;
	r.num = 1;
	r.den = AV_TIME_BASE;
	AVStream* stream = NULL;
	if (pPacket == NULL)
		return pts;
	stream = m_pFormatCtx->streams[pPacket->stream_index];
	if (pPacket->pts != AV_NOPTS_VALUE)
	{
		/* пакет имеет pts, конвертируем его в микросекунды*/
		pts = av_rescale_q(pPacket->pts, stream->time_base, r);
		return pts;
	}
	else if (pPacket->dts != AV_NOPTS_VALUE)
	{
		/* пакет не имеет pts, но имеет dts*/
		pts = av_rescale_q(pPacket->dts, stream->time_base, r);
		return pts;
	}
	return pts;
}
/* сортирует пакеты по типам и записывает их в соответствующие очереди с 
   использованием функции packet_queue_put
*/
void CFFMPEGPlayer::putPacketToQueue(AVPacket* pPacket)
{
	if (pPacket == NULL)
		return;

    if(pPacket->stream_index == m_videoStream) 
    { 
		/*пакеты содержащие видео данные*/
		packet_queue_put(&m_videoq, pPacket);
    } 
    else if(pPacket->stream_index == m_audioStream) 
    {
		/*пакеты содержащие аудио данные*/
		if (this->m_need_frame.GetValue() == false && this->m_seek_in_progress == false)
		{
			/*пакеты попадают в очередь, если плеер не 
			находится в режиме поиска*/
			packet_queue_put(&m_audioq, pPacket);
		}
    } 
    else 
    {
        /*все прочие пакеты, включая субтитры, освобождаются и не попадают в очередь*/
		av_free_packet(pPacket);
    }
}
/* главный цикл чтения информации из медиа-файла. 
   данные из файла извлекаются в виде пакетов с помощью  функции readPacketHelper. 
   При необходимости функция выполняет перемещение на указанное пользователем время 
   с помощью seekHelper
*/
int CFFMPEGPlayer::ReadPacketsLoop()
{
	for (;;)
	{
		if (m_quit)
		{
			/* выход из цикла осуществляется по переменной m_quit*/
			break;
		}
		if (this->m_need_seek.GetValue() == true)
		{
			/*при необходимости выполняется поиск*/
			this->seekHelper();
			SDL_Delay(READ_PACKET_DELAY);
			continue;
		}

		if (m_audioq.size > MAX_AUDIOQ_SIZE || m_videoq.size > MAX_VIDEOQ_SIZE || m_eof)
		{
			/* если пакетов в очереди слишком много или достигнут конец файла, 
				просто подолждем некоторое время. */

			SDL_Delay(READ_PACKET_DELAY);
			continue;
		}		

		if (!m_seek_in_progress)
		{
		      /*если не включен режим поиска новой сцены, то для чтения пакетов из файла
			  выполняется эта ветка.*/
			if (this->m_is_paused.GetValue() == true && !this->m_need_frame.GetValue())
			{
					/* если проигрыватель стоит на паузе и пользователь не запросил новый 
					   кадр с помощью команд поиска, просто подолждем ввода пользователя.*/
					SDL_Delay(READ_PACKET_DELAY);
					continue;
			}
			else
			{
				/* читаем пакет и записываем его в очередь пакетов.*/
				this->readPacketHelper();
			}
		}
		else
		{
			/*включен режим поиска новой сцены. этом режиме функция 
			просто читает пакеты и записывает их в очередь*/
			this->readPacketHelper();
		}
	}
	return 0;
}
/*
*/
int CFFMPEGPlayer::TranscodeLoop()
{
    int res = 0;
    m_save_in_progress = true;
    int64_t gst = m_TimeLine.LocalToGlobalTime(m_save_start);
    int64_t get = m_TimeLine.LocalToGlobalTime(m_save_finish);
    int64_t gd = get - gst;
    int64_t ld = (m_save_finish - m_save_start);
    this->m_seek_req = 1;
    this->m_seek_pos = gst;
   
    AVPacket Packet, *pkt = &Packet;
    av_init_packet(pkt);
    bool check_key = false;
    bool prev_visible = true;

    while(m_save_in_progress && !m_user_cancel)
    {
        /* make a jump if require 
        */
        if (m_seek_req)
        {
            int64_t seek_target = m_seek_pos;// + m_pFormatCtx->start_time;
            res = av_seek_frame(m_pFormatCtx, -1, seek_target, 0);
            if (res < 0)
               break;

            if (m_audio_st != NULL) 
            {
                packet_queue_flush(&m_audioq);
                packet_queue_put(&m_audioq, &flush_pkt);
                avcodec_flush_buffers(m_pFormatCtx->streams[m_audioStream]->codec);
            }
            if (m_video_st != NULL) 
            {
                packet_queue_flush(&m_videoq);
                packet_queue_put(&m_videoq, &flush_pkt);
                avcodec_flush_buffers(m_pFormatCtx->streams[m_videoStream]->codec);
            }

                m_seek_req = 0;
                check_key = true;
            }
        /* read the data from source 
        */
        res = av_read_frame(m_pFormatCtx, pkt);
        if (res < 0)
        {
            if (res == AVERROR_EOF || url_feof(m_pFormatCtx->pb) || m_pFormatCtx->pb->eof_reached)
            {
                m_save_in_progress = false;
            }
            break;
        }


        /*estimate the time. compute current pts 
        */
        double pts = 0;
        if (pkt->pts != AV_NOPTS_VALUE) 
            pts = (double)pkt->pts;
        else if (pkt->dts != AV_NOPTS_VALUE) 
            pts = (double)pkt->dts;
        else
        { 
              SDL_Delay(100); /* no error; wait for user input */
              continue;
        }

        AVStream* pInStream    = m_pFormatCtx->streams[pkt->stream_index];
        int64_t ct, lt;
        pts *= av_q2d(pInStream->time_base);
        ct = (int64_t)(pts*AV_TIME_BASE/* - m_pFormatCtx->start_time*/);

        lt = m_TimeLine.GlobalToLocalTime(ct);
        if (pkt->stream_index == m_videoStream)
        {
            /*process the time
            */           

            m_save_progress = 100*(float)(ct - gst)/ (float)(get - gst);
            if (ct >= get)
            {
                m_save_in_progress = false;
            }

        }
        
        if (!m_TimeLine.IsVisibleTime(ct))
        {
            //prev_visible = false;
            check_key = true;
            continue;
        }
        
        prev_visible = true;

        if (check_key)
        {
            if (pkt->flags != AV_PKT_FLAG_KEY)
                continue;
            else
                check_key = false;
        }
        if (!m_Encoder->SavePacket(pkt))
        {
            m_save_in_progress = false;
            res = 1; 
            continue;
        }
    }
	m_Encoder->CompleteTranscode();
    m_Encoder->Close();
    if (m_SaveFihishCallback != NULL)
    {
        int status;
        status = m_user_cancel? 1: 0;
        m_SaveFihishCallback(status, m_SaveFihishUserData);
    }
    m_save_in_progress = false;
    m_user_cancel = false;
    return res;
}


/* runs saving thread 
*/
bool CFFMPEGPlayer::Save(const char* lpFileName, int64_t StartTime, int64_t Duration)
{
    if (this->IsSave())
        return true;
    /* check the time 
    */
    if (StartTime < 0 || StartTime + Duration > this->Duration())
        return false;
    /* setup timing to save
    */
    m_save_start = StartTime;
    m_save_finish = StartTime + Duration;

    EFFMpegEncoderMode EncoderMode;
    EncoderMode = emTimeRecoding;
    if (m_pFrameProcessor && m_pFrameProcessor->GetMode() != pmNothing)
        EncoderMode = emVideoProcessing;
    m_Encoder = new CFFMpegEncoder(this, EncoderMode);
    if (!m_Encoder->Init(m_pFormatCtx, lpFileName))
    {
        delete m_Encoder;
        m_Encoder = NULL;
        return false;
    } 
    m_save_tid = NULL;
    m_save_tid = SDL_CreateThread(transcode_thread, this);
    return m_save_tid != NULL;
}
/* stops the saving thread 
*/
void   CFFMPEGPlayer::StopSave()
{
    m_save_in_progress = false;
    m_user_cancel = true;
}
/* returns current progress of saving
   -1 means there is not saving process
*/
float  CFFMPEGPlayer::GetSaveProgress()
{
    if (m_save_in_progress)
        return m_save_progress;
    else
        return -1;
}

int64_t CFFMPEGPlayer::GetSaveStartTime()
{
    return m_save_start;
}
/* Delete. this function add time segment to the m_TimeLine
   Start and Finish - mks in local time 
*/
void CFFMPEGPlayer::Delete(int64_t Start, int64_t Finish)
{
    /* convert to Global Time
    */
    int64_t gs,gd, ge;
    gs = m_TimeLine.LocalToGlobalTime(Start);
    ge = m_TimeLine.LocalToGlobalTime(Finish);
    gd =  ge - gs - 50;
    int64_t t = this->Duration();
    if (Finish >= t)
    {
        gd += (m_duration - gd - gs);
    }

    m_TimeLine.Add(gs, gd);
    if (Finish >= t)
    {
        Seek(this->Duration());
    }
    else
    {    
        Seek(Start);
    }
}
void CFFMPEGPlayer::Undo()
{
    m_TimeLine.Undo();
}
void CFFMPEGPlayer::Redo()
{
    m_TimeLine.Redo();
}

int  CFFMPEGPlayer::GetUndoCount()
{
    return m_TimeLine.UndoCount();
}

int  CFFMPEGPlayer::GetRedoCount()
{
    return m_TimeLine.RedoCount();
}


/*move to the next visible keyframe 
*/
bool CFFMPEGPlayer::NextFrame()
{ 
	this->Seek(this->m_TimeLine.GlobalToLocalTime(m_current_time + SEEK_GRANULARITY));
    return true;
}

/*move to previous visible keyframe
*/
bool CFFMPEGPlayer::PrevFrame()
{
	this->Seek(this->m_TimeLine.GlobalToLocalTime(m_current_time - 2*SEEK_GRANULARITY));
	return true;
}
/*переход на первый доступный кадр, с учетом временной шкалы. 
*/
bool CFFMPEGPlayer::FirstFrame()
{
	Seek(0);
	return true;
}

bool CFFMPEGPlayer::LastFrame()
{
    bool res = false;
    return res;
}

void CFFMPEGPlayer::SetFrameCallback(FrameCallback func, void* UserData)
{
    m_UserData = UserData;
    m_FrameCallBack = func;
}

void CFFMPEGPlayer::SetProcessingMode(int Mode)
{
    switch (Mode)
    {
    case 0:
        this->m_ProcessingMode = pmNothing;
        break;
    case 1:
        this->m_ProcessingMode = pmFlipLeft;
        break;
    case 2:
        this->m_ProcessingMode = pmFlipRight;
        break;
    case 3:
        this->m_ProcessingMode = pmRotate180;
        break;
    case 4:
        this->m_ProcessingMode = pmFlipVertical;
        break;
    case 5:
        this->m_ProcessingMode = pmFlipHorizontal;
        break;
    case 6:
        this->m_ProcessingMode = pmRotateMirror90;
        break;
    case 7:
        this->m_ProcessingMode = pmRotateMirror270;
        break;
    }
    this->display_image();
}


bool CFFMPEGPlayer::IsSeekBykeyFrames ()
{
    return m_seek_by_keyframes;
}
void CFFMPEGPlayer::SetSeekByKeyframes (bool value)
{
    m_seek_by_keyframes = value;
}


CFrameProcessor* CFFMPEGPlayer::GetFrameProcessor()
{
    return m_pFrameProcessor;
}
void CFFMPEGPlayer::SetFrameProcessor(CFrameProcessor* processor)
{
    m_pFrameProcessor = processor;
}

CFFMPEGTimeLine* CFFMPEGPlayer::GetTimeLine()
{
    return &m_TimeLine;
}

void CFFMPEGPlayer::GetLastError(int* minor, int* major)
{
    *minor = m_LastErrorMinor;
    *major = m_LastErrorMajor;
}

void CFFMPEGPlayer::SetSaveFinishCallback(SaveFihishCallback func, void* UserData)
{
    m_SaveFihishCallback = func;
    m_SaveFihishUserData = UserData;
}

bool CFFMPEGPlayer::has_video()
{
	return m_videoStream >= 0;
}

bool CFFMPEGPlayer::has_audio()
{
	return m_audioStream >= 0;
}

void CFFMPEGPlayer::SetUpAudioImage()
{
	
	if (this->m_audio_st == NULL)
		return;
	if (this->m_audio_st->codec == NULL)
		return;
	int nc = this->m_audio_st->codec->channels;
	awpPoint p1;
	awpPoint p2;
	
	float audio_min1 = FLT_MAX;
	float audio_max1 = -FLT_MAX;
	float audio_min2 = FLT_MAX;
	float audio_max2 = -FLT_MAX;

	float audio_avg1 = 0;
	float audio_avg2 = 0;
	for (int i = 1; i < this->m_audioArray.size(); i++)
	{
		CAudioSegment s = this->m_audioArray[i];
		const SAudioData* s0 = s.AudioData();

		audio_avg1 += s0[0].m_averageValue;
		if (nc > 1)
			audio_avg2 += s0[1].m_averageValue;
	}
	audio_avg1 /= this->m_audioArray.size();
	if (nc > 1)
		audio_avg2 /= this->m_audioArray.size();

	for (int i = 1; i < this->m_audioArray.size(); i++)
	{
		CAudioSegment s = this->m_audioArray[i];
		const SAudioData* s0 = s.AudioData();		
		float delta = fabs(audio_avg1 - s0[0].m_averageValue);
		if (audio_max1 < delta)
			audio_max1 = delta;
		if (audio_min1 > delta)
			audio_min1 = delta;
		if (nc > 1)
		{
			 delta = fabs(audio_avg2 - s0[1].m_averageValue);
			if (audio_max2 < delta)
				audio_max2 = delta;
			if (audio_min2 > delta)
				audio_min2 = delta;
		}
	}

	float sy = nc > 1? 120:240;

	for (int i = 1; i < this->m_audioArray.size(); i++)
	{
	
		CAudioSegment s = this->m_audioArray[i];
		const SAudioData* s0 = s.AudioData();
		float delta = fabs(audio_avg1 - s0[0].m_averageValue);
		p1.X = 1+i*2000 / this->m_audioArray.size();
		p2.X = p1.X;
		
		p1.Y = sy - sy*((delta)/(audio_max1));
		p2.Y = sy + sy*((delta) / (audio_max1));
		awpDrawCLine(m_AudioImageBkg, p1, p2, 0, 255, 0, 1);
		if (nc > 1)
		{
			delta = fabs(audio_avg2 - s0[1].m_averageValue);
			p1.X = i*2000 / this->m_audioArray.size();
			p2.X = p1.X;
		
			p1.Y = 3*sy - sy*((delta)/(audio_max2));
			p2.Y = 3*sy + sy*((delta) / (audio_max2));
			awpDrawCLine(m_AudioImageBkg, p1, p2, 0, 255, 0, 1);		
		}
	}


#ifdef _DEBUG
	awpSaveImage("audioimage.jpg", m_AudioImageBkg);
#endif
}

void CFFMPEGPlayer::UpdateAudioImage()
{
	awpPoint p1;
	awpPoint p2;
	p1.X = CurrentTime()*2000 / Duration();
	p1.Y = 1;
	p2.X = p1.X;
	p2.Y = 480 -1;	
	awpFastCopyImage(m_AudioImageBkg, m_AudioImage);
	awpColor* c = (awpColor*)m_AudioImage->pPixels;
	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < p1.X; x++)
		{
			if (c[x+y*2000].bGreen > 0)
				c[x+y*2000].bGreen = 200;
			else
			{
				c[x+y*2000].bGreen = 64;
				c[x+y*2000].bRed = 64;
				c[x+y*2000].bBlue = 64;
			}
		}
	}
	awpDrawCLine(m_AudioImage, p1, p2, 0, 0, 255, 3);
}

void CFFMPEGPlayer::PrepareAudioSegments()
{
	SDL_Thread* t = SDL_CreateThread(audio_analysis_thread, this);
}
/*цикл анализа аудиопотока 
*/
int CFFMPEGPlayer::PrepareAudioLoop()
{
	int ret = 0;
	if (this->m_audio_st == NULL)
		goto FINISH;
	AVFrame* frame = avcodec_alloc_frame();
	int got_frame= 0;
	int len1;
	AVCodecContext *dec = m_audio_st->codec;
	if (dec == NULL)
		goto FINISH;
	float* audio_buffer = NULL;
	int audio_buffer_size = 0;
	audio_buffer_size = dec->channels*dec->sample_rate / 10;
	audio_buffer = (float*)malloc(audio_buffer_size*sizeof(float));
	if (audio_buffer == NULL)
		goto FINISH;
	int write_count = 0;
	for(;;)
    {
        if (m_quit)
		{
			this->m_audioArray.clear();
			break;
		}
        if (m_eof)
            break;

        int ret1 = av_read_frame(m_pFormatCtx, packet);
        if(ret1 < 0) 
        {
      
          if (ret1 == AVERROR_EOF || url_feof(m_pFormatCtx->pb) || m_pFormatCtx->pb->eof_reached)  
          {
              m_eof = true;
          }
          else
          {
              SDL_Delay(100); /*no eof*/
              continue;
          } 
        }
		else  
		{
			/* распаковка пакета
			*/
			 avcodec_get_frame_defaults(frame);
			 len1 = avcodec_decode_audio4(dec, frame, &got_frame, packet);
			 if (len1 > 0)
			 {
				 for (int i = 0; i < frame->nb_samples; i++)
				 {
					 audio_buffer[write_count] = (float)frame->data[0][i];
					 write_count++;
					 if (write_count >= audio_buffer_size)
					 {
						write_count = 0;
						SAudioData sad[2];
						memset(sad, 0, sizeof(sad));
						sad[0].m_minValue = FLT_MAX;
						sad[0].m_maxValue = -FLT_MIN;
						sad[1].m_minValue = FLT_MAX;
						sad[1].m_maxValue = -FLT_MIN;
						int n = dec->channels > 1 ? 2:1;
						for (int j = 0; j < audio_buffer_size / n; j++)
						{
							sad[0].m_averageValue += audio_buffer[n*j];
							if (sad[0].m_maxValue < audio_buffer[n*j])
								sad[0].m_maxValue = audio_buffer[n*j];

							if (sad[0].m_minValue > audio_buffer[n*j])
								sad[0].m_minValue = audio_buffer[n*j];
							
							if (dec->channels > 1)
							{
								sad[1].m_averageValue += audio_buffer[n*j+1];
								if (sad[1].m_maxValue < audio_buffer[n*j+1])
									sad[1].m_maxValue = audio_buffer[n*j+1];
								if (sad[1].m_minValue > audio_buffer[n*j+1])
									sad[1].m_minValue = audio_buffer[n*j+1];

							}
						}
						sad[0].m_averageValue /= audio_buffer_size /n;
						if (dec->channels > 1)
							sad[1].m_averageValue  /= audio_buffer_size/n;

						CAudioSegment s(dec->channels, 1, 1, true, false, sad);
						this->m_audioArray.push_back(s);
					 }
				 }
			 }
		}
		av_free_packet(packet);
    }
	avcodec_flush_buffers(dec);
FINISH:	
	if (audio_buffer != NULL)
		free(audio_buffer);
	// сформируем событие обрабоки завершения анализа аудиодорожки
    SDL_Event event;
    event.type = FF_AUDIO_ANALYSIS_DONE_EVENT;
    event.user.data1 = this;
    SDL_PushEvent(&event);

	return ret;
}
/* вызывается из цикла обработки событий EventLoop и обрабатывает событие 
   завершение анализа аудиодорожки. 
*/
void CFFMPEGPlayer::OnAudioDone()
{
	// 
	this->m_is_closed = !this->m_audioArray.size() > 0;
	if (!this->m_is_closed)
	{
		m_decode_tid = SDL_CreateThread(read_thread, this);
		SetUpAudioImage();
		Seek(0);
		this->schedule_refresh(100);
	}
	else
	{
		SDL_Event e;
		e.type = FF_QUIT_EVENT;
		e.user.data1 = this;
		SDL_PushEvent(&e);
	}
}

#pragma endregion CFFMPEGPlayerArea

#pragma region CFFMPEGTimeLineArea

CTimeSegment::CTimeSegment()
{
    m_sp = -1;
    m_duration = -1;
    m_index = -1;
    m_ep = -1;
    m_erased =  false;
}
CTimeSegment::CTimeSegment(int64_t s, int64_t d)
{
    m_sp  = s;
    m_duration = d;
    m_ep = m_sp+m_duration;
    m_index = -1;
}
CTimeSegment::CTimeSegment(const CTimeSegment& ts)
{
    m_sp = ts.GetStartTime();
    m_duration = ts.GetDuration();
    m_ep = m_sp + m_duration;
    m_index = ts.GetIndex();
}
CTimeSegment::~CTimeSegment(){};
//props
void CTimeSegment::SetStratTime(int64_t s)
{
    m_sp = s;
    m_ep = s + m_duration;
}
int64_t CTimeSegment::GetStartTime() const 
{
    return m_sp;
}
void CTimeSegment::SetDuration(int64_t d)
{
    m_duration = d;
    m_ep = m_sp+d;
}
const int64_t CTimeSegment::GetDuration()const 
{
    return m_duration;
}
int64_t CTimeSegment::GetEndTime()
{
    return m_ep;
}
void CTimeSegment::SetIndex(int Value)
{
    m_index = Value;
}
int CTimeSegment::GetIndex()const 
{
    return m_index;
}
bool CTimeSegment::GetErased() const
{
    return m_erased;
}
void CTimeSegment::SetErased(bool Value)
{
    m_erased = Value;
}

/*cluster maker class
*/
class CClusterMaker
{
private:
    deque<CTimeSegment> m_SourceItems;
    int                 m_NumClusters;
    vector<vector<CTimeSegment>> m_Clusters;
    void Clear();
    deque <CTimeSegment>::iterator  GetMaxElement();
    void CollectClusterElents(unsigned int ClusterIndex);
    int  GetNumElements();
public:
    CClusterMaker();
    ~CClusterMaker();
    void DoClusters(deque<CTimeSegment> &items);
    int GetNumClusters();
    int GetNumClusterItems(unsigned int ClusterIndex);
    CTimeSegment GetClusterItem(unsigned int ClusterIndex, unsigned int SegmentIndex);
    CTimeSegment GetMaxClusterItem(unsigned int ClusterIndex);
};

CClusterMaker::CClusterMaker()
{   
    m_NumClusters = 0;
}

CClusterMaker::~CClusterMaker()
{
    // dummy
}
void CClusterMaker::DoClusters(deque<CTimeSegment> &items)
{
    // clear all items
    Clear();
    // copy source items to the m_SourceItems
    for (unsigned int i = 0; i < items.size(); i++)
        m_SourceItems.push_back(items[i]);
    // clear cluster info from m_SourceItems
    for (unsigned int i = 0; i < m_SourceItems.size();i++)
    {
        m_SourceItems[i].SetIndex(-1);
        m_SourceItems[i].SetErased(false);
    }

    int clusters_count = 0;
    do
    {
        /*get an iterator to the longest item in the collection.
          and store it in an internal variable "s"
        */
        deque <CTimeSegment>::iterator maxIter = GetMaxElement();
        if (maxIter == m_SourceItems.end() )
            break;
        CTimeSegment s = *maxIter;
        //m_SourceItems.erase(maxIter);
        maxIter->SetErased(true);
        /*create a new cluster based on the item.
        */
        {
            vector<CTimeSegment> vts;
            s.SetIndex(clusters_count);
            vts.push_back(s);
           
            m_Clusters.push_back(vts);
            /*as the longest item in our collection covers all the other elements,
            we simply choose them from the remnants of the collection.
            */
            CollectClusterElents(clusters_count);
            clusters_count++;
        }

    }while(GetNumElements() > 0);
}
int CClusterMaker::GetNumClusters()
{
    return m_Clusters.size();
}

int CClusterMaker::GetNumClusterItems(unsigned int ClusterIndex)
{
    if (ClusterIndex <0 || ClusterIndex >= m_Clusters.size())
        return 0;
    return m_Clusters[ClusterIndex].size();
}
CTimeSegment CClusterMaker::GetClusterItem(unsigned int ClusterIndex, unsigned int SegmentIndex)
{
    CTimeSegment res;
    if (ClusterIndex < 0 || ClusterIndex >= m_Clusters.size())
        return res;
    if (SegmentIndex < 0 || SegmentIndex >= m_Clusters[ClusterIndex].size())
        return res;
    return m_Clusters[ClusterIndex][SegmentIndex];
}
CTimeSegment CClusterMaker::GetMaxClusterItem(unsigned int ClusterIndex)
{
    CTimeSegment res;
    if (ClusterIndex < 0 || ClusterIndex >= m_Clusters.size())
        return res;
    vector<CTimeSegment> srcCluster = m_Clusters[ClusterIndex];
    
    int64_t st = srcCluster[0].GetStartTime();
    int64_t et = srcCluster[0].GetEndTime();

    for (unsigned int i = 1; i < srcCluster.size(); i++)
    {
        if (st > srcCluster[i].GetStartTime())
            st = srcCluster[i].GetStartTime();
        if (et < srcCluster[i].GetEndTime())
            et = srcCluster[i].GetEndTime();
    }

    int64_t d = et - st;
    res.SetStratTime(st);
    res.SetDuration(d);
    res.SetIndex(-1);
    return res;
}

void CClusterMaker::Clear()
{
    m_SourceItems.clear();
    for (unsigned int i = 0; i < m_Clusters.size(); i++)
        m_Clusters[i].clear();
    m_Clusters.clear();
    m_NumClusters = 0;
}

int  CClusterMaker::GetNumElements()
{
    int res = 0;
    for (unsigned int i = 0; i < m_SourceItems.size(); i++)
        if (!m_SourceItems[i].GetErased())
            res++;
    return res;
}


deque <CTimeSegment>::iterator CClusterMaker::GetMaxElement()
{
    deque <CTimeSegment>::iterator Iter;
    deque <CTimeSegment>::iterator end = m_SourceItems.end();
    deque <CTimeSegment>::iterator max_Iter;
    Iter = m_SourceItems.begin();
    while(Iter->GetErased() == true)
    {
        Iter++;
        if (Iter == m_SourceItems.end())
            break;
    }
    if (Iter == m_SourceItems.end())
        return Iter;
    max_Iter = Iter;

    for (; Iter != end; ++Iter )
    {
        if (Iter->GetErased())
            continue;
        int64_t t1 = Iter->GetDuration();
        int64_t t2 = max_Iter->GetDuration();
        if (t1 > t2)
            max_Iter = Iter;
    }
    return max_Iter;
}
/*
*/
void CClusterMaker::CollectClusterElents(unsigned int ClusterIndex)
{
    if (ClusterIndex  < 0 || ClusterIndex  >= m_Clusters.size())
        return;
   CTimeSegment ts = m_Clusters[ClusterIndex][0];
   deque <CTimeSegment>::iterator Iter = m_SourceItems.begin();
   deque <CTimeSegment>::iterator end = m_SourceItems.end();
   /* we mark all the overlapping elements.
   */
   for (;Iter != end; ++Iter)
   {
       if (ts.GetStartTime() <= Iter->GetStartTime()  && ts.GetEndTime() >= Iter->GetEndTime())
       {
           Iter->SetIndex(ClusterIndex);
           /*transfer the tagged items in the cluster.
           */
           m_Clusters[ClusterIndex].push_back(*Iter);
           //m_SourceItems.erase(Iter);
           Iter->SetErased(true);
           if (GetNumElements() == 0)
               break;
       }
   }
} 


CFFMPEGTimeLine::CFFMPEGTimeLine()
{
    m_GlobalDuration = -1;
}

CFFMPEGTimeLine::~CFFMPEGTimeLine()
{
}

void CFFMPEGTimeLine::Init(int64_t Duration)
{
    m_GlobalDuration = Duration; 
}

void CFFMPEGTimeLine::Close()
{
    m_GlobalDuration = -1;
	this->m_DelItems.clear();
	this->m_VisibleItems.clear();
	this->m_InvisibleItems.clear();
	this->m_RedoItems.clear();
}

void CFFMPEGTimeLine::Add(int64_t StartPos, int64_t duration)
{
    CTimeSegment ts(StartPos, duration);
    m_DelItems.push_back(ts);
    Calc();
}
/* remove TimeSegment from deleted items
*/
void CFFMPEGTimeLine::Undo()
{
    if (!m_DelItems.empty())
    {
        m_RedoItems.push_back(m_DelItems.back());
        m_DelItems.pop_back();
        Calc();
    }
}
/* Add TimeSegment to the deleted items from redo buffer
*/
void CFFMPEGTimeLine::Redo()
{
    if (!m_RedoItems.empty())
    {
        m_DelItems.push_back(m_RedoItems.back());
        m_RedoItems.pop_back();
        Calc();
    }
}
/* Returns number of deleted TimeSegments 
*/
int CFFMPEGTimeLine::UndoCount()
{
    return m_DelItems.size();
}
/* Returns size of redo buffer
*/
int CFFMPEGTimeLine::RedoCount()
{
    return m_RedoItems.size();
}

int64_t CFFMPEGTimeLine::GetGlobalDuration()
{
	return this->m_GlobalDuration;
}
/* dump deleted TimeSegments 
*/
void CFFMPEGTimeLine::_debug_dump_del_items()
{
#ifdef _DEBUG
    double gt = (double)m_GlobalDuration/AV_TIME_BASE ;
    for (int i = 0; i < m_DelItems.size(); i++)
    {
        double t = (double)m_DelItems[i].GetStartTime() / AV_TIME_BASE;
        double t1 = (double)m_DelItems[i].GetEndTime() / AV_TIME_BASE;
    }
#endif
}
bool UDgreater ( CTimeSegment& elem1, CTimeSegment& elem2 )
{
    return elem1.GetStartTime() < elem2.GetStartTime();
}
/*
*/
void CFFMPEGTimeLine::Calc()
{
    m_InvisibleItems.clear();
    m_VisibleItems.clear();

    if (m_DelItems.size() == 0)
        return;

    _debug_dump_del_items();

    CClusterMaker cm;
    cm.DoClusters(m_DelItems);
    /*todo: prepare arrays m_VisibleItems and m_InvisibleItems
    */
    for (int i = 0; i < cm.GetNumClusters(); i++)
    {
        CTimeSegment ts = cm.GetMaxClusterItem(i);
        m_InvisibleItems.push_back(ts);
    }

    /*setup visible items in the variable  m_VisibleItems
    */
    CTimeSegment ts;
    int64_t d;
    for (unsigned int i = 0; i < m_InvisibleItems.size() - 1; i++)
    {
        /* process first element of m_InvisibleItems
        */
        if (i == 0 && m_InvisibleItems[0].GetStartTime() == 0)
        {
            /*setup start time 
            */
            ts.SetStratTime(m_InvisibleItems[0].GetEndTime());
            if (m_InvisibleItems.size() == 1)
            {
                /*case began trimming video
                */
                d = m_GlobalDuration - ts.GetStartTime();
            }
            else
            {
                /*this case means that in addition to start, cut out some kind of part of the movie.
                  m_InvisibleItems.size() > 1 
                */
                d = m_InvisibleItems[1].GetStartTime() - m_InvisibleItems[0].GetEndTime();
            }
            ts.SetDuration(d);
            m_VisibleItems.push_back(ts);
        }
        else if (i == 0)
        {
            /* this case means that first invisible element in the body of movie, not at start 
            */
            ts.SetStratTime(0);
            d = m_InvisibleItems[1].GetStartTime();
            ts.SetDuration(d);
            m_VisibleItems.push_back(ts);
        }
        else
        {
            /*work with an arbitrary segment
            */
            ts.SetStratTime(m_InvisibleItems[i].GetEndTime());
            d = m_InvisibleItems[i+1].GetStartTime()  - m_InvisibleItems[i].GetEndTime();
            ts.SetDuration(d);
            m_VisibleItems.push_back(ts);
        }
    }
    /*processing the last segment
    */
    if (m_InvisibleItems[m_InvisibleItems.size() - 1].GetEndTime() != m_GlobalDuration)
    {
        ts.SetStratTime(m_InvisibleItems[m_InvisibleItems.size() - 1].GetEndTime());
        d = m_GlobalDuration - m_InvisibleItems[m_InvisibleItems.size() - 1].GetStartTime();
        ts.SetDuration(d);
        m_VisibleItems.push_back(ts);
    }
    /*sorting invisible items
    */
    for (int i = 0; i < m_InvisibleItems.size(); i++)
    {
        CTimeSegment min_ts = m_InvisibleItems[i];
        int index = i;
        for (int j = i; j < m_InvisibleItems.size(); j++)
        {
            if (min_ts.GetStartTime() > m_InvisibleItems[j].GetStartTime())
            {
                min_ts = m_InvisibleItems[j];
                index = j;
            }
        }
        CTimeSegment temp_ts = m_InvisibleItems[i];
        m_InvisibleItems[i] = min_ts;
        m_InvisibleItems[index] = temp_ts;
    }
    //sort(m_InvisibleItems.begin(), m_InvisibleItems.end(), UDgreater);
}
/* GetLocalDuration. 
  returns duration of the videoseq to the UI in the local time 
*/
int64_t CFFMPEGTimeLine::GetLocalDuration()
{
    int64_t res = m_GlobalDuration;
    if (m_InvisibleItems.size() == 0)
        return res;
    for (unsigned int i = 0; i < m_InvisibleItems.size(); i++)
    {
        int64_t d = m_InvisibleItems[i].GetDuration();
        res -= d;
    }

    return res;
}
/*GlobalToLocalTime. 
  Convert Global Time of of videoseq to the local time of UI .
*/
int64_t CFFMPEGTimeLine::GlobalToLocalTime(int64_t GlobalTime)
{
    int64_t res;
    res = GlobalTime;
    if (m_InvisibleItems.size() == 0)
        return res;
    unsigned int i = 0;
    
    for (unsigned int i = 0; i < m_InvisibleItems.size(); i++)
    {
        if (GlobalTime >= m_InvisibleItems[i].GetStartTime() && GlobalTime < m_InvisibleItems[i].GetEndTime())
        {
            GlobalTime = m_InvisibleItems[i].GetStartTime();
        };
    }
     
    while (i < m_InvisibleItems.size())
    {
        if (GlobalTime >= m_InvisibleItems[i].GetStartTime())
        {
            int64_t d = m_InvisibleItems[i].GetDuration();
            int64_t s = m_InvisibleItems[i].GetStartTime();
            if (s + d < m_GlobalDuration)
                res -= d;
        }
        i++;
    }
    return res;
}
/* LocalToGlobalTime. 
   Convert Local Time of UI to the global time of videoseq. 
*/
int64_t CFFMPEGTimeLine::LocalToGlobalTime(int64_t LocalTime)
{
    int64_t res = LocalTime;
    if (m_InvisibleItems.size() == 0)
        return res;
    unsigned int i = 0; 
    while (i < m_InvisibleItems.size())
    {
        if (res >= m_InvisibleItems[i].GetStartTime())
        {
            int64_t d = m_InvisibleItems[i].GetDuration();
            res += d;
        }
        i++;
    }
    return res;
}
/* Check the global time t. If the time t belongs to invible items - returns false
*/
bool CFFMPEGTimeLine::IsVisibleTime(int64_t t)
{
    bool res = true;
    for (unsigned int i = 0; i < m_InvisibleItems.size(); i++)
    {
        if (t >= m_InvisibleItems[i].GetStartTime() && t < m_InvisibleItems[i].GetEndTime())
            return false;
    }
    return res;
}
/* return next time from current t where there is not invisible area  
*/
int64_t CFFMPEGTimeLine::GetNextVisibleTime(int64_t t)
{
    /*todo: this seems as error. we may returns only global time
    */
    //if (t > GetLocalDuration())
    //    return GetLocalDuration();

    for (unsigned int i = 0; i < m_InvisibleItems.size(); i++)
    {
        if (t >= m_InvisibleItems[i].GetStartTime() && t < m_InvisibleItems[i].GetEndTime())
            return m_InvisibleItems[i].GetEndTime() + 50;
    }

    /*If time is not within the cut area, simply increase the value by 50
    */
    return t + 50 ; 
}
/* 
*/
int64_t CFFMPEGTimeLine::GetPrevVisibleTime(int64_t t)
{
    int64_t nt = t;
    /*
    */
    for (unsigned int i = 0; i < m_InvisibleItems.size(); i++)
    {
        if (t >= m_InvisibleItems[i].GetStartTime() && t < m_InvisibleItems[i].GetEndTime())
        {
            if (m_InvisibleItems[i].GetStartTime() > 0)
                return m_InvisibleItems[i].GetStartTime() - 50000;
            else
                return m_InvisibleItems[i].GetEndTime();
        }
    }

    /*If time is not within the cut area, simply increase the value by 50
    */
    return t - 50 > 0?t-50:0; 
}
#pragma endregion CFFMPEGTimeLineArea

const int   c_compare_img_size = 128;
const int   c_compare_img_size_sq = 128*128;

const float c_compare_img_norm = 128*128;
CFFMPEGPlayer::CImageCompare::CImageCompare()
{
    awpCreateImage(&m_image, c_compare_img_size, c_compare_img_size, 1, AWP_BYTE);
    first_time = true;
}

CFFMPEGPlayer::CImageCompare::~CImageCompare()
{
    awpReleaseImage(&m_image);
}
/*
*/
bool CFFMPEGPlayer::CImageCompare::Compare(AVPicture* frame, int height, int width, double threshold)
{
    bool res = true; 
    if (frame == NULL)
        return res;
    awpImage* img = NULL;
    awpCreateImage(&img, width, height, 1, AWP_BYTE);
    if (img != NULL)
    {
        BYTE* b  = (BYTE*)img->pPixels;
        uint8_t* p = frame->data[0]; 
        for (int i = 0; i < height; i++)
        {
            memcpy(b, p, width);
            b+= width;
            p+= frame->linesize[0];
        }

        res = InternalCompare(img, threshold);
    }
    return true;
}

bool CFFMPEGPlayer::CImageCompare::Compare(awpImage* frame, double threshold)
{
    bool res = true;
    if (frame == NULL)
        return res;
    awpImage* img = NULL;
    awpCopyImage(frame, &img);
    if (img != NULL)
    {
        awpConvert(img, AWP_CONVERT_3TO1_BYTE);
        res = InternalCompare(img, threshold);
        awpReleaseImage(&img);
    }
    return res;
}

bool CFFMPEGPlayer::CImageCompare::InternalCompare(awpImage* pImage, double threshold)
{
        awpResize(pImage, c_compare_img_size, c_compare_img_size);
        if (first_time)
        {
            first_time = false;
            awpFastCopyImage(pImage, m_image);
            return false;
        }
        double d = 0;
        BYTE* b1 = (BYTE*)pImage->pPixels;
        BYTE* b2 = (BYTE*)m_image->pPixels;
        for (int i = 0; i < c_compare_img_size_sq; i++)
        {
            d += ((double)b1[i] - (double)b2[i])*((double)b1[i] - (double)b2[i]);
        }
        d = sqrt(d);
        d /= c_compare_img_norm;
        awpFastCopyImage(pImage, m_image);
        awpReleaseImage(&pImage);
        return d > threshold;
}

CFrameProcessor::CFrameProcessor()
{
    m_Mode = pmNothing;
}
    
EFFMPEGPlayerProcessorMode CFrameProcessor::GetMode()
{
    return m_Mode;
}
void CFrameProcessor::SetMode(EFFMPEGPlayerProcessorMode Value)
{
    m_Mode = Value;
}

awpImage* CFrameProcessor::ProcessFrame(awpImage* source)
{
    awpImage* tmp = NULL;
    if (awpCopyImage(source, &tmp) != AWP_OK)
        return NULL;

    switch (m_Mode)
    {
    case pmNothing:
        return tmp;
    case pmFlipLeft:
        awpFlip(&tmp, AWP_FLIP_LEFT);
        break;
    case pmFlipRight:
        awpFlip(&tmp, AWP_FLIP_RGHT);
        break;
    case pmFlipHorizontal:
        awpFlip(&tmp, AWP_FLIP_HRZT);
        break;
    case pmFlipVertical:
        awpFlip(&tmp, AWP_FLIP_VERT);
        break;
    case pmRotate180:
        awpFlip(&tmp, AWP_FLIP_LEFT);
        awpFlip(&tmp, AWP_FLIP_LEFT);
        break;
    case pmRotateMirror90:
        awpFlip(&tmp, AWP_FLIP_LEFT);
        awpFlip(&tmp, AWP_FLIP_VERT);
        break;
    case pmRotateMirror270:
        awpFlip(&tmp, AWP_FLIP_RGHT);
        awpFlip(&tmp, AWP_FLIP_VERT);
        break;
    }
    return tmp;
}

CFrameSize CFrameProcessor::GetProcessedSize(CFrameSize src)
{
    CFrameSize res;
    switch (m_Mode)
    {
    case pmNothing:
    case pmRotate180:
    case pmFlipVertical:
    case pmFlipHorizontal:
        res = src;
        break;
    case pmFlipLeft:
    case pmFlipRight:
    case pmRotateMirror90:
    case pmRotateMirror270:
        res.height = src.width;
        res.width = src.height;
        break;
    }
    return res;
}

CFFMpegEncoder::CFFMpegEncoder(CFFMPEGPlayer* player, EFFMpegEncoderMode mode)
{
    m_pInFormat  = NULL;
    m_pOutFormat = NULL;
    m_pPlayer    = player;
    m_EncodingMode = mode;
    m_InVideoStreamIndex = -1;
    m_pFrame = NULL;
    m_pAFrame = NULL;
    m_pFilteredAFrame = NULL;
    m_pOutBuf = 0;
    m_OutBufSize = 0;
    m_needProcessAudio = false;

    m_InAudioStreamIndex = -1;
    m_OutAudioStreamIndex = -1;
    m_FrameCounter = 0;

    m_last_pkt_pts = AV_NOPTS_VALUE;
    m_last_pkt_dts = AV_NOPTS_VALUE;

    avfilter_register_all();
}

CFFMpegEncoder::~CFFMpegEncoder()
{
    Close();
}

bool CFFMpegEncoder::Init(AVFormatContext* pFormat, const char* lpFileName)
{
    /*проверка входных параметров. 
    */
    if (lpFileName == NULL)
        return false;
    if (pFormat == NULL)
        return false;
    m_pInFormat = pFormat;
    int res = 0;
    res = avformat_alloc_output_context2(&m_pOutFormat, NULL, NULL, lpFileName);
    if (res < 0 || m_pOutFormat == NULL)
        return false;
    /* установим поля для нового контекста.
    */
     m_pOutFormat->bit_rate   = m_pInFormat->bit_rate;
     m_pOutFormat->start_time =0;// m_pInFormat->start_time;
	 m_pOutFormat->duration = m_pInFormat->duration;

     m_mapInout.clear();
     m_mapInout.resize( m_pInFormat->nb_streams );


     for (unsigned int i = 0; i < m_pInFormat->nb_streams; i++)
     {
         AVCodecContext *pCodecCtx = m_pInFormat->streams[i]->codec;
         if (pCodecCtx->codec_type != AVMEDIA_TYPE_VIDEO)
         {
             if (m_pInFormat->streams[i]->codec->codec_id == CODEC_ID_AC3)
             {
                m_mapInout[i] = AddAudioStream(m_pOutFormat, m_pInFormat->streams[i]);
                m_needProcessAudio = true;
             }
             else
                m_mapInout[i] = AddCopyStream(m_pOutFormat, m_pInFormat->streams[i]);
             
             if (m_mapInout[i] < 0)
                 return false;
             this->m_InAudioStreamIndex = m_pInFormat->streams[i]->index;
             this->m_OutAudioStreamIndex = m_mapInout[i];
         }
         else if (pCodecCtx->codec_type == AVMEDIA_TYPE_VIDEO && m_EncodingMode == emVideoProcessing)
         {
             m_mapInout[i] = AddVideoStream(m_pOutFormat, m_pInFormat->streams[i]);
             if (m_mapInout[i] < 0)
                 return false;
             m_InVideoStreamIndex = m_pInFormat->streams[i]->index;
             m_OutVideoStreamIndex = m_mapInout[i];
         }
         else
         {
             m_mapInout[i] = AddCopyStream(m_pOutFormat, m_pInFormat->streams[i]);
             m_InVideoStreamIndex = m_pInFormat->streams[i]->index;
             m_OutVideoStreamIndex = m_mapInout[i];
             if (m_mapInout[i] < 0)
                 return false;
             m_InVideoStreamIndex = m_pInFormat->streams[i]->index;
             m_OutVideoStreamIndex = m_mapInout[i];
         }
     }
     /* todo: copy metadata to the new context
     */
     //av_metadata_copy(&m_pOutFormat->metadata, m_pInFormat->metadata, 0);
     if (!(m_pOutFormat->oformat->flags & AVFMT_NOFILE)) 
     {
        /* test if it already exists to avoid loosing precious files */
        /* open the file */
        if ((res = avio_open(&m_pOutFormat->pb, lpFileName, AVIO_FLAG_WRITE)) < 0) 
            return false;
     }
     /* open file and save header 
     */
     res = avformat_write_header(m_pOutFormat, NULL);
#ifdef _DEBUG
     av_dump_format (m_pOutFormat, 0, m_pOutFormat->filename, 1);
#endif
     m_FrameCounter = 0;
     return res == 0;
}
bool CFFMpegEncoder::Close()
{
	if (m_pOutFormat == NULL) 
        return false;

    /* close all open streams 
    */
	for( unsigned int i=0;i<m_pOutFormat->nb_streams;i++ )
	{
		if (m_mapInout[i] >= 0)
		{
			AVStream *pStream = m_pOutFormat->streams[i];
            if (pStream != NULL)
            {
                AVCodecContext *avctx = NULL;
                avctx = pStream->codec;
                if (avctx->codec != NULL)
                {
                    av_freep(&pStream->codec->extradata);
                    avcodec_close(avctx);
                }
            }
		}
	}

    m_needProcessAudio = false;
CLEANUP:
    if (m_pOutBuf)
        av_free(m_pOutBuf);
    //if (m_pFrame->data[0])
    //    av_free(m_pFrame->data[0]);
    if (m_pFrame)
        av_free(m_pFrame);
	if (m_pOutFormat->pb != NULL)
    avio_close(m_pOutFormat->pb);
    av_free(m_pOutFormat);
    m_pOutFormat = NULL;
    true;
}

bool CFFMpegEncoder::SavePacket(AVPacket* pPkt)
{
    if (pPkt == NULL)
        return false;
    if (m_EncodingMode == emVideoProcessing && pPkt->stream_index == m_InVideoStreamIndex)  
    {
        //if (!ConvertPaket(pPkt))
        //  return false;
        return ConvertPacket(pPkt);
    }
    if (pPkt->stream_index == this->m_InAudioStreamIndex && this->m_needProcessAudio)
    {
       return ConvertAudio(pPkt);
    }

    if (!PreparePacketTime(pPkt))
        return false;
    return WritePaket(pPkt);
}

int CFFMpegEncoder::DecodeAudio(AVPacket* pkt, bool& got_output)
{
    
    AVFrame *decoded_frame;
    int frame_finished;
    AVCodecContext *avctx = m_pInFormat->streams[m_InAudioStreamIndex]->codec;
    int ret;

    if (!m_pAFrame && !(m_pAFrame = avcodec_alloc_frame()))
        return AVERROR(ENOMEM);
    else
        avcodec_get_frame_defaults(m_pAFrame);

    decoded_frame = m_pAFrame;
    ret = avcodec_decode_audio4(avctx, decoded_frame, &frame_finished, pkt);
    if (ret < 0) 
        return ret;
    if (!frame_finished)
    {
        got_output = false;
        return ret;
    }
    if (decoded_frame->pts == AV_NOPTS_VALUE)
        decoded_frame->pts = pkt->pts;//av_rescale_q(pkt->dts, AV_TIME_BASE_Q, m_pInFormat->streams[m_InAudioStreamIndex]->time_base);
    got_output = true;


   ret =  av_buffersrc_add_frame(m_buffersrc_ctx, decoded_frame, 0);

    return ret;
}


bool CFFMpegEncoder::ConvertAudio(AVPacket* pPkt)
{
    AVPacket avpkt = *pPkt;
    bool got_output = false;
    int ret = 0;
    while (avpkt.size > 0)
    {
        ret = DecodeAudio(&avpkt, got_output);
        if (ret < 0)
            return false;

        avpkt.dts=
        avpkt.pts= AV_NOPTS_VALUE;

        avpkt.data += ret;
        avpkt.size -= ret;
    }
    return   DoAudioOut();
}

bool CFFMpegEncoder::DoAudioOut()
{
    AVCodecContext *enc = m_pOutFormat->streams[m_OutAudioStreamIndex]->codec;
    AVFilterBufferRef *picref = NULL;
    AVFrame *filtered_frame = NULL;
    AVPacket pkt;
    int got_packet = 0;

    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    if (!m_pFilteredAFrame && !(m_pFilteredAFrame = avcodec_alloc_frame())) {
        return AVERROR(ENOMEM);
    } else
        avcodec_get_frame_defaults(m_pFilteredAFrame);
    filtered_frame = m_pFilteredAFrame;

    int ret = av_buffersink_read_samples(m_buffersink_ctx, &picref, enc->frame_size);
    if (ret < 0)
        return false;
     
    avfilter_copy_buf_props(filtered_frame, picref);

    bool res = false;
    if (avcodec_encode_audio2(enc, &pkt, filtered_frame, &got_packet) < 0) {
        av_log(NULL, AV_LOG_FATAL, "Audio encoding failed (avcodec_encode_audio2)\n");
        return false;
    }
    if (got_packet) {
        if (pkt.pts != AV_NOPTS_VALUE)
            pkt.pts      = av_rescale_q(pkt.pts,      enc->time_base, m_pOutFormat->streams[m_OutAudioStreamIndex]->time_base);
        if (pkt.dts != AV_NOPTS_VALUE)
            pkt.dts      = av_rescale_q(pkt.dts,      enc->time_base, m_pOutFormat->streams[m_OutAudioStreamIndex]->time_base);
        if (pkt.duration > 0)
            pkt.duration = av_rescale_q(pkt.duration, enc->time_base, m_pOutFormat->streams[m_OutAudioStreamIndex]->time_base);

        res = WritePaket(&pkt);
        av_free_packet(&pkt);
    }
    return res;
}


bool CFFMpegEncoder::WritePaket(AVPacket* pPkt)
{
    if (m_last_pkt_pts == AV_NOPTS_VALUE || m_last_pkt_dts == AV_NOPTS_VALUE)
    {
        int res = av_interleaved_write_frame(m_pOutFormat, pPkt);
        if (res < 0)
           return false;
    }
    else if (m_last_pkt_pts < pPkt->pts && m_last_pkt_dts < pPkt->dts)
    {
        int res = av_interleaved_write_frame(m_pOutFormat, pPkt);
        if (res < 0)
           return false;
    }
    else
    {
        av_log(NULL, AV_LOG_FATAL, "Skip packet.\n");
    }
    
    m_last_pkt_pts = pPkt->pts;
    m_last_pkt_dts = pPkt->dts;

    return true;
}

bool CFFMpegEncoder::PreparePacketTime(AVPacket* pPkt)
{
    if (pPkt == NULL)
        return false;
    if (m_mapInout[pPkt->stream_index] < 0)
        return false;
    /* входной и выходной поток для пакета pPkt
    */
    AVStream* pInStream    = m_pInFormat->streams[pPkt->stream_index];
    pPkt->stream_index     = m_mapInout[pPkt->stream_index];
    AVStream* pOutStream   = m_pOutFormat->streams[pPkt->stream_index];
    /* начало записи. > 0 означает, что ведется запись выделенного 
       фрагмента,  а не всего ролика
    */
    int64_t save_start     = m_pPlayer->GetSaveStartTime();
    AVRational r;r.den = AV_TIME_BASE;r.num =1;
    /* время начала ролика, берем из потока. 
    */
    save_start = av_rescale_q(save_start, pInStream->time_base,  r);
    uint64_t stream_start = pInStream->start_time;
    stream_start = av_rescale_q(stream_start, pInStream->time_base,  r);
    /* текущее глобальное и локальное время
    */
    int64_t ct, lt, ctd, ltd;
    double pts = 0;
    double dts = 0;
   if (pPkt->pts != AV_NOPTS_VALUE)
   {
        pts = (double)pPkt->pts;
   }
   else if (pPkt->dts != AV_NOPTS_VALUE)
   {
        pts = (double)pPkt->dts;
   }
    else
        return false;
    pts *= av_q2d(pOutStream->time_base);
    ct = (int64_t)(pts*AV_TIME_BASE) - stream_start;
    lt = m_pPlayer->GetTimeLine()->GlobalToLocalTime(ct) - save_start;
	if (pPkt->dts != AV_NOPTS_VALUE)
	{
		dts = (double)pPkt->dts;
		dts *= av_q2d(pOutStream->time_base);
		ctd = (int64_t)(dts*AV_TIME_BASE) - stream_start;
		ltd = m_pPlayer->GetTimeLine()->GlobalToLocalTime(ctd) - save_start;
	}
    /*установки индекса потока для пакета
    */
    
    /*~~~~~~~~~~установка времени~~~~~~~~~~~~~~~~~~~~
       длительность пакета
    */
    pPkt->duration = (int)av_rescale_q(pPkt->duration, pInStream->time_base, pOutStream->time_base);
    /* время представления пакета 
    */    
    if (pPkt->pts != AV_NOPTS_VALUE)
    {
        pPkt->pts = av_rescale_q(lt, r, pOutStream->time_base);
    }
	if (pPkt->dts != AV_NOPTS_VALUE)
	{
        pPkt->dts = av_rescale_q(ltd, r, pOutStream->time_base);
	} 
	//pPkt->dts = AV_NOPTS_VALUE;
    return true;
}

/*
*/
int CFFMpegEncoder::AddCopyStream(AVFormatContext* pOutFormat, AVStream* pInStream )
{
    AVStream *pOutStream = NULL;
	int copy_tb = -1;
    pOutStream = avformat_new_stream(pOutFormat, pInStream->codec->codec);
    if (pOutStream == NULL)
    {
        return -1;
    }
    avcodec_get_context_defaults3(pOutStream->codec, pInStream->codec->codec);

	/*настройка кодеков*/
	 AVCodecContext *codec, *icodec;
	 codec = pOutStream->codec;
	 icodec = pInStream->codec; 


	    if((strcmp(pOutFormat->oformat->name, "mp4") == 0) || 
		   (strcmp(pOutFormat->oformat->name, "mov") == 0) ||
		   (strcmp(pOutFormat->oformat->name, "3gp") == 0)) 
		{
			pOutStream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
			codec->frame_size = 1;
		}


	uint64_t extra_size = (uint64_t)icodec->extradata_size + FF_INPUT_BUFFER_PADDING_SIZE;

	if (extra_size > INT_MAX)
		return -1;
	
	codec->codec_id   = icodec->codec_id;
	codec->codec_type = icodec->codec_type;
	
	if(!codec->codec_tag){
		if(   !pOutFormat->oformat->codec_tag
			|| av_codec_get_id (pOutFormat->oformat->codec_tag, pInStream->codec->codec_tag) == codec->codec_id
			|| av_codec_get_tag(pOutFormat->oformat->codec_tag, icodec->codec_id) <= 0)
			codec->codec_tag = icodec->codec_tag;
	}

	codec->bit_rate =  icodec->bit_rate;
	codec->rc_max_rate    =  icodec->rc_max_rate;
	codec->rc_buffer_size =  icodec->rc_buffer_size;
	codec->field_order = icodec->field_order;
	codec->extradata= (uint8_t *) av_mallocz(extra_size);
	if (!codec->extradata)
		return -1;
    if (icodec->extradata_size > 0)
	    memcpy(codec->extradata,  icodec->extradata,  icodec->extradata_size);
	codec->extradata_size= icodec->extradata_size;
	codec->bits_per_coded_sample = icodec->bits_per_coded_sample;

    codec->time_base = icodec->time_base;
	pOutStream->r_frame_rate = pInStream->r_frame_rate;
    pOutStream->start_time = 0;//pInStream->start_time;
	if(!strcmp(pOutFormat->oformat->name, "avi")) 
	{
        if ( copy_tb <0 && av_q2d(icodec->time_base)*icodec->ticks_per_frame > 2*av_q2d(pInStream->time_base)
                            && av_q2d(pInStream->time_base) < 1.0/500)
            {
            codec->time_base = icodec->time_base;
            codec->time_base.num *= icodec->ticks_per_frame;
            codec->time_base.den *= 2;
            codec->ticks_per_frame = 2;
        }
    } 
	else if(!(pOutFormat->oformat->flags & AVFMT_VARIABLE_FPS)
                && strcmp(pOutFormat->oformat->name, "mov") && strcmp(pOutFormat->oformat->name, "mp4") && strcmp(pOutFormat->oformat->name, "3gp")
                && strcmp(pOutFormat->oformat->name, "3g2") && strcmp(pOutFormat->oformat->name, "psp") && strcmp(pOutFormat->oformat->name, "ipod")
    ) {
        if(   av_q2d(icodec->time_base)*icodec->ticks_per_frame > av_q2d(pInStream->time_base)
                        && av_q2d(pInStream->time_base) < 1.0/500)
		{
            codec->time_base = icodec->time_base;
            codec->time_base.num *= icodec->ticks_per_frame;
        }
    }


    av_reduce(&codec->time_base.num, &codec->time_base.den,
                codec->time_base.num, codec->time_base.den, INT_MAX);


    pOutStream->avg_frame_rate = pInStream->avg_frame_rate;
    pOutStream->disposition = pInStream->disposition;
	pOutStream->codec->bits_per_raw_sample= pInStream->codec->bits_per_raw_sample;
	pOutStream->codec->chroma_sample_location = pInStream->codec->chroma_sample_location;


	switch(codec->codec_type)
	{
	case AVMEDIA_TYPE_AUDIO:

        codec->channel_layout =  icodec->channel_layout;
		codec->sample_rate =  icodec->sample_rate;
		codec->channels =  icodec->channels;
		codec->frame_size =  icodec->frame_size;
		codec->audio_service_type =  icodec->audio_service_type;
		codec->block_align=  icodec->block_align;
		break;

	case AVMEDIA_TYPE_VIDEO:

		codec->pix_fmt =  pInStream->codec->pix_fmt;
		codec->width =  pInStream->codec->width;
		codec->height =  pInStream->codec->height;
		codec->has_b_frames =  pInStream->codec->has_b_frames;
		if (!codec->sample_aspect_ratio.num)
		{
			AVRational defaultAspect = {0,1};
			codec->sample_aspect_ratio =
				pOutStream->sample_aspect_ratio =
				pInStream->sample_aspect_ratio.num ? pInStream->sample_aspect_ratio :
				pInStream->codec->sample_aspect_ratio.num ?
				pInStream->codec->sample_aspect_ratio : defaultAspect;
		}
		pOutStream->avg_frame_rate = pInStream->avg_frame_rate;

		break;
	case AVMEDIA_TYPE_SUBTITLE:
		pOutStream->codec->width = pInStream->codec->width;
		pOutStream->codec->height = pInStream->codec->height;
		break;
	case AVMEDIA_TYPE_DATA:
		break;
	}
	pOutStream->id = pInStream->id;
	pOutStream->pts_wrap_bits = pInStream->pts_wrap_bits;
	pOutStream->need_parsing = pInStream->need_parsing;
	pOutStream->codec_info_nb_frames = pInStream->codec_info_nb_frames;
	return pOutStream->index;
}

int CFFMpegEncoder::AddVideoStream(AVFormatContext* pOutFormat, AVStream* pInStream)
{
    AVStream *pOutStream = NULL;
    AVCodecContext *c, *ic;
    AVCodec *codec;
    pOutStream = avformat_new_stream(pOutFormat, pInStream->codec->codec);
    if (pOutStream == NULL)
    {
        av_log(NULL, AV_LOG_FATAL, "Could not alloc stream.\n");
        return -1;
    }

    pOutStream->codec->codec_type = AVMEDIA_TYPE_VIDEO;
    pOutStream->disposition = pInStream->disposition;


    codec = avcodec_find_encoder(pInStream->codec->codec_id);
    avcodec_get_context_defaults3(pOutStream->codec, codec);

    c  =  pOutStream->codec;
    ic =  pInStream->codec;

    c->time_base = ic->time_base;
    c->pix_fmt   = PIX_FMT_YUV420P;
    if (m_pPlayer->GetFrameProcessor()->GetMode() != pmNothing)
    {
        CFrameSize fsizesrc;
        fsizesrc.width = ic->width;
        fsizesrc.height = ic->height;
        CFrameSize fsize = m_pPlayer->GetFrameProcessor()->GetProcessedSize(fsizesrc);
        c->width = fsize.width;
        c->height = fsize.height;
    }
    else
    {
        c->width    = ic->width;
        c->height   = ic->height;
    }
    // c->bit_rate = 10*c->width*c->height;
    //AVRational defaultAspect = {0,1};
    //c->sample_aspect_ratio = pOutStream->sample_aspect_ratio = pInStream->sample_aspect_ratio.num ? pInStream->sample_aspect_ratio :
    //    pInStream->codec->sample_aspect_ratio.num ? pInStream->codec->sample_aspect_ratio : defaultAspect;
    //pOutStream->avg_frame_rate = pInStream->avg_frame_rate;


    if (pOutFormat->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    if (avcodec_open(c, codec) < 0)
        return -1;

    m_pFrame = alloc_picture(c->pix_fmt, c->width, c->height);
    if (m_pFrame == NULL)
        return -1;

    m_OutBufSize = c->width*c->height*10;
    m_pOutBuf = (uint8_t*)av_malloc(m_OutBufSize);

    return pOutStream->index;
}
/* создает новый аудио-поток
*/
int CFFMpegEncoder::AddAudioStream(AVFormatContext* pOutFormat, AVStream* pInStream)
{
    if (pOutFormat == NULL || pInStream == NULL)
        return -1;
    /* перекодировка аудио осуществляется только для случая CODEC_ID_AC3
       перекодирование ведется в формат CODEC_ID_MP2
    */
    if (pInStream->codec != NULL && pInStream->codec->codec_id != CODEC_ID_AC3)
        return -1;

    AVStream *pOutStream = NULL;
    AVCodecContext *c, *ic;
    AVCodec *codec;

    pOutStream = avformat_new_stream(pOutFormat, NULL);
    if (pOutStream == NULL)
    {
        av_log(NULL, AV_LOG_FATAL, "Could not alloc stream.\n");
        return -1;
    }

    pOutStream->id = pInStream->id;
    pOutStream->codec->codec_type = AVMEDIA_TYPE_AUDIO;
    codec = avcodec_find_encoder(CODEC_ID_MP2);

    int ret = avcodec_get_context_defaults3(pOutStream->codec, codec);


    c  =  pOutStream->codec;
    ic =  pInStream->codec;
        
    c->time_base = ic->time_base;
    c->channels = ic->channels;
    c->sample_fmt = ic->sample_fmt;
    c->sample_rate = ic->sample_rate;

    if (avcodec_open(c, codec) < 0)
        return -1;

    // 
    if (this->InitFilters())
        return -1;
    return pOutStream->index;
}


int CFFMpegEncoder::InitFilters()
{
    
    char args[512];//memset(args, 0, sizeof(args));
    int ret; 
    AVFilter *abuffersrc  = avfilter_get_by_name("abuffer");
    AVFilter *abuffersink = avfilter_get_by_name("abuffersink_old");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs  = avfilter_inout_alloc();
    const enum AVSampleFormat sample_fmts[] = { AV_SAMPLE_FMT_S16 };
    const  int64_t chlayouts[4]                = {AV_CH_LAYOUT_STEREO, -1};
    AVABufferSinkParams *abuffersink_params;
    const AVFilterLink *outlink;
    AVRational time_base = m_pInFormat->streams[1]->time_base;

    m_filter_graph = avfilter_graph_alloc();

    /* buffer audio source: the decoded frames from the decoder will be inserted here. */
    if (!m_pInFormat->streams[1]->codec->channel_layout)
        m_pInFormat->streams[1]->codec->channel_layout = av_get_default_channel_layout(m_pInFormat->streams[1]->codec->channels);

    sprintf(args,
            "time_base=%d/%d:sample_rate=%d:sample_fmt=%s:channel_layout=%d",
             time_base.num, time_base.den, m_pInFormat->streams[1]->codec->sample_rate,
             av_get_sample_fmt_name(m_pInFormat->streams[1]->codec->sample_fmt), m_pInFormat->streams[1]->codec->channel_layout);

    ret = avfilter_graph_create_filter(&m_buffersrc_ctx, abuffersrc, "in",
                                       args, NULL, m_filter_graph);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer source\n");
        return ret;
    }

    /* buffer audio sink: to terminate the filter chain. */
    abuffersink_params = av_abuffersink_params_alloc();
    abuffersink_params->sample_fmts     = sample_fmts;
    abuffersink_params->channel_layouts = &chlayouts[0];
    ret = avfilter_graph_create_filter(&m_buffersink_ctx, abuffersink, "out",
                                       NULL, abuffersink_params, m_filter_graph);
    av_free(abuffersink_params);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Cannot create audio buffer sink\n");
        return ret;
    }

    /* Endpoints for the filter graph. */
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = m_buffersrc_ctx;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    inputs->name       = av_strdup("out");
    inputs->filter_ctx = m_buffersink_ctx;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    if ((ret = avfilter_graph_parse(m_filter_graph, "anull",
                                   &inputs, &outputs, NULL)) < 0)
        return ret;

    if ((ret = avfilter_graph_config(m_filter_graph, NULL)) < 0)
        return ret;

    /* Print summary of the sink buffer
     * Note: args buffer is reused to store channel layout string */
    outlink = m_buffersink_ctx->inputs[0];
    av_get_channel_layout_string(args, sizeof(args), -1, outlink->channel_layout);

    av_log(NULL, AV_LOG_INFO, "Output: srate:%dHz fmt:%s chlayout:%s\n",
    (int)outlink->sample_rate,
    (char *)av_x_if_null(av_get_sample_fmt_name((AVSampleFormat)outlink->format), "?"),
    args);

    return 0;    
}

AVFrame* CFFMpegEncoder::PorcessFrame ()
{
    awpImage* src = NULL;
    // save picture as jpeg 
	if (!AVFrame2AwpRGBImage(m_pFrame, &src))
		return false;
	awpImage* dst = m_pPlayer->GetFrameProcessor()->ProcessFrame(src);
	if (dst == NULL)
	{
		awpReleaseImage(&src);
		return false;
	}
#ifdef _DEBUG
    char buf[32];
    sprintf(buf, "%i.jpg",this->m_FrameCounter); 
    //awpSaveImage(buf, dst);
#endif 

    AVFrame* the_picture = NULL;

	if (!AwpRGBImage2AVFrame(dst, &the_picture))
		return NULL;

    awpReleaseImage(&dst);
    awpReleaseImage(&src);

    return the_picture;
}


bool CFFMpegEncoder::ConvertPacket(AVPacket* pPkt)
{
    AVStream* vsti = m_pInFormat->streams[m_InVideoStreamIndex];
    AVCodecContext *c = m_pOutFormat->streams[m_OutVideoStreamIndex]->codec;
    int frameFinished = 0;
    AVPacket avpkt = *pPkt;

    while (frameFinished == 0)
	{
		int len1 = avcodec_decode_video2(vsti->codec, m_pFrame, &frameFinished, &avpkt);
		if (len1 < 0)
        {
		    av_log(NULL, AV_LOG_FATAL, "Video decoding failed\n");
            return false;
        }
        if (frameFinished == 0)
        {
		    av_log(NULL, AV_LOG_WARNING , "No picture yet.\n");
            avpkt.size -= len1;
			avpkt.data += len1;
        }
    }
    av_log(NULL, AV_LOG_WARNING, "New frame.\n");
    this->m_FrameCounter++;

    /* m_pFrame contains true frame process it if we need 
    */
    AVFrame* out_picture = this->PorcessFrame();
    if (out_picture == NULL)
        return false;
    int got_packet  =0;
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    int ret = 0;
    out_picture->pts = m_pFrame->best_effort_timestamp;
    out_picture->pict_type =  m_pFrame->pict_type;
    out_picture->format = m_pFrame->format;
    ret = avcodec_encode_video2(c,  &pkt, out_picture, &got_packet);
    if (ret < 0)
    {
        av_log(NULL, AV_LOG_WARNING, "Video encoding failed\n");
        free_frame(out_picture);
        return false;
    }

    if (got_packet)
    {
         av_log(NULL, AV_LOG_FATAL, "Save video paket.\n");         
         pkt.stream_index = m_OutVideoStreamIndex;
         pkt.duration = pPkt->duration;
         ret = av_interleaved_write_frame(m_pOutFormat, &pkt);
         if (ret < 0)
         {
            av_log(NULL, AV_LOG_WARNING, "Video write failed\n");
         }
         av_free_packet(&pkt);
    }

    free_frame(out_picture);
    return ret >=0 ;
}

bool CFFMpegEncoder::CompleteTranscode()
{
	if (m_pOutFormat == NULL) 
        return false;
    int ret = 0;
    /* write the trailer if needed and close file */
	ret = av_write_trailer(m_pOutFormat);
	return ret == 0;
}

CAudioSegment::CAudioSegment()
{
	m_numChannels = 0;
	memset(m_data, 0, sizeof(m_data));
	m_startTime = 0;
	m_duration = 0;
	m_visible = false;
	m_selected = false;
}
CAudioSegment::CAudioSegment(const CAudioSegment& segment)
{
	m_numChannels = segment.m_numChannels;
	memcpy(m_data, segment.m_data, sizeof(m_data));
	m_startTime = segment.m_startTime;
	m_duration = segment.m_duration;
	m_visible = segment.m_visible;
	m_selected = segment.m_selected;
}
CAudioSegment::CAudioSegment(int NumChannels, uint64_t startTime, uint64_t duration, bool visible, bool selected, SAudioData* data)
{
	m_numChannels = NumChannels;
	memcpy(m_data, data, m_numChannels*sizeof(SAudioData));
	m_startTime = startTime;
	m_duration = duration;
	m_visible = visible;
	m_selected = selected;
}
const bool CAudioSegment::IsSelected()
{
	return m_selected;
}
const bool CAudioSegment::IsVisible()
{
	return m_visible;
}
const uint64_t CAudioSegment::Duration()
{
	return m_duration;
}
const uint64_t CAudioSegment::StartTime()
{
	return m_startTime;
}
const int CAudioSegment::NumChannels()
{
	return m_numChannels;
}
const SAudioData* CAudioSegment::AudioData()
{
	return m_data;
}
void CAudioSegment::SetVisible(bool value)
{
	m_visible = value;
}
void CAudioSegment::SetSelected(bool value)
{
	m_selected = value;
}

CSafeBool::CSafeBool()
{
	m_Value = false;
	m_mutex = SDL_CreateMutex();
}

CSafeBool::~CSafeBool()
{
	SDL_DestroyMutex(m_mutex);
}

void CSafeBool::SetValue(bool Value)
{
	if (m_Value == Value)
		return;
	SDL_LockMutex(m_mutex);
	m_Value = Value;
	SDL_UnlockMutex(m_mutex);
}
bool CSafeBool::GetValue()
{
	return m_Value;
}

CVideoPicture::CVideoPicture()
{
	m_pImage = NULL;
	m_Picture.data[0] = NULL;
}
CVideoPicture::~CVideoPicture()
{
	if (m_pImage != NULL)
		awpReleaseImage(&m_pImage);
	if (m_Picture.data[0] != NULL)
		free(m_Picture.data[0]);
}

awpImage* CVideoPicture::SetAVFrame(AVFrame* pFrame)
{
	if (pFrame == NULL)
		return NULL;
	if (m_pImage == NULL)
	{
		awpCreateImage(&m_pImage, pFrame->width, pFrame->height, 3, AWP_BYTE);
		m_Picture.linesize[0] = 3*pFrame->width;
	    m_Picture.data[0] = (uint8_t*)malloc(m_Picture.linesize[0]*pFrame->height);
	}
	else if (m_pImage->sSizeX != pFrame->width || m_pImage->sSizeY != pFrame->height)
	{
		awpReleaseImage(&m_pImage);
		if (m_Picture.data[0] != NULL)
			free(m_Picture.data[0]);

		awpCreateImage(&m_pImage, pFrame->width, pFrame->height, 3, AWP_BYTE);
		m_Picture.linesize[0] = 3*pFrame->width;
	    m_Picture.data[0] = (uint8_t*)malloc(m_Picture.linesize[0]*pFrame->height);
	}
	//else
	{
		SwsContext* context = NULL;  

		context = sws_getContext(pFrame->width, pFrame->height, (PixelFormat)pFrame->format, 
			pFrame->width, pFrame->height, PIX_FMT_BGR24, 1, NULL, NULL, NULL);
    
		if (context == NULL)
			goto cleanup;

		int h = sws_scale(context, pFrame->data, pFrame->linesize, 0, pFrame->height, m_Picture.data, m_Picture.linesize);
		if (h != pFrame->height)
			goto cleanup;

		sws_freeContext(context);

		AWPBYTE* b = (AWPBYTE*)m_pImage->pPixels;
		memcpy(b, m_Picture.data[0], m_Picture.linesize[0]*pFrame->height);

	}
cleanup:
	return m_pImage;
}

awpImage* CVideoPicture::GetImage()
{
	return m_pImage;
}


CFFMpegTranscoder::CFFMpegTranscoder()
{
	memset(&this->m_InputFile, 0, sizeof(this->m_InputFile));
	memset(&this->m_OutputFile, 0, sizeof(this->m_OutputFile));
	memset(&this->m_Options, 0, sizeof(this->m_Options));

	input_streams = NULL;
	nb_input_streams = 0;

}

CFFMpegTranscoder::~CFFMpegTranscoder()
{
	close_transcoder();
}

int CFFMpegTranscoder::Init(STranscoderOptions* pOptions)
{
	close_transcoder();

	if (pOptions == NULL)
		return FFMPEG_TRANCODER_CANNOTOPEN_FILE;
	memcpy(&this->m_Options, pOptions, sizeof(this->m_Options));

	if (!this->open_input_file())
		return FFMPEG_TRANCODER_CANNOTOPEN_FILE;

	return 0;
}

int CFFMpegTranscoder::Transcode()
{
	return 0;
}
void CFFMpegTranscoder::Cancel()
{

}

bool CFFMpegTranscoder::open_input_file()
{
	AVFormatContext* ic = NULL; 
	AVInputFormat*   file_format = NULL;

	ic = avformat_alloc_context();
	if (!ic)
		return false; 
	int err = avformat_open_input(&ic, m_Options.m_pInputFileName, NULL, NULL);
	if (err < 0)
		return false;
	if (!this->add_input_streams(ic))
		return false;
	
	m_InputFile.m_ctx = ic;
	m_InputFile.m_eof_reached = false;

	return true;

}

void CFFMpegTranscoder::close_transcoder()
{

}

bool CFFMpegTranscoder::add_input_streams(AVFormatContext* ic)
{
    int i;
    char *next, *codec_tag = NULL;

	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVStream* st = ic->streams[i];
		AVCodecContext* dec = st->codec;

		InputStream* ist = (InputStream*)av_mallocz(sizeof(*ist));
		if (ist == NULL)
			goto error;
		
		InputStream** tmpptr = NULL;

		tmpptr = (InputStream**)grow_array(input_streams, sizeof(*input_streams), &nb_input_streams, nb_input_streams + 1);
		if (tmpptr == NULL)
			goto error;

		input_streams = tmpptr;
		input_streams[nb_input_streams - 1] = ist;
		 
		ist->st = st;
		ist->discard = 1;
		st->discard = AVDISCARD_ALL;
		ist->ts_scale = 1.0;

		ist->dec = avcodec_find_decoder(st->codec->codec_id);
		switch(dec->codec_type)
		{
		case AVMEDIA_TYPE_VIDEO:
			break;
		case AVMEDIA_TYPE_AUDIO:
			break;
		case AVMEDIA_TYPE_DATA:
		case AVMEDIA_TYPE_SUBTITLE:
			break;
		}

	}
	return true;
error:
	/*clean input_streams
	*/

	return false;
}
