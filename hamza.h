#ifndef HAMZA_H
#define HAMZA_H
#include<QFileDialog>
#include<QLabel>
#include<QTableView>
#include<QProgressBar>
#include"QStandardItemModel"
#include "arduino.h"
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "vehicule.h"
namespace Ui {
class hamza;
}

class hamza : public QDialog
{
    Q_OBJECT

public:
    explicit hamza(QWidget *parent = nullptr);
    ~hamza();

private slots:
    void on_pushButton_quitter_clicked();
    void on_pushButton_ajouter_clicked();
    void on_pushButton_page1_clicked();
    void on_pushButton_page2_clicked();
     void on_pushButton_page3_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_chercher_clicked();
    void on_pushButton_browseimage_clicked();
    void on_pushButton_pdf_clicked();

    void showTime();



    void on_pushButton_page4_clicked();



    void on_pushButton_tri_modeleAZ_clicked();



    void on_pushButton_tri_modeleZA_clicked();


    void on_pushButton_insertion_image_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_temp_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::hamza *ui;
    Vehicule V;
       QProgressBar* bar;
           QSlider* slider;
             QByteArray data1;
            QTableView* tableView;

             QStandardItemModel *model;

             Arduino A;
             QByteArray data;
};

#endif // HAMZA_H
