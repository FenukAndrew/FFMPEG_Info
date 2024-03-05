CXX      = g++
CXXFLAGS = -std=c++14 -pthread
INCPATH  = -I. -I../ffmpeg
LIBS     = -pthread -L../ffmpeg/libs/ -lavdevice -lavformat -lavfilter -lavcodec -lswresample -lswscale -lavutil -lz -llzma -ldrm

all: FFMPEG_Info

FFMPEG_Info: main.o
	$(CXX) main.o cnt_formatcontext.o -o FFMPEG_Info $(LIBS)

main.o: 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) main.cpp cnt_formatcontext.cpp



clean:
	rm *.o FFMPEG_Info

