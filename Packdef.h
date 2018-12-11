//#pragma pack(1)
#ifndef PACKDEF_H
#define PACKDEF_H



#define SERVER_IP   "10.50.66.241"
typedef char   PackType;

#define BEGIN_PROTOCOL_MAP static const ProtocolMap m_ProtocolMapEntries[]= \
{

#define END_PROTOCOL_MAP 	{0,0} \
};

#define PM(X,Y)  {X,Y},

//边界值
#define _DEF_SIZE		     	64
#define _DEF_STREAMSIZE			1024
#define _DEF_SQLLEN             300
#define _DEF_BUFFERNUM          10000


//recv result
#define _register_userexists     0
#define _register_success        1

#define _login_usernoexists      0
#define _login_passworderr       1
#define _login_success           2


#define _publish_success      1
#define _publish_fail         0


//协议
#define _DEF_PROTOCOL_BASE		100

#define _DEF_PROTOCOL_REGISTER_RQ			 _DEF_PROTOCOL_BASE +1//注册请求
#define _DEF_PROTOCOL_REGISTER_RS			 _DEF_PROTOCOL_BASE +2

#define _DEF_PROTOCOL_LOGIN_RQ				 _DEF_PROTOCOL_BASE +3//登录请求
#define _DEF_PROTOCOL_LOGIN_RS				 _DEF_PROTOCOL_BASE +4

#define _DEF_PROTOCOL_PUBLISH_RQ             _DEF_PROTOCOL_BASE +5//发布请求

#define _DEF_PROTOCOL_PUBLISH_RS             _DEF_PROTOCOL_BASE +6//发布回复

//Package Head
struct STRU_HEADER
{
    int pac_size;
};

//协议包
struct STRU_REGISTER_RQ
{
     PackType m_nType;
     char m_szAccount[_DEF_SIZE];
     char m_szPassword[_DEF_SIZE];
};

typedef  struct STRU_REGISTER_RS
{
     PackType m_nType;
     char m_szAccount[_DEF_SIZE];
     char m_szResult;
}STRU_LOGIN_RS;

struct STRU_LOGIN_RQ
{
     PackType m_nType;
     char m_szAccount[_DEF_SIZE];
     char m_szPassword[_DEF_SIZE];

};

//发布请求
struct STRU_PUBLISH_RQ
{
     PackType m_nType;
     int length;
     char m_szSTREAM[_DEF_STREAMSIZE]; //message
};

//发布回复
struct STRU_PUBLISH_RS
{
     PackType m_nType;
   //  char m_szAccount[_DEF_SIZE];
     char m_szResult;
};

#endif // PACKDEF_H
