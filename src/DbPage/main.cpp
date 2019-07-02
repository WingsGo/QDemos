#include "frmdbpage.h"
#include <QtGui>
#include <QtSql>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 9));

    //打开数据库,整个应用程序可用
    QSqlDatabase dbConn = QSqlDatabase::addDatabase("QSQLITE");
    auto dbName = qApp->applicationDirPath() + "/TA.db";
    dbConn.setDatabaseName(dbName);
    qDebug() << QString::fromLocal8Bit("数据库路径:") << dbName;
    if (dbConn.open()) {
        qDebug() << QString::fromLocal8Bit("连接数据库成功!");
    } else {
        qDebug() << QString::fromLocal8Bit("连接数据库失败!");
    }

    frmDbPage w;
    w.setWindowTitle(QString::fromLocal8Bit("数据库分页示例"));
    w.show();

    return a.exec();
}
