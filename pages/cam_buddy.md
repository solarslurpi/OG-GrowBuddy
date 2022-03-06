# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.

![CamBuddy Overview](https://docs.google.com/drawings/d/e/2PACX-1vR7BKwVcEOv1lxMWqTq1ONacsw_-yF_4VFnuayzybmG0wb4NXQavaYXJ4MrJ4nPLWTJjspexMjTidkJ/pub?w=796&h=287)

It is my first time using an ESP32-CAM.   

# Features

# Hardware
- [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN).  I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".  The challenge I am having with the AI Thinker is in robustness and completeness.  Sometimes the ESP32-CAM seems to freeze or drop out of showing the live stream.  This led me to looking at debugging.  Here I find:
- The AI Thinker's boards.txt entry does not have all the goodies other boards have.  Here's the AI Thinker board menu:

![AI Thinker Menu](../images/esp32aithinker.jpg)

Here's other ESP32's board menu:
![ESP32 menu](../images/esp32_great_tools_menu.jpg)

The other boards have cool options like partitioning for OTA, Core Debug logging...OOOHH!

I found an [Arduino Stack Exchange article](https://arduino.stackexchange.com/questions/75198/why-doesnt-ota-work-with-the-ai-thinker-esp32-cam-board) that added these features in for the AI Thinker.  So far it seems to work...

It requires finding the location of the boards.txt file.  The easiest way to find the location is to go to preferences within the Arduino IDE and check the verbose compiler output.  My location is:
```
C:\Users\happy\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\boards.txt
```
Then follow the instructions in the article to change the info within the AI Thinker board definition in the file to:
```
##############################################################

esp32AiThinkerCam.name=ESP32 AI Thinker Cam

esp32AiThinkerCam.upload.tool=esptool_py
esp32AiThinkerCam.upload.maximum_size=1310720
esp32AiThinkerCam.upload.maximum_data_size=327680
esp32AiThinkerCam.upload.wait_for_upload_port=true

esp32AiThinkerCam.serial.disableDTR=true
esp32AiThinkerCam.serial.disableRTS=true

esp32AiThinkerCam.build.mcu=esp32
esp32AiThinkerCam.build.core=esp32
esp32AiThinkerCam.build.variant=esp32
esp32AiThinkerCam.build.board=ESP32_DEV

esp32AiThinkerCam.build.f_cpu=240000000L
esp32AiThinkerCam.build.flash_size=4MB
esp32AiThinkerCam.build.flash_freq=40m
esp32AiThinkerCam.build.flash_mode=dio
esp32AiThinkerCam.build.boot=dio

esp32AiThinkerCam.menu.CPUFreq.240=240MHz (WiFi/BT)
esp32AiThinkerCam.menu.CPUFreq.240.build.f_cpu=240000000L
esp32AiThinkerCam.menu.CPUFreq.160=160MHz (WiFi/BT)
esp32AiThinkerCam.menu.CPUFreq.160.build.f_cpu=160000000L
esp32AiThinkerCam.menu.CPUFreq.80=80MHz (WiFi/BT)
esp32AiThinkerCam.menu.CPUFreq.80.build.f_cpu=80000000L

esp32AiThinkerCam.build.partitions=default
esp32AiThinkerCam.build.defines=-DBOARD_HAS_PSRAM -mfix-esp32-psram-cache-issue
esp32AiThinkerCam.menu.PartitionScheme.default=Default 1.2MB APP/1.5MB SPIFFS (OTA)
esp32AiThinkerCam.menu.PartitionScheme.default.build.partitions=default
esp32AiThinkerCam.menu.PartitionScheme.defaultffat=Default FATFS 1.2MB APP/1.5MB FATFS (OTA)
esp32AiThinkerCam.menu.PartitionScheme.defaultffat.build.partitions=default_ffat
esp32AiThinkerCam.menu.PartitionScheme.noota_3g=1MB APP/3MB SPIFFS (No OTA)
esp32AiThinkerCam.menu.PartitionScheme.noota_3g.build.partitions=noota_3g
esp32AiThinkerCam.menu.PartitionScheme.noota_3g.upload.maximum_size=1048576
esp32AiThinkerCam.menu.PartitionScheme.no_ota=2MB APP/2MB SPIFFS (No OTA)
esp32AiThinkerCam.menu.PartitionScheme.no_ota.build.partitions=no_ota
esp32AiThinkerCam.menu.PartitionScheme.no_ota.upload.maximum_size=2097152
esp32AiThinkerCam.menu.PartitionScheme.huge_app=3MB APP/1MB SPIFFS (No OTA)
esp32AiThinkerCam.menu.PartitionScheme.huge_app.build.partitions=huge_app
esp32AiThinkerCam.menu.PartitionScheme.huge_app.upload.maximum_size=3145728
esp32AiThinkerCam.menu.PartitionScheme.noota_ffat=2MB APP/2MB FATFS (No OTA)
esp32AiThinkerCam.menu.PartitionScheme.noota_ffat.build.partitions=noota_ffat
esp32AiThinkerCam.menu.PartitionScheme.noota_ffat.upload.maximum_size=2097152
esp32AiThinkerCam.menu.PartitionScheme.noota_3gffat=1MB APP/3MB FATFS (No OTA)
esp32AiThinkerCam.menu.PartitionScheme.noota_3gffat.build.partitions=noota_3gffat
esp32AiThinkerCam.menu.PartitionScheme.noota_3gffat.upload.maximum_size=1048576
esp32AiThinkerCam.menu.PartitionScheme.minimal=Min SPIFFS 1.3MB APP/700KB SPIFFS (OTA)
esp32AiThinkerCam.menu.PartitionScheme.minimal.build.partitions=minimal
esp32AiThinkerCam.menu.PartitionScheme.min_spiffs=Med SPIFFS 1.9MB APP/190KB SPIFFS (OTA)
esp32AiThinkerCam.menu.PartitionScheme.min_spiffs.build.partitions=min_spiffs
esp32AiThinkerCam.menu.PartitionScheme.min_spiffs.upload.maximum_size=1966080


esp32AiThinkerCam.menu.FlashMode.qio=QIO
esp32AiThinkerCam.menu.FlashMode.qio.build.flash_mode=dio
esp32AiThinkerCam.menu.FlashMode.qio.build.boot=qio
esp32AiThinkerCam.menu.FlashMode.dio=DIO
esp32AiThinkerCam.menu.FlashMode.dio.build.flash_mode=dio
esp32AiThinkerCam.menu.FlashMode.dio.build.boot=dio
esp32AiThinkerCam.menu.FlashMode.qout=QOUT
esp32AiThinkerCam.menu.FlashMode.qout.build.flash_mode=dout
esp32AiThinkerCam.menu.FlashMode.qout.build.boot=qout
esp32AiThinkerCam.menu.FlashMode.dout=DOUT
esp32AiThinkerCam.menu.FlashMode.dout.build.flash_mode=dout
esp32AiThinkerCam.menu.FlashMode.dout.build.boot=dout

esp32AiThinkerCam.menu.FlashFreq.80=80MHz
esp32AiThinkerCam.menu.FlashFreq.80.build.flash_freq=80m
esp32AiThinkerCam.menu.FlashFreq.40=40MHz
esp32AiThinkerCam.menu.FlashFreq.40.build.flash_freq=40m

esp32AiThinkerCam.menu.UploadSpeed.921600=921600
esp32AiThinkerCam.menu.UploadSpeed.921600.upload.speed=921600
esp32AiThinkerCam.menu.UploadSpeed.115200=115200
esp32AiThinkerCam.menu.UploadSpeed.115200.upload.speed=115200
esp32AiThinkerCam.menu.UploadSpeed.256000.windows=256000
esp32AiThinkerCam.menu.UploadSpeed.256000.upload.speed=256000
esp32AiThinkerCam.menu.UploadSpeed.230400.windows.upload.speed=256000
esp32AiThinkerCam.menu.UploadSpeed.230400=230400
esp32AiThinkerCam.menu.UploadSpeed.230400.upload.speed=230400
esp32AiThinkerCam.menu.UploadSpeed.460800.linux=460800
esp32AiThinkerCam.menu.UploadSpeed.460800.macosx=460800
esp32AiThinkerCam.menu.UploadSpeed.460800.upload.speed=460800
esp32AiThinkerCam.menu.UploadSpeed.512000.windows=512000
esp32AiThinkerCam.menu.UploadSpeed.512000.upload.speed=512000

esp32AiThinkerCam.menu.DebugLevel.none=None
esp32AiThinkerCam.menu.DebugLevel.none.build.code_debug=0
esp32AiThinkerCam.menu.DebugLevel.error=Error
esp32AiThinkerCam.menu.DebugLevel.error.build.code_debug=1
esp32AiThinkerCam.menu.DebugLevel.warn=Warn
esp32AiThinkerCam.menu.DebugLevel.warn.build.code_debug=2
esp32AiThinkerCam.menu.DebugLevel.info=Info
esp32AiThinkerCam.menu.DebugLevel.info.build.code_debug=3
esp32AiThinkerCam.menu.DebugLevel.debug=Debug
esp32AiThinkerCam.menu.DebugLevel.debug.build.code_debug=4
esp32AiThinkerCam.menu.DebugLevel.verbose=Verbose
esp32AiThinkerCam.menu.DebugLevel.verbose.build.code_debug=5
```

- USB cable.  One end is connected to the + and - 5V power of the ESP32-CAM.  The other end gets plugged into a USB port.  This provides the power.
- 3d Printed enclosure
# Software
Software was built using the Arduino IDE.  The main pieces include:

- [ESP32-CAM Video Streaming Web Code](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/): After much grinding and nashing of teeth, I ended up using the simplest Arduino code for video streaming from the ESP32-CAM.  I found [Rui Santos's Random Nerd tutorial](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/) to be very helpful.  Hmmm...the code seems to run a bit qwirky, occasionally freezing and rebooting.  However, so far I have not missed taking an image, so there is continual running.
- The code for storing the image on a Raspberry Pi server is pinned to run on the ESP32's Core0 (see [`initStorePicFTPonCore0()`](https://github.com/solarslurpi/GrowBuddy/blob/cdc84a9b7d882e8746123f16a8f8e802f8390ff4/camBuddy_code/camBuddy/storePicFTPonCore0.cpp))

- [FTP Arduino client]


# Setup
## FTP Server
An FTP Server running on the GrowBuddy Rasp Pi server is used to store images taken from camBuddy to create a timelapse.  I Installed the [FTP Server on Rasp Pi](https://phoenixnap.com/kb/raspberry-pi-ftp-server).
## Accessing Files
On a Windows PC, FTP shares can be accessed in the file manager.

![path to ftp server on Windows](../images/ftp_filemanager.jpg)

To access the ftp share on growbuddy for example - if the username = pi and password = raspberry, `ftp://pi:raspberry@growbuddy`.

### Timelapse
A timelapse is created using the images in the ftp share.
- [Creating a Timelapse video with ffmpeg](https://medium.com/@sekhar.rahul/creating-a-time-lapse-video-on-the-command-line-with-ffmpeg-1a7566caf877)
- [ffmpeg H.264 Video Encoding Guide](https://trac.ffmpeg.org/wiki/Encode/H.264)
A timelapse moving is created using `ffmpeg` using a `cron` job that runs once in the middle of the night.
```
ffmpeg -framerate 10 -pattern_type glob -i '*.jpg' -c:v libx264 -crf 18 -pix_fmt yuv420p out.mp4
```
- __framerate__: the number of images to render per second in the video.
- __pattern_type__: we set this to glob to tell ffmpeg to use all the images that match the pattern in the following parameter.
- __i__: a pattern that matches all the input photos in your timelapse.
- __c:v__: This command tell ffmpeg to encode into H264 video format. 
- __crf__:  A parameter specific to the H264 codec that determines the quality/compression.  [see the docs for H264 encoding for details of the crf command](https://trac.ffmpeg.org/wiki/Encode/H.264).
- __pix_fmt__: The stream needs to be encoded in YUV420p to work with video playback (Quicktime, etc...).


## Arduino IDE and Code
The code is written using the Arduino IDE.  Since I am not an expert with Arduino code (and JavaScript for that matter...oh and the details of HTML...hmmm...), I stuck with the Arduino IDE and installed all the ESP32 goo as described in multiple YouTube videos.
## ESP32-CAM Stuff
To use the ESP32-CAM:
- Initialize.  See the function `bool initCamera();`.  I am using the settings for the AI Thinker ESP32-CAM.  One thing that we might want to change is the image quality or perhaps the pixel format.  The constants are defined in [espressif's esp32-camera file sensor.h](https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h).
- Take a "snapshot" (i.e.: grab a frame) at the resolution and format specified in the camera initialization.



