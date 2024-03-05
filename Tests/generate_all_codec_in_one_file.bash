#!/bin/bash
i=0
q=""
map=""
file="used_audio_codec.txt"
for var in $(cat $file)
do
q="$q -i test_audio_$var.avi"
map="$map -map $i"
i=`expr $i + 1`
done
file="used_video_codec.txt"
for var in $(cat $file)
do
q="$q -i test_video_$var.avi"
map="$map -map $i"
i=`expr $i + 1`
done
result="ffmpeg -hide_banner $q -strict -2 $map -codec copy output_all.avi"
echo $result
$($result)

