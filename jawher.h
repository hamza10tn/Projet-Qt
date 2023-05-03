#ifndef JAWHER_H
#define JAWHER_H
#include <QMainWindow>
#include <QDialog>
#include "equipment.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class jawher;
}

class jawher : public QDialog
{
    Q_OBJECT

public:
    explicit jawher(QWidget *parent = nullptr);
    ~jawher();

private slots:
    void on_btn_update_clicked();

      void on_pushButton_clicked();


      void on_pushButton_13_clicked();

      void on_pushButton_2_clicked();


      void on_pushButton_3_clicked();

      void on_supprimerbutton_clicked();

      void on_validersupp_clicked();

      void on_pushButton_4_clicked();


      void on_toolButton_clicked();

      void on_pushButton_12_clicked();

      void on_pushButton_11_clicked();

      void on_statestique_clicked();

      void on_pdf_clicked();

       void on_rechercher_textChanged(const QString &arg1);

       void on_tri_clicked();

       void on_tri2_clicked();

       void on_excel_clicked();

       void on_qrcodegen_clicked();

       void on_arduino_clicked();

       void on_saveButton_clicked();

private:
    Ui::jawher *ui;
     Equipment E;
       int selected_publication = -1;
};

#endif // JAWHER_H
