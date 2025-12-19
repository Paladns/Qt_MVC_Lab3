#include "idatabase.h"
#include <QUuid>
#include <QSqlRecord>
#include <QDateTime>

void iDatabase::initDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");        //选择驱动
    QString afile = "D:/homework/3rd/QTQTQT666!/CODE/Lab3.db";        //数据库的位置
    // QString afile = "../../Lab3.db";        //数据库的位置
    database.setDatabaseName(afile);

    if(!database.open()){       //打开成功  但是这个打开只是fake打开 实际有没有还得通过操作SQL语句来实现判断
        qDebug()<<"数据库打开失败";
    }else
        qDebug()<<"数据库成功打开";
}

bool iDatabase::initPatientModel()
{
    patientTableModel = new QSqlTableModel(this,database);
    patientTableModel->setTable("patient");
    patientTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);     //数据保存模式
    patientTableModel->setSort(patientTableModel->fieldIndex("name"),Qt::AscendingOrder);   //排序
    if(!(patientTableModel->select()))
        return false;

    thePatientSelection = new QItemSelectionModel(patientTableModel);
    return true;
}

int iDatabase::addNewPatient()
{
    patientTableModel->insertRow(patientTableModel->rowCount(),QModelIndex());  //末尾添加新记录

    QModelIndex curIndex = patientTableModel->index(patientTableModel->rowCount() - 1, 1);

    int curRowNo = curIndex.row();
    QSqlRecord curRec = patientTableModel->record(curRowNo);        //获取当前的记录
    curRec.setValue("CREATEDTIMESTAM", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));

    patientTableModel->setRecord(curRowNo, curRec);     //写回记录

    return curIndex.row();
}

bool iDatabase::searchPatient(QString filter)
{
    patientTableModel->setFilter(filter);
    return patientTableModel->select();

}

bool iDatabase::deletePatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();     //和获取下表
    qDebug()<<"删除的Index"<<curIndex.row();
    patientTableModel->removeRow(curIndex.row());
    patientTableModel->submitAll();
    patientTableModel->select();

    return true;        //这个要return 不然会不知道的情况下退出 其实这个挺奇怪的
}

bool iDatabase::submitPatient()
{
    return patientTableModel->submitAll();
}

void iDatabase::revertPatient()
{
    patientTableModel->revertAll();
}

QString iDatabase::userLogin(QString userName, QString password)
{
    if (!database.isOpen()) {
        return "数据库未连接";
    }
    QSqlQuery query;        //查询出当前的字段
    // qDebug() << userName;
    query.prepare("select * from user where username = :USER");     //这个USER是用来替换
    query.bindValue(":USER",userName);

    query.exec();
    if(query.first() && query.value("username").isValid()){
        QString pswd = query.value("password").toString();

        if(pswd == password){
            qDebug()<<"登录成功";
            return "登录成功";
        }else{
            qDebug()<<"密码错误了";
            return "密码错误";
        }
    }else{
        qDebug()<<"该用户不存在";
        return "该用户不存在";
    }
}

// QString iDatabase::userLogin(QString userName, QString password)
// {
//     if (!database.isOpen()) {
//         return "数据库未连接";
//     }

//     QSqlQuery query;
//     query.prepare("SELECT password FROM user WHERE username = :USER");
//     query.bindValue(":USER", userName);

//     if (!query.exec()) {
//         qDebug() << "查询失败:" << query.lastError().text();
//         return "查询失败";
//     }
//     int count = 0;
//     if (query.next()) {
//         count++;
//         QString storedPwd = query.value(0).toString();
//         // 实际中应该使用加密比较
//         if (storedPwd == password) {
//             qDebug() << "登录成功";
//             return "登录成功";
//         } else {
//             qDebug() << "密码错误";
//             return "密码错误";
//         }
//     } else {
//         qDebug() << "该用户不存在";
//         // return "该用户不存在";
//     }
//     if (count == 0) {
//         qDebug() << "未找到用户，查询返回0条记录";

//         // 检查表是否存在
//         QSqlQuery checkTable;
//         checkTable.exec("SELECT COUNT(*) FROM user");
//         if (checkTable.next()) {
//             qDebug() << "user表总记录数:" << checkTable.value(0).toInt();
//         }

//         return "该用户不存在";
//     }
// }
iDatabase::iDatabase(QObject *parent)
    : QObject{parent}
{
    initDatabase();
}
