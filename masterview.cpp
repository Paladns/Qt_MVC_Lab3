#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    // this->setWindowFlag(Qt::FramelessWindowHint);       //这个是挡住 上面的退出 隐藏的上方窗口

    goLoginView();

    iDatabase::getInstance();           //建立连接
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    qDebug()<< "goLoginView......";
    loginView = new LoginView(this);

    pushWidgetToStackView(loginView);

    connect(loginView, SIGNAL(loginSuccess()),this, SLOT(goWelcomeView()));     //这个是？
}

void MasterView::goWelcomeView()
{
    qDebug()<< "goWelcomeview......";
    welcomeView = new WelcomeView(this);
    pushWidgetToStackView(welcomeView);
    ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

    connect(welcomeView, SIGNAL(goDoctor()),this, SLOT(goDoctorView()));        //接收到 这里的SIGNAL就响应对应的SLOT槽函数
    connect(welcomeView, SIGNAL(goDepartment()),this, SLOT(goDepartmentView()));
    connect(welcomeView, SIGNAL(goPatient()),this, SLOT(goPatientView()));
}

void MasterView::goDoctorView()
{
    qDebug()<< "go Doctor View......";
    doctorView = new DoctorView(this);
    pushWidgetToStackView(doctorView);
}

void MasterView::goDepartmentView()
{
    qDebug()<< "go Department View......";
    departmentView = new DepartmentView(this);
    pushWidgetToStackView(departmentView);
}

void MasterView::goPatientView()
{
    qDebug()<< "go Patient View......";
    patientView = new PatientView(this);
    pushWidgetToStackView(patientView);

    connect(patientView, SIGNAL(goPatientEdit(int)),this, SLOT(goPatientEditView(int)));      //接收信号就进入用户添加
}

void MasterView::goPatientEditView(int rowNo)
{
    qDebug()<< "go PatientEdit View......";
    patientEditView = new PatientEditView(this, rowNo);
    pushWidgetToStackView(patientEditView);


    connect(patientEditView, SIGNAL(goPrevious()),this, SLOT(goPreviousView())); // 添加/修改完毕 退出来
}

void MasterView::goPreviousView()
{

    int count = ui->stackedWidget->count();
    if(count>1){
        ui->stackedWidget->setCurrentIndex(count-2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count-1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count-1);       //最新的view
    ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());     //把标题 打到label上
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();       //回到之前界面
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    // 通过名字 来判断该不该显示
    int count = ui->stackedWidget->count();     //
    if(count>1){
        ui->btBack->setEnabled(true);       //不止一个界面  要有返回功能
    }else{
        ui->btBack->setEnabled(false);
    }

    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    if(title == "登录"){
        ui->btBack->setEnabled(false);
        ui->btLogout->setEnabled(true);
    }else{
        ui->btLogout->setEnabled(false);
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

