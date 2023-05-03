#ifndef RDV_H
#define RDV_H
#include"rendez_vous.h"
#include <QMainWindow>
#include<QString>
#include"connexion.h"
#include<QPieSeries>
#include<QChart>
#include<QtCharts>
#include<QChartView>
#include<QGridLayout>
#include <QtCharts/QChartView>
//#include"arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class rdv; }
QT_END_NAMESPACE

class rdv : public QMainWindow
{
    Q_OBJECT

public:

    rdv(QWidget *parent = nullptr);
    ~rdv();


private:
Connexion cc;
    Ui::rdv *ui;

}
;
#endif // RDV_H
