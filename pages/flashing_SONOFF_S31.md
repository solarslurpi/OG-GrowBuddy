The Sonoff S31 (or S31 Lite) can be flashed so that Tasmota is running on our local network.
- [instructions on how to flash Tosmota](https://www.youtube.com/watch?v=9N58uy3ezvA)

ooh! Extra care when soldering.  If not, well...it is way too easy to rip off one of the pads...

Once flashed and rebooted:
1. As with any Tasmota device, set up the configuration.  Here we set it up to be an S31:
![Tasmota s31 setup](../images/Tasmota_S21_Config.jpg)
2. Set up mqtt configuration:
![Tasmota s31 mqtt](../images/Tasmota_S31_mqtt.jpg)
The growbuddy raspberry pi server is the mqtt broker.  The topic is named `plug_CO2` or something like it ... to identify it as the relay plug that is turning on and off the CO2 solenoid.
3. Set up the time.  We set this to PST: `Backlog Timezone 99 ; TimeDST 0,2,03,1,3,-420 ; TimeSTD 0,1,11,1,2,-480`
4. Put the S31 back to it's original packaging.

The mqtt path to turn the power on/off is `cmnd/plug_CO2/power` _Note: `plug_CO2` is an example name_.  The message is either `on`, `off`, or `toggle`.