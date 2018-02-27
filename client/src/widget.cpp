#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>
//#include <QSettings>
//#include <QFileInfo>
#include "widget.h"
#include "ui_widget.h"
#include "cglobal.h"
#include "utils/utils.h"
#include "sqlite/sqlite.h"
#ifdef ARM
#include "mythread.h"
#endif

// 数据库文件的路径，如 "/mnt/nfs/boa/cgi-bin/test.db"
#define DB_PATH "./data/test.db"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    // 实例化虚拟键盘
    vd_keyboard = new Dialog;
    // 设置背景
    this->setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(74, 198, 161));
    //此处的数值，可以在样式表 中先选中你需要的颜色，然后 cope 数值即可。
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/background.jpg")));
    this->setPalette(palette);

#ifdef ARM
    MyThread *mth = new MyThread ;
    QObject::connect(mth,SIGNAL(send(char)),this,SLOT(receiveslot(char)));
    mth->start();
#endif

    ui->pushButton->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;background-color: #d0d0d0;}"
//                                  "QPushButton:hover{background-color: #d0d0d0}"
                                  "QPushButton:pressed{background-color: #898989}"
                                  );
    ui->pushButton_2->setStyleSheet("QPushButton{border:2px groove gray;border-radius:10px;background-color: #d0d0d0;}"
//                                  "QPushButton:hover{background-color: #d0d0d0}"
                                  "QPushButton:pressed{background-color: #898989}"
                                  );

    ui->pushButton_3->setStyleSheet("QPushButton{border-image: url(:/images/icons_keyboard.png);}"
                                     "QPushButton:pressed{border-image: url(:/images/icons_keyboard-filled.png);}"
                                     );

    ui->lineEdit->installEventFilter(this);  //在窗体上为lineEdit安装过滤器
    ui->lineEdit_2->installEventFilter(this);  //在窗体上为lineEdit_2安装过滤器

    //连接信号和槽
    connect(vd_keyboard, SIGNAL(sendData(QString)), this, SLOT(receiveDatafromVKbd(QString)));

    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(idEdited()));
    connect(ui->lineEdit_2, SIGNAL(textChanged(QString)), this, SLOT(idEdited_2()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(work_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(getoff_clicked()));

    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(v_keyboard()));
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    //ui->lineEdit->setFocus();

}

Widget::~Widget()
{
    //delete vd_keyboard;//删除指针，防止内存泄露
    delete ui;
}

//// config.ini 配置文件
//QString Widget::configIsExist(){
//    QFileInfo fi("config.ini");
//    qDebug()<<fi.isFile();
//    if(fi.isFile()){
//        //return ture;
//        QString  = read_setting();
//        return ;

//    }else{
//        write_setting();
//        return "test.db";
//    }
//}

//void write_setting()
//{
//    QSettings *config = new QSettings("config.ini", QSettings::IniFormat);
//    config->setValue("/default/", "test.db");
//    delete config;
//}

//QString read_setting()
//{
//    QSettings *config = new QSettings("config.ini", QSettings::IniFormat);
//    QString  = config->value("/default/").toString();
//    delete config;
//    qDebug() << ;
//    if(!=""){
//        return ;
//    }else{
//        return "test.db"; //返回默认值
//    }
//}

void Widget::idEdited() {
    // 在处理textedit clicked函数里我们将lineedit背景色变蓝色
    // ui->lineEdit->setStyleSheet("background-color:blue");
    // qDebug() << QString("staff_id is editing.");
}

void Widget::idEdited_2() {
    // 在处理textedit clicked函数里我们将lineedit背景色变红色
    // ui->lineEdit_2->setStyleSheet("background-color:red");
    // qDebug() << QString("staff_password is editing.");
}

// 打开虚拟键盘
void Widget::v_keyboard(){

//    QDialog *vd_keyboard=new QDialog();
//    vd_keyboard->show();
//    qDebug()<<"one:"<<CGlobal::kbd_Value;
    if(CGlobal::kbd_Value==0){
        vd_keyboard->show();
        CGlobal::kbd_Value=1;
    }else if(CGlobal::kbd_Value==1){
        vd_keyboard->hide();
        CGlobal::kbd_Value=0;
    }

//    qDebug() <<"v_keyboard";
}

