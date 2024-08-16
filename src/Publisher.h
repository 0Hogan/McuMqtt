#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include <cstdint>
#include <string>

#include "Client.h"
#include "PubSubBase.h"

namespace Mqtt
{
    template<typename msgType>
    class Publisher : public PubSubBase
    {
    public:
        virtual bool publish(const msgType &msg) const = 0;
        
    protected:
        Publisher(const std::string &topicName) : PubSubBase(topicName) {}
        Publisher(const char* topicName) : PubSubBase(topicName) {}

    private:
    };
}

#endif // MQTT_PUBLISHER_H