#ifndef RATING_H
#define RATING_H
#include<QSqlQuery>
#include<QSqlQueryModel>


class rating
{
private :
    int ID;
    int IDEMP;
    int NOTE;
public:
    rating();
    rating(int ID,int IDEMP,int NOTE);
       void setID(int ID);
       void setIDEMP(int IDEMP);
       void setNOTE(int NOTE);
       int getID();
       int getIDEMP();
       int getNOTE();
       rating getRatingByEmpl(int IDEMP);
       bool Add();
       bool Modifier();


};

#endif // RATING_H
