#ifndef _PACKDEF_H
#define _PACKDEF_H

#define SERVER_IP "10.51.39.54"
typedef char PackType;  
                       //static 不受作用域的限制
#define BEGIN_PROTOCOL_MAP static const ProtocolMap m_ProtocolMapEntries[]=\
{

#define END_PROTOCOL_MAP {0,0}\
};

#define PM(X,Y) {X,Y},

//边界值
#define _DEF_SIZE 64
#define _DEF_SQLLEN 300
#define _DEF_STREAMSIZE 2048

#define _register_accountexists 0
#define _register_success 1

#define _login_accountnoexists 0
#define _login_passworderr 1
#define _login_success 2

#define _publish_success 1
#define _publish_fail 0
//协议
#define _DEF_PROTOCOL_BASE 100
#define _DEF_PROTOCOL_REGISTER_RQ  _DEF_PROTOCOL_BASE+1
#define _DEF_PROTOCOL_REGISTER_RS  _DEF_PROTOCOL_BASE+2 
#define _DEF_PROTOCOL_LOGIN_RQ     _DEF_PROTOCOL_BASE+3
#define _DEF_PROTOCOL_LOGIN_RS     _DEF_PROTOCOL_BASE+4
#define _DEF_PROTOCOL_PUBLISH_RQ   _DEF_PROTOCOL_BASE+5
#define _DEF_PROTOCOLPUBLISH_RS    _DEF_PROTOCOL_BASE+6

//协议包
//注册
typedef struct STRU_REGISTER_RQ
{
	PackType m_Type;
	char m_szAccount[_DEF_SIZE];
	char m_szPassword[_DEF_SIZE];

}STRU_LOGIN_RQ;

typedef struct STRU_REGISTER_RS
{
 PackType m_Type;
 char m_szAccount[_DEF_SIZE];
 char m_szResult;
}STRU_LOGIN_RS;

//发布
//发布请求
struct STRU_PUBLISH_RQ
{
 PackType m_nType;
 int length;
 char m_szSTREAM[_DEF_STREAMSIZE]; //message
 int fin;
};

//发布回复
struct STRU_PUBLISH_RS
{
 PackType m_nType;
		    //  char m_szAccount[_DEF_SIZE];
 char m_szResult;
};







#endif
