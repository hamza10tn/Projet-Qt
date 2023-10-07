#ifndef MENU_H
#define MENU_H
#include<QDebug>
#include <QDialog>
#include <QSqlDatabase>
#include "rdv.h"
#include "jawher.h"
#include "samar.h"
#include "hamza.h"
#include "maissa.h"
namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_GestionEmployeBtn_clicked();

    void on_AccountMenuBtn_clicked();

    void on_GestionDesRdvbtn_clicked();

    void on_GestionClientBtn_clicked();

    void on_GestionDesEqbtn_clicked();

    void on_GestionDesVehiculebtn_clicked();

    void on_GestionDesServicebtn_clicked();

private:
    Ui::menu *ui;
    rdv *r;
    jawher *j;
    samar *c;
    hamza *h;
    maissa *m;

};

#endif // MENU_H
