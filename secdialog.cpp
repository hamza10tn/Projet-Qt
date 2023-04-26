#include "secdialog.h"
#include "ui_secdialog.h"
#include<QDebug>
#include<QMessageBox>
#include "employes.h"
#include"QtPrintSupport/QPrinter"
#include"QPdfWriter"
#include <cstdlib>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
//#include <QPrinter>
#include <QPainter>
#include<QLabel>
#include <QSqlRecord>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>




secDialog::secDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secDialog)
{
    ui->setupUi(this);
     ui->tableView->setModel(i.afficher());
     ui->lineEdit->setValidator(new QIntValidator(0,9999999,this));
      ui->lineEdit_6->setValidator(new QIntValidator(0,99,this));
      int ret=A.connect_arduino(); // lancer la connexion à arduino

      switch(ret){
      case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
          break;
      case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
         break;
      case(-1):qDebug() << "arduino is not available";
      }
       QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
       //le slot update_label suite à la reception du signal readyRead (reception des données).





  }

secDialog::~secDialog()
{
    delete ui;
}



void secDialog::on_pushButton_9_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}


void secDialog::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void secDialog::on_pb_ajouter_7_clicked()
{

 }

void secDialog::on_pushButton_7_clicked()
{

        int IDEMP=ui->lineEdit->text().toInt();
        QString NOM=ui->lineEdit_2->text();
        QString PRENOM=ui->lineEdit_3->text();
        QString EMAIL=ui->lineEdit_4->text();
        QString POSTE=ui->comboBox->currentText();
        int AGE=ui->lineEdit_6->text().toInt();
        QString PWD=ui->lineEdit_5->text();
        float SALAIRE=ui->lineEdit_7->text().toFloat();
         QString REPONSE_QS=ui->rp->text();
          QString QUESTION_SECRETE=ui->qs->text();

    Employes i (IDEMP,NOM,PRENOM,EMAIL,POSTE,AGE,PWD,SALAIRE,REPONSE_QS,QUESTION_SECRETE) ;
    bool test=i.ajouter();
    if (test)
     {

     ui->tableView->setModel(i.afficher());
         QMessageBox :: information (nullptr, QObject ::tr("OK"),
                      QObject ::tr("Ajout effectué\n"
                                  "click cancel to exit"),
                 QMessageBox:: Cancel);

    }
     else
     {
         QMessageBox::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr("try again.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);

    }

}

void secDialog::on_pushButton_14_clicked()
{
int IDEMP=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt(); // get the selected row id
        QString NOM= ui->nom->text();
         QString PRENOM=ui->prenom->text();
         QString EMAIL=ui->email->text();
         QString POSTE=ui->comboBox_2->currentText();
         int AGE=ui->age->text().toInt();
          QString PWD=ui->pwd->text();
          float SALAIRE=ui->salaire->text().toFloat();
          QString REPONSE_QS=ui->reponse->text();
           QString QUESTION_SECRETE=ui->question->text();

Employes i (IDEMP,NOM,PRENOM,EMAIL,POSTE,AGE,PWD,SALAIRE,REPONSE_QS,QUESTION_SECRETE) ;


bool test=i.modifier(IDEMP);

if (test)

             {

             ui->tableView->setModel(i.afficher());
                 QMessageBox :: information (nullptr, QObject ::tr("OK"),

                              QObject ::tr("modifier effectué\n"

                                           "click cancel to exit"),

                         QMessageBox:: Cancel);



         }

             else

             {

                 QMessageBox::critical(nullptr,QObject::tr("not ok"),

                                      QObject::tr("try again.\n"

                                                  "click cancel to exit."),QMessageBox::Cancel);

}}




void secDialog::on_pushButton_8_clicked()
{
 ui->stackedWidget->setCurrentIndex(2);
}



void secDialog::on_pushButton_16_clicked()
{
    int IDEMP=ui->lineEdit_11->text().toInt();
         bool test=i.supprimer(IDEMP);
         if (test)
         {
             ui->tableView->setModel(i.afficher());
            QMessageBox :: information (nullptr, QObject ::tr("OK"),
                          QObject ::tr("suppression effectué\n"
                                       "click cancel to exit"),
                     QMessageBox:: Cancel);

        }
         else
         {
             QMessageBox::critical(nullptr,QObject::tr("not ok"),
                                  QObject::tr("try again.\n"
                                              "click cancel to exit."),QMessageBox::Cancel);
         }
}



 void secDialog::on_tableView_doubleClicked(const QModelIndex &index)
 {
     ui->nom->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString());
        ui->prenom->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString());
        ui->email->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString());
        ui->comboBox_2->setCurrentText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString());

         ui->age->setText(QString::number(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toInt()));
         ui->pwd->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6)).toString());
         ui->salaire->setText(QString::number(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),7)).toFloat()));
         ui->reponse->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),8)).toString());
         ui->question->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),9)).toString());






}
 void secDialog::on_lineEdit_8_textEdited(const QString &arg1)
 {
        ui->tableView->setModel(i.Recherche(arg1));
 }
 //tri

 void secDialog::on_pushButton_13_clicked()
 {
     ui->tableView->setModel(i.triAge()) ;
 }