// 上班登记
void Widget::work_clicked()
{
    DataBase d;
    //QMessageBox::information(NULL, QString("Staff Attendance System"), QString("Finished!"));
    QString e_id = ui->lineEdit->text();
    QString e_pwd = ui->lineEdit_2->text();
//    qDebug()<<"id:"<<e_id;
//    qDebug()<<"pwd:"<<e_pwd;
    // 首先判断两个输入框是否为空
    if(e_id.isEmpty() || e_pwd.isEmpty()){
         qDebug() << "Can not be empty!";
    }else{

        if(d.createConnection(DB_PATH)){  // 连接数据库
            qDebug() << "Database Create/connect Sucessfully!";
                if(d.queryIsStaff(e_id,e_pwd)){  // 判断员工是否存在  d.queryIsStaff(e_id,e_pwd)
                    qDebug() << "This staff exists!";
//                    qDebug() << e_id;
                    QString r_id = d.queryIsRoutine(e_id); // 查询 routine id
//                    qDebug("r_id:");
//                    qDebug() << r_id;
                    if(r_id!="-1"){  //需要更新
                        if(d.queryComeTime(r_id.toInt()) > 0){ // 重复签到
                            qDebug()<<"Repeat check in!";
                            ui->lineEdit->clear();
                            ui->lineEdit_2->clear();
                            QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check in"),tr("Repeat check in!"));
                            //box->setParent(this);
                            QTimer::singleShot(2000,box,SLOT(accept())); //也可将accept改为close
                            box->exec();//box->show();都可以
                            //delete box;

                        }else{
                            if(d.update_work_ById(r_id.toInt(),getTimeInt())){
                                // 更新成功
                                qDebug()<<"check in finished!";
                                QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check in"),tr("Finished!"));
                                //box->setParent(this);
                                QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
                                box->exec();//box->show();都可以
                                //delete box;
                                ui->lineEdit->clear();
                                ui->lineEdit_2->clear();
                            }else{
                                // 更新失败
                                qDebug() << "check in failed!";
                                ui->lineEdit->clear();
                                ui->lineEdit_2->clear();
                            }

                        }

                    }else{  //需要插入
                       if(d.insert(e_id.toInt(),getDateInt())){
                           QString r2_id = d.queryIsRoutine(e_id);

                           if(d.update_work_ById(r2_id.toInt(),getTimeInt())){
                               // 更新成功
                               qDebug()<<"check in finished!";
                               QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check in"),tr("Finished!"));
                               //box->setParent(this);
                               QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
                               box->exec();//box->show();都可以
                               //delete box;
                               ui->lineEdit->clear();
                               ui->lineEdit_2->clear();
                           }else{
                               // 更新失败
                               qDebug() << "check in failed!";
                               ui->lineEdit->clear();
                               ui->lineEdit_2->clear();
                           }

                       }
                    }

                }else{
                    qDebug() << "This staff doesn't exist or password error!";
                    QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("System"),tr("This staff doesn't exist or password error!"));
                    //box->setParent(this);
                    QTimer::singleShot(2500,box,SLOT(accept())); //也可将accept改为close
                    box->exec();//box->show();都可以
                    //delete box;
                    ui->lineEdit->clear();
                    ui->lineEdit_2->clear();
                }
        }else{
            qDebug() << "Database Create/connect Failed!";
        }
    }


//    if(d.createTable()){
//        qDebug() << "Table Create Sucessfully!";
//    }
//    else{
//        qDebug() << "table Create Failed!";
//    }

//    QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Work"),tr("Finished!"));
//    QTimer::singleShot(2000,box,SLOT(accept())); //也可将accept改为close
//    box->exec();//box->show();都可以

}

