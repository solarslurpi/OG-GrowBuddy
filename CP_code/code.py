import board
import digitalio
import time
from adafruit_debouncer import Debouncer
from PAR_LIB import PAR


def bar_graph(read_value):
    scaled = int(read_value / 1000)
    return "[%5d] " % read_value + (scaled * "*")
    
def callback_function():
    print("in callback function")
    sensor_channels = p.take_reading()
    print("F1 - 415nm/Violet  %s" % bar_graph(sensor_channels[0]))
    print("F2 - 445nm//Indigo %s" % bar_graph(sensor_channels[1]))
    print("F3 - 480nm//Blue   %s" % bar_graph(sensor_channels[2]))
    print("F4 - 515nm//Cyan   %s" % bar_graph(sensor_channels[3]))
    print("F5 - 555nm/Green   %s" % bar_graph(sensor_channels[4]))
    print("F6 - 590nm/Yellow  %s" % bar_graph(sensor_channels[5]))
    print("F7 - 630nm/Orange  %s" % bar_graph(sensor_channels[6]))
    print("F8 - 680nm/Red     %s" % bar_graph(sensor_channels[7]))
    p.send_readings(sensor_channels)


p = PAR()
p.connect(callback_function)