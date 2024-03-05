/*
g++ -c -std=c++14 -pthread -I. -I../ffmpeg main.cpp
g++ -c -std=c++14 -pthread -I. -I../ffmpeg cnt_formatcontext.cpp
g++ -o FFMPEG_Info main.o cnt_formatcontext.o -pthread -L../ffmpeg/libs/ -lavdevice -lavformat -lavfilter -lavcodec -lswresample -lswscale -lavutil -lz -llzma -ldrm

    //pkg-config --cflags --libs libavutil
    //g++ -I/opt/ffmpeg/include -L/opt/ffmpeg/lib -lavcodec -lavfilter -lavresample -lpostproc -lswscale -lavdevice -lavformat -lavutil -lswresample
*/

#include <iostream>
#include <exception>
#include "cnt_formatcontext.h"

using namespace std;

int main(int argvc, const char** argv)
{
    if(argvc<2)
    {
        std::cerr << "need to specify a media file" << endl;
        return 0;
    }
    for(uint8_t i=1; i<argvc; i++)
    {
        const char* file_name(argv[i]);

        try
        {
            CNT_FormatContext cnt_formatcontext(file_name);
            cnt_formatcontext.show_info();
            cnt_formatcontext.show_streams();

        } catch(const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }

    }
}

