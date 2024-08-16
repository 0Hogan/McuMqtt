#ifndef MQTT_ADAFRUIT_PUBLISHER_H
#define MQTT_ADAFRUIT_PUBLISHER_H

#include "Publisher.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <memory>
#include <string>

namespace Mqtt
{
    template<typename msgType>
    class AdafruitPublisher : public Publisher<msgType>
    {
    public:
        AdafruitPublisher(std::shared_ptr<Adafruit_MQTT_Client> adafruitClient, const std::string &topicName) 
            : Publisher<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            m_adafruitPublisher = Adafruit_MQTT_Publish(m_adafruitClient, topicName);
        }

        AdafruitPublisher(std::shared_ptr<Adafruit_MQTT_Client> adafruitClient, const char* topicName)
            : Publisher<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            m_adafruitPublisher = Adafruit_MQTT_Publish(adafruitClient, topicName);
        }

        bool publish(const msgType &msg) const override
        {
            uint8_t numTriesRemaining = 3;
            while (!m_adafruitClient->connected() && numTriesRemaining > 0)
            {
                m_adafruitClient->connectServer();
                numTriesRemaining--;
            }
            return m_adafruitPublisher.publish(msg.getPayload());
        }

    private:
        Adafruit_MQTT_Publish m_adafruitPublisher;
        std::shared_ptr<Adafruit_MQTT_Client> m_adafruitClient = nullptr;
    };
}

#endif // MQTT_ADAFRUIT_PUBLISHER_H