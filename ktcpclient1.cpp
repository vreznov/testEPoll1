#include "ktcpclient1.h"

KTcpClient1::KTcpClient1()
{

}

int KTcpClient1::init()
{
}

int KTcpClient1::sendMsg()
{

}

int KTcpClient1::connect2Host(const string &f_target)
{
    if(m_socketId) { disconnectFromHost(); }

    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.s_addr = inet_addr(f_target.c_str());
    m_serverAddr.sin_port = htons(502);

    errno = 0;
    m_socketId = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socketId == -1) {
        cout << "open socket error: " << strerror(errno) << endl;
        return -1;
    }

    //连接到服务器
    if(connect(m_socketId, (struct sockaddr*)&m_serverAddr, sizeof (m_serverAddr)) < 0) {
        cout << "connect socket error: " << strerror(errno) << endl;
        return -1;
    }

    //创建EPOLL
    if((m_epId = epoll_create(MAXSIZE)) < 0) {
        cout << "poll create error: " << strerror(errno) << endl;
        return -1;
    }

    ev.events = EPOLLIN;
    ev.data.fd = m_socketId;
    if(epoll_ctl(m_epId, EPOLL_CTL_ADD, m_socketId, &ev) < 0)
    {
        printf("epoll_ctl Error: %s (errno: %d)\n", strerror(errno), errno);
        return -1;
    }


    m_connected = true;

    return 1;
}

void KTcpClient1::disconnectFromHost()
{
    close(m_socketId);
    close(m_epId);
    m_connected = false;
}

void KTcpClient1::testSend()
{
    if(!m_connected) {
        cout << __func__ << "error, not connectted" << endl;
    }

    string sinfo;
    sinfo.append("hello, i'm client ");

    int i=0;

    while (i++ < 10) {
        int sendNum = send(m_socketId, sinfo.c_str(), sinfo.length(), 0);
        cout << "send num: " << sendNum << endl;

        this_thread::sleep_for(chrono::milliseconds(500));

        //接收信息
//        char rbuf[512] = {};
//        int recvNum = recv(m_socketId, rbuf, 512, 0);
//        cout << "recv: " << rbuf << endl;

        //检测poll事件
        int ncounts;
        if((ncounts = epoll_wait(m_epId, events, MAXSIZE, -1)) < 0) {
            cout << "poll wait error: " << strerror(errno) << endl;
        }
        else if(ncounts == 0) {
            cout << "no trig" << endl;
        }
        else {
            for(int i=0; i<ncounts; i++) {
                int fid = events[i].data.fd;
                char rbuf[512] = {};
                int rcvCount = recv(fid, rbuf, 512, 0);
                cout << "recv: " << rbuf << endl;
            }
        }
    }

    sinfo = "exit";
    send(m_socketId, sinfo.c_str(), sinfo.length(), 0);
}

void KTcpClient1::run()
{
    int res = connect2Host("127.0.0.1");
    if(res < 0) {
        cout << "connect2Host error, quit";
        return;
    }
    testSend();
    cout << "client done, quit" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    disconnectFromHost();
}
