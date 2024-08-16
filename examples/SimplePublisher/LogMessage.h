#ifndef MQTT_LOG_MESSAGE_H
#define MQTT_LOG_MESSAGE_H

#include "Message.h"

namespace Mqtt
{
    class LogMessage : public Message
    {
    public:
        std::string logMsg;

        const char* getPayload() const override
        {
            std::string payload = "{logMsg:\"" + logMsg + "\"}";
            return payload.c_str();
        }

        uint8_t getQos() const override
        {
            return QOS;
        }

        static const uint8_t QOS = 0;
    };
}

#endif // MQTT_LOG_MESSAGE_H