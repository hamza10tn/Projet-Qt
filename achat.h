#ifndef ACHAT_H
#define ACHAT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class achat
{
private:
    int id,id_service;
    float prix;
public:
    achat();
    achat(int,int,float);
    //Les fonctions CRUD
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * combo_box();
};

#endif // ACHAT_H
