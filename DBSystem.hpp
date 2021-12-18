#pragma once
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDateTime>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qsqlerror.h>
#include <QList>


template <class T>
class DBSystem
{
public:
    DBSystem<T>(){}

    DBSystem<T>(const QString& dbname)
    {
        this->dbname = dbname;
        initDB(dbname);
    }

    virtual QSqlDatabase database(const QString& dbname) final
    {
        return QSqlDatabase::database(dbname);
    }

    virtual QString currTime() final
    {
        QDateTime curr = QDateTime::currentDateTime();
        return curr.toString("yyyy-MM-dd hh:mm:ss");
    }

    virtual bool CreateTable(const QString& tablename)=0;
    virtual bool InsertData(QString tableName,const T &data)=0;
    virtual bool SearchData(QString tableName,QList<T> &datas)=0;
    virtual bool DeleteTable(const QString& tableName)=0;

private:
    bool initDB(const QString& dbname)
    {
        db = QSqlDatabase::addDatabase("QSQLITE",dbname);
        db.setDatabaseName(dbname+".db");
        return true;
    }
protected:
    QSqlDatabase db;
    QString dbname;
};

