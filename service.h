#ifndef SERVICE_H
#define SERVICE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class service
{
private:
   int id;
   QString nom,description,type;
   float prix;
public:
    service();
    service(int,QString,QString,QString,float);
    //Les fonctions CRUD
    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * combo_box();
    QSqlQueryModel * combo_box_2();
    QSqlQueryModel * trier(QString,QString);
    QSqlQueryModel * recherche(QString);
    QVector <QString> getinforamation(QString);
};

#endif // SERVICE_H
