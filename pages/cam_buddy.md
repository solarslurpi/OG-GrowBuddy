# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.

![CamBuddy Overview](https://docs.google.com/drawings/d/e/2PACX-1vR7BKwVcEOv1lxMWqTq1ONacsw_-yF_4VFnuayzybmG0wb4NXQavaYXJ4MrJ4nPLWTJjspexMjTidkJ/pub?w=796&h=287)

# Features

# Hardware
- [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN).  I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".  I describe some ESP32 challenges I am having in the Arduino environment in [the section on ESP32 Arduino learnings](../pages/esp32_arduino_learnings.md).  

- 3d Printed enclosure
# Software
Software was built using the Arduino IDE.  The main pieces include:

- [ESP32-CAM Video Streaming Web Code](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/): After much grinding and nashing of teeth, I ended up using the simplest Arduino code for video streaming from the ESP32-CAM.  I found [Rui Santos's Random Nerd tutorial](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/) to be very helpful.  Hmmm...the code seems to run a bit qwirky, occasionally freezing and rebooting.  However, so far I have not missed taking an image, so there is continual running.
- The code for storing the image on a Raspberry Pi server is pinned to run on the ESP32's Core0 (see [`initStorePicFTPonCore0()`](https://github.com/solarslurpi/GrowBuddy/blob/cdc84a9b7d882e8746123f16a8f8e802f8390ff4/camBuddy_code/camBuddy/storePicFTPonCore0.cpp))
- Logging....

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



