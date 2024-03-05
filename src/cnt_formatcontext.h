#ifndef CNT_FORMATCONTEXT
#define CNT_FORMATCONTEXT

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

class CNT_FormatContext
{
public:
    CNT_FormatContext(const char* file_name);
    ~CNT_FormatContext();

    void show_info();
    void show_streams();

private:
    AVFormatContext* pFormatContext;
};

#endif
