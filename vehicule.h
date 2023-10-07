#ifndef VEHICULE_H
#define VEHICULE_H
#include<QString>
#include <QtCore/QRegExp>
#include <QtCore/QString>
#include<QSqlQueryModel>


class Vehicule
{
public:
    Vehicule();
    Vehicule(QString,QString,QString,QString);

       //set
        void setmatricule(QString );
        void setmodele(QString );
        void settype(QString );
        void setetat(QString );
        void setimage(QString );
        void settemperatur(int);

       //get
        QString get_matricule();
        QString get_modele();
        QString get_type();
        QString get_etat();
        QString get_image();
        int get_temperature();

       //les methodes
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(QString);
        bool modifier(QString , QString , QString , QString );
        bool chercher(QString);

         static bool matriculeExists(QString matricule);

         QSqlQueryModel * triB();
         QSqlQueryModel * triA();

    private:

        QString matricule,modele,type,etat,image;
        int temperature;

    };


#endif // VEHICULE_H
