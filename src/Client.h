namespace Mqtt
{
    class Client
    {
    public:
        Client() { establishConnection(); }

        virtual bool isConnected() = 0;
        virtual void establishConnection() = 0;

        virtual void publish(char* msg, char* topic) = 0;
        virtual void subscribe(char* topic) = 0;

    };
}