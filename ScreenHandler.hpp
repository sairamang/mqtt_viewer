#pragma once 
#include "Mqtt_controller.hpp"
#include<unistd.h>
#include<ncurses.h>
#include <thread>
#include <map>
extern void* screen_run(void* arg);

class ScreenHandler 
{
    private:
        int m_screen_row;
        int m_screen_col;
        
        Mqtt_client* m_mqtt_client;
        std::map<std::string , int> m_topic_row;
        std::map<std::string , int > m_topic_col;
        int m_col_index=1;
        WINDOW* m_local_win;

        int m_prev_row=1;
        int m_prev_col=1;


    protected:

    public:
        bool m_screen_thread_flag;
        ScreenHandler();
        ~ScreenHandler();
        int initscreen();
        Mqtt_client* getmqttclient();
        void run_screen();
        void check_for_reset_and_reset(int row,int col);
        void calculate_row_col_index(int& row_ind,int& col_ind,std::string topicname);
};