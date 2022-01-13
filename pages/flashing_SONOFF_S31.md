The Sonoff S31 (or S31 Lite) can be flashed so that Tasmota is running on our local network.
- [instructions on how to flash Tosmota](https://www.youtube.com/watch?v=9N58uy3ezvA)

ooh! Extra care when soldering.  If not, well...it is way too easy to rip off one of the pads...

Once flashed and rebooted:
1. As with any Tasmota device, set up the configuration.  Here we set it up to be an S31:
![Tasmota s31 setup](../images/Tasmota_S21_Config.jpg)
2. Set up mqtt configuration:
![Tasmota s31 mqtt](../images/Tasmota_S31_mqtt.jpg)
The growbuddy raspberry pi server is the mqtt broker.  The topic is named `plug_CO2` to identify it as the relay plug that is turning on and off the CO2 solenoid.
3. Put the S31 back to it's original packaging.