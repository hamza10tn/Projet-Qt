#include "menu.h"
#include "ui_menu.h"
#include "secdialog.h"
#include<QDebug>
#include "connection.h"
#include "sessionuser.h"
menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QString poste =SessionUser::getInstance()->getConnectedUser()->getPOSTE();
    qDebug()<<poste;
    if(poste=="Admin"){
        qDebug()<<"enter";

        ui->AccountMenuBtn->setDisabled(false);
        ui->GestionDesEqbtn->setDisabled(false);
        ui->GestionClientBtn->setDisabled(false);
        ui->GestionDesRdvbtn->setDisabled(false);
        ui->GestionEmployeBtn->setDisabled(false);
        ui->GestionDesServicebtn->setDisabled(false);
        ui->GestionDesVehiculebtn->setDisabled(false);
    }else if(poste=="ResponsableClient"){
        ui->GestionClientBtn->setDisabled(false);

    }else if(poste=="Technicien"){
        ui->GestionDesEqbtn->setDisabled(false);

    }
    else if(poste=="Technicien superieur"){
        ui->GestionDesServicebtn->setDisabled(false);

        }
    else if(poste=="inginieur"){
        ui->GestionDesVehiculebtn->setDisabled(false);

        }

}

menu::~menu()
{
    delete ui;
}



void menu::on_GestionEmployeBtn_clicked()
{
    this->hide();
    secDialog SecDialog;
   SecDialog.setModal(true);
    SecDialog.exec();
}
