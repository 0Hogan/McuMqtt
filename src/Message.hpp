#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H

#include <cstdint>
#include <cstring>
#include <concepts>
// #include <ArduinoJson.h>

namespace Mqtt
{
    // template<typename msgType>
    // concept HasTopicName = requires {
    //     { msgType::TOPIC_NAME } -> std::convertible_to<const char*>;
    // };

    // template<typename msgType>
    class Message
    {
    public:
        /**
         * \brief Gets the message data packaged and ready for transmission.
         *
         * \return char* A C-string containing the payload.
         *
         * \note The caller is responsible for deallocating the memory.
         *
         * \todo Consider encrypting the payload before returning it.
         *
         */
        virtual const char* getPayload() const = 0;
  
        /**
         * \brief Gets the QoS level for the message.
         *
         * \return uint8_t The QoS level associated with the given message.
         *
         */
        // virtual uint8_t getQos() const = 0;
  
        // static const char* getTopicName() const
        // {
        //     return msgType::TOPIC_NAME;
        // }
  
    protected:
        /**
         * \brief Construct a new Message object
         *
         */
        Message() {};
  
        /**
         * \brief Converts the message to a JSON representation.
         *
         * \note This is a virtual function, so it shouldn't
         *       actually be used directly. The message class is
         *       intended to be a parent class of the actual
         *       messages.
         *
         * \return JsonDocument A JSON representation of the
         *         contents of the Message instance.
         */
        // virtual JsonDocument convertMsgToJson() const = 0;
    };
}

#endif // MQTT_MESSAGE_H