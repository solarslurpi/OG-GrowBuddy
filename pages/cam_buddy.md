# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.


# Features
- __Continually running a live video stream__.  Here we see the live video stream as a UI component within a node-red dashboard:

![camBuddy video stream in nodered dashboard](../images/camBuddyInnodereddashboard.jpg)
- __Takes and sends an image over FTP every few minutes__.  This means we can make a timelapse out of the images and observe changes that occur over a longer timeframe.
- __Log information and errors to a logfile__ located on a Raspberry Pi.
- __OTA updating__ Over-The-Air updating is accessed through the 

# Hardware
## Microcontroller and Camera
The [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN) is a wonderful combination of a small powerful microcontroller integrated with a "good enough" camera! I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".  I describe some ESP32 challenges I am having in the Arduino environment in [the section on ESP32 Arduino learnings](../pages/esp32_arduino_learnings.md).  
## 3D Printed Enclosure
 I ended up using [ve7it's design on Thingiverse](https://www.thingiverse.com/thing:4057903).
### Improvements 
There are a few immediate improvements that should be considered for the next build including:
- Adding a [USB to DIP adapter](https://amzn.to/3CIpQ3q) to make it easy to plug in a USB cord.  [MagnusT's "Smallest possible ESP32-CAM~ entry on Thingiverse](https://www.thingiverse.com/thing:4107609) has shared such a design:

![USB to DIP ESP32-CAM case](../images/thingiversecase_with_usb_connector.jpg)
- Adding a way to easily mount either in a grow tent or elsewhere.  Right now I use string and some two sided tape.  
# Software
The code is written using the Arduino IDE.  Since I am not an expert with Arduino code (and JavaScript for that matter...oh and the details of HTML...hmmm...), I stuck with the Arduino IDE and installed all the ESP32 goo as described in multiple YouTube videos.  As I got deeper into the project, I couldn't help thinking it might be a better path to code directly in the ESP IDF instead of using the Arduino IDE...

The main pieces include:

- The code that streams a live video feed over http to one client.  The majority of this code is found in [app_http.cpp](https://github.com/solarslurpi/GrowBuddy/blob/ad03f6705e5399dbb0571254f4b25ed775f86e3d/camBuddy_code/camBuddy/app_httpd.cpp).  The code was evolved from Rui Santos' excellent tutorial, [ESP32-CAM Video Streaming Web Code](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/). The camera is initialized in the function `bool initCamera();`.  I am using the settings for the AI Thinker ESP32-CAM.  One thing that we might want to change is the image quality or perhaps the pixel format.  The constants are defined in [espressif's esp32-camera file sensor.h](https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h).
- The code for storing the image on a Raspberry Pi server is pinned to run on the ESP32's Core0 (see [`initStorePicFTPonCore0()`](https://github.com/solarslurpi/GrowBuddy/blob/cdc84a9b7d882e8746123f16a8f8e802f8390ff4/camBuddy_code/camBuddy/storePicFTPonCore0.cpp))
- ESP32 logging. Implementing logging gave me better insight into the Arduino IDE's abstraction layer over the ESP32 IDF.  The Arduino IDE only gave me rudimentary printf to a locally plugged in serial monitor for logging.  Yet, in the depths below the Arduino abstraction layer, the ESP IDF has a much more powerful logging subsystem.  There's a few things to do before we can use it in our project, especially with the AI Thinker ESP32-CAM.  To get logging to work, I had to understand and implement the [menu access and debugging "toggles"](esp32_arduino_learnings.md)

Once we've done the somewhat confusing goop to get ESP32 logging on the Arduino, we can send logs to an FTP Server.
```
03-12-2022_04:34:30I (181253893) camBuddy-ftp_stuff: File img03-12-2022_04:34:29.jpg sent over ftp
03-12-2022_04:49:36E (182158491) camBuddy-ftp_stuff: Camera capture failed
03-12-2022_04:49:36E (182160692) FreeRTOS: FreeRTOS Task "Task0" should not return, Aborting now!
03-12-2022_04:49:42I (4841) camBuddy-app-http: Starting stream server on port: '80'

03-17-2022_13:02:51I (457985863) camBuddy-ftp_stuff: File img03-17-2022_13:02:50.jpg sent over ftp
03-17-2022_13:41:47E (47018) ARDUINO: socket error on fd 59, errno: 104, "Connection reset by peer"
03-17-2022_13:41:57E (47018) ARDUINO: socket error on fd 59, errno: 104, "Connection reset by peer"

03-17-2022_13:56:05I (905503) camBuddy-ftp_stuff: File img03-17-2022_13:56:04.jpg sent over ftp

03-19-2022_11:46:53I (110937101) camBuddy-ftp_stuff: File img03-19-2022_11:46:53.jpg sent over ftp
03-19-2022_11:59:14I (4840) camBuddy-app-http: Starting stream server on port: '80'

03-27-2022_04:45:49E (5428) ARDUINO: DNS Failed for growbuddy
03-27-2022_04:45:59E (5428) ARDUINO: DNS Failed for growbuddy
03-27-2022_04:46:10E (5428) ARDUINO: DNS Failed for growbuddy
03-27-2022_04:46:21E (5428) ARDUINO: DNS Failed for growbuddy

```
The above shows logging when the timelapse photo was taken.  I included several "snapshots" where camBuddy failed to take the image.  VERY useful!  I'm not fixing anything at this point because camBuddy readjusts and keeps going.
## OTA
There are several OTA methods available for ESP32 boards.  After trial and error, I ended up using the [AsynccElegantOTA Library as recommended by Ruis Santos](https://randomnerdtutorials.com/esp32-ota-over-the-air-arduino/).  I register the OTA server on port 91.  OTA update is accessed by going to the URL `cambuddy:91/update` (note: the name of your ESP32 may be different.  My code uses the name cambuddy).  I'm not thrilled to be running two services - the web service on port 80 and the update service on port 90 - however, this was the most expedient way to get everything working.  I mean, it doesn't get simpler than this!:
```
AsyncElegantOTA.begin(&otaServer);    // Start ElegantOTA
otaServer.begin();
```

# Setup
## FTP Server
An FTP Server running on the GrowBuddy Rasp Pi server is used to store images taken from camBuddy to create a timelapse.  I Installed the [FTP Server on Rasp Pi](https://phoenixnap.com/kb/raspberry-pi-ftp-server).
## Accessing Files
On a Windows PC, FTP shares can be accessed in the file manager.

![path to ftp server on Windows](../images/ftp_filemanager.jpg)

To access the ftp share on the Rasp Pi Server named growbuddy for example - if the username = pi and password = raspberry, `ftp://pi:raspberry@growbuddy`.

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






