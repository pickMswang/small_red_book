#ifndef PUBLISH_H
#define PUBLISH_H

#include <QWidget>
#include <stdio.h>
#include <string.h>
#include <QDebug>
#include <QDataStream>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include "TCPKernel.h"
#include "login.h"
namespace Ui {
class Publish;
}

class Publish : public QWidget
{
    Q_OBJECT

public:
    explicit Publish(TCPKernel*,QWidget *parent = 0);
    ~Publish();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();
    void ShowMsg(char *);

    void on_pushButton_2_clicked();

private:
    Ui::Publish *ui;
    TCPKernel* tcpKernel;

    int m_nBuffSize; /**<  有效数据长度 */
    char* m_pBuff; /**< 数据 */
};

#endif // PUBLISH_H
