#include "ScreenHandler.hpp"
#include "Mqtt_controller.hpp"
#include "MqttViewer.hpp"

#include "stdio.h"
#include <iostream>
#include <cstdlib>


MqttViewer::MqttViewer()
{
    printf("Constructing Mqtt Viewer Object \n");
    printf("Initializing Mqtt Viewer \n");
   
    m_mqtt_ctrl=new  Mqtt_controller("tcp://127.0.0.1:1883","TestMqttViewer");
    m_scr_handl=new ScreenHandler();
    pthread_create(&thread,nullptr,screen_run,nullptr); 
}
MqttViewer::~MqttViewer()
{
    delete m_mqtt_ctrl;
    delete m_scr_handl;
    pthread_join(thread,nullptr);
    printf("Destroying Mqtt Viewer Obj \n");
}
int main()
{
    MqttViewer m_mqttviewer_obj;
    m_mqttviewer_obj.m_mqtt_ctrl->subscribe("Mqtt_Test1/#",1);
    m_mqttviewer_obj.m_mqtt_ctrl->registermqttcallbacks(m_mqttviewer_obj.m_scr_handl->getmqttclient());
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