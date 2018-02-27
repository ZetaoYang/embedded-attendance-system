#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QEvent>
#include <QDebug>
#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    Dialog *vd_keyboard;


//    bool connectDB(const QString &dbName);


private slots:
//    void on_pushButton_clicked();
//    void on_pushButton_2_clicked();

    void work_clicked();
    void getoff_clicked();
    void v_keyboard();

    void idEdited();
    void idEdited_2();
    void receiveDatafromVKbd(QString data);   //接收传递过来的数据的槽


public slots:
#ifdef ARM
    char receiveslot(char);
#endif
private:
    Ui::Widget *ui;
protected:
    void closeEvent(QCloseEvent *);
    bool eventFilter(QObject *, QEvent *);
};



#endif // WIDGET_H
