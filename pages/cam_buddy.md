# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.

![CamBuddy Overview](https://docs.google.com/drawings/d/e/2PACX-1vR7BKwVcEOv1lxMWqTq1ONacsw_-yF_4VFnuayzybmG0wb4NXQavaYXJ4MrJ4nPLWTJjspexMjTidkJ/pub?w=796&h=287)

It is my first time using an ESP32-CAM.  I am sure the software could be much better written. 

## Features

# Hardware
- [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN).  I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".
- USB cable.  One end is connected to the + and - 5V power of the ESP32-CAM.  The other end gets plugged into a USB port.  This provides the power.
- 3d Printed enclosure
# Software
- [ESPAsyncWebServer library](https://github.com/me-no-dev/ESPAsyncWebServer) - From my limited experience, folks using the ESP32-CAM have been enabled by the Arduino IDE libraries and example code.   I started with straight ESP32-CAM Video Streaming as [well documented in a Random Nerd Tutorial](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/).  Unfortunately, the synchronous nature did not allow me to also send timelapse images to a Raspberry Pi for the timelapse gif.
- [FTP Arduino client]


## Setup
### FTP Server
An FTP Server runs on the GrowBuddy Rasp Pi server.  I Installed the [FTP Server on Rasp Pi](https://phoenixnap.com/kb/raspberry-pi-ftp-server).
### Arduino IDE and Code
The code is written using the Arduino IDE.  Since I am not an expert with Arduino code (and JavaScript for that matter...oh and the details of HTML...hmmm...), I stuck with the Arduino IDE and installed all the ESP32 goo as described in multiple YouTube videos.
#### ESP32-CAM Stuff
To use the ESP32-CAM:
- Initialize.  See the function `bool initCamera();`.  I am using the settings for the AI Thinker ESP32-CAM.  One thing that we might want to change is the image quality or perhaps the pixel format.  The constants are defined in [espressif's esp32-camera file sensor.h](https://github.com/espressif/esp32-camera/blob/master/driver/include/sensor.h).
- Take a "snapshot" (i.e.: grab a frame) at the resolution and format specified in the camera initialization.