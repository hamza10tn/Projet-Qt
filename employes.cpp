#include "employes.h"
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include "connection.h"
#include<QtSql/QSqlQueryModel>
#include<QtSql/QSqlQuery>
#include <QTextBrowser>
#include <QFileDialog>
#include<QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include<QPrinter>
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
//executer les requetes sql
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
    //affiche lees donnees f tables view
QSqlQueryModel * model=new QSqlQueryModel ();
//tekhouli les donnes mel base
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

QSqlQueryModel* Employes::triAge()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM EMPLOYES ORDER BY AGE");

    return model;
}
void Employes::exporterpdf(QTextBrowser *text)
    {

          // QString tt;
            QSqlQuery qry;
            std::list<QString> tt;
            qry.exec("select * from EMPLOYES");
            while(qry.next())
            {
                tt.push_back("IDEMP: "+qry.value(0).toString()+"\n"+"NOM "+qry.value(1).toString()+"\n"+"PRENOM: "+qry.value(2).toString()+"\n"+"EMAIL: "+qry.value(3).toString()+"\n"+"POSTE: "+qry.value(4).toString()+"\n"+"\n"+"AGE: "+qry.value(5).toString()+"\n"+"\n"+"PWD: "+qry.value(6).toString()+"\n"+"\n"+"SALAIRE: "+qry.value(7).toString()+"\n");

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


bool Employes::verifEmailAndId(int id,QString email)
{
    QSqlQuery query ;
    query.prepare("SELECT * FROM EMPLOYES WHERE IDEMP=:id AND EMAIL=:EMAIL");
    query.bindValue(":id", id);
    query.bindValue(":EMAIL", email);
    if (query.exec() && query.next()) {

        return true;
    } else {
        // The query either didn't execute successfully or didn't return any results
        return false;
    }
}
