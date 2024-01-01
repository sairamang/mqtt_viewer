#include "WebSocketHandler.hpp"
#include <iostream>
websockethandler::websockethandler()
{
    std::cout<<"Web Socket Handler started"<<std::endl;
}
websockethandler::~websockethandler()
{
    std::cout<<"Web Socket Handler destroyed"<<std::endl;
}
void websockethandler::connect()
{
    std::cout<<"Connection Initiated"<<std::endl;
}
void websockethandler::disconnect()
{
    std::cout<<"Websocket disconnected"<<std::endl;
}
void websockethandler::sendpayload(std::string payload)
{
    std::cout<<"Sending payload "<<payload<<std::endl;
}
void websockethandler::Onpayloadreceived(std::string payload)
{
    std::cout<<"Received payload "<<payload<<std::endl;
}