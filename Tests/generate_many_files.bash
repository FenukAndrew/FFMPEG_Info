#!/bin/bash
rm -f used_audio_codec.txt
rm -f test_audio_*.avi
awk '{print $2F}' audio.txt > audio_name.txt
file="audio_name.txt"
for var in $(cat $file)
do
echo ""
echo "ffmpeg -c:a $var test_audio_$var.avi"
$(ffmpeg -hide_banner -f lavfi -i "sine=frequency=3000: sample_rate=22050" -strict -2 -t 3 -c:a $var test_audio_$var.avi)
x=$?
echo $x
if [ $x -eq 0 ]; then
echo OK
echo $var >> used_audio_codec.txt
else
echo FAIL
rm test_audio_$var.avi
fi
done

echo ""
echo ""
rm -f used_video_codec.txt
rm -f test_video_*.avi
awk '{print $2F}' video.txt > video_name.txt
file="video_name.txt"
for var in $(cat $file)
do
echo ""
echo "ffmpeg -c:v $var test_video_$var.avi"
$(ffmpeg -hide_banner -f lavfi -i "testsrc=size=320x200:rate=30" -pix_fmt yuv420p -timestamp now -t 3 -c:v $var test_video_$var.avi)
x=$?
echo $x
if [ $x -eq 0 ]; then
echo OK
echo $var >> used_video_codec.txt
else
echo FAIL
rm test_video_$var.avi
fi
done
