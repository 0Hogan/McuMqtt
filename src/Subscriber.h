#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H

#include <cstdint>

#include "PubSubBase.h"

namespace Mqtt
{
    typedef void (*msgCallback)(char *str, uint16_t len);

    template<typename msgType>
    class Subscriber : public PubSubBase
    {
    public:
        virtual void subscribe(msgCallback callback) = 0;

    protected:
        Subscriber(const std::string &topicName) : PubSubBase(topicName) {}
        Subscriber(const char* topicName) : PubSubBase(topicName) {}
    };
}

#endif // MQTT_SUBSCRIBER_H