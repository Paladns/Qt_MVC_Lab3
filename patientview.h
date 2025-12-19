#ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QWidget>
#include <QDataWidgetMapper>

namespace Ui {
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT

public:
    explicit PatientView(QWidget *parent = nullptr);
    ~PatientView();

private slots:
    void on_btAdd_clicked();


    void on_btSearch_clicked();

    void on_btDelete_clicked();

    void on_btEdit_clicked();

signals:
    void goPatientEdit(int idx);        //加上个行号

private:
    Ui::PatientView *ui;

    QDataWidgetMapper *dataMapper;      //数据映射
};

#endif // PATIENTVIEW_H
