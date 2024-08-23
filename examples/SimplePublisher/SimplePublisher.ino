#include "AdafruitPublisher.h"
#include "AdafruitSubscriber.h"
#include "LogMessage.h"

#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>

const uint16_t TIME_BETWEEN_MSGS_S = 5;
const uint16_t MS_PER_S = 1000;

WiFiClient wifiClient;
std::shared_ptr<Adafruit_MQTT_Client> mqttClient =
    std::make_shared<Adafruit_MQTT_Client>(&wifiClient, "192.168.1.64", 1883, "mhogan", "");

Mqtt::AdafruitPublisher<Mqtt::LogMessage> logPublisher(mqttClient, "/logs");

void setup()
{
    mqttClient->connect();
}

uint64_t counter = 0;
void loop()
{
    Mqtt::LogMessage logMsg;
    logMsg.logMsg = "Publishing log message #" + counter++;
    logPublisher.publish(logMsg);
    delay(TIME_BETWEEN_MSGS_S * MS_PER_S);
}