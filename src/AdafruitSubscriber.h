#ifndef MQTT_ADAFRUIT_SUBSCRIBER_H
#define MQTT_ADAFRUIT_SUBSCRIBER_H

#include <string>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include "Subscriber.h"


namespace Mqtt
{
    /**
     * @brief A wrapper for the Adafruit implementation of an MQTT Subscriber.
     *
     * @tparam msgType The type of message that this class will subscribe to. This message should be a child class of Mqtt::Message.
     *
     * @todo Need to add an unsubscribe method.
     */
    template<typename msgType>
    class AdafruitSubscriber : public Subscriber<msgType>
    {
    public:
        AdafruitSubscriber(Adafruit_MQTT_Client* adafruitClient, const std::string &topicName)
            : Subscriber<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            delete m_adafruitSubscriber;
            m_adafruitSubscriber = new Adafruit_MQTT_Subscribe(m_adafruitClient, topicName.c_str());
        }

        AdafruitSubscriber(std::shared_ptr<Adafruit_MQTT_Client> adafruitClient, const char* topicName)
            : Subscriber<msgType>(topicName), m_adafruitClient(adafruitClient)
        {
            delete m_adafruitSubscriber;
            m_adafruitSubscriber = new Adafruit_MQTT_Subscribe(m_adafruitClient, topicName);
        }

        void subscribe(msgCallback callback) override
        {
            bool wasConnected = false;
            if (m_adafruitClient->connected())
            {
                wasConnected = true;
                m_adafruitClient->disconnect();
            }
            m_adafruitSubscriber->setCallback(callback);
            m_adafruitClient->subscribe(m_adafruitSubscriber);

            if (wasConnected)
            {
                m_adafruitClient->connect();
            }
        }

    private:
        Adafruit_MQTT_Subscribe* m_adafruitSubscriber = nullptr;
        Adafruit_MQTT_Client* m_adafruitClient = nullptr;
    };
}

#endif // MQTT_ADAFRUIT_SUBSCRIBER_H