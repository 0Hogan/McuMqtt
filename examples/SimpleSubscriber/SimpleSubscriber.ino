#include "AdafruitPublisher.h"
#include "AdafruitSubscriber.h"
#include "LogMessage.h"

#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>

const uint16_t TIMEOUT_S = 5;
const uint16_t MS_PER_S = 1000;

WiFiClient wifiClient;
std::shared_ptr<Adafruit_MQTT_Client> mqttClient =
    std::make_shared<Adafruit_MQTT_Client>(&wifiClient, "192.168.1.64", 1883, "mhogan", "");

Mqtt::AdafruitSubscriber<Mqtt::LogMessage> logSubscriber(mqttClient, "/logs");

void checkSubscriptions()
{
    mqttClient->processPackets(TIMEOUT_S * MS_PER_S);
}

void logMsgCallback(char* buffer, uint16_t size)
{
    Mqtt::LogMessage logMsg(buffer, size);
    Serial.printf("I heard \"%s\"!", logMsg.logMsg);
}

void setup()
{
    Serial.begin(115200);
    logSubscriber.subscribe(logMsgCallback);
    mqttClient->connect();
}

void loop()
{
    checkSubscriptions();
}