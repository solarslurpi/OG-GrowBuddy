# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.

![CamBuddy Overview](https://docs.google.com/drawings/d/e/2PACX-1vR7BKwVcEOv1lxMWqTq1ONacsw_-yF_4VFnuayzybmG0wb4NXQavaYXJ4MrJ4nPLWTJjspexMjTidkJ/pub?w=796&h=287)

It is my first time using an ESP32-CAM.   

# Features

# Hardware
- [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN).  I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".
- USB cable.  One end is connected to the + and - 5V power of the ESP32-CAM.  The other end gets plugged into a USB port.  This provides the power.
- 3d Printed enclosure
# Software
Software was built using the Arduino IDE.  The main pieces include:

- [ESP32-CAM Video Streaming Web Code](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/): After much gringing and nashing of teeth, I ended up using the simplest Arduino code for video streaming from the ESP32-CAM.  I found [Rui Santos's Random Nerd tutorial](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/) to be very helpful.
- The code for storing the image on a Raspberry Pi server is pinned to run on the ESP32's Core0 (see [`initStorePicFTPonCore0()`]())

- [FTP Arduino client]


# Setup
## FTP Server
An FTP Server runs on the GrowBuddy Rasp Pi server.  I Installed the [FTP Server on Rasp Pi](https://phoenixnap.com/kb/raspberry-pi-ftp-server).
## Arduino IDE and Code
The code is written using the Arduino IDE.  Since I am not an expert with Arduino code (and JavaScript for that matter...oh and the details of HTML...hmmm...), I stuck with the Arduino IDE and installed all the ESP32 goo as described in multiple YouTube videos.
## ESP32-CAM Stuff
To use the ESP32-CAM:
- Initialize.  See the function `bool initCamera();`.  I am using the settings for the AI Thinker ESP32-CAM.  One thing that we might want to change is the image quality or perhaps the pixel format.  The constants are defined in [espressif's esp32-camera file sensor.h](https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h).
- Take a "snapshot" (i.e.: grab a frame) at the resolution and format specified in the camera initialization.

# Timelapse
- [Creating a Timelapse video with ffmpeg](https://medium.com/@sekhar.rahul/creating-a-time-lapse-video-on-the-command-line-with-ffmpeg-1a7566caf877)
- [ffmpeg H.264 Video Encoding Guide](https://trac.ffmpeg.org/wiki/Encode/H.264)
A timelapse moving is created using `ffmpeg` using a `cron` job that runs once in the middle of the night.
```
ffmpeg -framerate 5 -pattern_type glob -i '*.jpg' -c:v libx264 -crf 18 -pix_fmt yuv420p out.mp4
```
- __framerate__: the number of images to render per second in the video.
- __pattern_type__: we set this to glob to tell ffmpeg to use all the images that match the pattern in the following parameter.
- __i__: a pattern that matches all the input photos in your timelapse.
- __c:v__: This command tell ffmpeg to encode into H264 video format. 
- __crf__:  A parameter specific to the H264 codec that determines the quality/compression.  [see the docs for H264 encoding for details of the crf command](https://trac.ffmpeg.org/wiki/Encode/H.264).
- __pix_fmt__: This is here because I copy pasted.  As I understanding it, the stream needs to be encoded in YUV420p to work with video playback (Quicktime, etc...).