void secDialog::on_lineEdit_2_textEdited(const QString &arg1)

    {
        QString name = ui->lineEdit_2->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

        // Vérification si le champ est vide ou non
        if (name.isEmpty()) {
            QMessageBox::warning(this, "Champ vide", "Le champ du nom est vide.");
            return;
        }

        // Vérification si le prenom contient des caractères non alphabétiques
        QRegularExpression regex("[^a-zA-Z]");
        if (regex.match(name).hasMatch()) {
            QMessageBox::warning(this, "Nom invalide", "Le nom ne doit contenir que des lettres alphabétiques.");
            return;
        }
    }



void secDialog::on_lineEdit_3_textEdited(const QString &arg1)
{
    QString surname = ui->lineEdit_3->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

    // Vérification si le champ est vide ou non
    if (surname.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Le champ du prenom est vide.");
        return;
    }

    // Vérification si le prenom contient des caractères non alphabétiques
    QRegularExpression regex("[^a-zA-Z]");
    if (regex.match(surname).hasMatch()) {
        QMessageBox::warning(this, "Nom invalide", "Le prenom ne doit contenir que des lettres alphabétiques.");
        return;
    }
}

void secDialog::on_lineEdit_6_textEdited(const QString &arg1)
{
   QString age = ui->lineEdit_6->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

    // Vérification si le champ est vide ou non
    if (age.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "L age ne doit pas etre vide.");
        return;
    }
}

void secDialog::on_lineEdit_7_textEdited(const QString &arg1)
{
    QString salaire = ui->lineEdit_7->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

    // Vérification si le champ est vide ou non
    if (salaire.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "le salaire ne doit  pas etre est vide.");
        return;
    }

}



void secDialog::on_lineEdit_4_textEdited(const QString &arg1)
{


        }









void secDialog::on_lineEdit_5_textEdited(const QString &arg1)

{}

void secDialog::on_pushButton_17_clicked()
{
 ui->stackedWidget->setCurrentIndex(3);
}

void secDialog::on_lineEdit_4_editingFinished(){

QString EMAIL=ui->lineEdit_4->text();
    if
    (!QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(EMAIL).hasMatch()) {
            QMessageBox::critical(this, "Error", "L'adresse mail n'est pas valide.");}
            else
                QMessageBox::information(this,"ok","adresse valide");

            return;
}

void secDialog::on_pushButton_18_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void secDialog::on_lineEdit_5_editingFinished()
{

    if (ui->lineEdit_5->text().length() < 8) {
           QMessageBox::warning(this,"false","il faut avoir au moins 8 caracters ");

       }
       // Ajouter des règles de validation supplémentaires ici, si nécessaire
else
       QMessageBox::information(this,"ok"," mot de passe confirme ");
       return ;

}

void secDialog::on_lineEdit_textEdited(const QString &arg1)
{

}

void secDialog::on_lineEdit_7_editingFinished()
{
    QString salaire = ui->lineEdit_7->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

    // Vérification si le champ est vide ou non
    if (salaire.isEmpty()) {
        QMessageBox::warning(this, "Champ vide", "Le champ salaire est vide.");
        return;
    }
}

void secDialog::on_nom_textEdited(const QString &arg1)
{

        QString surname = ui->nom->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

        // Vérification si le champ est vide ou non
        if (surname.isEmpty()) {
            QMessageBox::warning(this, "Champ vide", "Le champ du prenom est vide.");
            return;
        }

        // Vérification si le prenom contient des caractères non alphabétiques
        QRegularExpression regex("[^a-zA-Z]");
        if (regex.match(surname).hasMatch()) {
            QMessageBox::warning(this, "prenom invalide", "Le prenom ne doit contenir que des lettres alphabétiques.");
            return;
        }

}

