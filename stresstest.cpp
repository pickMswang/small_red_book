#include <iostream>
#include "TCPNet.h"
using namespace std;

int main()
{
	TCPNet tcpNet[3000];
	int port = 10000;
	//1.选择种类 -- 
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        // printf("WSAStartup failed with error: %d\n", err);
        return false;
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        // printf("Could not find a usable version of Winsock.dll\n");
        for(int i=0;i<1000;i++)
		{
			tcpNet[i].UnInitNetWork();
		}
        return false;
    }

	TCPNet::InitCS();

	for(int i=0;i<2000;i++)
	{
		tcpNet[i].InitNetWork(port);
		port++;
		Sleep(1);
	}
	while(1)
	{
		Sleep(20);
	}

	WSACleanup();
	return 0;
}
