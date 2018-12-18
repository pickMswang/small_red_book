#ifndef  _TCPNET_H
#define _TCPNET_H

#include <iostream>
#include <process.h>
#include <Winsock2.h>
#pragma comment(lib,"Ws2_32.lib")

using namespace std;

class TCPNet
{
public :
	TCPNet(){}
	~TCPNet()
	{
		UnInitNetWork();
	}
public:
	bool InitNetWork(int port);
	void UnInitNetWork();
	//bool SendData(char* szbuf,int nlen);
public:
	static  unsigned _stdcall ThreadCon( void * );
	static void InitCS();
private:
	SOCKET sockClient;
	HANDLE m_hThreadCon;
	static int con;
};


#endif
