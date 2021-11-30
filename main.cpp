#include <iostream>
#include <string>
#include <string.h>

#include "ktcpclient1.h"
#include "ktcpserver1.h"

// 参考
//https://blog.csdn.net/yusiguyuan/article/details/15027821

using namespace std;

int main(int argc, char ** argv)
{
    cout << "Hello World!" << endl;

    if(argc != 2) {
        cout << "input param s:server  c:client" << endl;
        return -1;
    }

    if(strcmp(argv[1], "s") == 0) {
        KTcpServer1 srv;
        srv.run();
    }
    else if (strcmp(argv[1], "c") == 0) {
        KTcpClient1 clt;
        clt.run();
    }

    return 0;
}
