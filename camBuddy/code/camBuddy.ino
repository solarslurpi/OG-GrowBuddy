//*****************************************************************
// camBuddy
// - uses an AI Thinker ESP32-CAM to live video stream and periodically
//   take a snapshot.  The snapshot is sent to an FTP server for post
//   processing into a gif.
// - OTA updates handled over port 91.
// - Documentation at https://github.com/solarslurpi/GrowBuddy/blob/main/pages/cam_buddy.md
//
//   MIT License
//   Copyright (c) 2022 Margaret Johnson
//
//   Permission is hereby granted free of charge to any person obtaining a copy
//   of this software and associated documentation files (the \Software\) to deal
//   in the Software without restriction including without limitation the rights
//   to use copy modify merge publish distribute sublicense and / or sell
//   copies of the Software and to permit persons to whom the Software is
//   furnished to do so subject to the following conditions:
//
//   The above copyright notice and this permission notice shall be included in all
//   copies or substantial portions of the Software.
//
//   THE SOFTWARE IS PROVIDED \AS IS\ WITHOUT WARRANTY OF ANY KIND EXPRESS OR
//   IMPLIED INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY
//   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM DAMAGES OR OTHER
//   LIABILITY WHETHER IN AN ACTION OF CONTRACT TORT OR OTHERWISE ARISING FROM
//   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//   SOFTWARE.
//*****************************************************************

#include "wifiBuddy.h"
#include "initCamera.h"
/*
 * I ended up using both the httpd Espressif server (see app_http) and
 * here I'm using the Async.  Arguably, I could use just the AsyncWebServer
 * and indeed I got a video stream to work.  However, it was unstable.  Perhaps
 * the instability was in my code (could very well be).  I wanted to at OTA to
 * httpd but that got confusing on just uploading the .bin file.  I liked the way
 * ElegantOTA just handles uploading and updating...that was really nice!
 */
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>

AsyncWebServer otaServer(91);

#include "ftp_stuff.h"
#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h"  //disable brownout problems
//-----------------------------------------------------------------
// see app_http.cpp
// starts up the "video" stream
//-----------------------------------------------------------------
void startCameraServer();



void setup() {
  esp_log_level_set("*", ESP_LOG_INFO);
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  initWifi("camBuddyV2");
  initFTP();
  initCamera();


  startCameraServer();

  AsyncElegantOTA.begin(&otaServer);    // Start ElegantOTA
  otaServer.begin();
}

void loop() {
  delay(1);
}
