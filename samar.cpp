#include "samar.h"
#include "ui_samar.h"

samar::samar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::samar)
{
    ui->setupUi(this);
}

samar::~samar()
{
    delete ui;
}
