#include "mainwindow.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QDebug>

QSqlDatabase createSqlServerDb(const QString& serverAddr,
                               const QString& userName,
                               const QString& userPwd,
                               const QString& dbName)
{
    QString connectionTemplate = "DRIVER={SQL SERVER};SERVER=%1;DATABASE=%2;";

    QString connectionInfo = connectionTemplate.arg(serverAddr).arg(dbName);
    auto db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName(serverAddr);
    db.setUserName(userName);
    db.setPassword(userPwd);
    db.setDatabaseName(connectionInfo);
    return db;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString serverAddr = "127.0.0.1";
    QString dbName = "YXH_DTU_Data";
    QString userName = "sa";
    QString pwd = "371171046";
    auto db = createSqlServerDb(serverAddr, userName, pwd, dbName);
    if(!db.open()) {
        qDebug() << QString::fromLocal8Bit("数据库打开失败: ") << db.lastError().text();
    } else{
        qDebug() << QString::fromLocal8Bit("数据库打开成功");
    }

    MainWindow w;
    w.show();

    return a.exec();
}
