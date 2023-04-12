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
#include <QtCharts>
#include <QChartView>
#include <QHBoxLayout>
Employes::Employes(){}
Employes:: Employes(int IDEMP,QString NOM,QString PRENOM,QString EMAIL ,QString POSTE,int AGE,QString PWD,float SALAIRE,QString REPONSE_QS,QString QUESTION_SECRETE){

     this->IDEMP=IDEMP ;
     this->NOM=NOM ;
     this->PRENOM=PRENOM ;
     this->EMAIL=EMAIL ;
     this->POSTE=POSTE ;
     this->AGE=AGE ;
     this->PWD =PWD ;
    this->SALAIRE =SALAIRE ;
 this->REPONSE_QS =REPONSE_QS;
    this->QUESTION_SECRETE =QUESTION_SECRETE;
}
int Employes::getID(){return IDEMP;}
QString Employes::getNOM(){return NOM;}
QString Employes::getPRENOM(){return PRENOM;}
QString Employes::getEMAIL(){return EMAIL;}
QString Employes::getPOSTE(){return POSTE;}
int Employes::getAGE(){return AGE;}
QString Employes::getPWD(){return PWD;}
float Employes::getSALAIRE(){return SALAIRE;}
QString Employes::getREPONSE_QS(){return REPONSE_QS;}
QString Employes::getQUESTION_SECRETE(){return QUESTION_SECRETE;}

void Employes::setID(int IDEMP){ this->IDEMP=IDEMP;}
void Employes::setNOM(QString NOM){ this->NOM=NOM;}
void Employes::setPRENOM(QString PRENOM){ this->PRENOM=PRENOM;}
void Employes::setEMAIL(QString EMAIL){ this->EMAIL=EMAIL;}
void Employes::setPOSTE(QString POSTE){ this->POSTE=POSTE;}
void Employes::setAGE(int AGE){ this->AGE=AGE;}
void Employes::setPWD(QString PWD){ this->PWD=PWD;}
void Employes::setSALAIRE(float SALAIRE){ this->SALAIRE=SALAIRE;}
void Employes::setREPONSE_QS(QString REPONSE_QS){ this->REPONSE_QS=REPONSE_QS;}
void Employes::setQUESTION_SECRETE(QString QUESTION_SECRETE){ this->QUESTION_SECRETE=QUESTION_SECRETE;}
bool Employes::ajouter() {
//executer les requetes sql
    QSqlQuery query;
    QString res1 = QString :: number(IDEMP);
    QString res2 = QString :: number(AGE);
    QString res3 = QString :: number(SALAIRE);
    query.prepare("INSERT INTO EMPLOYES (IDEMP, NOM, PRENOM, EMAIL, POSTE,AGE,PWD,SALAIRE,REPONSE_QS,QUESTION_SECRETE) VALUES (:IDEMP, :NOM, :PRENOM , :EMAIL , :POSTE , :AGE , :PWD ,:SALAIRE,:REPONSE_QS , :QUESTION_SECRETE) ");
    query.bindValue(":IDEMP", res1);
    query.bindValue(":NOM", NOM);
    query.bindValue(":PRENOM", PRENOM);
    query.bindValue(":EMAIL", EMAIL);
    query.bindValue(":POSTE", POSTE);
    query.bindValue(":AGE",res2);
    query.bindValue(":PWD", PWD);
    query.bindValue(":SALAIRE", res3);
    query.bindValue(":REPONSE_QS", REPONSE_QS);
    query.bindValue(":QUESTION_SECRETE", QUESTION_SECRETE);

    return query.exec();

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

       query.prepare("UPDATE EMPLOYES SET NOM=:NOM,PRENOM=:PRENOM,EMAIL=:EMAIL,POSTE=:POSTE,AGE=:AGE,PWD=:PWD,SALAIRE=:SALAIRE,REPONSE_QS=:REPONSE_QS,QUESTION_SECRETE=:QUESTION_SECRETE where IDEMP=:IDEMP");
       query.bindValue(":IDEMP",res1);
       query.bindValue(":NOM",NOM);
       query.bindValue(":PRENOM",PRENOM);
       query.bindValue(":EMAIL",EMAIL);
       query.bindValue(":POSTE",POSTE);
       query.bindValue(":AGE",res2);
       query.bindValue(":PWD",PWD);
       query.bindValue(":REPONSE_QS",REPONSE_QS);
       query.bindValue(":QUESTION_SECRETE",QUESTION_SECRETE);
       query.bindValue(":SALAIRE",res3);

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
model->setHeaderData(8,Qt::Horizontal,QObject::tr("REPONSE_QS"));
model->setHeaderData(9,Qt::Horizontal,QObject::tr("QUESTION_SECRETE"));
return model;
}


