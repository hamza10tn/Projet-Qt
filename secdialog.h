#ifndef SECDIALOG_H
#define SECDIALOG_H
#include<QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include "employes.h"
#include <QProgressBar>
#include <QSlider>
#include "stat_combo.h"
#include<QTableView>
#include"arduino.h"
#include"menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {

class secDialog;
}
QT_END_NAMESPACE
class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

private slots:

    void update_label();

    void on_pushButton_9_clicked();

    void on_pushButton_15_clicked();

    void on_pb_ajouter_7_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_8_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_16_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_6_textEdited(const QString &arg1);

    void on_lineEdit_7_textEdited(const QString &arg1);

    void on_pushButton_10_clicked();

    void on_lineEdit_4_textEdited(const QString &arg1);

    void on_lineEdit_5_textEdited(const QString &arg1);

    void on_pushButton_17_clicked();

    void on_lineEdit_4_editingFinished();

    void on_pushButton_18_clicked();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_lineEdit_7_editingFinished();

    void on_nom_textEdited(const QString &arg1);

    void on_email_editingFinished();

    void on_pwd_editingFinished();

    void on_age_textEdited(const QString &arg1);

    void on_age_editingFinished();
    void on_pushButton_10_clicked(const QString &arg1);

    void on_lineEdit_8_textEdited(const QString &arg1);

    void on_pushButton_13_clicked();

    void on_pushButton_12_clicked();

    void on_comboBox_3_textHighlighted(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_stackedWidget_currentChanged(int index);

    void on_pushButton_11_clicked();

    void on_pushButton_19_clicked();

    void on_lineEdit_8_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_9_textEdited(const QString &arg1);

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_stackedWidget_objectNameChanged(const QString &objectName);

private:
    Ui::secDialog *ui;
    Employes i;
    stat_combo *s;
    QProgressBar* bar;
    QSlider* slider;
    QByteArray data;
     QByteArray data1;
     QTableView* tableView;
     Arduino A;
    menu *Menu ;

};

#endif // SECDIALOG_H
