#include "menu.h"
#include "ui_menu.h"
#include "secdialog.h"
#include<QDebug>
#include "connection.h"
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_2_clicked()
{
     this->hide();
     secDialog SecDialog;
    SecDialog.setModal(true);
     SecDialog.exec();
}

void menu::on_pushButton_clicked()
{

}
