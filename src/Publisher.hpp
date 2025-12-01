#ifndef MQTT_PUBLISHER_H
#define MQTT_PUBLISHER_H

#include <cstdint>
#include <string>

#include "PubSubBase.hpp"
#include "Client.hpp"

namespace Mqtt
{
    /// \brief Concept to ensure that msgType has a getPayload() method returning const char*.
    template<typename MsgType>
    concept HasGetPayload = requires {
        { MsgType::getPayload() } -> std::convertible_to<const char*>;
    };

    template<typename MsgType>
    class Publisher : public PubSubBase
    {
    public:
        Publisher(Mqtt::Client& client) : PubSubBase(client) {}

        bool publish(const MsgType &msg) const
        {
            uint8_t numTriesRemaining = 3;
            while (!m_client->isConnected() && numTriesRemaining > 0)
            {
                m_client->establishConnection();
                numTriesRemaining--;

                /// \todo Tune the delay time
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
            return m_client->publish(msg.getPayload());
        };
    };
}

#endif // MQTT_PUBLISHER_H