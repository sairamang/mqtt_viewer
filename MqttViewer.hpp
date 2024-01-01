#pragma once 
#include<memory>
#include "pthread.h"
#include "WebSocketHandler.hpp"
#include "httpserver.hpp"
class MqttViewer 
{

    private:
    

    protected:

    public:
        pthread_t thread;
        pthread_t http_thread;
        pthread_t http_run_thread;
        Mqtt_controller* m_mqtt_ctrl;
        ScreenHandler* m_scr_handl;
        websockethandler* m_web_socket_handler;
        httpserver* m_httpserver;
        MqttViewer();
        ~MqttViewer();

};