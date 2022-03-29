#include "WiFi.h"
#include "secrets.h"
#include <esp32-hal-log.h>
static const char* _tag = "camBuddy-wifiBuddy";

bool initWifi(char *hostname) {
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  ESP_LOGI(_tag, "Connected to wifi : %s", WiFi.localIP().toString().c_str());
  return (true);
}
