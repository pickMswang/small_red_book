#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>
#include "his.h"
namespace Ui {
class Information;
}

class Information : public QWidget
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = 0);
    ~Information();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Information *ui;
    His*his;
};

#endif // INFORMATION_H
