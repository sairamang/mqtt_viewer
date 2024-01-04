#include "Mqtt_Cloud.hpp"
#include "unistd.h"
#include "MqttPublisher.hpp"
mqtt_cloud_handler* g_mqtt_cloud_handler;
mqtt_cloud_handler::mqtt_cloud_handler(std::string Address,std::string clientname)
{
    m_address=Address;
    m_clientid=clientname;
    m_thread=true;
    g_mqtt_cloud_handler=this;
    m_mqtt_client=new Mqtt_client();
    m_mqttpublisher=new MqttPublisher(Address,clientname);

}
mqtt_cloud_handler::~mqtt_cloud_handler()
{
    m_thread=false;

    delete m_mqtt_client;
    delete m_mqttpublisher;
    g_mqtt_cloud_handler=nullptr;

}
Mqtt_client* mqtt_cloud_handler::getmqttclient()
{
    return m_mqtt_client;
}
void* mqtt_cloud_run(void*)
{
    while(g_mqtt_cloud_handler->m_thread)
    {   
        g_mqtt_cloud_handler->run();
        usleep(10000);
    }
}
void mqtt_cloud_handler::run()
{
    if(m_mqtt_client->is_new_msg_arrived())
    {
        mqtt_msg new_msg;
        m_mqtt_client->get_msg_arrived(new_msg);
        new_msg.topicname="sairamang/"+new_msg.topicname;

        m_mqttpublisher->publish(new_msg.topicname,new_msg.payload);
    }
}
