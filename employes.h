#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QMessageBox>
#include <QTextBrowser>
#include <QTextBrowser>
class Employes
{


private:
int IDEMP;
QString NOM,PRENOM,EMAIL,POSTE;
int AGE;
QString PWD;
float SALAIRE;

public:
    Employes ();
    Employes(int ,QString,QString,QString,QString,int,QString,float);

    bool ajouter();
   QSqlQueryModel * afficher();
   bool supprimer (int );
   bool modifier(int );
   QSqlQueryModel *Recherche(QString );
   QSqlQueryModel* triAge();
  void exporterpdf(QTextBrowser *text);





    int getID();
    QString getNOM();
    QString getPRENOM();
    QString getEMAIL();
    QString getPOSTE();
    int getAGE();
    QString getPWD();
    float getSALAIRE();
    void setID(int );
    void setNOM(QString );
    void setPRENOM(QString );
    void setEMAIL(QString );
    void setPOSTE(QString );
    void setAGE(int );
    void setPWD(QString );
    void setSALAIRE(float );
    bool verifEmailAndId(int id,QString email);




};

#endif // EMPLOYES_H







