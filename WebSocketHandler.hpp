#pragma once
#include <string>
class websockethandler
{
    private:
        std::string payload;
        bool m_connection_status;
        
    public:
        websockethandler();
        ~websockethandler();
        void connect();
        void disconnect();
        void sendpayload(std::string payload);
        void Onpayloadreceived(std::string payload);
};