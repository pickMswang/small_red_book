#ifndef CHAT_H
#define CHAT_H

#include <QWidget>

namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    explicit Chat(QWidget *parent = 0);
    ~Chat();

private slots:
    void on_pushButton_2_clicked();//

private:
    Ui::Chat *ui;
};

#endif // CHAT_H
