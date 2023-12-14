#pragma once
#include<string>
struct mqtt_msg 
{
    std::string topicname;
    std::string payload;
};
class Mqtt_client 
{
    private:
        mqtt_msg m_msg;
        bool m_flag_msg_arrived;
    public:
        Mqtt_client();
        ~Mqtt_client();
        void new_msg_arrived(mqtt_msg arrival_msg);
        bool is_new_msg_arrived();
        void get_msg_arrived(mqtt_msg& msg);
};