# Cam Buddy
Cam Buddy provides a web cam and timelapse using a low cost ESP32-CAM.

![CamBuddy Overview](https://docs.google.com/drawings/d/e/2PACX-1vR7BKwVcEOv1lxMWqTq1ONacsw_-yF_4VFnuayzybmG0wb4NXQavaYXJ4MrJ4nPLWTJjspexMjTidkJ/pub?w=796&h=287)

## Features
- Live Stream
- TimeLapse photos taken once an hour.
It is up to you to place cam buddy so the camera has the best view it can of the plants.
# Hardware
- [ESP32 CAM by AI Thinker](https://amzn.to/3LHZ6UN).  I used the AI Thinker version because comments "on the Internet" noted this was "the best" ESP32-CAM...for the "buck".
- USB cable.  One end is connected to the + and - 5V power of the ESP32-CAM.  The other end gets plugged into a USB port.  This provides the power.
- 3d Printed enclosure
# Software
- [ESPAsyncWebServer library](https://github.com/me-no-dev/ESPAsyncWebServer) - From my limited experience, folks using the ESP32-CAM have been enabled by the Arduino IDE libraries and example code.   I started with straight ESP32-CAM Video Streaming as [well documented in a Random Nerd Tutorial](https://randomnerdtutorials.com/esp32-cam-video-streaming-web-server-camera-home-assistant/).  Unfortunately, the synchronous nature did not allow me to also send timelapse images to a Raspberry Pi for the timelapse gif.
- [FTP Arduino client]



Installed [FTP Server on Rasp Pi](https://phoenixnap.com/kb/raspberry-pi-ftp-server)