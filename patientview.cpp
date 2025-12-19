#include "patientview.h"
#include "ui_patientview.h"
#include "idatabase.h"

PatientView::PatientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientView)
{
    ui->setupUi(this);

    // 设置表格
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //含操作
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);//一次一行
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);  //表格只显示 不可操作
    ui->tableView->setAlternatingRowColors(true);           //不同行不同颜色

    //要在这里表映射数据
    iDatabase &idata = iDatabase::getInstance();
    if(idata.initPatientModel()){
        ui->tableView->setModel(idata.patientTableModel);
        ui->tableView->setSelectionModel(idata.thePatientSelection);
    }
}

PatientView::~PatientView()
{
    delete ui;
}

void PatientView::on_btAdd_clicked()
{
    int currow = iDatabase::getInstance().addNewPatient();
    emit goPatientEdit(currow);   //传递信号 然后进入patient edit里面
}


void PatientView::on_btSearch_clicked()
{
    QString filter = QString("name like '%%1%'").arg(ui->txtSearch->text());
    iDatabase::getInstance().searchPatient(filter);
}


void PatientView::on_btDelete_clicked()
{
    iDatabase::getInstance().deletePatient();
}


void PatientView::on_btEdit_clicked()
{
    QModelIndex curIndex = iDatabase::getInstance().thePatientSelection->currentIndex();     //和获取下表

    emit goPatientEdit(curIndex.row());
}

