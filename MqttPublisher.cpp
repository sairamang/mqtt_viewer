#include "MqttPublisher.hpp"
#include "string.h"


#define QOS         1
#define TIMEOUT     10000L

#include <iostream>

MqttPublisher::MqttPublisher(std::string address,std::string clientid)
{
   
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    
    
    int rc;

    if ((rc = MQTTClient_create(&m_client, address.c_str(), clientid.c_str(),
        MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS)
    {
         std::cout<<"Failed to create client, return code "<<rc;
    }

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_connect(m_client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        std::cout<<"Failed to connect, return code "<<rc;
        
    }

}

void MqttPublisher::publish(std::string topicname,std::string payload)
{
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token; 
    int rc;
    char* char_array = new char[payload.length() + 1];
    strcpy(char_array,payload.c_str()); 
    pubmsg.payload=static_cast<void*>(char_array);
    pubmsg.qos=1;
    pubmsg.retained=0;
    pubmsg.payloadlen=payload.length();

    if ((rc = MQTTClient_publishMessage(m_client,topicname.c_str() , &pubmsg, &token)) != MQTTCLIENT_SUCCESS)
    {
         std::cout<<"Failed to publish message, return code" << rc;
    }

    rc = MQTTClient_waitForCompletion(m_client, token, TIMEOUT);
    
    delete char_array;
}


MqttPublisher::~MqttPublisher()
{
    int rc;
    if ((rc = MQTTClient_disconnect(m_client, 10000)) != MQTTCLIENT_SUCCESS)
    	std::cout<<"Failed to disconnect, return code "<<rc;
    MQTTClient_destroy(&m_client);
}
