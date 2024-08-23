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
        PubSubBase(const std::string &topicName) : m_topicName(topicName.c_str()) {}
        PubSubBase(const char* topicName) : m_topicName(topicName) {}

        const char* m_topicName = nullptr;
    };
}

#endif // PUB_SUB_BASE_H