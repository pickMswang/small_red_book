#include "login.h"
#include "ui_login.h"

Login::Login(TCPKernel* pKernel,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    tcpKernel = pKernel;
    connect(tcpKernel,SIGNAL(MsgBox(char*)),this,SLOT(ShowMsg(char*)));
    ui->setupUi(this);
}

/*void Login::InitKernel(TCPKernel *pKernel)
{
    tcpKernel = pKernel;
}*/

Login::~Login()
{
    delete ui;
}
//转到主页 (登录)
void Login::on_login_button_clicked()
{
    QString account = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    STRU_LOGIN_RQ srr;
    srr.m_nType = _DEF_PROTOCOL_LOGIN_RQ;
    sprintf(srr.m_szAccount,account.toStdString().c_str());
    sprintf(srr.m_szPassword,password.toStdString().c_str());
    //先发数据包头
    STRU_HEADER shead;
    shead.pac_size = sizeof(STRU_LOGIN_RQ);
    while(tcpKernel->SendData((char *)&shead,sizeof(STRU_HEADER)) == -1)
    {
        Sleep(50);
    }
    //发实际数据包
    while(tcpKernel->SendData((char *)&srr,sizeof(STRU_LOGIN_RQ)) == -1)
    {
        Sleep(50);
    }
    HomePage* homepage=new HomePage(tcpKernel);
    // hide();
    homepage->show();
}

//注册
void Login::on_pushButton_clicked()
{
    //获取控件文本
    QString account = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    for(int i=10;i<50;i++)
    {
         STRU_REGISTER_RQ srr;
         srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
         sprintf(srr.m_szAccount,"%s%d",account.toStdString().c_str(),i);
         sprintf(srr.m_szPassword,"%s",password.toStdString().c_str());
         //发送数据包头
         STRU_HEADER shead;
         shead.pac_size = sizeof(STRU_REGISTER_RQ);
         while(tcpKernel->SendData((char *)&shead,sizeof(shead)) == -1)
         {
             Sleep(50);
         }
         //发送实际数据报
         while(tcpKernel->SendData((char *)&srr,sizeof(srr)) == -1)
         {
             Sleep(50);
         }
    }

/*  STRU_REGISTER_RQ srr;
    srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
    sprintf(srr.m_szAccount,account.toStdString().c_str());
    sprintf(srr.m_szPassword,password.toStdString().c_str());

    tcpKernel->SendData((char *)&srr,sizeof(srr));*/
   // qDebug()<<"login";
    //qDebug()<<sizeof(srr);
}

void Login::ShowMsg(char* msg)
{
  /*  QMessageBox messageBox;
    messageBox.setWindowTitle(QObject::tr("HINT"));
    messageBox.setText(QObject::tr(msg));
    messageBox.exec();
    if(strcmp(msg,"login success") == 0)
    {
        qDebug()<<"login";
      HomePage* homepage=new HomePage(tcpKernel);
       // hide();
        homepage->show();

    }
    else
        qDebug()<<"login fail";
        */
}
