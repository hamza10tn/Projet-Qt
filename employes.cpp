#include "employes.h"
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include "connection.h"
#include <QMessageBox>




Employes::Employes(){}
Employes:: Employes(int IDEMP,QString NOM,QString PRENOM,QString EMAIL ,QString POSTE,int AGE,QString PWD,float SALAIRE){

     this->IDEMP=IDEMP ;
     this->NOM=NOM ;
     this->PRENOM=PRENOM ;
     this->EMAIL=EMAIL ;
     this->POSTE=POSTE ;
     this->AGE=AGE ;
     this->PWD =PWD ;
     this->SALAIRE =SALAIRE ;
}
int Employes::getID(){return IDEMP;}
QString Employes::getNOM(){return NOM;}
QString Employes::getPRENOM(){return PRENOM;}
QString Employes::getEMAIL(){return EMAIL;}
QString Employes::getPOSTE(){return POSTE;}
int Employes::getAGE(){return AGE;}
QString Employes::getPWD(){return PWD;}
float Employes::getSALAIRE(){return SALAIRE;}

void Employes::setID(int IDEMP){ this->IDEMP=IDEMP;}
void Employes::setNOM(QString NOM){ this->NOM=NOM;}
void Employes::setPRENOM(QString PRENOM){ this->PRENOM=PRENOM;}
void Employes::setEMAIL(QString EMAIL){ this->EMAIL=EMAIL;}
void Employes::setPOSTE(QString POSTE){ this->POSTE=POSTE;}
void Employes::setAGE(int AGE){ this->AGE=AGE;}
void Employes::setPWD(QString PWD){ this->PWD=PWD;}
void Employes::setSALAIRE(float SALAIRE){ this->SALAIRE=SALAIRE;}
bool Employes::ajouter() {

    QSqlQuery query;
    QString res1 = QString :: number(IDEMP);
    QString res2 = QString :: number(AGE);
    QString res3 = QString :: number(SALAIRE);
    query.prepare("INSERT INTO EMPLOYES (IDEMP, NOM, PRENOM, EMAIL, POSTE,AGE,PWD,SALAIRE) VALUES (:IDEMP, :NOM, :PRENOM , :EMAIL , :POSTE , :AGE , :PWD ,:SALAIRE) ");
    query.bindValue(":IDEMP", res1);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":AGE",res2);
    query.bindValue(":PWD", PWD);
     query.bindValue(":SALAIRE", res3);

    return query.exec();
}


////afficher////
QSqlQueryModel * Employes :: afficher()
{
QSqlQueryModel * model=new QSqlQueryModel ();
model->setQuery("select * from EMPLOYES");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEMP"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("POSTE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("PWD"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("SALAIRE"));
return model;
}

////supprimer////
bool Employes ::supprimer(int id)
{
QSqlQuery query;
QString res1=QString ::number(id);
query.prepare("delete from EMPLOYES where IDEMP= :id");
query.bindValue(":id",res1);
return query.exec();
}
////modifier////

bool Employes::modifier(int IDEMP)
{
     QSqlQuery query;
     QString res1=QString ::number(IDEMP);
     QString res2 = QString :: number(AGE);
     QString res3 = QString :: number(SALAIRE);

     query.prepare("UPDATE EMPLOYES SET NOM=:NOM,PRENOM=:PRENOM,EMAIL=:EMAIL,POSTE=:POSTE,AGE=:AGE,PWD=:PWD,SALAIRE=:SALAIRE  where IDEMP=:IDEMP");
     query.bindValue(":IDEMP",res1);
     query.bindValue(":NOM",NOM);
     query.bindValue(":PRENOM",PRENOM);
     query.bindValue(":EMAIL",EMAIL);
     query.bindValue(":POSTE",POSTE);
     query.bindValue(":AGE",res2);
     query.bindValue(":PWD",PWD);
     query.bindValue(":SALAIRE",res3);



     return query.exec();
}

QSqlQueryModel * Employes:: Recherche(QString a){

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM EMPLOYES WHERE ( NOM LIKE '%"+a+"%' OR PRENOM LIKE '%"+a+"%')");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDEMP"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("POSTE"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));
      model->setHeaderData(6,Qt::Horizontal,QObject::tr("PWD"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("SALAIRE"));



    return  model ;
}



