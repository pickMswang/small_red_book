#ifndef _TCPKERNEL_H
#define _TCPKERNEL_H

#include <QMessageBox>
#include <QObject>
#include "IKernel.h"
#include "TCPNet.h"
#include "Packdef.h"

class TCPKernel;
class TCPNet;

typedef void (TCPKernel:: *PFUN)(char*);
struct ProtocolMap
{
    PackType m_nType;
	PFUN     m_pfun;
};

class TCPKernel:public QObject
{
    Q_OBJECT
public:
	TCPKernel();
	virtual ~TCPKernel();

public:
	bool Open();
	void Close();
	void DealData(char* szbuf);
	bool SendData(char* szbuf,int nlen);
    //void SendFileData(char*szpath,char *szFileName);

public:
	void RegisterRs(char* szbuf);
	void LoginRs(char* szbuf);
    void PublishRs(char*szbuf);
//  void GetRoomInfoRs(char* szbuf);
//	void SetRoomInfoRq(SOCKET sock,char* szbuf);

signals:
    void MsgBox(char*);

private:
    TCPNet *m_pTcpNet;
	
};

#endif
