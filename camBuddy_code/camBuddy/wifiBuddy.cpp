#include "WiFi.h"
#include "secrets.h"

bool initWifi() {
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  WiFi.mode(WIFI_STA);
  WiFi.setHostname("cambuddy");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected. ");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  return (true);
}