void secDialog::on_email_editingFinished()
{
    QString EMAIL=ui->email->text();
        if
        (!QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(EMAIL).hasMatch()) {
                QMessageBox::critical(this, "Error", "L'adresse mail n'est pas valide.");}
                else
                    QMessageBox::information(this,"ok","adresse valide");

                return;
}

void secDialog::on_pwd_editingFinished()
{

    if (ui->pwd->text().length() < 8) {
           QMessageBox::warning(this,"false","il faut avoir au moins 8 caracters ");
}}





void secDialog::on_age_textEdited(const QString &arg1)
{
    QString age = ui->age->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

     // Vérification si le champ est vide ou non
     if (age.isEmpty()) {
         QMessageBox::warning(this, "Champ vide", "L age ne doit pas etre vide.");
         return;
     }
}
//recherche



void secDialog::on_pushButton_12_clicked()
{

 ui->tableView->setModel(i.trisalaire()) ;
}





void secDialog::on_pushButton_10_clicked()
{
    QPrinter printer;

        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = tableView->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(tableView->rect());
        tableView->render(&painter);}



void secDialog::on_stackedWidget_currentChanged(int index)
{

        // Effacer le texte affiché dans le label nommé label_stat
        ui->label_stat->clear();

        // Si l'index est égal à 2, cela signifie que l'utilisateur a sélectionné l'onglet approprié
        if (index == 3 )
        {
            // Supprimer tous les widgets contenus dans le layout vertical nommé verticalLayout
            QLayoutItem* child;
            while ((child = ui->verticalLayout->takeAt(0)) != nullptr) {
                delete child->widget();
                delete child;
            }

            // Exécuter une requête SQL pour compter le nombre d'employés dont le salaire est supérieur à 1500
            QSqlQuery query("SELECT COUNT(*) FROM EMPLOYES WHERE SALAIRE > 1500");
            query.next();
            int nbSUP = query.value(0).toInt();

            // Exécuter une requête SQL pour compter le nombre d'employés dont le salaire est inférieur à 1500
            query.exec("SELECT COUNT(*) FROM  EMPLOYES WHERE SALAIRE < 1500");
            query.next();
            int nbINF = query.value(0).toInt();

            // Calculer les pourcentages de chaque groupe
            qreal total = nbSUP + nbINF;
            qreal pourcentageSUP = nbSUP / total * 100;
            qreal pourcentageINF = nbINF / total * 100;
//QBarSet contient les barres graphiques
            // Créer des barres pour le graphique
            //Chaque QBarSet contient le nombre d'employés correspondant à chaque groupe.
            QBarSet *setSUP = new QBarSet("SUPERIEUR 1500");
            *setSUP << nbSUP;

            QBarSet *setINF = new QBarSet("INFERIEUR 1500");
            *setINF << nbINF;

            // Créer une série de barres pour le graphique
            //regrouper les deux QBarest
            QBarSeries *series = new QBarSeries();
            series->append(setSUP);
            series->append(setINF);

            // Créer un graphique à barres
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Répartition des EMPLOYES selon le salaire");
            chart->createDefaultAxes();

            // Personnaliser l'axe horizontal du graphique
            QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
            axisX->setTitleText("SALAIRE");
            axisX->append("Superieur 1500");
            axisX->append("INFERIEUR 1500");

            // Personnaliser l'axe vertical du graphique
            QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
            axisY->setLabelFormat("%.0f");
            axisY->setTitleText("Nombre de EMPLOYES");
            axisY->setRange(0, total + 1);
            axisY->setTickCount(total + 2);

            // Créer une vue pour le graphique
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            // Ajouter la vue dans le layout vertical nommé verticalLayout
            ui->verticalLayout->addWidget(chartView);

            // Afficher les pourcentages dans un label nommé label_stat



            // Affichage des pourcentages dans un QLabel
            ui->label_stat->setText(QString("SUPERIEUR 1500 : %1 (%2 %)\nINFERIEUR 1500 : %3 (%4 %)")
                                       .arg(nbSUP)
                                       .arg(QString::number(pourcentageSUP, 'f', 2))
                                       .arg(nbINF)
                                       .arg(QString::number(pourcentageINF, 'f', 2)));


        }
}










void secDialog::on_lineEdit_9_textEdited(const QString &arg1)
{
      ui->tableView->setModel(i.Recherche(arg1));
}





void secDialog::on_pushButton_19_clicked()
{
 ui->stackedWidget->setCurrentIndex(2);
}

void secDialog::on_pushButton_20_clicked()
{
     i.exporterpdf(ui->textBrowser);
}




