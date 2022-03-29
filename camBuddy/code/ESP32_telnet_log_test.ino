#include <WiFi.h>

#include <TelnetStream.h>

const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = SECRET_SSID;    // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int vprintf_into_telnet(const char* szFormat, va_list args);
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

  esp_log_set_vprintf(&vprintf_into_telnet);

  TelnetStream.begin();
}

void loop() {
  ESP_LOGI("TELNET-LOG", "Sample text %d", nth_message++);
  delay(1000);
}
static char log_print_buffer[512];
int vprintf_into_telnet(const char *szFormat, va_list args)
{
  struct tm timeinfo;
  //write evaluated format string into buffer
  int ret = vsnprintf(log_print_buffer, sizeof(log_print_buffer), szFormat, args);
  //output is now in buffer. write to file.
  if (ret >= 0)
  {
    char timeStr[22];
    if (!getLocalTime(&timeinfo)) {
      return ret;
    }
    strftime(timeStr, sizeof(timeStr),"%m-%d-%Y_%H:%M:%S ", &timeinfo);
    TelnetStream.print(timeStr);
    TelnetStream.println(log_print_buffer);
  }
  return ret;
}