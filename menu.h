#ifndef MENU_H
#define MENU_H
#include<QDebug>
#include <QDialog>
#include <QSqlDatabase>
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

private:
    Ui::menu *ui;
};

#endif // MENU_H
