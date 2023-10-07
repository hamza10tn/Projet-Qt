#include "achat.h"

achat::achat()
{
    id=0;
    id_service=0;
    prix=0;
}
achat::achat(int id,int id_service,float prix)
{
    this->id=id;
    this->id_service=id_service;
    this->prix=prix;
}

QSqlQueryModel * achat::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select nom from service");
    return model;
}


bool achat::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id);
    QString res1= QString::number(prix);
    QString res2= QString::number(id_service);


    query.prepare("INSERT INTO achat(id, id_service, prix) "
                  "VALUES(:id ,:id_service ,:prix)");


    query.bindValue(":id", res);
    query.bindValue(":prix",res1);
        query.bindValue(":id_service",res2);

    return query.exec();
}


QSqlQueryModel*achat::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select a.id,s.nom,s.type,s.description,a.prix from achat a inner join service s on s.id=a.id_service");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id achat"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom de service"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));



    return model;
}

bool achat::supprimer(QString id)
{
    QSqlQuery query;
    QString res= QString(id);
    query.prepare("Delete from achat where id = :id");
    query.bindValue(":id", res);
    return query.exec();
}

