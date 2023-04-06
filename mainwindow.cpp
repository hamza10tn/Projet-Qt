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

void MainWindow::on_pushButton_2_clicked()
{recuperermotdepasse Recuperermotdepasse;
    Recuperermotdepasse.setModal(true);
    Recuperermotdepasse.exec();


}
