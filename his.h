#ifndef HIS_H
#define HIS_H

#include <QWidget>

namespace Ui {
class His;
}

class His : public QWidget
{
    Q_OBJECT

public:
    explicit His(QWidget *parent = 0);
    ~His();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::His *ui;
};

#endif // HIS_H
