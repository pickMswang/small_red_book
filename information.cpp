#include "information.h"
#include "ui_information.h"

Information::Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
}

Information::~Information()
{
    delete ui;
}

void Information::on_pushButton_2_clicked()
{
    close();
}
//转到his
void Information::on_pushButton_clicked()
{
    his=new His();
    his->show();
}
