#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "MQTTClient.h"

class MqttPublisher
{

private:
    std::string m_address;
    std::string m_clientid;
    MQTTClient m_client;

public:
  MqttPublisher(std::string address,std::string clientid);
  ~MqttPublisher();
  void publish(std::string topic,std::string payload);



};