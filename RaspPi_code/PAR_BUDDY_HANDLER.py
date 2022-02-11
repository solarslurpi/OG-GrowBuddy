import logging
import sys
import json
import os

import paho.mqtt.client as mqtt
_SEND_READING = "PAR/READING"
_READING_MADE_IT = "PAR/READING_OK"
# 
#  Set up logging to go to journalctl.
# 
logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s:%(levelname)s:%(message)s')
handler = logging.StreamHandler(stream=sys.stdout)
handler.setFormatter(formatter)
logger.addHandler(handler)

# 
#  Set up mosquitto sub.
client_name='PARbuddy'
sub_name= _SEND_READING
serverAddress = 'growbuddy'
mqttClient = mqtt.Client(client_name)
# 
# 
# def on_log(client,userdata,level,buf):
#     logger.debug('log: '+buf)
# 
# 
def on_connect(client, userdata, flags, rc):
    logger.debug("subscribing")
    mqttClient.subscribe(sub_name)
    logger.debug("subscribed")
# 
# 
def on_message(client, userdata, msg):
    message = msg.payload.decode(encoding='UTF-8')
    try:
        reading = json.loads(message)
        directory = os.path.dirname(__file__)
        os.chdir(directory)
        logger.debug(f'Current working directory: {os.getcwd()} directory of python file: {directory}')
        logger.debug(f' Channel reading: {reading}.  The data type: {type(reading)}')
        # We should have been sent a list of PPFD from mq-500 and 8 channel readings from AS7341
        print(f'length of reading list: {len(reading)}')
        if isinstance(reading,list) and len(reading) == 9:
            logger.debug('we are sending a reading made it mqtt message.')

            # Store message in a csv file.
            with open('readings.csv','a') as f:
                if(os.stat('readings.csv').st_size == 0) :
                    f.write("PPFD,415,445,480,515,555,590,630,680\n")
                logger.debug('writing to readings.csv')
                # Remove [ and ]
                m = (message.translate({ord(i): None for i in '[]'}))
                f.write(m+"\n")
        # Send back that we got the message.
        mqttClient.publish(_READING_MADE_IT,message)

    except:
        logger.debug("error")

        
  

# # 
# 
# Set up calling functions to mqttClient
logger.debug('starting up!')
mqttClient.on_connect = on_connect
mqttClient.on_message = on_message
# mqttClient.on_log = on_log

# Connect to the MQTT server & loop forever.
# CTRL-C will stop the program from running.

mqttClient.connect(serverAddress)
mqttClient.loop_forever()
