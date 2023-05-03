#include "equipment.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QString>
#include <QtDebug>
#include<QPdfWriter>
#include<QPainter>

Equipment::Equipment()
{
    idequi=0;
    nombre=0;
    nomE=" ";
    date=" ";
    description=" ";
    video=" ";
}
Equipment::Equipment(int idequi,QString nomE,int nombre,QString date ,QString description,QString video)
{
    this->idequi=idequi;
      this->nomE=nomE;
    this->nombre=nombre;

    this->date=date;
    this->description=description;
    this->video=video;
}
int Equipment::getidequi()
{
   return idequi;
}
QString Equipment::getdate(){
   return date;
}
int Equipment::getnombre()
{ return nombre;
}
QString Equipment::getnomE()
{ return nomE;
}
QString Equipment::getdescription()
{ return description;
}
QString Equipment::getvideo()
{ return video;
}
void Equipment::setidequi(int idequi)
{     this->idequi=idequi;

}
void Equipment::setnombre(int nombre)
{     this->nombre=nombre;
}
void Equipment::setnomE(QString nomE){     this->nomE=nomE;
}
void Equipment::setdescription(QString description){     this->description=description;
}
void Equipment::setvideo(QString video){     this->video=video;
}
void Equipment::setdate(QString date)
{
    this->date=date;
}


bool Equipment::ajouter()
{


    QSqlQuery query;
        QString res1 = QString :: number(idequi);

    query.prepare("INSERT INTO EQUIPEMENT (ID_EQUI, NOM_EQUI, NOMBRE, DATE_ACHAT, DESCRIP_EQUI, VIDEO) "
                  "VALUES (:idequi, :nomE, :nombre, :date, :description, :video)");

    query.bindValue(":idequi", res1);
    query.bindValue(":nomE", nomE);
    query.bindValue(":nombre", nombre);
    query.bindValue(":date", date);
    query.bindValue(":description", description);
    query.bindValue(":video", video);
    return query.exec();


}


QSqlQueryModel * Equipment::afficher()
{
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("Select * from EQUIPEMENT");
    return  model;
}



bool Equipment::supprimer(int ID_EQUI)
{
    QSqlQuery query;

    QString SqlQuery = "Delete FROM EQUIPEMENT WHERE ID_EQUI = :ID_EQUI;";
    query.prepare(SqlQuery);

    query.bindValue(":ID_EQUI",ID_EQUI);

    return query.exec();
}

bool Equipment::modifier(int idequi ,QString nomE ,int nombre, QString date , QString description, QString video)
{
    QSqlQuery query;
    QString SqlQuery = "UPDATE EQUIPEMENT set NOM_EQUI=:nomE,NOMBRE=:nombre,DATE_ACHAT=:date,DESCRIP_EQUI=:description,VIDEO=:video where id_equi=:idequi";
    query.prepare(SqlQuery);

    query.bindValue(":ID_EQUI",idequi);
    query.bindValue(":NOM_EQUI",nomE);
    query.bindValue(":NOMBRE",nombre);
    query.bindValue(":DATE_ACHAT",date);
    query.bindValue(":DESCRIP_EQUI",description);
    query.bindValue(":VIDEO",video);
    return query.exec();




    bool result = query.exec();
    if (query.numRowsAffected() == 0) {
        result = false;
    }
    return result;


}
//pdf

void Equipment::genererPDFact()
{

   QPdfWriter pdf("C:/Users/ferja/Desktop/ferjani/loginApp/pdf/publication.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::green);
        painter.setFont(QFont("Arial", 50));
        painter.drawText(1100,1200,"Liste Des equipment");
        painter.setPen(Qt::red);
        painter.setFont(QFont("Arial", 15));
        painter.drawRect(100,100,7300,2600);
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(500,3300,"ID_EQUI");
        painter.drawText(2000,3300,"NOM_EQUI");
        painter.drawText(3000,3300,"NOMBRE");
        painter.drawText(4000,3300,"DATE_ACHAT");
        painter.drawText(5000,3300,"DESCRIPTION_EQUI");
        painter.drawText(7000,3300,"VIDEO");






        QSqlQuery query;
        query.prepare("select * from EQUIPEMENT");
        query.exec();
        while (query.next())
        {
            painter.drawText(500,i,query.value(0).toString());
            painter.drawText(2000,i,query.value(1).toString());
            painter.drawText(3000,i,query.value(2).toString());
            painter.drawText(4000,i,query.value(4).toString());
            painter.drawText(5000,i,query.value(3).toString());
            painter.drawText(7000,i,query.value(5).toString());

           i = i + 500;
        }


}


//tri asc desc
QSqlQueryModel * Equipment::triB()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EQUIPEMENT ORDER BY DATE_ACHAT ASC");
        return model;
}

        QSqlQueryModel * Equipment::triA()
        {
            QSqlQueryModel * model= new QSqlQueryModel();
                model->setQuery("SELECT * FROM EQUIPEMENT ORDER BY DATE_ACHAT DESC");
                return model;
        }



//recherche
QSqlQueryModel* Equipment::Recherche(QString recherche)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("SELECT * FROM EQUIPEMENT WHERE ID_EQUI LIKE '"+recherche+"%' ");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_EQUI"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_EQUI"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOMBRE"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_ACHAT"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DESCRIPTION_EQUI"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("VIDEO"));
return model;
}
