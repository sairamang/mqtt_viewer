#pragma once
#include "Mqtt_client.hpp"
#include "MqttPublisher.hpp"
extern  void* mqtt_cloud_run(void* );
class mqtt_cloud_handler
{

private:

Mqtt_client* m_mqtt_client;
std::string m_address;
std::string m_clientid;
MqttPublisher* m_mqttpublisher;

public:
bool m_thread;
mqtt_cloud_handler(std::string Address, std::string clientid);
~mqtt_cloud_handler();
void startthread();
void connecttocloud();
void stopthread();
void run();
void uploadtocloud();
Mqtt_client* getmqttclient();

};