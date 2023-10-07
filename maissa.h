#ifndef MAISSA_H
#define MAISSA_H
#include <QMainWindow>
#include <QFileDialog>
#include "type_service.h"
#include "reduction.h"
#include "service.h"
#include <QVBoxLayout>
#include "stat.h"
#include "achat.h"
#include "arduino.h"
#include <QDialog>

namespace Ui {
class maissa;
}

class maissa : public QDialog
{
    Q_OBJECT

public:
    explicit maissa(QWidget *parent = nullptr);
    ~maissa();
    void display_listes();
       void refresh_stat();
       void sendSMS(QString recipient, QString message);

private slots:
       void on_addTypeService_clicked();
        void on_refresh_toggled(bool checked);

        void on_modifierTypeService_clicked();

        void on_supprimerchantier_clicked();

        void on_tab1_activated(const QModelIndex &index);

        void on_addTypeService_2_clicked();

        void on_supprimerchantier_2_clicked();

        void on_tab1_2_activated(const QModelIndex &index);

        //void on_refresh_2_clicked();

        void on_refresh_2_toggled(bool checked);



        void on_addServiceButton_clicked();

        void on_id_combo_activated(const QString &);

        void on_comboBox_6_id_activated(const QString &);

        void on_modifierchantier_6_clicked();

        void on_supprimerchantier_5_clicked();

        void on_tabcha_2_activated(const QModelIndex &index);

        void on_supprimerservice_clicked();



        void on_refresh_4_toggled(bool checked);

        void on_comboBox_2_activated(const QString &arg1);

        void on_pb_ok1_2_clicked();

        void on_pushButton_11_clicked();

    void on_addTypeService_5_clicked();

    void on_typeservice_3_activated(const QString &);

    void on_tab1_5_activated(const QModelIndex &index);

    void on_refresh_6_toggled(bool checked);

    void on_pushButton_clicked();
    void detectFlamme();



    void on_pushButton_2_clicked();

private:
    Ui::maissa *ui;
    type_service tmp_tab1;
       reduction tmp_tab2;
       service tmp_tab3;
       achat tmp_tab4;

       QVBoxLayout* mainLayout;
       Stat s;
       Arduino A;
       QByteArray data ;
};

#endif // MAISSA_H
