#include "sqlite/sqlite.h"
#include "utils/utils.h"
#include <QDebug>
#include <QString>

//QSqlQuery sql_query;

QString create_p_table_sql = "create table persons (name varchar(40), number varchar(40) primary key, psw varchar(40))";
QString create_r_table_sql = "create table routines (id integer primary key autoincrement,pnumber varchar(40),date integer,"
                             "cometime integer,isLate integer not null default(0),leavetime integer,"
                             "isEarlyLeave not null default(0))";
QString select_staff_by_num_sql = "select number,psw from persons where number =%1";
QString select_routine_by_pnumber_sql = "select id,date from routines where pnumber =%1";
QString select_cometime_by_id_sql = "select cometime from routines where id =%1";
QString select_leavetime_by_id_sql = "select leavetime from routines where id =%1";
QString update_work_sql = "update routines set cometime = :cometime ,isLate = :isLate where id = %1";
QString update_getoff_sql = "update routines set leavetime = :leavetime ,isEarlyLeave = :isEarlyLeave where id = %1";
QString insert_sql = "insert into routines(pnumber,date) values (:pnumber, :date)";


// 建立一个数据库连接
bool DataBase::createConnection(const QString &dbFileName) {
    //以后就可以用"att"与数据库进行连接了
    qDebug() << "creatConnection...";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "att");
    db.setDatabaseName(dbFileName);
//    qDebug() << "con2";
    if( !db.open()) {  // db.open();// 打开数据库连接
        qDebug() << "Database Error!";
        db.close(); // 释放数据库连接
        return false;
    }
    qDebug() << "con3";
    db.close(); // 释放数据库连接
    return true;
}

//// 创建数据库表
//bool DataBase::createTable()
//{
//    db = QSqlDatabase::database("att"); //建立数据库连接
//    QSqlQuery query(db);
//    bool p_success = query.exec(create_p_table_sql);
//    bool r_success = query.exec(create_r_table_sql);
//    if(p_success && r_success)
//    {
//        // 表建立成功
//        db.close();
//        return true;
//    }
//    else
//    {
//        // 表建立失败
//        qDebug() << sql_query.lastError();
//        db.close();
//        return false;
//    }
//}

// 查询员工是否存在且验证身份
bool DataBase::queryIsStaff(QString num,QString password)
{
    qDebug("queryIsStaff...");
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    //query.exec(QString(select_staff_by_num_sql).arg(num));
    query.exec("select number,psw from persons where number =" + num);
    QSqlRecord rec = query.record();
//    qDebug() << QObject::tr("persons 表字段数：" ) << rec.count();
    int fieldNo = rec.indexOf("number");
    int fieldpswNo = rec.indexOf("psw");
    bool isVarified = false;
//    qDebug("queryIsStaff2");

    while(query.next())
    {
//        for(int index = 0; index < 10; index++)
//            qDebug() << query.value(index) << " ";
//        qDebug() << "\n";
         QString number = query.value(fieldNo).toString();
         QString psw = query.value(fieldpswNo).toString();

         if(number==num && psw== password){
//             db.close();
//             qDebug()<<"here he is.";
             isVarified = true;
         }else{
//             db.close();
//              qDebug()<<"here she is.";
             isVarified = false;
         }
//         if(number!=""){
//             db.close();
//             return true;
//         }else{
//             db.close();
//             return false;
//         }

//        qDebug() << query.value(fieldNo).toString() << " ";
//        qDebug() << "\n";
    }
//    qDebug("queryIsStaff3");
    db.close();
    return isVarified;
}

// 查询 routines 信息
QString DataBase::queryIsRoutine(QString pnum)
{
    qDebug("queryisrountine...");
    //qDebug() << "contain:" << QSqlDatabase::contains("att");
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
//    qDebug("queryisrountine11");
    QSqlQuery query(db);
//    qDebug("queryisrountine12");
//    query.exec(QString(select_routine_by_pnumber_sql).arg(pnum));
    query.exec("select id,date from routines where pnumber =" + pnum );
//    qDebug("queryisrountine13");
    QSqlRecord rec = query.record();
//    qDebug("queryisrountine14");
//    qDebug() << QObject::tr("routines 表字段数：" ) << rec.count();
    int fieldNo = rec.indexOf("date");
    int fieldidNo = rec.indexOf("id");
    QString routine_id = "-1";
//    qDebug("queryisrountine2");

    while(query.next())
    {
//        for(int index = 0; index < 10; index++)
//            qDebug() << query.value(index) << " ";
//        qDebug() << "\n";
        QString r_date = query.value(fieldNo).toString();
//        qDebug()<<r_date.toInt()<<" "<<getDateInt();

        if(r_date.toInt()==getDateInt()){  // 需要更新
//            qDebug() << query.value(fieldNo).toString() << " ";
//            qDebug() << query.value(fieldidNo).toString() << " ";
            routine_id = query.value(fieldidNo).toString();
            //return query.value(fieldidNo).toString();  // 返回了id
        }

    }
     db.close();
//     QSqlDatabase::removeDatabase("att");
     // 需要插入
//     qDebug("queryisrountine3");
     return routine_id;
}

