#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>

PatientEditView::PatientEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    mapper = new QDataWidgetMapper();
    QSqlTableModel *tableModel = iDatabase::getInstance().patientTableModel;
    mapper->setModel(tableModel);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    //添加映 关于patient的数据表
    mapper->addMapping(ui->EditID, tableModel->fieldIndex("ID"));
    mapper->addMapping(ui->EditName, tableModel->fieldIndex("NAME"));
    mapper->addMapping(ui->EditCard, tableModel->fieldIndex("ID_CARD"));
    mapper->addMapping(ui->spinH, tableModel->fieldIndex("HEIGHT"));
    mapper->addMapping(ui->spinW, tableModel->fieldIndex("WEIGHT"));
    mapper->addMapping(ui->EditPhone, tableModel->fieldIndex("MOBILEPHONE"));
    mapper->addMapping(ui->dateEdit, tableModel->fieldIndex("DOB"));        //出生日期
    mapper->addMapping(ui->comboGender, tableModel->fieldIndex("SEX"));
    mapper->addMapping(ui->EditTime, tableModel->fieldIndex("CREATEDTIMESTAM"));

    mapper->setCurrentIndex(index);

    // ui->EditID->setEnabled(false);      //不能这样编辑个UUid
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_btSave_clicked()
{
    iDatabase::getInstance().submitPatient();

    emit goPrevious();
}


void PatientEditView::on_pushButton_2_clicked()
{
    iDatabase::getInstance().revertPatient();

    emit goPrevious();
}

