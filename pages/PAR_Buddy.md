# System

# Hardware
- [Adafruit's AS7341 breakout board](https://www.adafruit.com/product/4698)
- [Adafruit's QT Py ESP32-S2](https://www.adafruit.com/product/5325)
# Calibration
To calibrate, the approach taken in the article, [_A Novel Approach to Obtain PAR with a Multi-Channel Spectral Microsensor_](https://pubmed.ncbi.nlm.nih.gov/34068029/) will be used.

A statistically significant number of samples will be fed into a multiple linear regression to find the slope coefficients.

$$ PPFD = b_0 + \sum_{i=1}^{n=8} (b_ix_i) + \epsilon $$

A sample consists of:
- reading the PPFD of a known reference - in this case an Apogee meter.
- readings from the 8 channels on the as7341 that are within the PAR range.



# Calibrator Prototype
To capture the channel values

```
import board
import digitalio
# This button can also be read as GPIO 0 (set it to be an input-with-pullup)
but = digitalio.DigitalInOut(board.D0)
but.pull = digitalio.Pull.UP
```
