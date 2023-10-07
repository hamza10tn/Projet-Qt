#ifndef RDV_H
#define RDV_H

#include <QDialog>
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
#include"arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class rdv;
}

class rdv : public QDialog
{
    Q_OBJECT

public:
    explicit rdv(QWidget *parent = nullptr);
    ~rdv();

private slots:

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_6_clicked();

    void on_pushButton_2_clicked();


    void on_pushButton_supprimez_clicked();

    void on_tableView_clicked(const QModelIndex &index);




    void on_pushButton_ajouter_rdv_clicked();

    void on_modifier_rdv_clicked();

    void on_chercher_clicked();

    void on_ASC_clicked();

    void on_DESC_clicked();

    void on_pdf_clicked();


    void on_proche_clicked();

    void on_pushButton_7_clicked();

    void on_stat_clicked();

    void on_pushButton_supprimez_2_clicked();

    void on_enregister_temperature_clicked();

    void on_id_editingFinished();
    void on_pushButton_clicked();

private:
    Ui::rdv *ui;
    Connexion cc;
   rendez_vous rr;
Arduino a;
};

#endif // RDV_H
