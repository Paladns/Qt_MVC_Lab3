#ifndef PATIENTEDITVIEW_H
#define PATIENTEDITVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "idatabase.h"

namespace Ui {
class PatientEditView;
}

class PatientEditView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditView(QWidget *parent = nullptr,int index = 0);
    ~PatientEditView();

private slots:
    void on_btSave_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PatientEditView *ui;

    QDataWidgetMapper *mapper;      //数据映射 从表格映射数据库大概


signals:
    void goPrevious();      //一个槽
};

#endif // PATIENTEDITVIEW_H
