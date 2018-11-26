#include "TCPKernel.h"

TCPKernel::TCPKernel()
{
	m_pTcpNet = new TCPNet(this);
}

TCPKernel::~TCPKernel()
{
	if(m_pTcpNet)
	{
		delete m_pTcpNet;
		m_pTcpNet = NULL;
	}
}

BEGIN_PROTOCOL_MAP
	PM(_DEF_PROTOCOL_REGISTER_RS,&TCPKernel::RegisterRs)
	PM(_DEF_PROTOCOL_LOGIN_RS,&TCPKernel::LoginRs)
    PM(_DEF_PROTOCOL_PUBLISH_RS,&TCPKernel::PublishRs)
    //PM(_DEF_PROTOCOL_GETROOMINFO_RS,&TCPKernel::GetRoomInfoRs)
	/*PM(_DEF_PROTOCOL_SETROOMINFO_RQ,&TCPKernel::SetRoomInfoRq)*/
END_PROTOCOL_MAP

/*void TCPKernel::SendFileData(char*szpath,char *szFileName)
{
	FILE *pFile = NULL;
	fopen_s(&pFile,szpath,"rb");
	if(pFile == NULL)
		return;
	fseek(pFile,0,SEEK_END);
	int nFileSize = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	//发送文件信息（文件大小）

	STRU_VIDEOSTREAM_RQ su;
	su.m_nType = _DEF_PROTOCOL_VIDEOSTREAMINFO_RQ;
	WideCharToMultiByte(CP_ACP,0,((CDlgMain*)theApp.m_pMainWnd)->m_username,-1,su.m_szName,sizeof(su.m_szName),0,0);
	strcpy_s(su.m_szStream,sizeof(su.m_szStream),szFileName);
	su.m_nlen = nFileSize;
	SendData((char*)&su,sizeof(su));
	//读文件内容并发送
	while(1)
	{
		su.m_nType = _DEF_PROTOCOL_VIDEOSTREAM_RQ;
		su.m_nlen = fread_s(su.m_szStream,sizeof(su.m_szStream),sizeof(char),sizeof(su.m_szStream),pFile);
		if(su.m_nlen==0)
		{
			break;
		}

		SendData((char*)&su,sizeof(su));

	}

	fclose(pFile);

}*/

/*void TCPKernel::GetRoomInfoRs(char* szbuf)
{
	STRU_GETROOMINFO_RS *psgr = (STRU_GETROOMINFO_RS*)szbuf;
	theApp.m_pMainWnd->SendMessage(UM_ROOMINFOMSG,(WPARAM)&psgr->m_roomid,(LPARAM)psgr->m_szRoomName);
}*/

void TCPKernel::LoginRs(char* szbuf)
{
	STRU_LOGIN_RS *psrr = (STRU_LOGIN_RS*)szbuf;
    if(psrr->m_szResult == _login_usernoexists)
        MsgBox("user no exists");
    else if(psrr->m_szResult == _login_passworderr)
        MsgBox("passworderr");
    else if(psrr->m_szResult == _login_success)
        MsgBox("login success");
}

void TCPKernel::RegisterRs(char* szbuf)
{
	STRU_REGISTER_RS *psrr = (STRU_REGISTER_RS*)szbuf;
    if(psrr->m_szResult == _register_userexists)
        MsgBox("user exists");
    else if(psrr->m_szResult == _register_success)
        MsgBox("register success");
}
void TCPKernel::PublishRs(char* szbuf)
{
    STRU_PUBLISH_RS *pspr = (STRU_PUBLISH_RS*)szbuf;
   /* if(pspr->m_szResult ==_publish_fail)
        MsgBox("publish fail");
    else if(pspr->m_szResult == _publish_success)
        MsgBox("publish success");*/
}

bool TCPKernel::Open()
{
	if(!m_pTcpNet->InitNetWork())
		return false;
	return true;
}

void TCPKernel::Close()
{
	m_pTcpNet->UnInitNetWork();
}

bool TCPKernel::SendData(char* szbuf,int nlen)
{
	if(!m_pTcpNet->SendData(szbuf,nlen))
		return false;
	return true;
}

void TCPKernel::DealData(char* szbuf)
{
	 //处理数据---协议映射表
	PackType *pType = (PackType *)szbuf;
	int i = 0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType ==  *pType)
		{
			(this->*m_ProtocolMapEntries[i].m_pfun)(szbuf);
			break;
		}
		else if(m_ProtocolMapEntries[i].m_nType ==0 || m_ProtocolMapEntries[i].m_pfun ==0)
			break;

		i++;
	}

}
