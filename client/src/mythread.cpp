#ifdef ARM
#include "mythread.h"

MyThread::MyThread()
{

}
void MyThread::run()
{
    char mykey;
    kbd_init();
    while(true)
    {
        //sleep(5);
        mykey = get_key();
        emit send(mykey);
        //qDebug()<<"Thread is running!";
    }
    kbd_close();
}
#endif
