#ifndef DB1_HPP
#define DB1_HPP

#include "DBSystem.hpp"

struct DataFormat
{
    QString time;
    QString logData;
};

template<class T = DataFormat>
class DB1 : public DBSystem<T>
{
public:
    DB1<T>(){}
    DB1<T>(const QString& dbname):DBSystem<T>(dbname)
    {}

    virtual bool CreateTable(const QString& tablename)override
    {
        auto db = QSqlDatabase::database(this->dbname);
        db.open();
        QSqlQuery query(db);
        query.clear();
        bool sucess = query.exec(QString("create table if not exists '%1'(\
                                         time varchar(512) ,\
                                         info varchar(512) );").arg(tablename));
                db.close();
        if (sucess)
        {
    #ifdef QT_DEBUG
            qDebug() << "LOG1 : create successfully!";
    #endif
            return true;
        }
        else
        {
    #ifdef QT_DEBUG
            qDebug() <<"ERR1 : "<< query.lastError().text();
    #endif
            return false;
        }
    }
    virtual bool InsertData(QString tableName,const T &data)override
    {
        auto db = QSqlDatabase::database(this->dbname);
        db.open();
        QSqlQuery query(db);
        query.clear();

        bool insertOk = query.prepare(QString("insert into '%0' values(?,?)").arg(tableName));
        query.bindValue(0,data.time);
        query.bindValue(1,data.logData);
        query.exec();
        db.close();
        if (insertOk)
        {
    #ifdef QT_DEBUG
            qDebug() << "LOG1 : insert data successfully!";
    #endif
            return true;
        }
        else
        {
    #ifdef QT_DEBUG
            qDebug() << "ERR1 : "<<query.lastError().text();
    #endif
            return false;
        }
    }
    virtual bool SearchData(QString tableName,QList<T> &datas)override
    {
        auto db = QSqlDatabase::database(this->dbname);
            db.open();
            QSqlQuery query(db);
            query.clear();
            bool isDataExist = query.exec(QString("select * from '%0'").arg(tableName));
            if (isDataExist)
            {
                if (!query.next())
                {
        #ifdef QT_DEBUG
                    qDebug() << "LOG1 : data is non-exist!";
        #endif
                    return false;
                }
                else
                {
                    do
                    {
                        T data;
                        data.time = query.value(0).toString();
                        data.logData = query.value(1).toString();
                        datas.push_back(data);
                    } while (query.next());
                    db.close();
                    return true;
                }
            }
            else
            {
        #ifdef QT_DEBUG
                qDebug() << "ERR1 : "<<query.lastError().text();
        #endif
                db.close();
                return false;
            }
    }
    virtual bool DeleteTable(const QString& tableName)override
    {
        auto db = QSqlDatabase::database(this->dbname);
        db.open();
        QSqlQuery query(db);
        query.clear();

        bool deleteOk = query.exec(QString("drop table '%1';").arg(tableName));
        db.close();
        if (deleteOk)
        {
    #ifdef QT_DEBUG
            qDebug() << "LOG1 : drop table successfully!";
    #endif
            return true;
        }
        else
        {
    #ifdef QT_DEBUG
            qDebug() << "ERR1 : "<<query.lastError().text();
    #endif
            return false;
        }
    }
};

#endif // DB1_H
