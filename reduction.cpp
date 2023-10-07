#include "reduction.h"

reduction::reduction()
{
    id = 0;
    code ="";
}
reduction::reduction(int id,QString code)
{
    this->id = id;
    this->code = code;
}

bool reduction::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("INSERT INTO reduction(id, code) "
                  "VALUES(:id ,:code)");

    query.bindValue(":id", res);
    query.bindValue(":code",code);

    return query.exec();
}

QSqlQueryModel*reduction::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from reduction");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("code"));

    return model;
}

bool reduction::supprimer(QString id)
{
    QSqlQuery query;
    QString res= QString(id);
    query.prepare("Delete from reduction where id = :id");
    query.bindValue(":id", res);
    return query.exec();
}

bool reduction::supprimerParCode(QString id)
{
    QSqlQuery query;
    QString res= QString(id);
    query.prepare("Delete from reduction where code = :id");
    query.bindValue(":id", res);
    return query.exec();
}
