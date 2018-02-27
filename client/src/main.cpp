#include "widget.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QApplication>


#define CURRENT_VERSION "0.2"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
//#ifdef ARM
//    w.setFont(QFont("unifont",9,QFont::Normal));
//    w.setWindowTitle(QString::fromUtf8("规范化"));
//#endif

    w.setWindowFlags(w.windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint);
    w.setFixedSize(417,247); // 禁止改变窗口大小。
   // centre window
    //w.setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, w.size(), a.desktop()->availableGeometry()));
    w.move(110,20);
    w.setWindowTitle(QString("Staff Attendance System v" CURRENT_VERSION));// 员工考勤系统
    w.show();

    return a.exec();
}
