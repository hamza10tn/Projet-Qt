#include "rating.h"
#include <QDebug>
rating::rating()
{
    this->ID=0;
    this->IDEMP=0;
    this->NOTE=0;
}
rating::rating(int ID, int IDEMP, int NOTE)
{
    this->ID=ID;
    this->IDEMP=IDEMP;
    this->NOTE=NOTE;
}

void rating::setID(int ID)
{
    this->ID = ID;
}

void rating::setIDEMP(int IDEMP)
{
    this->IDEMP = IDEMP;
}

void rating::setNOTE(int NOTE)
{
    this->NOTE = NOTE;
}

int rating::getID()
{
    return ID;
}

int rating::getIDEMP()
{
    return IDEMP;
}

int rating::getNOTE()
{
    return NOTE;
}
rating rating::getRatingByEmpl(int IDEMP){
    rating x;
    x.setID(-1);

  QSqlQuery query;
   query.prepare("SELECT ID, IDEMP, NOTE FROM RATING where IDEMP=:IDEMP");
   query.bindValue(":IDEMP",IDEMP);
   if(query.exec()&&query.next()){
   x.setID(query.value(0).toInt());
   x.setIDEMP(query.value(1).toInt());
   x.setNOTE(query.value(2).toInt());
   }
   return  x;

}
bool rating::Add(){
    QSqlQuery query;

    query.prepare("insert into RATING (IDEMP, NOTE)" "values (:IDEMP, :NOTE)");

    query.bindValue(":IDEMP",this->IDEMP);
    query.bindValue(":NOTE",this->NOTE);
    if (!query.exec())
        { return false;
            qDebug() << "Error adding rating:" ;
        }
    return true;

}

bool rating::Modifier(){
    QSqlQuery query;

    query.prepare("UPDATE RATING SET NOTE=:NOTE  where ID=:ID");

    query.bindValue(":NOTE",this->NOTE);
    query.bindValue(":ID",this->ID);
    if (!query.exec())
        { return false;
            qDebug() << "Error adding rating:" ;
        }
    return true;

}
