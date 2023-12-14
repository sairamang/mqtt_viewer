#pragma once 
/*Mqtt Headers*/

#include "MQTTClient.h"


#include "string.h"
#include <string>
#include <vector>

#include "Mqtt_client.hpp"
extern void routemsg(mqtt_msg msg);
class Mqtt_controller 
{
    private:

    MQTTClient m_mqtt_client;

    void routemsg(mqtt_msg msg);
    
    

    protected:

    public:
        std::vector<Mqtt_client*> m_vec_mqtt_callbacks;
        Mqtt_controller()=default;
        Mqtt_controller(std::string Address,std::string clientid);
        ~Mqtt_controller();
        int init_subscribe(std::string Address,std::string clientid);    
        int deinit_subscribe();
        int subscribe(std::string topic,int QOS); 
        int registermqttcallbacks(Mqtt_client* mqtt_ptr);  
        int deregistermqttcallbacks();         
};

