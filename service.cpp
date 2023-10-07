#include "service.h"

service::service()
{
    id=0;
    nom="";
    type="";
    description="";
    prix=0;
    }
    service::service(int id,QString nom,QString type,QString description,float prix)
    {
    this->id=id;

    this->nom=nom;
    this->type=type;
    this->description=description;
    this->prix=prix;
    }
    bool service::ajouter(){
        QSqlQuery query;
        QString res= QString::number(id);
        QString res1= QString::number(prix);

        query.prepare("INSERT INTO service(id, nom, type, description, prix) "
                      "VALUES(:id ,:nom ,:type ,:description ,:prix)");

            query.bindValue(":nom", nom);
        query.bindValue(":description", description);
        query.bindValue(":id", res);
        query.bindValue(":prix",res1);
            query.bindValue(":type",type);

        return query.exec();
    }


    QSqlQueryModel * service::combo_box(){
        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select typeservice from type_service");
        return model;
    }

    QSqlQueryModel * service::combo_box_2(){
        QSqlQueryModel * model = new QSqlQueryModel();
        model->setQuery("Select id from service");
        return model;
    }
    bool service::modifier(){
        QSqlQuery query;
        QString res= QString::number(id);
        QString res1= QString::number(prix);

        query.prepare("UPDATE service SET nom=:nom , description=:description , prix=:prix , type=:type WHERE (id =:id)");
        query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":id", res);
    query.bindValue(":prix",res1);
        query.bindValue(":type",type);

        return query.exec();
    }

    QSqlQueryModel*service::afficher()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("Select * from service");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));



        return model;
    }
    bool service::supprimer(QString id)
    {
        QSqlQuery query;
        QString res= QString(id);
        query.prepare("Delete from service where id = :id");
        query.bindValue(":id", res);
        return query.exec();
    }


    QSqlQueryModel *   service::recherche(QString val)
    {
        QSqlQueryModel * model = new QSqlQueryModel();

        model->setQuery("Select * from service WHERE id||NOM||type||description||prix LIKE '%"+val+"%'");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
        return model;
    }

    QSqlQueryModel *  service::trier(QString critere ,QString mode)
    {
       QSqlQueryModel * model= new QSqlQueryModel();

       model->setQuery("Select * from service order by "+critere+" "+mode+"");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr("prix"));
     return model;
    }

    QVector <QString> service::getinforamation(QString id){
        QSqlQuery query,query2;
        QString nom ,type,description, prix;
        QVector <QString> information;
        query.prepare("select * from service WHERE id LIKE "+id+"");
        query.exec();

         while(query.next()){
            nom= query.value(1).toString();
            type =query.value(2).toString();
            description = query.value(3).toString();
            prix= query.value(4).toString();
         }


         information.push_back(nom);
         information.push_back(type);
         information.push_back(description);
         information.push_back(prix);

         return  information;
    }


