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
QString NOM,PRENOM,EMAIL,POSTE,REPONSE_QS, QUESTION_SECRETE;
int AGE;
QString PWD;
float SALAIRE;


public:
    Employes ();
    Employes(int ,QString,QString,QString,QString,int,QString,float,QString,QString);

    bool ajouter();
   QSqlQueryModel * afficher();
   bool supprimer (int );
   bool modifier(int );
   QSqlQueryModel *Recherche(QString );
   QSqlQueryModel* triAge();
    QSqlQueryModel* trisalaire();
  void exporterpdf(QTextBrowser *text);
  void statistiqueSegment();
  void imprimer(QTextEdit* widget);





    int getID();
    QString getNOM();
    QString getPRENOM();
    QString getEMAIL();
    QString getPOSTE();
    int getAGE();
    QString getPWD();
    float getSALAIRE();
    QString getREPONSE_QS();
    QString getQUESTION_SECRETE();


    void setID(int );
    void setNOM(QString );
    void setPRENOM(QString );
    void setEMAIL(QString );
    void setPOSTE(QString );
    void setAGE(int );
    void setPWD(QString );
    void setSALAIRE(float );
    void setREPONSE_QS(QString );
    void setQUESTION_SECRETE(QString );
    bool verifEmailAndId(int id,QString email);




};

#endif // EMPLOYES_H







