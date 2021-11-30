#ifndef KTCPSERVER1_H
#define KTCPSERVER1_H

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


using namespace std;

class KTcpServer1
{
public:
    KTcpServer1();

    int m_socketId = 0;

    //! 开始监听
    void run();

    //! 停止监听
    void stop();
};

#endif // KTCPSERVER1_H
