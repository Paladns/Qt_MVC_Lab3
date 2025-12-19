#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>
// #include <QtSql/QSql>
// #include <QtSql/QSqlDatabase>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDataWidgetMapper>
#include <QSqlTableModel>
#include <QItemSelectionModel>

class iDatabase : public QObject
{
    Q_OBJECT
public:

    static iDatabase &getInstance()
    {
        static iDatabase instance;      //这里有潜在的创建对象
        return instance;
    }

    QString userLogin(QString userName, QString password);

private:
    explicit iDatabase(QObject *parent = nullptr);

    iDatabase(iDatabase const&) = delete;
    void operator=(iDatabase const &) = delete;

    QSqlDatabase database;        //定义一个    不然连不了数据库

    void initDatabase();    //连接数据库

signals:

public:
    bool initPatientModel();

    int addNewPatient();

    bool searchPatient(QString filter);
    bool deletePatient();
    bool submitPatient();
    void revertPatient();

    //添加些与数据库相关模型
    QSqlTableModel *patientTableModel;     //数据模型
    QItemSelectionModel *thePatientSelection;      //选择模型

};

#endif // IDATABASE_H
