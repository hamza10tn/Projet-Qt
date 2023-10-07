#ifndef CLIENT_H
#define CLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QTextBrowser>

class Client
{
private:

    int ID_C ;
    QString NOM_C, PRENOM_C,ADRESSE,EMAIL_C;
    int NUM_TEL, FIDELITE;
    float remise;
public:
    Client();
    Client(int ,QString ,QString ,QString ,QString , int  );

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier (int);

    int  getID_C();

    QString getnom_c();
    QString getPRENOM_C();
    QString  getADRESSE();
    QString  getEMAIL_C();
    int  getNUM_TEL();
    int  getFIDELITE();
    void setID_C(int);
    void setNOM_C(QString);
    void setPRENOM_C(QString );
    void setADRESSE(QString);
    void setEMAIL_C(QString);
    void setNUM_TEL(int);
    void setFIDELITE(int);
    QSqlQueryModel *Recherche(QString );

    QSqlQueryModel* trifidelite();
    void exporterpdf(QTextBrowser *text);
    bool testerRendezVous(QString mat,int idClient);

    };



#endif // CLIENT_H
