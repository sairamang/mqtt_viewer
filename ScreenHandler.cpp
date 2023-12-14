#include "ScreenHandler.hpp"
#include <pthread.h>
#include "stdio.h"
#include <cstdlib>
ScreenHandler*  scr_ptr=nullptr;
ScreenHandler::ScreenHandler()
{
    printf("Screen handler Initialization \n");
    scr_ptr=this;   
    initscr();
    raw();
    noecho();	
    getmaxyx(stdscr,m_screen_row,m_screen_col);
    m_local_win=newwin(m_screen_row, m_screen_col,1, 1);		
    printf("Screen rows %d %d \n",m_screen_row,m_screen_col);
    m_mqtt_client = new Mqtt_client();
    m_screen_thread_flag=true;
}
Mqtt_client* ScreenHandler::getmqttclient()
{
    return m_mqtt_client;
}
int count=1;

void ScreenHandler::check_for_reset_and_reset(int row,int col)
{
    if((row>(m_screen_row-10))||(col>(m_screen_col-10)))
    {
        endwin();
        initscr();
        raw();
        noecho();	
        getmaxyx(stdscr,m_screen_row,m_screen_col);
        m_local_win=newwin(m_screen_row, m_screen_col,1, 1);	
        m_topic_row.clear();
        m_topic_col.clear();
        m_col_index=1;
    }
}
void ScreenHandler::calculate_row_col_index(int& row_ind,int& col_ind,std::string topicname)
{
    
    auto col_itr=m_topic_col.find(topicname);
        if(col_itr!=m_topic_col.end())
        {
            col_ind=col_itr->second;
        }
        else 
        {
            m_topic_col.insert(std::pair<std::string,int>(topicname,m_col_index));
            col_ind=m_col_index;
            m_col_index=m_col_index+60;
        } 

        auto row_itr=m_topic_row.find(topicname);
        if(row_itr!=m_topic_row.end())
        {
            row_itr->second=row_itr->second+1;
            row_ind=row_itr->second;
        }
        else 
        {
            m_topic_row.insert(std::pair<std::string,int>(topicname,1));
            row_ind=2;        
        }
}
void ScreenHandler::run_screen()
{
    if(m_mqtt_client->is_new_msg_arrived())
    { 
        check_for_reset_and_reset(m_prev_row,m_prev_col);

        mqtt_msg print_msg;
        m_mqtt_client->get_msg_arrived(print_msg);  
        int row_ind,col_ind;
        calculate_row_col_index(row_ind,col_ind,print_msg.topicname);
        if(row_ind==2)
        {
            mvwprintw(m_local_win,1,col_ind," %s",print_msg.topicname.c_str());   
            mvwprintw(m_local_win,2,col_ind," %s",print_msg.payload.c_str());   
        }
        mvwprintw(m_local_win,row_ind,col_ind," %s ",print_msg.payload.c_str());
        //mvprintw(row_ind,col_ind," %d : %d ",row_ind,col_ind);
        wrefresh(m_local_win);
        m_prev_row=row_ind;
        m_prev_col=col_ind;
    }
}
void* screen_run(void* arg)
{
    printf("Screen:Thread Created Successfully \n");
    while(scr_ptr->m_screen_thread_flag)
    {
        scr_ptr->run_screen();
        usleep(1000); // Run every 10 ms
    };
}
ScreenHandler::~ScreenHandler()
{
    printf("Screen handler Destruction \n");
    endwin();
    m_screen_thread_flag=false;
    delete m_mqtt_client;       
}

