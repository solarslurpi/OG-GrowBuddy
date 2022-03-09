#include <WiFi.h>
#include <ESP32_FTPClient.h>
#include <esp_camera.h>
#include <stdarg.h>
#include "secrets.h"
#include <esp32-hal-log.h>

static const char* _tag = "camBuddy-ftp_stuff";

struct tm timeinfo;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -8 * 60 * 60;
const int   daylightOffset_sec = 3600;
const unsigned int ms_between_pic_lapse = 1000 * 60 * 15; //Time Lapse between taking Pics
//const unsigned int ms_between_pic_lapse = 1000 * 15; //TEST Time Lapse between taking Pics
TaskHandle_t Task0;

int _vprintf_into_ftp(const char *szFormat, va_list args);
void _initStorePicFTPonCore0();

ESP32_FTPClient ftp ("growbuddy", FTP_USER, FTP_PASS);

//**************************************************************************
// INITIALIZATION
void initFTP()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  esp_log_set_vprintf(&_vprintf_into_ftp);
  _initStorePicFTPonCore0();
}
//**************************************************************************
//LOGGING
int _vprintf_into_ftp(const char *szFormat, va_list args)
{
  struct tm timeinfo;
  static char log_print_buffer[512];
  //write evaluated format string into buffer
  int ret = vsnprintf(log_print_buffer, sizeof(log_print_buffer), szFormat, args);
  //output is now in buffer. write to file.
  if (ret >= 0)
  {
    if (!getLocalTime(&timeinfo)) {
      return ret;
    }
    // send to growbuddy using FTP.
    ftp.OpenConnection();
    ftp.InitFile("Type I");
    ftp.ChangeWorkDir("/home/pi/camBuddy/logs");
    if (!getLocalTime(&timeinfo)) {
      ESP_LOGE(_tag,"Could not get the local time.");
      return ret;
    }
    ftp.AppendFile("camBuddy_logs.txt");
    char timestr[20];
    memset(timestr,0,sizeof(timestr));
    strftime(timestr, sizeof(timestr), "%m-%d-%Y_%H:%M:%S.jpg", &timeinfo);
    int outBuf_size = sizeof(timestr) + ret;
    unsigned char outBuf[outBuf_size];
    memset(outBuf,0,outBuf_size);
    memcpy(outBuf, timestr, sizeof(timestr));
    memcpy(outBuf + sizeof(timestr) -1 , log_print_buffer, ret);
    ftp.WriteData( outBuf, outBuf_size );
    ftp.CloseFile();
  }
  return ret;
}
//**************************************************************************
//TIMELAPSE
void _storePicFTPonCore0(void * param) {
  for (;;) {
    // "sleep" until the time has lapse to store a pic on the FTP Server.
    delay(ms_between_pic_lapse);
    // Initialize variables.
    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    // Get the current pic from the camera
    fb = esp_camera_fb_get();
    if (!fb)
    {
      ESP_LOGE(_tag,"Camera capture failed");
      return;
    }
    // send to growbuddy using FTP.
    ftp.OpenConnection();
    ftp.InitFile("Type I");
    ftp.ChangeWorkDir("/home/pi/camBuddy/images");
    if (!getLocalTime(&timeinfo)) {
      ESP_LOGE(_tag,"Failed to obtain time");
      return;
    }
    char filename[32];
    strftime(filename, 32, "img%m-%d-%Y_%H:%M:%S.jpg", &timeinfo);
    ftp.NewFile(filename);
    ftp.WriteData( fb->buf, fb->len );
    ftp.CloseFile();
    ESP_LOGI(_tag,"File %s sent over ftp",filename);

    //_sendFrameFTP(buff, fb->len);
    //return the frame buffer back to be reused
    esp_camera_fb_return(fb);
  }
}

void _initStorePicFTPonCore0() {
  xTaskCreatePinnedToCore(
    _storePicFTPonCore0, /* Function to implement the task */
    "Task0", /* Name of the task */
    10000, /* Stack size in words */
    NULL, /* Task input parameter */
    0, /* Priority of the task */
    &Task0, /* Task handle. */
    0); /* Core where the task should run */

}
