namespace Mqtt
{
    class Client
    {
    public:
        Client() {}

        virtual bool isConnected() = 0;
        virtual void establishConnection() = 0;

        virtual bool publish(char* msg, char* topic) = 0;
        virtual void subscribe(const char* topic, int qosLevel=1) = 0;
        virtual void unsubscribe(const char* topic) = 0;
    };
}