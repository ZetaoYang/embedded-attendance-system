#ifndef SQLITE_H
#define SQLITE_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QVariant>

class DataBase
{
public:
    bool createConnection(const QString &dbFileName);     // 创建一个连接
    bool createTable();                                   // 创建数据库表
    bool insert(int pnumber, long r_date);                // 插入数据
    bool update_work_ById(int id, long cometime);         // 更新
    bool update_getoff_ById(int id,long leavetime);       // 更新
    bool queryIsStaff(QString num, QString password);     // 查询是否为自己的员工
    int queryComeTime(int id);                            // 查询上班签到时间
    int queryLeaveTime(int id);                           // 查询下班签退时间
    QString queryIsRoutine(QString pnum);                  // 查询routine记录是否存在
};

#endif // SQLITE_H
