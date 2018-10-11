#! /usr/bin/env python
import paho.mqtt.client as mqtt
import os
import urlparse
import serial
from time import sleep


TOPIC_SET = "ban/set"
TOPIC_STATE = "ban/state"
SERIAL_DEVICE = '/dev/ttyUSB0'

global ser


def send_serial_command(num_command):
    global ser
    if not ser.is_open:
        ser.open()
    ser.write(chr(num_command))
    sleep(1)

# Define event callbacks


def on_connect(client, userdata, flags, rc):
    print("Connected " + str(rc))
    client.subscribe(TOPIC_SET)


def on_message(client, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    if str(msg.payload) == "OPEN":
        send_serial_command(50)
    if str(msg.payload) == "STOP":
        send_serial_command(51)
    if str(msg.payload) == "CLOSE":
        send_serial_command(49)


def main():
    global ser
    mqttHost = os.environ.get("MQTTHOST", "localhost")
    ser = serial.Serial(port=SERIAL_DEVICE,
                        timeout=1,
                        baudrate=9600,
                        rtscts=False,
                        dsrdtr=False)
    mqttc = mqtt.Client()
    mqttc.on_message = on_message
    mqttc.on_connect = on_connect
    mqttc.connect(mqttHost)
    # Start subscribe, with QoS level 0
    mqttc.subscribe(TOPIC_SET, 0)

    # Continue the network loop, exit when an error occurs
    rc = 0
    while rc == 0:
        rc = mqttc.loop()
    print("rc: " + str(rc))


if __name__ == '__main__':
    main()
