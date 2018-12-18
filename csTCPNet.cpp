#include "TCPNet.h"

int TCPNet::con = 0;
CRITICAL_SECTION g_CS;

bool TCPNet::InitNetWork(int port)
{   
	//2.雇佣店长 -- socket 
	sockClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sockClient == INVALID_SOCKET )
	{
		UnInitNetWork();
		 return false;
	}

	//3.client选址 --- 
	sockaddr_in  addrClient;
	addrClient.sin_family = AF_INET;
	addrClient.sin_addr.S_un.S_addr = inet_addr("10.51.92.106");
	addrClient.sin_port = htons(port);
	if(SOCKET_ERROR == bind(sockClient,(const sockaddr*)&addrClient,sizeof(addrClient)))
	{
		 UnInitNetWork();
		 return false;
	}

	//5.创建线程
	m_hThreadCon = (HANDLE)_beginthreadex(NULL,0,&ThreadCon,this,0,0);
	
	return true;
}

void TCPNet::UnInitNetWork()
{
	if(m_hThreadCon)
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadCon,100))
			TerminateThread(m_hThreadCon,-1);
		
		CloseHandle(m_hThreadCon);
		m_hThreadCon = NULL;
	}
	if(sockClient)
	{
		closesocket(sockClient);
		sockClient = NULL;
	}
	cout<<"出错啦"<<endl;
}

unsigned _stdcall TCPNet::ThreadCon( void * lpvoid)
{
	TCPNet* pthis  = (TCPNet*)lpvoid;
	//4.server选址 --- 
	sockaddr_in  addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = inet_addr("10.51.39.54");
	addrServer.sin_port = htons(8000);
	if(SOCKET_ERROR == connect(pthis->sockClient,(const sockaddr*)&addrServer,sizeof(addrServer)))
	{
		pthis->UnInitNetWork();
	}
	EnterCriticalSection(&g_CS);
	cout<<con++<<endl;
	LeaveCriticalSection(&g_CS);
	while(1)
	{
		Sleep(30);
	}
	return 0;
}

void TCPNet::InitCS()
{
	InitializeCriticalSection(&g_CS);
}
