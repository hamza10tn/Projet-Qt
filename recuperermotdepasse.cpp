#include "recuperermotdepasse.h"
#include "ui_recuperermotdepasse.h"
#include "employes.h"
#include<QDebug>

#include <random>
#include <iostream>
#include <sstream>
#include "sendmailer.h"
using namespace std;

recuperermotdepasse::recuperermotdepasse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recuperermotdepasse)
{
    ui->setupUi(this);
    ui->widgetEtape2->hide();

}

recuperermotdepasse::~recuperermotdepasse()
{
    delete ui;
}

void recuperermotdepasse::on_validerEtape1_2_clicked()
{
    int id=ui->inputId_2->text().toInt();
    QString email=ui->inputEmail_2->text();
    Employes e;
    bool test=e.verifEmailAndId(id,email);
    if(test){
        random_device rd; // objet pour générer des nombres aléatoires
           mt19937 gen(rd()); // générateur de nombres aléatoires
           uniform_int_distribution<> dis(0, 9); // distribution uniforme de 0 à 9

           // génération des 6 chiffres
           ostringstream oss;
           for (int i = 0; i < 6; i++) {
               int digit = dis(gen);
               oss << digit;
               //oss b3ed el boucle bech ikoun faha el chaine fi .str();

           }

           // conversion de la chaîne de caractères en string
           string generatedCode = oss.str();
            finalCode = QString::fromStdString(generatedCode);
    sendMailer::send(email,"recuperer votre mot de passe ","votre code : = "+finalCode);

    ui->widgetEtape1->hide();
    ui->widgetEtape2->show();


}else{
        QMessageBox::information(nullptr, QObject::tr("Employe n'existe pas "),
                    QObject::tr("Employe n'existe pas.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
