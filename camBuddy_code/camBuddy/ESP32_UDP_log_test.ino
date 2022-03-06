//**************************************************************
// Example provided by @turai on reddit.  See 
//   https://www.reddit.com/r/esp32/comments/t6w2gw/can_esp32_arduino_stack_traces_be_routed_to_telnet/hzhc2uw/?context=3
#include <esp_log.h>
#include <sys/socket.h>
#include <WiFi.h>

// Put this in esp32-hal-log.h after the header guard (ifndef arduhal_log)
// #define USE_ESP_IDF_LOG 1

static const size_t LOG_BUF_SIZE = 1450;
static const char* SSID = "MikroTik DKVLAN";
static const char* PSK = "WhatEver123123";
static const char* TARGET_IP = "192.168.0.200";
static const uint16_t TARGET_PORT = 60000;
struct sockaddr_in target;

size_t nth_message = 0;
int sock = -1;
char log_buffer[LOG_BUF_SIZE];

int esp_log_to_nc_on_nas(const char* what, va_list args) {
  if(sock < 0) {
    return ESP_FAIL;
  }
  int written = vsnprintf(log_buffer, LOG_BUF_SIZE, what, args);
  return sendto(sock, log_buffer, written, 0, (struct sockaddr*)&target, sizeof(target));
}

void setup() {
  esp_log_level_set("*", ESP_LOG_VERBOSE);
  ESP_LOGI("UART-LOG", "Wifi");
  WiFi.begin(SSID, PSK);
  do { delay(100); } while (WiFi.status() != WL_CONNECTED);
  
  target.sin_family = AF_INET;
  target.sin_port = htons(TARGET_PORT);
  target.sin_addr.s_addr = inet_addr(TARGET_IP);
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  int written = snprintf(log_buffer, LOG_BUF_SIZE, "Socket opened, fd=%d\n", sock);
  sendto(sock, log_buffer, written, 0, (struct sockaddr*)&target, sizeof(target));
  
  ESP_LOGI("UART-LOG", "sock = %d", sock);
  esp_log_set_vprintf(&esp_log_to_nc_on_nas);
}

void loop() {
  ESP_LOGI("UDP-LOG", "Sample text %d", nth_message++);
  delay(1000);
}