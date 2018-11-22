#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <stdio.h>
#include <string.h>
#include <QDebug>
#include"homepage.h"
#include "TCPKernel.h"


namespace Ui {
class login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(TCPKernel*,QWidget *parent = 0);
    ~Login();
public:
   // void InitKernel(TCPKernel*);
private slots:
    void on_login_button_clicked();

    void on_pushButton_clicked();

    void ShowMsg(char *);

private:
    Ui::login *ui;

    TCPKernel* tcpKernel;
    //HomePage * homepage;
};

#endif // LOGIN_H
