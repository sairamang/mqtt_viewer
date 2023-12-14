#pragma once 
#include<memory>
#include "pthread.h"
class MqttViewer 
{

    private:
    

    protected:

    public:
        pthread_t thread;
        Mqtt_controller* m_mqtt_ctrl;
        ScreenHandler* m_scr_handl;
        MqttViewer();
        ~MqttViewer();

};