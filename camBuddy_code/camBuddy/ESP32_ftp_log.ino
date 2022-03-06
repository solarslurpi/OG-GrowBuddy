#include <WiFi.h>


#include <ESP32_FTPClient.h>

const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = SECRET_SSID;    // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

ESP32_FTPClient ftp ("growbuddy", FTP_USER, FTP_PASS);
  
int vprintf_into_ftp(const char* szFormat, va_list args);
size_t nth_message = 0;


void setup() {

  esp_log_level_set("*", ESP_LOG_VERBOSE);
  ESP_LOGI("UART-LOG", "Attempting to connect to WPA SSID: %s", ssid);

  WiFi.begin(ssid, pass);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");

  ESP_LOGI("UART-LOG", "Connected to wifi : %s", WiFi.localIP().toString().c_str());


  esp_log_set_vprintf(&vprintf_into_ftp);

}

void loop() {
  ESP_LOGI("TELNET-LOG", "Sample text %d", nth_message++);
  delay(1000);
}
static char log_print_buffer[512];
int vprintf_into_ftp(const char *szFormat, va_list args)
{
  struct tm timeinfo;
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
      return ret;
    }
    ftp.AppendFile("camBuddy_logs.txt");
    char timestr[22];
    strftime(timestr, sizeof(timestr), "\n%m-%d-%Y_%H:%M:%S.jpg", &timeinfo);
    int outBuf_size = sizeof(timestr) + ret;
    unsigned char outBuf[outBuf_size];
    memcpy(outBuf,timestr,sizeof(timestr));
    memcpy(outBuf+sizeof(timestr)+1,log_print_buffer,ret);
    ftp.WriteData( outBuf, outBuf_size );
    ftp.CloseFile();
  }
  return ret;
}