// 根据id查询 routines 表的 cometime 信息
int DataBase::queryComeTime(int id)
{
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    //query.exec(QString(select_cometime_by_id_sql).arg(id));
    query.exec("select cometime from routines where id ="+id);
    QSqlRecord rec = query.record();
//  qDebug() << QObject::tr("routines 表字段数：" ) << rec.count();
    int fieldNo = rec.indexOf("cometime");
    int cometime = -1;

    while(query.next())
    {
//      qDebug() << query.value(fieldNo).toString() << " ";
        if(query.value(fieldNo)!=""){
            cometime = query.value(fieldNo).toInt();  // 返回了cometime
        }else{
            cometime = -1;
        }

    }
     db.close();
//     QSqlDatabase::removeDatabase("att");
     return cometime;
}

// 根据id查询 routines 表的 leavetime 信息
int DataBase::queryLeaveTime(int id)
{
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    //query.exec(QString(select_leavetime_by_id_sql).arg(id));
    query.exec("select leavetime from routines where id ="+id);
    QSqlRecord rec = query.record();
//    qDebug() << QObject::tr("routines 表字段数：" ) << rec.count();
    int fieldNo = rec.indexOf("leavetime");

    while(query.next())
    {
//        qDebug() << query.value(fieldNo).toString() << " ";
//        qDebug() << "ghfh:"<<query.value(fieldNo).toInt();
        return query.value(fieldNo).toInt();  // 返回了leavetime
    }
     db.close();
     return -1;
}

// 根据 id 更新上班记录
bool DataBase::update_work_ById(int id,long cometime)
{
//    qDebug()<<"id:"<<id;
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString(update_work_sql).arg(id));
    //query.prepare("update routines set cometime = :cometime ,isLate = :isLate where id ="+ id);
//    qDebug()<<"time:"<<cometime;
    query.bindValue(":cometime",QString::number(cometime, 10));

    if(cometime <= 90000 && cometime > 0){  // 0点~9点签到为正常情况
        query.bindValue(":isLate",0);
    }else{  // 迟到
        query.bindValue(":isLate",1);
    }

    bool success=query.exec();
    if(!success)
    {
      QSqlError lastError = query.lastError();
      qDebug() << lastError.driverText() << QString("update failed!");
      db.close();
//      QSqlDatabase::removeDatabase("att");
      return false;
    }
    db.close();
//    QSqlDatabase::removeDatabase("att");
    return true;
}

// 根据 id 更新下班记录
bool DataBase::update_getoff_ById(int id,long leavetime)
{
//    qDebug()<<"id:"<<id;
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    query.prepare(QString(update_getoff_sql).arg(id));
    //query.prepare("update routines set leavetime = :leavetime ,isEarlyLeave = :isEarlyLeave where id ="+id);
//    qDebug()<<"time:"<<leavetime;
    query.bindValue(":leavetime",QString::number(leavetime, 10));

    if(leavetime > 170000 && leavetime<= 235959){ // 17点~23点59分59秒为签退时间
        query.bindValue(":isEarlyLeave",0);
    }else{ // 早退
        query.bindValue(":isEarlyLeave",1);
    }

    bool success=query.exec();
    if(!success)
    {
      QSqlError lastError = query.lastError();
      qDebug() << lastError.driverText() << QString("update failed!");
      db.close();
      return false;
    }
    db.close();
    return true;
}

// 向数据库中插入记录
bool DataBase::insert(int pnumber,long r_date)
{
    QSqlDatabase db = QSqlDatabase::database("att"); //建立数据库连接
    QSqlQuery query(db);
    //QSqlQuery query;
    //query.exec("SELECT *FROM tablename;");
    //query.prepare(QString(insert_sql));
    //query.prepare("insert into routines(pnumber,date) values (:pnumber, :date)");
    query.prepare(QString(insert_sql));

//    long records = 3;
//    for(int i=0; i<records; i++)
//    {
        query.bindValue(":pnumber", pnumber);
        query.bindValue(":date", QString::number(r_date, 10));

        bool success=query.exec();
        if(!success)
        {
            QSqlError lastError = query.lastError();
            qDebug() << lastError.driverText();
            db.close();
//            QSqlDatabase::removeDatabase("att");
            return false;
        }
//    }
        db.close();
//        QSqlDatabase::removeDatabase("att");
    return true;
}
