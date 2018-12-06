#include "publish.h"
#include "ui_publish.h"

Publish::Publish(TCPKernel* pKernel,QWidget *parent) :
    QWidget(parent), m_nBuffSize(0), m_pBuff(NULL),
    ui(new Ui::Publish)
{
    tcpKernel = pKernel;
    connect(tcpKernel,SIGNAL(MsgBox(char*)),this,SLOT(ShowMsg(char*)));
    ui->setupUi(this);
}

Publish::~Publish()
{
    if (m_pBuff != NULL)
    {
        delete m_pBuff;
        m_pBuff = NULL;
    }

    delete ui;
}

void Publish::on_pushButton_5_clicked()
{
    close();
}
//选择图片
void Publish::on_pushButton_clicked()
{

    //获取图片文件
    QString strFileName = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    if (strFileName.isEmpty())
    {
        QMessageBox::information(NULL, tr("Warning"), tr("You didn't select any files."));
        return;
    }

    QFile file(strFileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, tr("Warning"), tr("File open fail."));
        return;
    }

    //先释放内存
    if (m_pBuff != NULL)
    {
        delete m_pBuff;
        m_pBuff = NULL;
    }

    //确保内存分配成功
    int nSize = file.size();
    do
    {
        m_pBuff = new char[nSize + 1];
    }while (m_pBuff == NULL);

    QDataStream in(&file);
    //需要的有效长度为函数返回值，并非nSize
    m_nBuffSize = in.readRawData(m_pBuff, nSize);

    //读取失败则结束操作
    if (m_nBuffSize == -1)
    {
        return;
    }

    //验证读取的数据，通过转化成图片显示出来
    QImage image;
    image.loadFromData(reinterpret_cast<unsigned char*>(m_pBuff), m_nBuffSize);
    //ui->Publish->label->setPixmap(QPixmap::fromImage(image));
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void Publish::ShowMsg(char* msg)
{
   /* QMessageBox messageBox;
    messageBox.setWindowTitle(QObject::tr("HINT"));
    messageBox.setText(QObject::tr(msg));
    messageBox.exec();
    if(strcmp(msg,"publish success") == 0)
    {
        qDebug()<<"publish";

    }
    else
        qDebug()<<"publish fail";*/
}

//发布
void Publish::on_pushButton_2_clicked()
{
    STRU_PUBLISH_RQ spr;
    qDebug()<<m_nBuffSize<<endl;
    int index = 0;
    while((index+2034) < m_nBuffSize)
    {
        memset(spr.m_szSTREAM,'0',sizeof(spr.m_szSTREAM));
        spr.m_nType =_DEF_PROTOCOL_PUBLISH_RQ;
        spr.fin = 0;
        spr.length = 2034;
        memcpy(spr.m_szSTREAM,m_pBuff+index,2034);
        tcpKernel->SendData((char *)&spr,sizeof(spr));
        index += 2034;
        qDebug()<<index<<endl;
       // Sleep(50);
    }
    spr.fin = 1;
    spr.length = m_nBuffSize - index;
    spr.m_nType =_DEF_PROTOCOL_PUBLISH_RQ;
    memcpy(spr.m_szSTREAM,m_pBuff+index,m_nBuffSize - index);
    tcpKernel->SendData((char *)&spr,sizeof(spr));
    qDebug()<<sizeof(spr)<<endl;
    //qDebug()<<m_nBuffSize - index<<endl;
    /*delete m_pBuff;
    m_pBuff = NULL;*/
}
