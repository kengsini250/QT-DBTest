#include <QCoreApplication>

#include "DB1.hpp"
#include "DB2.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DBSystem<DataFormat>*db = new DB1<DataFormat>("A");
    DBSystem<DataFormat2>*db2 = new DB2<DataFormat2>("B");
    db->CreateTable("a");
    db->InsertData("a",{db->currTime(),"test"});
    db2->CreateTable("b");
    db2->InsertData("b",{db->currTime(),"test","oppai"});
    QList<DataFormat> datas;
    db->SearchData("A",datas);
    qDebug()<<datas[0].time;
    qDebug()<<datas[0].logData;
    QList<DataFormat2> datas2;
    db2->SearchData("B",datas2);
    qDebug()<<datas2[0].time;
    qDebug()<<datas2[0].logData;
    qDebug()<<datas2[0].test;
    return 0;
}
