#include "rendez_vous.h"
#include<QString>
#include<QTime>
#include<QDate>
#include<QMessageBox>
#include<QDebug>
rendez_vous::rendez_vous()
{

}
void rendez_vous::setid(QString n)
{
    id=n;
}
void rendez_vous::setdate(QDate n)
{
    dat=n;
}
void  rendez_vous::setheure(QTime n)
{
    heure=n;
}
void rendez_vous::setmat(QString n)
{
matricule=n;
}




QString rendez_vous::get_id()
{
 return id;
}
QDate rendez_vous::get_date()
{
return dat;
}
QTime rendez_vous::get_heure()
{
return heure;
}

QString rendez_vous::get_mat()
{
return matricule;
}

bool rendez_vous::ajouter_rdv(rendez_vous r)
{
  //  QString date = dat.toString("dd/MM/yyyy");
//rendez_vous r;
    QSqlQuery query2;
    qDebug() << "id eeeee" << r.get_id();

    query2.prepare("SELECT * FROM RDV WHERE ID_R = :id ");
    query2.bindValue(":id", r.get_id());
    //query2.bindValue(":date_r", date);
    if (query2.exec() && query2.next()) {
        //"Date déjà prise", "La date sélectionnée est déjà prise. Veuillez sélectionner une autre date.
        return false;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO rdv (ID_R, DATE_R, heure, matricule) "
                  "VALUES (:id, :date_r, :heure, :mat)");
    qDebug() << "id de prepare" << id;

    query.bindValue(":id", r.get_id());
    query.bindValue(":date_r",r.get_date());
    query.bindValue(":heure", r.get_heure());
    query.bindValue(":mat", r.get_mat());

    return query.exec();
}

bool rendez_vous::ajouter_rdv_temp(QString id, QString temp)
{


    QSqlQuery query;
    query.prepare("UPDATE RDV SET  TEMP = :temp WHERE ID_R = :id");
    query.bindValue(":id", id);
    query.bindValue(":temp",temp);



    return query.exec();
}




bool rendez_vous::supprimer_rdv(QString id)
{

    QSqlQuery query;
    query.prepare("DELETE FROM RDV WHERE ID_R=:ID_R");
    query.bindValue(":ID_R",id);
    return  query.exec();



}




