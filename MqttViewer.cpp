#include "ScreenHandler.hpp"
#include "Mqtt_controller.hpp"
#include "MqttViewer.hpp"
#include "Mqtt_Cloud.hpp"

#include "stdio.h"
#include <iostream>
#include <cstdlib>


MqttViewer::MqttViewer()
{
    printf("Constructing Mqtt Viewer Object \n");
    printf("Initializing Mqtt Viewer \n");
   
    m_mqtt_ctrl=new  Mqtt_controller("tcp://127.0.0.1:1883","mqtt_client");
    m_scr_handl=new ScreenHandler();
    m_web_socket_handler=new websockethandler();
    m_httpserver=new httpserver();
    m_mqttcloudhandler=new mqtt_cloud_handler("mqtt://test.mosquitto.org:1883","sairamang_test_pub");
    pthread_create(&http_run_thread,nullptr,httpserverrunmqtt,nullptr);
    pthread_create(&http_thread,nullptr,httpserverrun,nullptr);
    pthread_create(&thread,nullptr,screen_run,nullptr);
    pthread_create(&mqtt_cloud_thread,nullptr,mqtt_cloud_run,nullptr); 
}
MqttViewer::~MqttViewer()
{
    delete m_httpserver;
    delete m_mqtt_ctrl;
    delete m_scr_handl;
    delete m_web_socket_handler;
    delete m_mqttcloudhandler;
    
    pthread_join(thread,nullptr);
    pthread_join(http_thread,nullptr);
    pthread_join(http_run_thread,nullptr);
    pthread_join(mqtt_cloud_thread,nullptr);
    printf("Destroying Mqtt Viewer Obj \n");
}
int main()
{
    MqttViewer m_mqttviewer_obj;
    m_mqttviewer_obj.m_mqtt_ctrl->subscribe("Mqtt_Test1/#",1);
    m_mqttviewer_obj.m_mqtt_ctrl->registermqttcallbacks(m_mqttviewer_obj.m_scr_handl->getmqttclient());
    m_mqttviewer_obj.m_mqtt_ctrl->registermqttcallbacks(m_mqttviewer_obj.m_httpserver->getmqttclient());
    m_mqttviewer_obj.m_mqtt_ctrl->registermqttcallbacks(m_mqttviewer_obj.m_mqttcloudhandler->getmqttclient());
    char quit_char;
    while(true)
    {
        quit_char=getchar();
        if(quit_char=='q')
        {
            break;
        }
        if(quit_char=='c')
        {
            system("clear");
        }
    };

    m_mqttviewer_obj.m_mqtt_ctrl->deregistermqttcallbacks();

    
    return 0;
}