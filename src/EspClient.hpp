#ifndef MQTT_ESP_CLIENT_H
#define MQTT_ESP_CLIENT_H

#include <mqtt_client.h>
#include <esp_log.h>
#include <queue>

#include "Client.hpp"

static const char* TAG = "Mqtt::EspClient";

namespace Mqtt
{    
    class EspClient : public Client
    {
    public:
        EspClient(const char* brokerAddress, uint16_t brokerPort)
            : m_brokerAddress(brokerAddress), m_brokerPort(brokerPort)
        {
            establishConnection();
            registerEventHandler();
        }

        ~EspClient()
        {
            if (m_client)
            {
                esp_mqtt_client_destroy(m_client);
            }
        }

        bool isConnected() override { return m_client && m_isConnected; }

        void establishConnection() override;
        void registerEventHandler();

        /**
         * \brief Publishes an MQTT message to the specified topic.
         * 
         * \param msg The message to publish (usually a JSON formatted string)
         * \param topic The topic to which the message should be published
         * 
         * \todo To throw or not to throw - that is the question.
         * \todo But also whether to inline or not...
         */
        bool publish(char* msg, char* topic) override
        {
            if (isConnected())
            {
                int qosLevel = 1;
                int retCode = esp_mqtt_client_publish(m_client, topic, msg, 0, qosLevel, 0);
                
                if (retCode < 0)
                    ESP_LOGE(TAG, "Failed to publish message: ", retCode == -2 ? "Outbox full" : "Unknown error");
                else
                    ESP_LOGI(TAG, "Published message to topic %s with msgId %d", topic, retCode);
            }
            else
            {
                ESP_LOGW(TAG, "Cannot publish message, client not connected");
            }
        }

        /**
         * \brief Subscribes to the specified MQTT topic.
         * 
         * \param topic The topic to which to subscribe
         */
        void subscribe(const char* topic, int qosLevel=1) override
        {
            if (isConnected())
            {
                int msgId = esp_mqtt_client_subscribe(m_client, topic, qosLevel);

                if (msgId < 0)
                    ESP_LOGE(TAG, "Failed to subscribe to topic %s: ", topic, msgId == -1 ? "Client not connected" : "Unknown error");
                else
                    ESP_LOGI(TAG, "Subscribed to topic %s with msgId %d", topic, msgId);
            }
            else
            {
                ESP_LOGW(TAG, "Cannot subscribe to topic yet, client not connected. Queueing subscription.");
                esp_mqtt_topic_t topicToSubscribe = {
                    .filter = topic,
                    .qos = qosLevel
                };
                m_topicsToSubscribe.push(topicToSubscribe);
            }
        }

        /**
         * \brief Unsubscribes from the specified MQTT topic.
         * 
         * \param topic The topic from which to unsubscribe
         */
        void unsubscribe(const char* topic) override
        {
            int msgId = esp_mqtt_client_unsubscribe(m_client, topic);
        }

    private:
        void setConnected(bool isConnected) { m_isConnected = isConnected; onConnected();}
        void onConnected() { for (auto topic = m_topicsToSubscribe.front(); !m_topicsToSubscribe.empty(); m_topicsToSubscribe.pop()) esp_mqtt_client_subscribe(m_client, topic.filter, topic.qos); };

        friend void onMqttEventReceived(void *arg, esp_event_base_t base, int32_t eventId, void *eventData);

        std::queue<esp_mqtt_topic_t> m_topicsToSubscribe; ///< Queue of topics to subscribe to upon connection

        const char* m_brokerAddress; ///< The address of the MQTT broker (e.g. "192.168.0.23" or "mqtt.example.com")
        uint16_t m_brokerPort; ///< The port of the MQTT broker (e.g. 1883)
        esp_mqtt_client_handle_t m_client = nullptr; ///< The underlying ESP MQTT client handle
        bool m_isConnected = false; ///< Whether or not the client is currently connected
    };
}

#endif // MQTT_ESP_CLIENT_H