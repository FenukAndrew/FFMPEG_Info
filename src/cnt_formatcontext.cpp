#include <iostream>
#include <sstream>
#include <exception>
#include "cnt_formatcontext.h"

void throw_ffmpeg(const int errnum, const char* errstr)
{
    const size_t errbuf_size=2048;
    char errbuf[errbuf_size];
    av_strerror(errnum, errbuf, errbuf_size);

    std::ostringstream ss;
    ss << errstr << "\t ErrNum: " << errnum << " : " << errbuf;

    throw std::runtime_error(ss.str());
}

CNT_FormatContext::CNT_FormatContext(const char* file_name)
{
    //av_register_all();
    //avcodec_register_all();

    //std::cout << avformat_version() << std::endl;

    std::cout << std::endl << "File: " << file_name << std::endl;

    if(!(pFormatContext=avformat_alloc_context()))
    {
        //throw std::bad_alloc();
        throw std::runtime_error("could not allocate memory for Format Context");
    };

    int errnum=avformat_open_input(&pFormatContext, file_name, NULL, NULL);
    if(errnum!=0) throw_ffmpeg(errnum, "could not open the file");

    errnum=avformat_find_stream_info(pFormatContext,NULL);
    if(errnum<0) throw_ffmpeg(errnum, "could not get the stream info");
}

CNT_FormatContext::~CNT_FormatContext()
{
    avformat_close_input(&pFormatContext);
}

void CNT_FormatContext::show_info()
{
    std::cout << "Format fullname: "<< pFormatContext->iformat->long_name << std::endl;
    std::cout << "Format: " << pFormatContext->iformat->name << std::endl;
    std::cout << "Duration: " << ((double)pFormatContext->duration)/1000000 << std::endl;
    //std::cout << "Bit_rate bits/seconds: " << pFormatContext->bit_rate << std::endl;
}

void CNT_FormatContext::show_streams()
{
    int count_streams=pFormatContext->nb_streams;
    std::cout << "Count streams: " << count_streams << std::endl;
    for(int i=0;i<count_streams;i++)
    {
        AVStream* curStream=pFormatContext->streams[i];
        std::cout << "\tStream number: " << i << " - ";
            //std::cout << "\tDuration: " << ((double)curStream->duration) << std::endl;// /1000000
            //std::cout << "\tStart time: " << ((double)curStream->start_time)/1000000 << std::endl;
            //std::cout << "\tTime base: " << curStream->time_base.den << "/" << curStream->time_base.num << std::endl;
            //std::cout << "\tFrame rate: " << curStream->r_frame_rate.den << "/" << curStream->r_frame_rate.num << std::endl;

        AVCodecParameters* pCodecParams=curStream->codecpar;
        if(pCodecParams==NULL)
        {
            std::cerr << "\tNo params" << std::endl;
            continue;
        }

        AVMediaType media_type=pCodecParams->codec_type;
        const char* media_type_string=av_get_media_type_string(media_type);
        std::cout << ((media_type_string) ? media_type_string : "") << std::endl;
        //const char* ss=NULL;
        //std::cout << "NULL: " << ss << std::endl;
        std::cout << "\tFrames: " << curStream->nb_frames << std::endl;
        std::cout << "\tBit_rate: " << pCodecParams->bit_rate << std::endl;
        if(media_type==AVMEDIA_TYPE_VIDEO)
        {
            //AVRational rate=pCodecParams->framerate;
            std::cout << "\tResolution: " << pCodecParams->width << "x" << pCodecParams->height << std::endl; // " Rate: " << rate.num << "/" << rate.den <<

        } else if(media_type==AVMEDIA_TYPE_AUDIO) {
            std::cout << "\tChannel: " << pCodecParams->ch_layout.nb_channels << " Rate: " << pCodecParams->sample_rate << std::endl;
        }

        AVCodecID codec_id=pCodecParams->codec_id;
        const AVCodec* pCodec=avcodec_find_decoder(codec_id);
        if(pCodec==NULL)
        {
            std::cerr << "\tCodec Id=" << codec_id << " unsupport";
            continue;
        } else {
            std::cout << "\tCodec_id: " << codec_id << std::endl;
            std::cout << "\tCodec: [" << pCodec->name << "] " << pCodec->long_name << std::endl;
        }

        std::cout << std::endl;
    }
}
