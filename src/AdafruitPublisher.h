#ifndef MQTT_ADAFRUIT_PUBLISHER_H
#define MQTT_ADAFRUIT_PUBLISHER_H

#include <string>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include "Publisher.h"

namespace Mqtt
{
    template<typename msgType>
    class AdafruitPublisher : public Publisher<msgType>
    {
    public:
        AdafruitPublisher(Adafruit_MQTT_Client* adafruitClient, const std::string &topicName)
            : Publisher<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            delete m_adafruitPublisher;
            m_adafruitPublisher = new Adafruit_MQTT_Publish(m_adafruitClient, topicName.c_str());
        }

        AdafruitPublisher(Adafruit_MQTT_Client* adafruitClient, const char* topicName)
            : Publisher<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            delete m_adafruitPublisher;
            m_adafruitPublisher = new Adafruit_MQTT_Publish(adafruitClient, topicName);
        }

        bool publish(const msgType &msg) const override
        {
            uint8_t numTriesRemaining = 3;
            while (!m_adafruitClient->connected() && numTriesRemaining > 0)
            {
                m_adafruitClient->connect();
                numTriesRemaining--;
            }
            return m_adafruitPublisher->publish(msg.getPayload());
        }

    private:
        Adafruit_MQTT_Publish* m_adafruitPublisher = nullptr;
        Adafruit_MQTT_Client* m_adafruitClient = nullptr;
    };
}

#endif // MQTT_ADAFRUIT_PUBLISHER_H