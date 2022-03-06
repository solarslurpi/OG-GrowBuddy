#include <SPIFFS.h>
int vprintf_into_spiffs(const char* szFormat, va_list args);
size_t nth_message = 0;


char message[] = "hello";
const char str[] = "Hello World!";
void setup() {
  esp_log_level_set("*", ESP_LOG_VERBOSE);
  ESP_LOGI("UART-LOG", "Starting");
  // Setup Logging
  while (!SPIFFS.begin(true)) {
    ESP_LOGE("UART-LOG", "An Error has occurred while mounting SPIFFS");
  }

}

void loop() {
    ESP_LOGI("UDP-LOG", "Sample text %d", nth_message++);
  delay(1000);
}
static char log_print_buffer[512];
int vprintf_into_spiffs(const char *szFormat, va_list args)
{
  //write evaluated format string into buffer
  int ret = vsnprintf(log_print_buffer, sizeof(log_print_buffer), szFormat, args);

  //output is now in buffer. write to file.
  if (ret >= 0)
  {
    if (!SPIFFS.exists("/LOGS.txt"))
    {
      File writeLog = SPIFFS.open("/LOGS.txt", FILE_WRITE);
      if (!writeLog)
        Serial.println("Couldn't open spiffs_log.txt");
      delay(50);
      writeLog.close();
    }

    File spiffsLogFile = SPIFFS.open("/LOGS.txt", FILE_APPEND);
    //debug output
    Serial.printf("[Writing to SPIFFS] %.*s", ret, log_print_buffer);
    spiffsLogFile.write((uint8_t *)log_print_buffer, (size_t)ret);
    //to be safe in case of crashes: flush the output
    spiffsLogFile.flush();
    spiffsLogFile.close();
  }
  return ret;
}