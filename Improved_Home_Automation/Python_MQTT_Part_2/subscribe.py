# Subscribe
import sys
import os
import paho.mqtt.client as paho

broker = "192.168.1.9"
port = 1883

def on_message(mosq, obj, msg):
    pri_str = msg.topic + "   " + msg.payload.decode("utf-8") 
    print(pri_str)
    pass
    
    
mqtt_sub = paho.Client()
mqtt_sub.on_message = on_message
mqtt_sub.connect(broker, port)
mqtt_sub.loop_start()
mqtt_sub.subscribe("#")
#mqtt_sub.subscribe("topic1/something")
#mqtt_sub.subscribe("topic2/something")

while True:
    pass