// 下班登记
void Widget::getoff_clicked(){
    DataBase d;
    //QMessageBox::information(NULL, QString("Staff Attendance System"), QString("Finished!"));
    QString e_id = ui->lineEdit->text();
    QString e_pwd = ui->lineEdit_2->text();
    // 首先判断两个输入框是否为空
    if(e_id.isEmpty() || e_pwd.isEmpty()){
         qDebug() << "Can not be empty!";
    }else{

        if(d.createConnection(DB_PATH)){  // 连接数据库
            qDebug() << "Database Create/connect Sucessfully!";
                if(d.queryIsStaff(e_id,e_pwd)){  // 判断员工是否存在
                    qDebug() << "This staff exists!";

                    QString r_id = d.queryIsRoutine(e_id); // 查询 routine id
               //     qDebug() << r_id;
                    if(r_id!="-1"){  //需要更新
                        if(d.queryLeaveTime(r_id.toInt()) > 0){  // 重复签退
                            qDebug()<<"Repeat check out!";
                            ui->lineEdit->clear();
                            ui->lineEdit_2->clear();
                            QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check out"),tr("Repeat check out!"));
                            //box->setParent(this);
                            QTimer::singleShot(2000,box,SLOT(accept())); //也可将accept改为close
                            box->exec();//box->show();都可以
                            //delete box;

                        }else{

                            if(d.update_getoff_ById(r_id.toInt(),getTimeInt())){
                                // 更新成功
                                QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check out"),tr("Finished!"));
                                //box->setParent(this);
                                QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
                                box->exec();//box->show();都可以
                                //delete box;
                                ui->lineEdit->clear();
                                ui->lineEdit_2->clear();
                            }else{
                                // 更新失败
                                qDebug() << "check out failed!";
                                ui->lineEdit->clear();
                                ui->lineEdit_2->clear();
                            }

                        }

                    }else{  //需要插入
//                       if(d.insert(e_id.toInt(),getDateInt())){
//                           QString r2_id = d.queryIsRoutine(e_id);

//                           if(d.update_getoff_ById(r2_id.toInt(),getTimeInt())){
//                               // 更新成功
//                               QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("Check out"),tr("Finished!"));
//                               QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
//                               box->exec();//box->show();都可以
//                               delete box;
//                               ui->lineEdit->clear();
//                               ui->lineEdit_2->clear();
//                           }else{
//                               // 更新失败
//                               qDebug() << "check out failed!";
//                               ui->lineEdit->clear();
//                               ui->lineEdit_2->clear();
//                           }

//                       }

                        QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("System"),tr("Not check in!"));
                        //box->setParent(this);
                        QTimer::singleShot(1500,box,SLOT(accept())); //也可将accept改为close
                        box->exec();//box->show();都可以
                        //delete box;
                        ui->lineEdit->clear();
                        ui->lineEdit_2->clear();

                    }

                }else{
                    qDebug() << "This staff doesn't exist or password error!";
                    QMessageBox *box = new QMessageBox(QMessageBox::Information,tr("System"),tr("This staff doesn't exist or password error!"));
                    //box->setParent(this);
                    QTimer::singleShot(2500,box,SLOT(accept())); //也可将accept改为close
                    box->exec();//box->show();都可以
                    //delete box;

                    ui->lineEdit->clear();
                    ui->lineEdit_2->clear();
                }
        }else{
            qDebug() << "Database Create/connect Failed!";
        }
    }


}

// 窗体关闭时将虚拟键盘也关闭
void Widget::closeEvent(QCloseEvent *)
{
     vd_keyboard->close();

}

// 两个 QLineEdit 的事件过滤器
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
     if (watched==ui->lineEdit) // 首先判断控件(这里指 lineEdit)
     {
          if (event->type()==QEvent::FocusIn) // 然后再判断控件的具体事件 (这里指获得焦点事件)
          {
             ui->lineEdit->setStyleSheet("background-color:#d1d1d3");

             CGlobal::Value = 1;

          }
          else if (event->type()==QEvent::FocusOut) // 这里指 lineEdit 控件的失去焦点事件
          {
              ui->lineEdit->setStyleSheet("background-color:white");

              //CGlobal::Value = 0;

          }
     }
     if (watched==ui->lineEdit_2) // 这里来处理 lineEdit_2 , 和处理lineEdit 是一样的
     {
          if (event->type()==QEvent::FocusIn)
         {
              ui->lineEdit_2->setStyleSheet("background-color:#d1d1d3");

              CGlobal::Value = 2;

         }
         else if (event->type()==QEvent::FocusOut)
         {
             ui->lineEdit_2->setStyleSheet("background-color:white");

             //CGlobal::Value = 0;

         }
     }
 return QWidget::eventFilter(watched,event); // 最后将事件交给上层对话框
}

// 虚拟键盘
void Widget::receiveDatafromVKbd(QString data)
{
    if(CGlobal::Value == 1){

        if(data=="cls"){
            ui->lineEdit->clear();
        }else if(data=="bak"){
            ui->lineEdit->backspace();
        }
        else{
            QString input_key = ui->lineEdit->text();
            input_key.append(data);
            ui->lineEdit->setText(input_key);
        }

//        qDebug() << "here1";
    }
    if(CGlobal::Value == 2){
        if(data=="cls"){
            ui->lineEdit_2->clear();
        }else if(data=="bak"){
            ui->lineEdit_2->backspace();
        }
        else{
            QString input_key = ui->lineEdit_2->text();
            input_key.append(data);
            ui->lineEdit_2->setText(input_key);
        }

//        qDebug() << "here2";
    }
//    qDebug() <<"is:" <<data;
}

#ifdef ARM
// 物理17键小键盘
char Widget::receiveslot(char c)
{
    //QMessageBox::information(0,"Information",c);
    qDebug() << "press key is: " <<c;
    if(CGlobal::Value == 1){

        QString str = QString(c);
        QString input_key = ui->lineEdit->text();
        input_key.append(str);
        ui->lineEdit->setText(input_key);
    }
    if(CGlobal::Value == 2){

        QString str = QString(c);
        QString input_key = ui->lineEdit_2->text();
        input_key.append(str);
        ui->lineEdit_2->setText(input_key);
    }
    return c;
}
#endif
