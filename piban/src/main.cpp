#include <Arduino.h>

#define LONG_DELAY_US 702
#define SHORT_DELAY_US 317
#define REPEAT_DELAY_MS 8
#define REPEAT_NUM 2
#define START_DELAY_US 4535
#define START_DELAY_BEFORE_US 1500

#define RF433MHZ_PIN 3
#define MILIEU 0
#define HAUT 1
#define BAS 2

//Static array from wave analysis
byte enterban[] =   {0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1};
byte getoutban[] =  {0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,0,1,1,0,0,1,1};
byte stopban[]=    {0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0,1};

void setup() 
{
    pinMode(RF433MHZ_PIN, OUTPUT);
    Serial.begin(9600);
}

//Send a single bit
void sendBit(byte b) 
{
    if (b == 1) {
        digitalWrite(RF433MHZ_PIN, HIGH);
        delayMicroseconds(LONG_DELAY_US);
        digitalWrite(RF433MHZ_PIN, LOW);
        delayMicroseconds(SHORT_DELAY_US);
    }
    else 
    {
        digitalWrite(RF433MHZ_PIN, HIGH);
        delayMicroseconds(SHORT_DELAY_US);
        digitalWrite(RF433MHZ_PIN, LOW);
        delayMicroseconds(LONG_DELAY_US);
    }
}

//send bits sequence
void sendSequence(byte* bouton) 
{
    for (byte i = 0; i < 40; i++)
    {
        sendBit(bouton[i]);
    }
}

// start : initial wave
void start()
{
    digitalWrite(RF433MHZ_PIN, HIGH);
    delayMicroseconds(START_DELAY_US);
    digitalWrite(RF433MHZ_PIN, LOW);
    delayMicroseconds(START_DELAY_BEFORE_US);
}

// sendRemote : play button sequence
void sendRemote(byte* bouton)
{
  start();
  sendSequence(bouton);
  start();
  sendSequence(bouton);
}


void loop() 
{
  int message;
if (Serial.available())  {
    message = Serial.read();
   
    switch (message) {
    case 49:
      sendRemote(enterban);
      break;
    case 50:
      sendRemote(getoutban);
      break;
    case 51:
      sendRemote(stopban);
      break;
    }
}
}

