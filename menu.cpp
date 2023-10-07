#include "menu.h"
#include "ui_menu.h"
#include "secdialog.h"
#include<QDebug>
#include "connection.h"
#include "sessionuser.h"
#include "login.h"
#include <QDialog>
#include "mainwindow.h"
#include "rdv.h"
#include "hamza.h"
#include "maissa.h"

#include "samar.h"

menu::menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    QString poste =SessionUser::getInstance()->getConnectedUser()->getPOSTE();
    qDebug()<<poste;
    if(poste=="Admin"){
        qDebug()<<"enter";

        //ui->AccountMenuBtn->setDisabled(false);
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

void menu::on_AccountMenuBtn_clicked()
{


}

void menu::on_GestionDesRdvbtn_clicked()
{

    r = new rdv(this); // allocated space for a new MyDialog
                                         // while also giving a parent class of
                                         // this, the MainWindow class
            r->show();
}

void menu::on_GestionClientBtn_clicked()
{
    c = new samar(this); // allocated space for a new MyDialog
                                         // while also giving a parent class of
                                         // this, the MainWindow class
            c->show();
}

void menu::on_GestionDesEqbtn_clicked()
{
    j = new jawher(this); // allocated space for a new MyDialog
                                         // while also giving a parent class of
                                         // this, the MainWindow class
            j->show();
}

void menu::on_GestionDesVehiculebtn_clicked()
{
    h = new hamza(this); // allocated space for a new MyDialog
                                         // while also giving a parent class of
                                         // this, the MainWindow class
            h->show();
}

void menu::on_GestionDesServicebtn_clicked()
{
    m = new maissa(this); // allocated space for a new MyDialog
                                         // while also giving a parent class of
                                         // this, the MainWindow class
            m->show();
}
