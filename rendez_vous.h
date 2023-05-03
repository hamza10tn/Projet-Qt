#ifndef RENDEZ_VOUS_H
#define RENDEZ_VOUS_H
#include<QString>
#include<QDate>
#include<QTime>
#include"QMessageBox"
#include<QVector>
#include<QString>
#include"QTableView"
#include"QStandardItemModel"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include<QSqlQueryModel>
#include<QPainter>
#include <QPrinter>
#include<QTextDocument>
#include<QTextFrameFormat>
#include<QTextCursor>
#include<QTextTableCell>
#include<QVector>
class rendez_vous
{
private:

    QString id;
    QDate dat;
    QTime heure;
    QString matricule;

public:
    rendez_vous();
    void setid(QString n);
    void setdate(QDate n);
    void setheure(QTime n);
    void setmat(QString n);
    bool ajouter_rdv(rendez_vous);
    bool supprimer_rdv(QString id);
   QStandardItemModel* afficher_rdv();
    bool modfier_rdv(rendez_vous r);
    bool chercher_rdv(QString id);
    QStandardItemModel* chercherr_rdv(QString type);
    QStandardItemModel* trier_rdv(QString type);
    QDate chercherDateDisponible();
    void exporter_rdv();
    std::vector<QDate> getDatesFromRdvTable();
    QDate  getDateFromRdvTable(int id) ;
    QString matricule_existe(QString );
    bool ajouter_rdv_temp(QString id, QString temp);



    //void setmat(QString n);




    QString get_mat();
    QString get_id();
    QTime get_heure();
    QDate get_date();


};

#endif // RENDEZ_VOUS_H
