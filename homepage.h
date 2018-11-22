#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include"messege.h"
#include"myredbook.h"
#include "TCPKernel.h"
#include"publish.h"
#include"information.h"
namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(TCPKernel*,QWidget *parent = 0);
    ~HomePage();

//signals:
  //  Signal();


private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();
    void openDialog();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    bool eventFilter2(QObject *obj, QEvent *event);
    bool eventFilter3(QObject *obj, QEvent *event);
    bool eventFilter4(QObject *obj, QEvent *event);

private:
    Ui::HomePage *ui;
    Messege *messege;
    MyRedBook*myredbook;
    //Publish*publish;
    Information*information;
    TCPKernel* tcpKernel;
};

#endif // HOMEPAGE_H
