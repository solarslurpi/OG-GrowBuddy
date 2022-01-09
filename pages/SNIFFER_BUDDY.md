# Sniffer Buddy 
[Back to Top](../README.md)

### Hardware
- [SCD30 sensor from Adafruit](https://www.adafruit.com/product/4867)
- [ESP32 mini32](https://forum.mhetlive.com/topic/8/mh-et-live-minikit-for-esp32) I had in my parts bin.
- Photoresistor and 10K resistor for light on/off detection.

_Note: I wanted to use a battery to power the Air Sensor.  However, it turns out the ESP32 was not designed for battery power. From a Discord chat:_
```
ESP8266 is not suitable for battery operation, unless long deep sleep intervals

Due to the extra battery t[d]rain, probably not too much shorter than 5 minutes
```