#ifdef ARM
#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QString>
#include <QDebug>
#include "keyboard/get_key.h"

class MyThread: public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run();

signals:
    void send(char);
};

#endif // MYTHREAD_H
#endif
