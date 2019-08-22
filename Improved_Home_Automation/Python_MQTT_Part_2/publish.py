# Publish
import paho.mqtt.client as paho

broker = "192.168.1.9"
port = 1883

def on_publish(client,userdata,result):
    print("\ndata published \n")
    pass
    
    
mqtt_pub = paho.Client("PubDevice")
mqtt_pub.on_publish = on_publish
mqtt_pub.connect(broker,port)
ret = mqtt_pub.publish("topic","Some data")
