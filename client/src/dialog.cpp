#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QPalette>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/bkd_background.jpg")));
//    palette.setColor(QPalette::Background, QColor(71, 146, 169));
    this->setPalette(palette);

    this->move(70,315);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Button1_kbd()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Button2_kbd()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(Button3_kbd()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(Button4_kbd()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(Button5_kbd()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(Button6_kbd()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(Button7_kbd()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(Button8_kbd()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(Button9_kbd()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(Button0_kbd()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(Button_bak_kbd()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(Button_ent_kbd()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(Button_cls_kbd()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(Button_mul_kbd()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(Button_div_kbd()));
    connect(ui->pushButton_16, SIGNAL(clicked()), this, SLOT(Button_add_kbd()));
    connect(ui->pushButton_17, SIGNAL(clicked()), this, SLOT(Button_sub_kbd()));
    connect(ui->pushButton_18, SIGNAL(clicked()), this, SLOT(Button_space_kbd()));
}

Dialog::~Dialog()
{
    delete ui;
}

//0
void Dialog::Button0_kbd(){
    emit sendData(QString("0"));
//    qDebug() << '0';
}
//1
void Dialog::Button1_kbd(){
    emit sendData(QString("1"));
//    qDebug() << '1';
}
//2
void Dialog::Button2_kbd(){
    emit sendData(QString("2"));
//    qDebug() << '2';
}
//3
void Dialog::Button3_kbd(){
    emit sendData(QString("3"));
//    qDebug() << '3';
}
//4
void Dialog::Button4_kbd(){
    emit sendData(QString("4"));
//    qDebug() << '4';
}
//5
void Dialog::Button5_kbd(){
    emit sendData(QString("5"));
//    qDebug() << '5';
}
//6
void Dialog::Button6_kbd(){
    emit sendData(QString("6"));
//    qDebug() << '6';
}
//7
void Dialog::Button7_kbd(){
    emit sendData(QString("7"));
//    qDebug() << '7';
}
//8
void Dialog::Button8_kbd(){
    emit sendData(QString("8"));
//    qDebug() << '8';
}
//9
void Dialog::Button9_kbd(){
    emit sendData(QString("9"));
//    qDebug() << '9';
}
//bak
void Dialog::Button_bak_kbd(){
    emit sendData(QString("bak"));
//    qDebug() << QString("backspace");
}
//ent
void Dialog::Button_ent_kbd(){
    emit sendData(QString("\n"));
//    qDebug() << QString("enter");
}
//cls
void Dialog::Button_cls_kbd(){
    emit sendData(QString("cls"));
//    qDebug() << QString("clear");
}
//mul
void Dialog::Button_mul_kbd(){
    emit sendData(QString("*"));
//    qDebug() << QString("*");
}
//div
void Dialog::Button_div_kbd(){
    emit sendData(QString("*"));
//    qDebug() << QString("/");
}
//add
void Dialog::Button_add_kbd(){
    emit sendData(QString("+"));
//    qDebug() << QString("+");
}
//sub
void Dialog::Button_sub_kbd(){
    emit sendData(QString("-"));
//    qDebug() << QString("-");
}
//space
void Dialog::Button_space_kbd(){
    emit sendData(QString(" "));
//    qDebug() << QString(" ");
}

