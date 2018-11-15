#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Wire.h>

#include "main.h"

// #define MILIEU 0
// #define HAUT 1
// #define BAS 2

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
    Serial.begin(115200);

    delay(10);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected");

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    pinMode(RF433MHZ_PIN, OUTPUT);
}

//Send a single bit
void sendBit(byte b)
{
    if (b == 1)
    {
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
void sendSequence(const byte *bouton)
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
void sendRemote(const byte *bouton)
{
    start();
    sendSequence(bouton);
    start();
    sendSequence(bouton);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }

    client.loop();
    yield();
    //   int message;
    // if (Serial.available())  {
    //     message = Serial.read();

    //     switch (message) {
    //     case 49:
    //       sendRemote(enterban);
    //       break;
    //     case 50:
    //       sendRemote(getoutban);
    //       break;
    //     case 51:
    //       sendRemote(stopban);
    //       break;
    //     }
    // }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    if (!strcmp((char *)topic, BANTOPIC))
    {
        if (!strncmp((char *)payload, "OPEN", length))
        {
            Serial.print("J'OUVRE");

            sendRemote(getoutban);
        }
        else if (!strncmp((char *)payload, "STOP", length))
        {
            Serial.print("JE STOP");

            sendRemote(stopban);
        }
        else if (!strncmp((char *)payload, "CLOSE", length))
        {
            Serial.print("JE FERME");

            sendRemote(enterban);
        }
    }

    Serial.println();
}

void reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect("ESP8266 piban"))
        {
            Serial.println("connected");
            client.subscribe(BANTOPIC);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}
