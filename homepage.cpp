#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(TCPKernel* pKernel,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
 tcpKernel = pKernel;
    ui->setupUi(this);
    //为label添加鼠标按下的事件进入他的主页
               //事件过滤器
    ui->label->installEventFilter(this);
    //为label_2添加鼠标按下的事件进入他的主页
    ui->label_2->installEventFilter(this);
    //为label_3添加鼠标按下的事件进入他的主页
    ui->label_3->installEventFilter(this);
    //为label_4添加鼠标按下的事件进入他的主页
    ui->label_4->installEventFilter(this);

}


//为label添加鼠标按下的事件进入他的主页
bool HomePage::eventFilter(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj)==ui->label&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    } else if(qobject_cast<QLabel*>(obj)==ui->label_2&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    }
    else if(qobject_cast<QLabel*>(obj)==ui->label_3&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    } else if(qobject_cast<QLabel*>(obj)==ui->label_4&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    }
    else {
        return false;

    }
}
/*
//为label_2添加鼠标按下的事件进入他的主页
bool HomePage::eventFilter2(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj)==ui->label_2&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    }
    else {
        return false;

    }
}
//为label_3添加鼠标按下的事件进入他的主页
bool HomePage::eventFilter3(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj)==ui->label_3&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    }
    else {
        return false;

    }
}
//为label_4添加鼠标按下的事件进入他的主页
bool HomePage::eventFilter4(QObject *obj, QEvent *event)
{
    if(qobject_cast<QLabel*>(obj)==ui->label_4&&event->type() == QEvent::MouseButtonRelease)
    {

        information=new Information();
        information->show();
        return true;
    }
    else {
        return false;

    }
}*/
HomePage::~HomePage()
{
    delete ui;
}
void HomePage::openDialog()
{
    information=new Information(this);
    information->show();
}

//转到消息
void HomePage::on_pushButton_4_clicked()
{
   messege =new Messege();
   // hide();
    messege->show();

    show();

}
//转到我的
void HomePage::on_pushButton_5_clicked()
{
    myredbook=new MyRedBook();
   // hide();
    myredbook->show();
}
//转到发布
void HomePage::on_pushButton_3_clicked()
{
   Publish *publish=new Publish(tcpKernel);
 //   hide();
    publish->show();
}
