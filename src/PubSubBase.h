#ifndef PUB_SUB_BASE_H
#define PUB_SUB_BASE_H

#include <memory>
#include <string>

namespace Mqtt
{
    class PubSubBase
    {
    public:
        std::string getTopicName() const { return m_topicName; }

    protected:
        PubSubBase(const std::string &topicName) : m_topicName(topicName) {}
        PubSubBase(const char* topicName) : m_topicName(topicName) {}

        std::string m_topicName;
    };
}

#endif // PUB_SUB_BASE_H