QStandardItemModel *rendez_vous::afficher_rdv()
{
    QSqlQuery query;
    QSqlQuery query2;

  //  query2.prepare("SELECT v.MATRICULE FROM rdv r JOIN vehicule v ON r.MATRICULE = v.MATRICULE JOIN clients c ON v.ID_C = c.ID_C WHERE c.ID_C = :idc");
   /*query2.prepare("SELECT v.MATRICULE FROM VEHICULE v JOIN RDV r ON r.ID_C = v.ID_C where r.ID_R=:id");
   query2.bindValue(":idc", 1);
    query2.bindValue(":id", 123);

    query2.exec();
    QString matricule =query2.value(0).toString();

    qDebug()<<matricule;
query.next();
qDebug()<<"affichage de mat";

qDebug()<<matricule;

qDebug() << query2.lastError().text();
*/


    QStandardItemModel *model1 = new QStandardItemModel();
    model1->setColumnCount(3);
    model1->setHorizontalHeaderItem(0, new QStandardItem(QString("id")));
    model1->setHorizontalHeaderItem(1, new QStandardItem(QString("calendar")));
    model1->setHorizontalHeaderItem(2, new QStandardItem(QString("time")));
   model1->setHorizontalHeaderItem(3, new QStandardItem(QString("matricule")));
    if (query.exec("SELECT * FROM RDV")) {
        int row = 0;
        while (query.next()) {
            QString field1 = query.value(0).toString();
QDate dat=query.value(1).toDate();
QString field2 = dat.toString("yyyy-MM-dd");

            QTime time = query.value(2).toTime();
            QString field3 = time.toString("hh:mm:ss");
QString field4=query.value(3).toString();
            QStandardItem *item1 = new QStandardItem(field1);
            QStandardItem *item2 = new QStandardItem(field2);
            QStandardItem *item3 = new QStandardItem(field3);
            QStandardItem *item4 = new QStandardItem(field4);

            model1->setItem(row, 0, item1);
            model1->setItem(row, 1, item2);
            model1->setItem(row, 2, item3);
            model1->setItem(row, 3, item4);

            row++;
        }
    }
    return model1;
}

  bool rendez_vous::modfier_rdv(rendez_vous r)
  {




      QSqlQuery query;

      query.prepare("UPDATE RDV SET  DATE_R = :date_r, HEURE = :heure WHERE ID_R = :id");
      query.bindValue(":id", r.get_id());
      query.bindValue(":date_r",r.get_date());
      query.bindValue(":heure", r.get_heure());
      query.exec();



return query.exec();
  }



 bool rendez_vous::chercher_rdv(QString id)
 {
     QSqlQuery query;
     query.prepare("SELECT * FROM RDV where ID_R = :id");
     query.bindValue(":id",id);

     if (query.exec()) {
         while (query.next())
          {
return true;

         }





 }

return false;
}
 //chercher 2eme metode

 /*QSqlQueryModel* rendez_vous :: chercherr_rdv(QString a)
 {



    QSqlQueryModel* model= new QSqlQueryModel();


 model->setQuery("select * from JUGE WHERE (CIN_J LIKE '%"+a+"%' OR NOM LIKE '%"+a+"%' OR PRENOM LIKE '%"+a+"%' OR NB_PROCESS_GAGNER LIKE '%"+a+"%' "
               "OR NUM_BUREAU LIKE '%"+a+"%') ");

 model->setHeaderData(0, Qt::Horizontal,QObject::tr("identifiant"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("num_bureau"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("nb_process_gagner"));

   return model ;
 }

 */


 QStandardItemModel *rendez_vous::trier_rdv(QString type)
 {
     QSqlQuery query;
     QSqlQuery query2;



     QStandardItemModel *model1 = new QStandardItemModel();
     model1->setColumnCount(3);
     model1->setHorizontalHeaderItem(0, new QStandardItem(QString("id")));
     model1->setHorizontalHeaderItem(1, new QStandardItem(QString("calendar")));
     model1->setHorizontalHeaderItem(2, new QStandardItem(QString("time")));
   model1->setHorizontalHeaderItem(3, new QStandardItem(QString("matricule")));
   if (query.prepare("SELECT * FROM RDV ORDER BY DATE_R " + type) && query.exec()){
         int row = 0;
         while (query.next()) {
             QString field1 = query.value(0).toString();
 QDate dat=query.value(1).toDate();
 QString field2 = dat.toString("yyyy-MM-dd");

             QTime time = query.value(2).toTime();
             QString field3 = time.toString("hh:mm:ss");
QString field4=query.value(3).toString();
             QStandardItem *item1 = new QStandardItem(field1);
             QStandardItem *item2 = new QStandardItem(field2);
             QStandardItem *item3 = new QStandardItem(field3);
             QStandardItem *item4 = new QStandardItem(field4);

             model1->setItem(row, 0, item1);
             model1->setItem(row, 1, item2);
             model1->setItem(row, 2, item3);
             model1->setItem(row, 3, item4);

             row++;
         }
     }

   return model1;
 }
 QDate rendez_vous::chercherDateDisponible()
 {
     // Extraire les dates de la base de données et les stocker dans un vector
     QVector<QDate> dates;
     QSqlQuery query;
     query.exec("SELECT DISTINCT DATE_R FROM RDV");
     while (query.next()) {
         QDate date = query.value(0).toDate();
         dates.append(date);
       //  qDebug() << date <<"|";
     }

     // Trier les dates dans l'ordre croissant
     std::sort(dates.begin(), dates.end());

     // Chercher la première date disponible
     QDate currentDate = QDate::currentDate();

     // Current date is already in the list of dates, find next available date
     for (int i = 0; i < dates.size() - 1; i++) {
         if (dates.at(i).addDays(1) != dates.at(i + 1)) {
             // There is an available date between the two dates
             currentDate = dates.at(i).addDays(1);
             break;
         }
     }

     if (currentDate == QDate::currentDate()) {
         // No date available between existing dates, return next day
         currentDate = currentDate.addDays(1);
     }

     return currentDate;
 }


 std::vector<QDate> rendez_vous:: getDatesFromRdvTable() {
     std::vector<QDate> dates;


     QSqlQuery query;
     query.prepare("SELECT DATE_R FROM rdv");
     if (!query.exec()) {
         // Error handling
         return dates;
     }

     while (query.next()) {
         QDate date = query.value(0).toDate();
         if (date.isValid()) {
             dates.push_back(date);
         }
     }


     return dates;
 }




 QDate rendez_vous:: getDateFromRdvTable(int id) {

QDate date;

     QSqlQuery query;
     query.prepare("SELECT DATE_R FROM rdv where id_r=:id");
     query.bindValue(":id",id);
     if (!query.exec()) {
         // Error handling
         return date;
     }

     while (query.next()) {
         QDate date = query.value(0).toDate();
         if (date.isValid()) {
         return date;}
     }


     return date;
 }
QString rendez_vous::matricule_existe(QString id)
{

    QSqlQuery query;
    query.prepare("SELECT MATRICULE FROM rdv where id_r=:id");
    query.bindValue(":id",id);
    if (!query.exec()) {
        // Error handling

    }
    while (query.next()) {
        return query.value(0).toString();
qDebug()<<"found it ";
    }


    return "";
}
