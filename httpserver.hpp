#pragma once 
#include "httplib.h"
#include "Mqtt_controller.hpp"
#include "Mqtt_client.hpp"
#include <vector>
#include<deque>
extern void* httpserverrun(void*);
extern void* httpserverrunmqtt(void*);
class httpserver
{

    private:
    httplib::Server m_svr;
    Mqtt_client* m_mqtt_client;
    std::deque<mqtt_msg> m_deque_payload;
    int m_msg_count;
    public:
    
    bool m_mqttthread;
    httpserver();
    ~httpserver();
    void start_server();
    Mqtt_client* getmqttclient();
    std::string handlerequest(std::string request_name);
    void runmqttmsghandling();
    void end_server();

};