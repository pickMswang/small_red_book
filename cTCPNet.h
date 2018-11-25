#ifndef  _TCPNET_H
#define _TCPNET_H


#include <process.h>
#include "INet.h"
#include "IKernel.h"
#include "Packdef.h"
#include "thread.h"
#define _DEFPORT    1234
//#define _DEFSIZE     1024

class RecvThread;
class TCPKernel;

class TCPNet :public INet
{
public:
    TCPNet(TCPKernel *pKernel);
	virtual ~TCPNet();
public:
	bool InitNetWork();
	void UnInitNetWork();
	bool SendData(char* szbuf,int nlen);
    //static  unsigned ThreadRecv( void * );
public:
	SOCKET m_sockClient;
    //static bool   m_bFlagQuit;
    TCPKernel *m_pKernel;
    RecvThread* recvThread;
};





#endif
