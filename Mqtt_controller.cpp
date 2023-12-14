#include "Mqtt_controller.hpp"

#include<iostream>
#include "stdio.h"
/*Defines */
Mqtt_controller* g_mqtt_ptr;
Mqtt_controller::Mqtt_controller(std::string Address,std::string clientid)
{
    printf("Mqtt Controller started \n");
    g_mqtt_ptr=this;
    init_subscribe(Address,clientid);

}
Mqtt_controller::~Mqtt_controller()
{
    deinit_subscribe();
    g_mqtt_ptr=nullptr;
    printf("Mqtt Controller destroyed \n");
}

void delivered(void *context, MQTTClient_deliveryToken dt)
{
    //pass
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    mqtt_msg msg;
    std::string tmp_1(topicName);
    std::string tmp_2((char*)message->payload);
    msg.topicname=tmp_1;
    msg.payload=tmp_2;
    routemsg(msg);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void routemsg(mqtt_msg msg)
{
    for(auto& ptr:g_mqtt_ptr->m_vec_mqtt_callbacks)
    {
        ptr->new_msg_arrived(msg);
    }
}
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    if (cause)
    	printf("     cause: %s\n", cause);
}

int Mqtt_controller::init_subscribe(std::string address,std::string clientid)
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    printf("Mqtt:Mqtt Client Created \n");
    if ((rc = MQTTClient_create(&m_mqtt_client, address.c_str(), clientid.c_str(),
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to create client, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    printf("Mqtt:Set Callbacks \n");
    if ((rc = MQTTClient_setCallbacks(m_mqtt_client, NULL, connlost, msgarrvd, delivered)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to set callbacks, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    printf("Mqtt:Connection Request \n");
    if ((rc = MQTTClient_connect(m_mqtt_client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        rc = EXIT_FAILURE;
    }
    return rc;
}

int Mqtt_controller::subscribe(std::string topic,int QOS)
{
    printf("Mqtt:Subscription topic : %s \n",topic.c_str());
    int rc;
    if ((rc = MQTTClient_subscribe(m_mqtt_client, topic.c_str(), QOS)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to subscribe, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
    return rc;
}

int Mqtt_controller::deinit_subscribe()
{
    int rc;
    if ((rc = MQTTClient_disconnect(m_mqtt_client, 10000)) != MQTTCLIENT_SUCCESS)
    {
    	printf("Failed to disconnect, return code %d\n", rc);
    	rc = EXIT_FAILURE;
    }
    return rc;
}
int Mqtt_controller::registermqttcallbacks(Mqtt_client* mqtt_ptr)
{
    if(mqtt_ptr!=nullptr)
    {
        m_vec_mqtt_callbacks.push_back(mqtt_ptr);
    }
    return 0;
}
int Mqtt_controller::deregistermqttcallbacks()
{

    m_vec_mqtt_callbacks.clear();
}