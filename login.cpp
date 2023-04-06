#include "login.h"
#include "employes.h"
#include "sessionuser.h"
login::login()
{

}
bool login::connect(int IDEMP, QString PWD)
{
    QSqlQuery query ;
    query.prepare("SELECT * FROM EMPLOYES WHERE IDEMP=:id AND PWD=:pwd");
    query.bindValue(":id", IDEMP);
    query.bindValue(":pwd", PWD);
    if (query.exec() && query.next()) {
        // The query executed successfully and returned at least one result
        Employes *e=new Employes(query.value("IDEMP").toInt(),query.value("NOM").toString(),query.value("PRENOM").toString(),query.value("EMAIL").toString(),query.value("POSTE").toString(),query.value("AGE").toInt(),query.value("PWD").toString(),query.value("SALAIRE").toFloat());
        qDebug()<<e->getPOSTE();
        SessionUser::getInstance()->setConnectedUser(e);


        return true;
    } else {
        // The query either didn't execute successfully or didn't return any results
        return false;
    }
}
