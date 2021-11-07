# What is GrowBuddy?
I am building GrowBuddy to work with my indoor grow.  I am intrigued to find out how much "care and feeding" of indoor plants can be done with technology.  With that said, when I am home I will always check up on my plants daily.  I just love the idea of having a "little buddy" helping me.
1. __(GrowBuddy)__ Automates humidity, temperature, CO2 concentration. 
There are above ground and below ground environmental factors that affect healthy plant growth.

2. __(Doctor GrowBuddy)__ Uses camera and machine learning to aid in plant stress diagnosis.

3. __(GrowBuddy Journal)__ Journal daily growth metrics and publish to online growing diaries.
# Automates humidity, temperature, CO2 concentration.
There are above ground and below ground environmental factors that affect healthy plant growth.
## Above Ground
- Light 
- Air Temperature
- Humidity
- Air Circulation and ventilation
- CO2 concentration
### Light
Light is provided by an LED setup.  I don't automate lighting.  I adjust PPFD by hand.  I guess I could set up a system that figured out the current height of the canopy and then adjusted the LED distance.  But for now I don't.
#### EXCEPT Light ON and OFF
I use a [photoresistor that works with the Rasp Pi](https://smile.amazon.com/gp/product/B07S683LRT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1).  The Rasp Pi doesn't have an ADC, thus this instead of a simple photoresistor.
### Air Circulation and ventilation
I don't automate.  Rather, I add fans to circulate the air around the plant leaves.  For ventilation, I provide input and exhaust fans.
### Humidity, Temperature, and CO2 Concentration
This is the stuff I automate using sensors and stuff like a humidifier and CO2 cannister - referred to from now on as "appliances".  The sensors tell the system what the values are.  The system then either turns on or off the appliance to adjust the value within an acceptable range.
#### Sensors
- CO2 concentration, air temperature, humidity: For my prototype, I used the [SCD-30](https://www.adafruit.com/product/4867).
- Light ON and OFF: The [photoresistor](https://smile.amazon.com/gp/product/B07S683LRT/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1) I noted above.
#### Appliances
When the 
## Below Ground
- Healthy soil (loaded with Bacteria, fungi, and nutrients)
- Water
- Oxygen
## System Overview
Each automated task has it's own flow.
### CO2 Concentration Correction
_TBD: I do not detect the amount of CO2 in a tank.  Knowing this would be useful in alerting me when I need to refill the CO2 tank.  With that said, I get a rough idea over time based on the size of the tank when refilling will occur._
<iframe style="border:none" width="800" height="450" src="https://whimsical.com/embed/3oTnu5rQ7CTUTeLPvVAv3k"></iframe>
<p>&nbsp;</p>

The SCD-30 sensor is read every 3 seconds to get the CO2 level.  To minimize noise, a sliding window of 10 values is done before using in a calculation.
<p>&nbsp;</p>

#### Is It The Right Time To Check?

CO2 concentration correction DOES NOT occur when:
- Maintenance is TRUE.
- Lights are OFF.
- Lights have been on for less than 30 minutes.

#### How Many Seconds?