import wifi
import socketpool
import adafruit_minimqtt.adafruit_minimqtt as MQTT
import ssl

class PAR:
    def __init__(self):
        pass
    def _connect_mqtt(self):
        # This function will be called when the mqtt_client is connected
        # successfully to the broker.
        print("Connected to MQTT Broker!")
        print("Flags: {0}\n RC: {1}".format(flags, rc))      
    def connect(self):
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
        # connect to mqtt broker
        # Create a socket pool
        mqtt_client = MQTT.MQTT(
            broker=secrets["broker"],
            port=secrets["port"],
            socket_pool=pool,
            ssl_context=ssl.create_default_context(),
            )
        # Connect callback handlers to mqtt_client
        mqtt_client.on_connect = _connect_mqtt
        print("Attempting to connect to %s" % mqtt_client.broker)
        mqtt_client.connect()

