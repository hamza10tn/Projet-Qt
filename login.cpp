#include "login.h"

login::login()
{

}
bool login::connect(int IDEMP, QString PWD)
{
    QSqlQuery query ;
    query.prepare("SELECT IDEMP FROM LOGIN WHERE IDEMP=:id AND PWD=:pwd");
    query.bindValue(":id", IDEMP);
    query.bindValue(":pwd", PWD);
    if (query.exec() && query.next()) {
        // The query executed successfully and returned at least one result
        return true;
    } else {
        // The query either didn't execute successfully or didn't return any results
        return false;
    }
}
