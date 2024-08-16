#ifndef MQTT_MESSAGE_H
#define MQTT_MESSAGE_H

#include <cstdint>
#include <cstring>
// #include <ArduinoJson.h>

namespace Mqtt
{
  static const size_t MAX_TOPIC_LENGTH = 128; ///< Maximum length that a topic name can use. 128 seems large enough...

  class Message
  {
    public:
      /**
       * @brief Gets the message data packaged and ready for transmission.
       * 
       * @return char* A C-string containing the payload.
       * 
       * @note The caller is responsible for deallocating the memory.
       * 
       * @todo Consider encrypting the payload before returning it.
       * 
       */
      virtual const char* getPayload() const = 0;

      /**
       * @brief Gets the QoS level for the message.
       * 
       * @return uint8_t The QoS level associated with the given message.
       * 
       */
      virtual uint8_t getQos() const = 0;

    protected:
      /**
       * @brief Construct a new Message object
       * 
       */
      Message() {};

      /**
       * @brief Converts the message to a JSON representation.
       * 
       * @note This is a virtual function, so it shouldn't
       *       actually be used directly. The message class is 
       *       intended to be a parent class of the actual 
       *       messages.
       * 
       * @return JsonDocument A JSON representation of the
       *         contents of the Message instance. 
       */
      // virtual JsonDocument convertMsgToJson() const = 0;
  };
}

#endif // MQTT_MESSAGE_H