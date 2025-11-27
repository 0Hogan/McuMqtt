#ifndef PUB_SUB_BASE_H
#define PUB_SUB_BASE_H

#include <memory>
#include <string>

#include "Client.hpp"

namespace Mqtt
{
    /// \brief Concept to ensure that msgType has a static TOPIC_NAME (const char*) member.
    template<typename MsgType>
    concept HasTopicName = requires {
        { MsgType::TOPIC_NAME } -> std::convertible_to<const char*>;
    };

    template<typename MsgType>
    class PubSubBase
    {
    public:
        static const char* getTopicName() const { return MsgType::TOPIC_NAME; }

    protected:
        PubSubBase(Client& client) : m_client(client) {}
    
        Client& m_client;
    };
}

#endif // PUB_SUB_BASE_H