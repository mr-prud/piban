## Homemade remote controller for my retractable awning

### Schematic

![full schema](/doc/pibanfull.png)

### arduino part

You can find in piban dir the arduino file, the arduino part send radio wave to trigger awning motor.

> with platform.io

### Broker part

For trigger arduino, i use a Raspberry pi 1, it's the gateway between home assistant and the arduino, via mqtt.
