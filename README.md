# FFMPEG_Info

##ПОДГОТОВКА
Успешно скомпилировать проект получилось на последней версии FFMPEG, полученной с сайта
Проблемы были с версией, установленной через apt-get install ffmpeg
Когда папка src находится в одном каталоге с ffmpeg

git clone https://git.ffmpeg.org/ffmpeg.git ffmpeg
cd ffmpeg
./configure --disable-x86asm
make
	
cd ffmpeg
find . -name *.a
mkdir libs
cp ./libavutil/libavutil.a libs
cp ./libavcodec/libavcodec.a libs
cp ./libavfilter/libavfilter.a libs
cp ./libswresample/libswresample.a libs
cp ./libavformat/libavformat.a libs
cp ./libswscale/libswscale.a libs
cp ./libavdevice/libavdevice.a libs
cd ..


##ИСХОДНИКИ
src
Папка с исходниками

Компиляция
make или make all

##ЗАПУСК
В командной строке можно указать любое количество имён файлов, содержащихся в текущей папке
./FFMPEG_Info file1 file2 ... fileN
Например
./FFMPEG_Info Megamind.avi output.avi output_all.avi


##РЕЗУЛЬТАТЫ
Results/test_100_stream.txt
Результат работы для 3 файлов, содержащих разное количество потоков в разных аудио и видео форматах при выполнении команды
./FFMPEG_Info Megamind.avi output.avi output_all.avi  > test_100_stream.txt


##ТЕСТИРОВАНИЕ
Генерация множества файлов разных кодеков

Команда выводит список список доступных кодеков
ffmpeg -hide_banner -decoders
Список разделяется для 2 файла:
	для аудио - audio.txt
	для видео - video.txt

Tests/generate_many_files.bash
Для каждого доступного аудиокодека из файла audio.txt создается файл сгерерированный виртуальным устройством lavfi.
Если генерация происходит успешно имя кодека помещается в файл used_audio_codec.txt

Для каждого доступного видеокодека из файла video.txt создается файл сгерерированный виртуальным устройством lavfi.
Если генерация происходит успешно имя кодека помещается в файл used_video_codec.txt

Tests/generate_all_codec_in_one_file.bash
Герерация одного большого файла содержащего потоки во всех доступных кодеках
Название кодеков берётся из файлов used_audio_codec.txt и used_video_codec.txt
Выходной файл output_all.avi
