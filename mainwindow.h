#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QDebug>
#include <QMainWindow>
#include "secdialog.h"
#include "menu.h"
#include <QSqlDatabase>
#include "employes.h"
#include"login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pb_mdpOublie_clicked();

    void on_pushButton_3_clicked();

    void on_btn_changerMdp_clicked();

private:
    Ui::MainWindow *ui;

        secDialog *SecDialog;
        menu *Menu ;

        Employes i;
        login l;

};
#endif // MAINWINDOW_H
