#include "Mqtt_client.hpp"

Mqtt_client::Mqtt_client()
{
    printf("Mqtt client initiated \n"); 
    m_flag_msg_arrived=false; 
}
Mqtt_client::~Mqtt_client()
{
    printf("Mqtt client Destroyed \n");   
}
void Mqtt_client::new_msg_arrived(mqtt_msg arrival_msg)
{   
    m_msg=arrival_msg;
    m_flag_msg_arrived=true;
}
void Mqtt_client::get_msg_arrived(mqtt_msg& new_msg )
{
    new_msg=m_msg;
    m_flag_msg_arrived=false;
}
bool Mqtt_client::is_new_msg_arrived()
{
    return m_flag_msg_arrived;
}
