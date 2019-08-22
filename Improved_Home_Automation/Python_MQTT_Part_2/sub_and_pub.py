import sys
import os
import paho.mqtt.client as paho
from datetime import datetime

broker = "192.168.1.9"
port = 1883

def on_publish(client,userdata,result):
    print("data published \n")
    pass


def on_message(mosq, obj, msg):
    pri_str = msg.topic + "   " + msg.payload.decode("utf-8") 
    print(pri_str)
    pass
    
    
mqtt_sub = paho.Client()
mqtt_sub.on_message = on_message
mqtt_sub.connect(broker, port)
mqtt_sub.loop_start()
mqtt_sub.subscribe("#")

OldSec = 0

while True:
    Sec = (datetime.now().second) % 3
    if OldSec != Sec:
        mqtt_pub = paho.Client("PubDevice")
        mqtt_pub.on_publish = on_publish
        mqtt_pub.connect(broker,port)
        ret = mqtt_pub.publish("topic","Seconds from Publish Device : {}\n".format(Sec))
        OldSec = Sec
