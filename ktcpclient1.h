#ifndef KTCPCLIENT1_H
#define KTCPCLIENT1_H

/* epoll学习测试
 *
 *
 *
 *
 * */

#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <string.h>
#include <cerrno>
#include <chrono>
#include <string>
#include <sys/epoll.h>  //epoll

using namespace std;

#define MAXSIZE 10

class KTcpClient1
{
public:
    KTcpClient1();

    int init();  //初始化socket
    int m_socketId = 0;
    int m_epId = 0;

    //=========客户端使用
    bool m_connected = false;  //客户端已连接
    int sendMsg();
    int connect2Host(const string &f_target);
    void disconnectFromHost();
    void testSend();  //测试发送并接收

    void run();

    struct epoll_event ev, events[MAXSIZE];

private:
    struct sockaddr_in m_serverAddr;  //服务器地址
};

#endif // KTCPCLIENT1_H
