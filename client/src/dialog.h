#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
public slots:
    void Button0_kbd();
    void Button1_kbd();
    void Button2_kbd();
    void Button3_kbd();
    void Button4_kbd();
    void Button5_kbd();
    void Button6_kbd();
    void Button7_kbd();
    void Button8_kbd();
    void Button9_kbd();
    void Button_bak_kbd();
    void Button_ent_kbd();
    void Button_cls_kbd();
    void Button_mul_kbd();
    void Button_div_kbd();
    void Button_add_kbd();
    void Button_sub_kbd();
    void Button_space_kbd();

private:
    Ui::Dialog *ui;

signals:
    void sendData(QString);   //用来传递数据的信号

};

#endif // DIALOG_H
