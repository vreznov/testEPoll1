#include "ktcpserver1.h"

KTcpServer1::KTcpServer1()
{

}

void KTcpServer1::run()
{
    std::cout << "This is server" << std::endl;
        // socket
        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd == -1) {
            std::cout << "Error: socket" << std::endl;
            return ;
        }

        // bind
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(502);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
            std::cout << "Error: bind " << strerror(errno) << std::endl;
            return ;
        }

        cout << "bind done" << endl;

        // listen
        if(listen(listenfd, 5) == -1) {
            std::cout << "Error: listen" << std::endl;
            return ;
        }

        // accept
        int conn;
        char clientIP[INET_ADDRSTRLEN] = "";
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        bool quit = false;
        while (!quit) {
            std::cout << "...listening" << std::endl;
            conn = accept(listenfd, (struct sockaddr*)&clientAddr, &clientAddrLen);
            if (conn < 0) {
                std::cout << "Error: accept" << std::endl;
                continue;
            }
            inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);
            std::cout << "...connect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;

            char buf[255];
            while (true) {
                memset(buf, 0, sizeof(buf));
                int len = recv(conn, buf, sizeof(buf), 0);
                buf[len] = '\0';
                if (strcmp(buf, "exit") == 0) {
                    std::cout << "...disconnect " << clientIP << ":" << ntohs(clientAddr.sin_port) << std::endl;
                    quit = true;
                    break;
                }
                std::cout << buf << std::endl;
                send(conn, buf, len, 0);
            }

            close(conn);
        }
        close(listenfd);
        return ;
}

void KTcpServer1::stop()
{

}
