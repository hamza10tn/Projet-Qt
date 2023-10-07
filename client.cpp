#include "client.h"
#include <QMessageBox>
#include <QString>
#include<QSqlQuery>
#include <QDebug>
#include <QTextBrowser>
#include <QFileDialog>
#include<QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include<QPrinter>
Client::Client(){


}
Client::Client(int ID_C,QString NOM_C,QString PRENOM_C,QString ADRESSE,QString EMAIL_C , int NUM_TEL )
{
    this->ID_C=ID_C;
    this->NOM_C=NOM_C;
    this->PRENOM_C=PRENOM_C;
    this->ADRESSE=ADRESSE;
    this->EMAIL_C=EMAIL_C;
    this->NUM_TEL=NUM_TEL;
    this->FIDELITE=0;
    this->remise=0;

}
int Client::getID_C(){return ID_C;}
QString Client:: getnom_c(){return NOM_C;}
QString Client:: getPRENOM_C(){return PRENOM_C;}
QString Client:: getADRESSE(){return ADRESSE;}
QString  Client::getEMAIL_C(){return EMAIL_C;}
int  Client::getNUM_TEL(){return NUM_TEL;}
int  Client::getFIDELITE(){return FIDELITE;}

void Client::setID_C(int i){this->ID_C=i;}
void Client::setNOM_C(QString n){this->NOM_C=n;}
void Client::setPRENOM_C(QString p){this->PRENOM_C=p;}
void Client::setADRESSE(QString q){this->ADRESSE=q;}
void Client::setEMAIL_C(QString y){this->EMAIL_C=y;}
void Client::setNUM_TEL(int t){this->NUM_TEL=t;}
void Client::setFIDELITE(int F){this->FIDELITE=F;}



bool Client::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(ID_C);
    QString res2 = QString::number(NUM_TEL);
     QString res3 = QString::number(FIDELITE);

    query.prepare("insert into CLIENTS (ID_C, NOM_C, PRENOM_C, ADRESSE ,EMAIL_C ,NUM_TEL, FIDELITE,REMISE)" "values (:ID_C, :NOM_C, :PRENOM_C,:ADRESSE,:EMAIL_C,:NUM_TEL,:FIDELITE,:remise)");

    query.bindValue(":ID_C",res);
    query.bindValue(":NOM_C",NOM_C);
    query.bindValue(":PRENOM_C",PRENOM_C);
    query.bindValue(":ADRESSE",ADRESSE);
    query.bindValue(":EMAIL_C",EMAIL_C);
    query.bindValue(":NUM_TEL",res2);
    query.bindValue(":FIDELITE",res3);
    query.bindValue(":remise",0);



    return query.exec(); //exec() envoie la requete pour l'execution
}


QSqlQueryModel * Client::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from CLIENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_C"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_C"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_C"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL_C"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("FIDELITE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("REMISE"));





    return model;
}


bool Client::supprimer(int ID_C)
{
QSqlQuery query;
QString res=QString::number(ID_C);
query.prepare("Delete from CLIENTS where ID_C= :ID_C");
query.bindValue(":ID_C",res);
return query.exec();
}

bool Client::modifier(int ID_C)
{
    QSqlQuery query;
    QString res=QString ::number(ID_C);
    QString res2 = QString::number(NUM_TEL);
    QString res3 = QString::number(FIDELITE);
    query.prepare("UPDATE CLIENTS SET NOM_C=:NOM_C,PRENOM_C=:PRENOM_C,ADRESSE=:ADRESSE,EMAIL_C=:EMAIL_C,NUM_TEL=:NUM_TEL ,FIDELITE=:FIDELITE where ID_C=:ID_C");
    query.bindValue(":ID_C",res);
    query.bindValue(":NOM_C",NOM_C);
    query.bindValue(":PRENOM_C",PRENOM_C);
    query.bindValue(":ADRESSE",ADRESSE);
    query.bindValue(":EMAIL_C",EMAIL_C);
    query.bindValue(":NUM_TEL",res2);
    query.bindValue(":FIDELITE",res3);



    return query.exec();
}
QSqlQueryModel * Client:: Recherche(QString a){

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CLIENTS WHERE ( NOM_C LIKE '%"+a+"%' )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_C"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM_C"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM_C"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL_C"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("NUM_TEL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("FIDELITE"));

    model->setHeaderData(7,Qt::Horizontal,QObject::tr("REMISE"));



    return  model ;
}
QSqlQueryModel* Client::trifidelite()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM CLIENTS ORDER BY FIDELITE");

    return model;
}
void Client::exporterpdf(QTextBrowser *text)
    {

          // QString tt;
            QSqlQuery qry;
            std::list<QString> tt;
            qry.exec("select * from CLIENTS");
            while(qry.next())
            {
                tt.push_back("ID_C: "+qry.value(0).toString()+"\n"+"NOM_C "+qry.value(1).toString()+"\n"+"PRENOM_C: "+qry.value(2).toString()+"\n"+"ADRESSE: "+qry.value(3).toString()+"\n"+"EMAIL_C: "+qry.value(4).toString()+"\n"+"\n"+"NUM_TEL: "+qry.value(5).toString()+"\n"+"\n"+"FIDELITE: "+qry.value(6).toString()+"\n");

            }

            for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
            {
                text->setText(text->toPlainText()+*it + "\n");
            }

            QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);
            text->print(&printer);
            QMessageBox::information(nullptr, QObject::tr("Export PDF"),
                                      QObject::tr("Export avec succes .\n"
                                                  "Click OK to exit."), QMessageBox::Ok);

    }
bool Client::testerRendezVous(QString mat, int idClient){
    QSqlQuery query;
    int maxfidelite=5;
    int userFidelite;
    int userRemise;
   /* //test d'insertion de rdv
    query.prepare("insert into RDV ( DATE_R, HEURE, MATRICULE ,ID_CLIENT )" "values (:DATE_R, :HEURE, :MATRICULE,:ID_CLIENT)");

    query.bindValue(":DATE_R","12-12-2022");
    query.bindValue(":HEURE","8:00");
    query.bindValue(":MATRICULE",mat);
    query.bindValue(":ID_CLIENT",idClient);
    query.exec();
    //fin test d'insertion de rdv
*/
    query.prepare("SELECT FIDELITE,REMISE FROM CLIENTS where ID_C=:ID_C");
    query.bindValue(":ID_C",idClient);
    query.exec();
    if(query.next()){

    userFidelite=query.value("FIDELITE").toInt();

    userRemise=query.value("REMISE").toFloat();

    if(userRemise==100){
        userRemise=20;
        userFidelite=userFidelite+1;

    }else if(userFidelite==maxfidelite-1){
        userRemise=userRemise+20;
        userFidelite=1;

    }else{
        userFidelite=userFidelite+1;
    }
    query.prepare("update CLIENTS SET FIDELITE=:FIDELITE,REMISE=:REMISE where ID_C=:ID_C");
    query.bindValue(":ID_C",idClient);
    query.bindValue(":FIDELITE",userFidelite);
    query.bindValue(":REMISE",userRemise);

    query.exec();
    qDebug()<<userRemise<<userFidelite;

}else{
        qDebug()<<"Problem de query ";
    }

}
