#include "loginview.h"
#include "ui_loginview.h"
#include "idatabase.h"

LoginView::LoginView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginView)
{
    ui->setupUi(this);
}

LoginView::~LoginView()
{
    delete ui;
}

void LoginView::on_btSignin_clicked()
{
    // iDatabase::getInstance();       //这里获取的 话是不会再次给到对象的

    QString res = iDatabase::getInstance().userLogin(ui->inputUserName->text(),
                                                     ui->inputUserPassword->text());
    if(res == "登录成功"){
        qDebug()<<"登录成功";
        emit loginSuccess();        //按钮-传递信号
    }
}

