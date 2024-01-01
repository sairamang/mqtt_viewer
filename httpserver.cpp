#include "httpserver.hpp"

#include <iostream>
#include<unistd.h>
#include "rapidjson/writer.h"

httpserver* g_httpserver;
void* httpserverrun(void* arg)
{
    g_httpserver->start_server();   
    return nullptr;
}
void httpserver::runmqttmsghandling()
{
    if(g_httpserver->getmqttclient()->is_new_msg_arrived())
    {
        mqtt_msg new_msg;
        m_mqtt_client->get_msg_arrived(new_msg);
        m_deque_payload.push_back(new_msg);
    }
}
void* httpserverrunmqtt(void* arg)
{
    while(g_httpserver->m_mqttthread)
    {
        g_httpserver->runmqttmsghandling();
        usleep(10000);
    };
    return nullptr;
}
httpserver::httpserver()
{
    std::cout<<"Starting http server "<<std::endl;
    g_httpserver=this;
    m_mqttthread=true;
    m_mqtt_client = new Mqtt_client();
    m_msg_count=1;
}
httpserver::~httpserver()
{
    end_server();
    m_mqttthread=false;
    g_httpserver=nullptr;
    delete m_mqtt_client;
    m_mqtt_client=nullptr;
    std::cout<<"Closing http server"<<std::endl;
}
Mqtt_client* httpserver::getmqttclient()
{
    return m_mqtt_client;
}

void httpserver::start_server()
{
    httplib::Headers svr_header={
        {
            "Access-Control-Allow-Origin",
            "*"
        },
        {
            "Access-Control-Allow-Methods",
            "GET, POST, OPTIONS, PUT, PATCH, DELETE"
        },
        {
            "Access-Control-Allow-Headers",
            "X-Requested-With,content-type"
        }};
    m_svr.set_default_headers(svr_header);
    m_svr.Get("/hi", [this](const httplib::Request &, httplib::Response &res) {
    res.set_content(this->handlerequest("/hi").c_str(), "text/plain");
    });
    m_svr.Get("/connect", [this](const httplib::Request &, httplib::Response &res) {
    res.set_content(this->handlerequest("/connect").c_str(), "text/plain");
    });
    m_svr.Get("/mqtt", [this](const httplib::Request &, httplib::Response &res) {
    res.set_content(this->handlerequest("/mqtt").c_str(), "text/plain");
    });
    m_svr.listen("127.0.0.1", 8080);
}
void httpserver::end_server()
{
    m_svr.stop();
}
std::string httpserver::handlerequest(std::string request_name)
{
    std::string rtn_string;
    if(request_name=="/hi")
    {
        rtn_string="Hello World !";
    }
    if(request_name=="/connect")
    {
        rtn_string="success";
    }
    if(request_name=="/mqtt")
    {
        std::string final_payload;
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> r_writer(buffer);

        r_writer.StartObject();
        r_writer.Key("data");
        r_writer.StartArray();
        int no_of_elements=0;
        for(int i=0;i<m_deque_payload.size();i++)
        {
            mqtt_msg m_current_msg=m_deque_payload.front();
            m_deque_payload.pop_front();
            
            r_writer.StartObject();
            r_writer.Key("id");
            r_writer.String(std::to_string(m_msg_count).c_str());
            r_writer.Key("Topicname");
            r_writer.String(m_current_msg.topicname.c_str(),(rapidjson::SizeType)m_current_msg.topicname.size());
            r_writer.Key("Payload");
            r_writer.String(m_current_msg.payload.c_str(),(rapidjson::SizeType)m_current_msg.payload.size());
            r_writer.EndObject();
            no_of_elements++;
            m_msg_count++;
            if(i>5)
            {
                break;
            }
        }
        r_writer.EndArray();
        r_writer.Key("no");
        r_writer.Uint(no_of_elements);
        r_writer.EndObject();
        rtn_string=buffer.GetString();
        printf("Final payload %s \n",rtn_string.c_str());
    }
    return rtn_string;
}