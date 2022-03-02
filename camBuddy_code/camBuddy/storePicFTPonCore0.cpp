//*****************************************************************
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
#include "WiFi.h"
#include "Arduino.h"
#include "esp_camera.h"
#include "ESP32_FTPClient.h"
#include "time.h"
#include "secrets.h"



struct tm timeinfo;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -8 * 60 * 60;
const int   daylightOffset_sec = 3600;
const unsigned int ms_between_pic_lapse = 1000 * 60 * 15; //Time Lapse between taking Pics
TaskHandle_t Task0;

//// you can pass a FTP timeout and debug mode on the last 2 arguments
//ESP32_FTPClient ftp ("growbuddy", FTP_USER, FTP_PASS, 5000, 2);
ESP32_FTPClient ftp ("growbuddy", FTP_USER, FTP_PASS);
//----------------------------------------------------------------
void initTime() {

  // Init time - Time is used in the filename.
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
//----------------------------------------------------------------
void storePicFTPonCore0(void * param) {
  for (;;) {
    // "sleep" until the time has lapse to store a pic on the FTP Server.
    delay(ms_between_pic_lapse);
//    Serial.println("SNAP!");
//    Serial.print("Running on core: ");
//    Serial.println(xPortGetCoreID());
    // Initialize variables.
    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    // Get the current pic from the camera
    fb = esp_camera_fb_get();
//    Serial.print("Frame size ");
//    Serial.println(fb->len);
    if (!fb)
    {
      Serial.println("Camera capture failed");
      return;
    }
    // send to growbuddy using FTP.
    ftp.OpenConnection();
    ftp.InitFile("Type I");
    ftp.ChangeWorkDir("/home/pi/camBuddy/images");
    if (!getLocalTime(&timeinfo)) {
      Serial.println("Failed to obtain time");
      return;
    }
    char filename[32];
    strftime(filename, 32, "img%m-%d-%Y_%H:%M:%S.jpg", &timeinfo);
    ftp.NewFile(filename);
    ftp.WriteData( fb->buf, fb->len );
    ftp.CloseFile();
    Serial.println("***> File sent over ftp");

    //_sendFrameFTP(buff, fb->len);
    //return the frame buffer back to be reused
    esp_camera_fb_return(fb);
  }
}

void initStorePicFTPonCore0() {
  xTaskCreatePinnedToCore(
    storePicFTPonCore0, /* Function to implement the task */
    "Task0", /* Name of the task */
    10000, /* Stack size in words */
    NULL, /* Task input parameter */
    0, /* Priority of the task */
    &Task0, /* Task handle. */
    0); /* Core where the task should run */

}
