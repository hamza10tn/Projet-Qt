#include "type_service.h"

type_service::type_service()
{
  id = 0;
  typeService ="";
}
type_service::type_service(int id,QString typeService)
{
  this->id=id;
  this->typeService=typeService;
}
bool type_service::ajouter(){
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("INSERT INTO type_service(id, typeservice) "
                  "VALUES(:id ,:typeservice)");

    query.bindValue(":id", res);
    query.bindValue(":typeservice",typeService);

    return query.exec();
}

QSqlQueryModel * type_service::combo_box(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("Select ID from TYPE_SERVICE");
    return model;
}
bool type_service::modifier(){
    QSqlQuery query;
    QString res= QString::number(id);

    query.prepare("UPDATE type_service SET typeservice=:typeservice WHERE (id =:id)");
    query.bindValue(":id", res);
    query.bindValue(":typeservice",typeService);

    return query.exec();
}

QSqlQueryModel*type_service::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("Select * from type_service");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("typeservice"));

    return model;
}

bool type_service::supprimer(QString id)
{
    QSqlQuery query;
    QString res= QString(id);
    query.prepare("Delete from type_service where id = :id");
    query.bindValue(":id", res);
    return query.exec();
}

