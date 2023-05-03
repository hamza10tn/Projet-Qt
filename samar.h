#ifndef SAMAR_H
#define SAMAR_H

#include <QDialog>

namespace Ui {
class samar;
}

class samar : public QDialog
{
    Q_OBJECT

public:
    explicit samar(QWidget *parent = nullptr);
    ~samar();

private:
    Ui::samar *ui;
};

#endif // SAMAR_H
