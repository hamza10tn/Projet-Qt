#ifndef RECUPERERMOTDEPASSE_H
#define RECUPERERMOTDEPASSE_H

#include <QDialog>

namespace Ui {
class recuperermotdepasse;
}

class recuperermotdepasse : public QDialog
{
    Q_OBJECT

public:
    explicit recuperermotdepasse(QWidget *parent = nullptr);
    ~recuperermotdepasse();

private slots:
    void on_validerEtape1_2_clicked();

private:
    Ui::recuperermotdepasse *ui;
    QString finalCode;

};

#endif // RECUPERERMOTDEPASSE_H
