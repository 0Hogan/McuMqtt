#ifndef MQTT_ADAFRUIT_SUBSCRIBER_H
#define MQTT_ADAFRUIT_SUBSCRIBER_H

#include "Subscriber.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <memory>

namespace Mqtt
{
    template<typename msgType>
    class AdafruitSubscriber : public Subscriber<msgType>
    {
    public:
        AdafruitSubscriber(std::shared_ptr<Adafruit_MQTT_Client> adafruitClient, const std::string &topicName)
            : Subscriber<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            m_adafruitSubscriber = Adafruit_MQTT_Subscribe(m_adafruitClient, topicName);
        }

        AdafruitSubscriber(std::shared_ptr<Adafruit_MQTT_Client> adafruitClient, const char* topicName)
            : Subscriber<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            m_adafruitSubscriber = Adafruit_MQTT_Subscribe(m_adafruitClient, topicName);
        }

        void subscribe(msgCallback callback) override
        {
            bool wasConnected = false;
            if (m_adafruitClient->connected())
            {
                wasConnected = true;
                m_adafruitClient->disconnectServer();
            }
            m_adafruitSubscriber.setCallback(callback);
            m_adafruitClient->subscribe(&m_adafruitSubscriber);

            if (wasConnected)
            {
                m_adafruitClient->connectServer();
            }
        }

    private:
        Adafruit_MQTT_Subscribe m_adafruitSubscriber;
        std::shared_ptr<Adafruit_MQTT_Client> m_adafruitClient = nullptr;
    };
}

#endif // MQTT_ADAFRUIT_SUBSCRIBER_H