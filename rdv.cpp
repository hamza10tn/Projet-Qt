#include "rdv.h"
#include "ui_rdv.h"
#include"QMessageBox"
#include<QVector>
#include<QString>
#include<rendez_vous.h>
#include"QTableView"
#include"QStandardItemModel"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include"connexion.h"
#include <QDate>
#include <QColor>
#include <QList>
#include <QCalendarWidget>
#include<QDebug>
#include"rendez_vous.h"
#include"arduino.h"


rdv::rdv(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::rdv)
{

    ui->setupUi(this);
   }
rdv::~rdv(){

}
