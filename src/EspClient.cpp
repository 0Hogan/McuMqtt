#include "EspClient.hpp"

const char TAG[] = "Mqtt::EspClient";

void Mqtt::onMqttEventReceived(void *arg, esp_event_base_t base, int32_t eventId, void *eventData)
{
    if (!arg)
    {
        /// \todo Need to throw an error here.
        ESP_LOGE("MqttClient", "Event handler received null argument");
        return;
    }

    Mqtt::EspClient& espClient = *static_cast<Mqtt::EspClient*>(arg);
    switch (eventId)
    {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "Event MQTT_EVENT_CONNECTED");
            espClient.setConnected(true);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "Event MQTT_EVENT_DISCONNECTED");
            espClient.setConnected(false);
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "Event MQTT_EVENT_SUBSCRIBED");
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "Event MQTT_EVENT_UNSUBSCRIBED");
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGV(TAG, "Event MQTT_EVENT_PUBLISHED");
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGV(TAG, "Event MQTT_EVENT_DATA");
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGE(TAG, "Event MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGW(TAG, "Unknown event received: %d", eventId);
    }
}

void Mqtt::EspClient::establishConnection()
{
    if (m_client == nullptr)
    {
        esp_mqtt_client_config_t clientConfig = {
            .broker = {
                .address = {
                    .uri = nullptr,
                    .hostname = m_brokerAddress,
                    .transport = MQTT_TRANSPORT_OVER_TCP,
                    .path = nullptr,
                    .port = m_brokerPort
                },
                .verification = {
                    .use_global_ca_store = false,
                    .crt_bundle_attach = nullptr,
                    .certificate = nullptr,
                    .certificate_len = 0,
                    .psk_hint_key = nullptr,
                    .skip_cert_common_name_check = false,
                    .alpn_protos = nullptr,
                    .common_name = nullptr,
                }
            },
            .credentials = {
                .username = nullptr,
                .client_id = nullptr,
                .set_null_client_id = false,
                .authentication = {
                    .password = nullptr,
                    .certificate = nullptr,
                    .certificate_len = 0,
                    .key = nullptr,
                    .key_len = 0,
                    .key_password = nullptr,
                    .key_password_len = 0,
                    .use_secure_element = false,
                    .ds_data = nullptr
                }
            },
            .session = {
                .last_will = {
                    .topic = nullptr,
                    .msg = nullptr,
                    .msg_len = 0,
                    .qos = 0,
                    .retain = 0
                },
                .disable_clean_session = false,
                .keepalive = 120,
                .disable_keepalive = false,
                .protocol_ver = MQTT_PROTOCOL_V_3_1_1,
                .message_retransmit_timeout = 2000
            },
            .network = {
                .reconnect_timeout_ms = 10000,
                .timeout_ms = 10000,
                .refresh_connection_after_ms = 0,
                .disable_auto_reconnect = false,
                .transport = nullptr,
                .if_name = nullptr
            },
            .task = {
                .priority = 5,
                .stack_size = 4096
            },
            .buffer = {
                .size = 1024,
                .out_size = 0
            },
            .outbox = {
                .limit = 0
            }
        };

        m_client = esp_mqtt_client_init(&clientConfig);
    }

    esp_mqtt_client_start(m_client);
}

void Mqtt::EspClient::registerEventHandler()
{
    esp_mqtt_client_register_event(m_client, static_cast<esp_mqtt_event_id_t>(ESP_EVENT_ANY_ID), onMqttEventReceived, NULL);
}