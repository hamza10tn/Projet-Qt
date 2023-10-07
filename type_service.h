#ifndef TYPE_SERVICE_H
#define TYPE_SERVICE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class type_service
{
 private :
    int id;
    QString typeService;


public:
    type_service();
    type_service(int,QString);
    QString GettypeService() { return  typeService; }
            void SettypeService(QString val) {  typeService = val; }
            int Getid(){ return id; }
                    void Setid (int val){id=val;}
                    //Les fonctions CRUD
                                bool ajouter();
                                QSqlQueryModel*afficher();
                                bool supprimer(QString);
                                bool modifier();
                                QSqlQueryModel * combo_box();


};

#endif // TYPE_SERVICE_H

