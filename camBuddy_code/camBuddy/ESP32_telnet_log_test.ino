
//*****************************************************************
// ESP32_telnet_log_test.ino
// This example code shows using the ESP32 logging system within the Arduino environment.
// Good article that discusses ESP32 debugging within the Arduino IDE: https://thingpulse.com/esp32-logging/
// See details on "little known" aspects to get this working..
// First, find the esp32-hal-log.h ... I'm on a Windows PC.  The locatin for me is: 
//   C:\Users\happy\AppData\Local\Arduino15\packages\esp32\hardware\esp32\1.0.6\cores\esp32
// Open esp32-hal-log.h and modif
// - uses an AI Thinker ESP32-CAM to live video stream and periodically
//   take a snapshot.  The snapshot is sent to an FTP server for post
//   processing into a gif.
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
#include <WiFi.h>
#include <TimeLib.h>
#include <TelnetStream.h>

const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;

#include "arduino_secrets.h"
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = SECRET_SSID;    // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

void setup() {
  Serial.begin(115200);

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Failed to connect.");
    while (1) {
      delay(10);
    }
  }

  configTime(gmtOffset_sec, daylightOffset_sec, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < SECS_YR_2000) {
    delay(100);
    now = time(nullptr);
  }
  setTime(now);

  IPAddress ip = WiFi.localIP();
  Serial.println();
  Serial.println("Connected to WiFi network.");
  Serial.print("Connect with Telnet client to ");
  Serial.println(ip);

  TelnetStream.begin();
}

void loop() {
  switch (TelnetStream.read()) {
    case 'R':
    TelnetStream.stop();
    delay(100);
    ESP.restart();
      break;
    case 'C':
      TelnetStream.println("bye bye");
      TelnetStream.stop();
      break;
  }

  static unsigned long next;
  if (millis() - next > 5000) {
    next = millis();
    log();
  }
}

void log() {
  static int i = 0;

  char timeStr[20];
  sprintf(timeStr, "%02d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());

  TelnetStream.print(i++);
  TelnetStream.print(" ");
  TelnetStream.print(timeStr);
  TelnetStream.print(" A0: ");
  TelnetStream.println(analogRead(A0));
}