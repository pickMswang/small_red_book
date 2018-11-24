#include "his.h"
#include "ui_his.h"

His::His(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::His)
{
    ui->setupUi(this);
}

His::~His()
{
    delete ui;
}

void His::on_pushButton_2_clicked()
{
    close();
}
