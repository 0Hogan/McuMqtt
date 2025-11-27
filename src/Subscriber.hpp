#ifndef MQTT_SUBSCRIBER_H
#define MQTT_SUBSCRIBER_H

#include <cstdint>
#include <concepts>

#include "PubSubBase.hpp"

namespace Mqtt
{
    typedef void (*msgCallback)(char *str, uint16_t len);

    template<typename msgType>
    class Subscriber : public PubSubBase<msgType>
    {
    public:
        Subscriber(Client& client) : PubSubBase<MsgType>(client) {}

        void subscribe(msgCallback callback, int qosLevel=1)
        {
            m_client.subscribe(getTopicName(), qosLevel);
            /// \todo Implement callback registration
        }
        /// \todo Would be nice to support lambda function callbacks as well.

        /// \brief Unsubscribes from the topic
        void unsubscribe() { m_client.unsubscribe(getTopicName()); }
        
    private:
        /// \todo Might need to track this per topic? To know when to actually unsubscribe
        ///       from the client, in the case of multiple subscribers to the same topic?
        ///       The slight trick will be in removing the appropriate callback, but we might
        ///       be able to manage that by mapping the subscriber instance to the callback...
        ///       But, then again, we could probably just unsubscribe if we remove the last
        ///       callback, which would eliminate the need to track subscriber instances.
        // static uint16_t numOfSubscriptions = 0; 
    };
}

#endif // MQTT_SUBSCRIBER_H