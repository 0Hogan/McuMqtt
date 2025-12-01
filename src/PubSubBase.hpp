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
        /// \todo Should the topic name be stored here instead of in the MsgType?
        ///       Probably, since we might have multiple topics per MsgType - e.g.
        ///       /lights/kitchen, /lights/livingroom, etc.(all same MsgType, but
        ///       different instances/endpoints). Introduces issues with memory 
        ///       management for string vs. c-string, but probably fine since there
        ///       won't be a ton of copies. Also will mean that a PubSubBase* can be
        ///       used to track all publishers/subscribers regardless of MsgType.
        static const char* getTopicName() const { return MsgType::TOPIC_NAME; }

    protected:
        PubSubBase(Client& client) : m_client(client) {}
    
        Client& m_client;
    };
}

#endif // PUB_SUB_BASE_H