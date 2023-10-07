#include "vehicule.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>


Vehicule::Vehicule()
{
    matricule="";
    modele="";
    type="";
    etat="";
}
Vehicule::Vehicule(QString matricule,QString modele,QString type,QString etat)
{
  this->matricule=matricule;
  this->modele=modele;
  this->type=type;
  this->etat=etat;
    this->temperature=temperature;
}


void Vehicule::setmatricule(QString n){matricule=n;}
void Vehicule::setmodele(QString n){modele=n;}
void Vehicule::settype(QString n){type=n;}
void Vehicule::setetat(QString n){etat=n;}
void Vehicule::settemperatur(int n){temperature=n;}

QString Vehicule::get_matricule(){return matricule;}
QString Vehicule::get_modele(){return modele;}
QString Vehicule::get_type(){return type;}
QString Vehicule::get_etat(){return etat;}
int Vehicule::get_temperature(){return temperature;}

bool Vehicule::ajouter()
{
    bool test=false;
    QSqlQuery query;
        query.prepare("INSERT INTO VEHICULE (matricule, modele, type,etat) "
                      "VALUES (:matricule, :modele, :type ,:etat)");
        query.bindValue(":matricule", get_matricule());
        query.bindValue(":modele", get_modele());
        query.bindValue(":type", get_type());
        query.bindValue(":etat", get_etat());
        query.exec();


    return test;
}

QSqlQueryModel* Vehicule::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM VEHICULE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Matricule"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Modele"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("etat"));




  return model;
}

bool Vehicule::supprimer(QString matricule)
{

    QSqlQuery query;  //query is an object to execute sql queries
    //prepare la requete pour l'execution
        query.prepare("DELETE FROM VEHICULE WHERE MATRICULE = :matricule" );
        query.bindValue(":matricule", matricule );

        bool result=  query.exec(); //execute la requete
        if (query.numRowsAffected() == 0) {
             result = false;
         }

         return result;

}

bool Vehicule::modifier(QString matricule, QString modele, QString type, QString etat)
  {
    QSqlQuery query;
    query.prepare("UPDATE VEHICULE SET MODELE = :modele, TYPE = :type, ETAT = :etat WHERE MATRICULE = :matricule" );
   //:modele :placeholder
    query.bindValue(":modele", modele ); //pour associe la valeur a la placeholder
    //placeholder pour eviter les injections sql
    query.bindValue(":type", type );
    query.bindValue(":etat", etat );
    query.bindValue(":matricule", matricule );

    bool result = query.exec();
    if (query.numRowsAffected() == 0) { //recuperer le nombre de lignes affecté
        result = false;
    }
    return result;
}



bool Vehicule::matriculeExists(QString matricule) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM VEHICULE WHERE matricule=:matricule");
    query.bindValue(":matricule", matricule);
    query.exec();
    query.first(); //la premiere ligne
    int count = query.value(0).toInt();
    return count > 0;
}

//tri asc desc par id
QSqlQueryModel * Vehicule::triB()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VEHICULE ORDER BY MODELE ASC");
        return model;
}


QSqlQueryModel * Vehicule::triA()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VEHICULE ORDER BY MODELE DESC");
        return model;
}

