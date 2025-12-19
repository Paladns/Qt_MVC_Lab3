#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "welcomeview.h"
#include "doctorview.h"
#include "departmentview.h"
#include "patientview.h"
#include "patienteditview.h"
//#include


QT_BEGIN_NAMESPACE
namespace Ui { class MasterView; }
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();

public slots:
    void goLoginView();
    void goWelcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPatientEditView(int rowNo);       //病人管理的

    void goPreviousView();

    void pushWidgetToStackView(QWidget *widget);


private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    Ui::MasterView *ui;


    WelcomeView *welcomeView;
    DoctorView *doctorView;
    PatientView *patientView;
    PatientEditView *patientEditView;
    DepartmentView *departmentView;
    LoginView *loginView;










};
#endif // MASTERVIEW_H
