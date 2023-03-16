#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include<QDebug>
#include<QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "menu.h"
#include <QSqlDatabase>
#include <QMainWindow>

class login
{
public:
    login();
    bool connect(int,QString);

};

#endif // LOGIN_H
