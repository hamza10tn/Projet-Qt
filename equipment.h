#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <QString>
#include <QSqlQueryModel>

class Equipment
{
public:
    Equipment();
    Equipment(int,QString,int,QString,QString,QString);
        int getidequi();
        QString getnomE();
        int getnombre();
         QString getdate();
        QString getdescription();
        QString getvideo();
        void setidequi(int);

        void setnomE(QString);
        void setnombre(int);
        void setdate(QString);

        void setdescription(QString);
        void setvideo(QString);

        //fonctions
        bool ajouter();
        QSqlQueryModel* afficher();
        bool researchID(int);
        bool modifier(int ,QString,int , QString , QString , QString );

        bool supprimer(int);
        QSqlQueryModel* Recherche(QString);
    QSqlQueryModel * triB();
    QSqlQueryModel * triA();
    void genererPDFact();

     private:
        int idequi;
        QString nomE;
        int nombre;
         QString date,description,video;
    };

#endif // EQUIPMENT_H
