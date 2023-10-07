#ifndef REDUCTION_H
#define REDUCTION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class reduction
{

private :
   int id;
   QString code;

public:
    reduction();
    reduction(int,QString);
    QString Getcode() { return  code; }
            void SettypeService(QString val) {  code = val; }
            int Getid(){ return id; }
                    void Setid (int val){id=val;}
                    //Les fonctions CRUD
                                bool ajouter();
                                QSqlQueryModel*afficher();
                                bool supprimer(QString);
                                bool modifier();
                                QSqlQueryModel * combo_box();
                              bool  supprimerParCode(QString id);
};

#endif // REDUCTION_H

