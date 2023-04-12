#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QDebug>
#include <QPixmap>
#include "connection.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/ferja/Documents/loginApp/image/img1.png");
    int w =ui->label_pic->width();
    int h =ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->statusbar->addPermanentWidget(ui->label_3);
    ui->statusbar->addPermanentWidget(ui->progressBar);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDebug () <<"closing the connection to database";

}


void MainWindow::on_pushButton_login_clicked()
{

       int username = ui->lineEdit_username->text().toInt() ;
        QString password = ui->lineEdit_password->text();

       bool test= l.connect(username,password);

     if(test){
         this->hide();
         qDebug ()<<test ;
          menu Menu;
          Menu.setModal(true);
          Menu.exec() ;
           }
            else {
           ui->statusbar->showMessage("username and password is  not correct" ,5000);


     }}




void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit_username->setText("");
    ui->lineEdit_password->setText("");
}



void MainWindow::on_pb_mdpOublie_clicked()
{

        ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_3_clicked()
{
        QString EMAIL = ui->lineEdit_username_2->text();
        QString reponse = ui->lineEdit_reponse->text();
        QSqlQuery query;
        query.prepare("SELECT REPONSE_QS FROM EMPLOYES WHERE EMAIL = :EMAIL");
        query.bindValue(":EMAIL", EMAIL);
        query.exec();
        if (query.next())
        {
            QString Reponse_qs = query.value(0).toString();
            if (reponse == Reponse_qs)
            {
                // La réponse est correcte, on ouvre la fenêtre pour changer le mot de passe
                ui->stackedWidget->setCurrentIndex(2);
            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                    QObject::tr("LA RÉPONSE À LA QUESTION SECRÈTE EST INCORRECTE.\nCLIQUEZ SUR ANNULER POUR REVENIR."), QMessageBox::Ok);
            }
        }
    }



void MainWindow::on_btn_changerMdp_clicked()
{
         QString EMAIL = ui->lineEdit_username1->text();
        QString PWD = ui->lineEdit_password_2->text();
        QSqlQuery query;
        query.prepare("UPDATE EMPLOYES SET PWD = :PWD WHERE EMAIL = :EMAIL");
        query.bindValue(":PWD", PWD);
        query.bindValue(":EMAIL", EMAIL);
        if (query.exec())
        {
            QMessageBox::information(nullptr, QObject::tr("SUCCÈS"),
                QObject::tr("LE MOT DE PASSE A ÉTÉ CHANGÉ AVEC SUCCÈS.\nCLIQUEZ SUR ANNULER POUR REVENIR."), QMessageBox::Ok);
            ui->stackedWidget->setCurrentIndex(0);
        }
        else
        {
            QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                QObject::tr("UNE ERREUR S'EST PRODUITE LORS DU CHANGEMENT DE MOT DE PASSE.\nCLIQUEZ SUR ANNULER POUR REVENIR."), QMessageBox::Ok);
        }
    }

