#ifndef SAMAR_H
#define SAMAR_H
#include <QMessageBox>
#include <QDebug>
#include <QMainWindow>
#include "client.h"
#include "qratingbar.h"
#include "rating.h"
#include"dialog.h"
QT_BEGIN_NAMESPACE
#include <QDialog>

namespace Ui {
class samar;
}

class samar : public QDialog
{
    Q_OBJECT

public:
    explicit samar(QWidget *parent = nullptr);
    ~samar();
    QString randomString(int length);
      void generateCaptcha();


private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_9_clicked();

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();
    void onRatingChanged(int rating);

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_5_clicked();

    void on_label_20_linkActivated(const QString &link);

private:
    Ui::samar *ui;
   Client i;
       Dialog *s;
       Ratingbar *m_ratingBar;
       int IDEMP=1;
       rating r;
       QString captcha;
};

#endif // SAMAR_H
