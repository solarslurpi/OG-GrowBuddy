import board
import busio
import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT
import ssl
from adafruit_as7341 import AS7341
import json



class PAR:
    def __init__(self):
        i2c = busio.I2C(board.SCL1,board.SDA1)  # uses board.SCL and board.SDA
        self.sensor = AS7341(i2c)
        self.bConnected = False
        print(type(self.sensor))
    def _connect_mqtt(self,mqtt_client, userdata, flags, rc):
        # This function will be called when the mqtt_client is connected
        # successfully to the broker.
        self.bConnected = True
        print("Connected to MQTT Broker!")
        print("Flags: {0}\n RC: {1}".format(flags, rc))      
    def connect(self,callback_function):
        # Get wifi details and more from a secrets.py file
        try:
            from secrets import secrets
        except ImportError:
            print("WiFi secrets are kept in secrets.py, please add them there!")
            raise
        # connect to wifi
        print("Connecting to %s"%secrets["ssid"])
        wifi.radio.connect(secrets["ssid"], secrets["password"])
        print("Connected to %s!"%secrets["ssid"])
        # Create a socket pool
        pool = socketpool.SocketPool(wifi.radio)
        # connect to mqtt broker
        self.mqtt_client = MQTT.MQTT(
            broker=secrets["broker"],
            port=secrets["port"],
            socket_pool=pool,
            ssl_context=ssl.create_default_context(),
            )
        # Connect callback handlers to mqtt_client
        self.mqtt_client.on_connect = self._connect_mqtt
        print("Attempting to connect to %s" % self.mqtt_client.broker)
        self.mqtt_client.connect()
        callback_function()
    def take_reading(self):
        sensor_channels = self.sensor.all_channels
        return [ sensor_channels[i] for i in range(8)]
    def send_readings(self,readings):
        if (not self.bConnected):
            raise Exception("Please connect first")
        readingsJson = json.dumps(readings)
        self.mqtt_client.loop()
        self.mqtt_client.publish("PAR/readings",readingsJson)

        print("readings sent!")

