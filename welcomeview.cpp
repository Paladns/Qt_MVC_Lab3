#include "welcomeview.h"
#include "ui_welcomeview.h"
#include <QDebug>

WelcomeView::WelcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeView)
{
    qDebug()<<"create goWelcome";
    ui->setupUi(this);
}

WelcomeView::~WelcomeView()
{
    qDebug()<<"destroy goWelcome";
    delete ui;
}

void WelcomeView::on_btDepartment_clicked()
{
    emit goDepartment();
}


void WelcomeView::on_btDoctor_clicked()
{
    emit goDoctor();
}


void WelcomeView::on_btPatient_clicked()
{
    emit goPatient();
}