QSqlQueryModel * Employes:: Recherche(QString a){

    //Elle peut être utilisée pour stocker les résultats d'une requête SQL dans une structure de données utilisable par une vue, telle qu'un QTableView
//fournir un modele de donnes pour les requetes sql
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
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("REPONSE_QS"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("QUESTION_SECRETE"));



    return  model ;
}

QSqlQueryModel* Employes::triAge()
{
    //Elle peut être utilisée pour stocker les résultats d'une requête SQL dans une structure de données utilisable par une vue, telle qu'un QTableView


    QSqlQueryModel* model=new QSqlQueryModel();
//resultat stocke fil setQuer
    model->setQuery("SELECT* FROM EMPLOYES ORDER BY AGE");

    return model;
}
QSqlQueryModel* Employes::trisalaire(){
//Elle peut être utilisée pour stocker les résultats d'une requête SQL dans une structure de données utilisable par une vue, telle qu'un QTableView
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM EMPLOYES ORDER BY SALAIRE");

    return model;

}


void Employes::exporterpdf(QTextBrowser *text)
    {

          // QString tt;
            QSqlQuery qry;
            std::list<QString> tt;
            qry.exec("select * from EMPLOYES");
            //chaque ligne mel table yhotha fi chaine de caractere
            while(qry.next())
            {
                tt.push_back("IDEMP: "+qry.value(0).toString()+"\n"+"NOM "+qry.value(1).toString()+"\n"+"PRENOM: "+qry.value(2).toString()+"\n"+"EMAIL: "+qry.value(3).toString()+"\n"+"POSTE: "+qry.value(4).toString()+"\n"+"\n"+"AGE: "+qry.value(5).toString()+"\n"+"\n"+"PWD: "+qry.value(6).toString()+"\n"+"\n"+"SALAIRE: "+qry.value(7).toString()+"\n"+"\n"+"REPONSE_QS: "+qry.value(8).toString()+"\n"+"QUESTION_SECRETE: "+qry.value(8).toString()+"\n");

            }
//il parcourt cette liste et ajoute chaque élément à un objet QTextEdit(setText), qui affiche toutes les données de la table.
            for(std::list<QString>::iterator it =tt.begin();it!=tt.end();++it)
            {
                text->setText(text->toPlainText()+*it + "\n");

            }
/* il affiche une boîte de dialogue de sauvegarde de fichier pour permettre à l'utilisateur d'enregistrer les données affichées dans un fichier PDF.
 * Si l'utilisateur sélectionne un nom de fichier valide,
 * le texte est imprimé sur une imprimante virtuelle PDF,
 *  créée à l'aide de la classe QPrinter.*/
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




    void Employes::statistiqueSegment()
    {

        // Requête SQL pour récupérer les données
        QSqlQuery query("SELECT COUNT(*) FROM EMPLOYES WHERE SALAIRE>1500");
        query.next();
        int nbSUP = query.value(0).toInt();
        query.exec("SELECT COUNT(*) FROM EMPLOYES WHERE SALAIRE<1500");
        query.next();
        int nbINF = query.value(0).toInt();

        // Création de la série de données en courbe
        QLineSeries *series = new QLineSeries();
        series->append(0, nbSUP);
        series->append(1, nbINF);

        // Création du graphique
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition des clients selon le salaire");
        chart->createDefaultAxes();

        // Personnalisation de l'axe des X
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append("superieur 1500");
        axisX->append("infirieur 1500");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        // Personnalisation de l'axe des Y
        QValueAxis *axisY = new QValueAxis();
        axisY->setTitleText("Nombre de employes");
        chart->setAxisY(axisY, series);

        // Création de la vue du graphique
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Ajout de la vue dans la fenêtre principale
       // ui->verticalLayout->addWidget(chartView);

    }
    void Employes::imprimer(QTextEdit* widget)
    {
        QPrinter printer;

          QPrintDialog dialog(&printer);
          if (dialog.exec() != QDialog::Accepted) {
              return;
          }

          QPainter painter(&printer);
          QRect rect = painter.viewport();
          QSize size = widget->document()->size().toSize();
          size.scale(rect.size(), Qt::KeepAspectRatio);
          painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
          painter.setWindow(0, 0, widget->document()->pageSize().width(), widget->document()->pageSize().height());
          painter.setRenderHint(QPainter::Antialiasing, true);
          widget->document()->drawContents(&painter);
    }



