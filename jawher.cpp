#include "jawher.h"
#include "ui_jawher.h"
#include "equipment.h"
#include <QMessageBox>
#include<QIntValidator>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QFile>
#include <QPdfWriter>
#include <QDialog>
#include <QtDebug>
#include <QSqlQuery>
#include <QFile>
#include <QFileDialog>
#include <QDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QUrl>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QAbstractItemModel>
#include "qrcode.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "menu.h"
using namespace qrcodegen;
jawher::jawher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::jawher)
{
    ui->setupUi(this);
   ui->table_eq->setModel(E.afficher());
}

jawher::~jawher()
{
    delete ui;
}

void jawher::on_pushButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);

}





void jawher::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void jawher::on_btn_update_clicked()
{


    ui->stackedWidget->setCurrentIndex(2);



}


void jawher::on_pushButton_2_clicked()
{
    Equipment V;
            V.setidequi(ui->linemodifierid->text().toInt());
            V.setnomE(ui->linemodifie->text());
            V.setnombre(ui->linemodifienombre->text().toInt());
            V.setdate(ui->datemodifier->text());
            V.setdescription(ui->linemodifiedescr->text());
            V.setvideo(ui->linemodifievideo->text());

        qDebug() << "Updating record with matricule" << V.getidequi();
        bool test = V.modifier(V.getidequi(),V.getnomE(),V.getnombre(),V.getdate(),V.getdescription(),V.getvideo());
        qDebug() << "Update result:" << test;

        if (test) {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Modification successful. \nClick Cancel to exit."),
                QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                QObject::tr("id n'existe pas ou informations manquantes.\nClick Cancel to exit."),
                QMessageBox::Cancel);
        }
        ui->table_eq->setModel(E.afficher());


}




void jawher::on_supprimerbutton_clicked()
{
     ui->stackedWidget->setCurrentIndex(3);
}

void jawher::on_validersupp_clicked()
{
Equipment E1;
E1.setidequi(ui->idsupp->text().toInt());
bool test=E1.supprimer(E1.getidequi());
QMessageBox msgbox;
if(test)
    msgbox.setText("suppresion avec succes");
else
    msgbox.setText("echec de suprimer");
    msgbox.exec();

 ui->table_eq->setModel(E1.afficher());
}

void jawher::on_pushButton_3_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void jawher::on_pushButton_4_clicked()
{
    this->hide();

     menu Menu;
     Menu.setModal(true);
     Menu.exec() ;
}


void jawher::on_toolButton_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);

}

void jawher::on_pushButton_12_clicked()
{
    int idequi = ui->lineEdit_2->text().toInt();
    QString nomE = ui->lineEdit_3->text();
    int nombre = ui->lineEdit_4->text().toInt();
    QString date = ui->dateEdit->text();
    QString description = ui->lineEdit_6->text();
    QString video = ui->lineEdit_7->text();


     Equipment p(idequi,nomE,nombre,date,description,video);




     bool test;
test=p.ajouter();

if (test)
     {

     ui->table_eq->setModel(p.afficher());
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

void jawher::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}


//recherche

void jawher::on_rechercher_textChanged(const QString &arg1)
{
   Equipment p;

         QString rech=ui->rechercher->text();
         ui->table_eq->setModel(p.Recherche(rech));
}



//statistique
void jawher::on_statestique_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EQUIPEMENT where nombre < 4 ");
    float place1=model->rowCount();
    model->setQuery("select * from EQUIPEMENT where nombre  between 4 and 8 ");
    float place2=model->rowCount();
    model->setQuery("select * from EQUIPEMENT where nombre > 8 ");
    float place3=model->rowCount();
    float total=place1+place2+place3;

    QString a=QString("inferier 4 nombre equipment faible . "+QString::number((place1*100)/total,'f',2)+"%" );
    QString b=QString("entre 4 et 8 nombre equipment moyen .  "+QString::number((place2*100)/total,'f',2)+"%" );
    QString c=QString("plus de 10 nombre equipment tres bien.   "+QString::number((place3*100)/total,'f',2)+"%" );

    QPieSeries *series = new QPieSeries();//PieSeries object calculates the percentage the actual size of the slice in the chart.
    series->append(a,place1);
    series->append(b,place2);//concatiner 2 chaines
    series->append(c,place3);
    if (place1!=0)
    {QPieSlice *slice = series->slices().at(0);//the percentage the actual slice
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::red));}
    if ( place2!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(place3!=0)
    {
        // Add labels to rest of slices
        QPieSlice *slice2 = series->slices().at(2);
        //slice1->setExploded();
        slice2->setLabelVisible();// Sets the label visibility for all contours in the collection
    }
    // Create the chart widget
    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series); // widget
    chart->setTitle("review de nombre de equipment "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);//creation de la fenetre de widget
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}
//pdf
void jawher::on_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/ferja/Desktop/ferjani/loginApp/pdf/publication.pdf");



                  QPainter painter(&pdf);
                                QPixmap image("C:/Users/MonMSI/Downloads/logo.png");

                                // Afficher l'image avec QPainter
                              //  QPainter painter(&pdf);
                                painter.drawPixmap(423,417,image);
                  int i = 4000;
                         painter.setPen(Qt::darkCyan);
                         painter.setFont(QFont("Time New Roman", 25));
                         painter.drawText(3000,1400,"equipment list");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Time New Roman", 15));
                         painter.drawRect(100,100,9400,2500);
                         painter.drawRect(100,3000,9400,500);
                         painter.setFont(QFont("Time New Roman", 9));
                         painter.drawText(500,3300,"ID_EQUI");
                         painter.drawText(2000,3300,"NOM_EQUI");
                         painter.drawText(3000,3300,"NOMBRE");
                         painter.drawText(4000,3300,"DATE_ACHAT");
                         painter.drawText(5000,3300,"DESCRIPTION_EQUI");
                          painter.drawText(7000,3300,"VIDEO");
                         painter.drawRect(100,3000,9400,9000);

                         QSqlQuery query;
                         query.prepare("select * from EQUIPEMENT");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(500,i,query.value(0).toString());
                             painter.drawText(2000,i,query.value(1).toString());
                             painter.drawText(3000,i,query.value(2).toString());
                             painter.drawText(4000,i,query.value(4).toString());
                             painter.drawText(5000,i,query.value(3).toString());
                             painter.drawText(7000,i,query.value(5).toString());




                            i = i + 350;
                         }
                         QMessageBox::information(this, QObject::tr("PDF Saved Successfuly!"),
                         QObject::tr("PDF Saved Successfuly!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void jawher::on_tri_clicked()
{
    Equipment p;
    ui->table_eq->setModel(E.triB());

}

void jawher::on_tri2_clicked()
{
    Equipment p;
    ui->table_eq->setModel(E.triA());
}

void jawher::on_excel_clicked()
{
    QTableView *table;
                     table = ui->table_eq;

                     QString filters("CSV files (.csv);;All files (.*)");
                     QString defaultFilter("CSV files (*.csv)");
                     QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                        filters, &defaultFilter);
                     QFile file(fileName);

                     QAbstractItemModel *model =  table->model();
                     if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                         QTextStream data(&file);
                         QStringList strList;
                         for (int i = 0; i < model->columnCount(); i++) {
                             if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                                 strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                             else
                                 strList.append("");
                         }
                         data << strList.join(";") << "\n";
                         for (int i = 0; i < model->rowCount(); i++) {
                             strList.clear();
                             for (int j = 0; j < model->columnCount(); j++) {

                                 if (model->data(model->index(i, j)).toString().length() > 0)
                                     strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                                 else
                                     strList.append("");
                             }
                             data << strList.join(";") + "\n";
                         }
                         file.close();
                         QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
                     }
}

void jawher::on_qrcodegen_clicked()
{

    QMessageBox msg;
          QItemSelectionModel *select = ui->table_eq->selectionModel();
          if (!select->hasSelection()){
               msg.setText("Please select something");

               msg.setIcon(msg.Critical);
               msg.exec();
               return;
          }
    int tabeq=ui->table_eq->currentIndex().row();//selectionner dons le tab client ligne
           QVariant idd=ui->table_eq->model()->data(ui->table_eq->model()->index(tabeq,0));//selectionne le cin exactement
           QString id= idd.toString();//convertir a une chaine
           QSqlQuery qry;//navigating and retrieving data from SQL queries which are executed on a QSqlDatabase.

           qry.prepare("select * from equipment where ID_EQUI=:id");//Prepares the SQL query  for execution. Returns true or false
           qry.bindValue(":id",id);//prendre valeur id et mettre dans table client
           qry.exec();//Executes a previously prepared SQL query
              QString idequi, nomE,nombre, date , description, video,ide;

           while(qry.next()){//prend des variable de la base de donnes
               idequi=qry.value(1).toString();
               nomE=qry.value(2).toString();
               nombre=qry.value(3).toString();
               date=qry.value(4).toString();
               description=qry.value(5).toString();
               video=qry.value(6).toString();
           }
           ide=QString(id);
                  ide="ID_EQUI:"+idequi+"NOM_EQUI:"+nomE+"NOMBRE:"+nombre+"DATE_ACHAT:"+date+"DESCRIPTION_EQUI:"+description+"VIDEO:"+video;//pendre la chaine a code
           QrCode qr = QrCode::encodeText(ide.toUtf8().constData(), QrCode::Ecc::HIGH);

           // Read the black & white pixels
           QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
           for (int y = 0; y < qr.getSize(); y++) {
               for (int x = 0; x < qr.getSize(); x++) {
                   int color = qr.getModule(x, y);  // 0 for white, 1 for black

                   // You need to modify this part
                   if(color==0)
                       im.setPixel(x, y,qRgb(254, 254, 254));
                   else
                       im.setPixel(x, y,qRgb(0, 0, 0));
               }
           }
           im=im.scaled(200,200);
           ui->label_2->setPixmap(QPixmap::fromImage(im));

}

void jawher::on_arduino_clicked()

    {
     /*   // Connecter à l'Arduino via le port série
        QSerialPort arduino;
        arduino.setPortName(portName);
        arduino.setBaudRate(QSerialPort::Baud9600);
        arduino.open(QIODevice::ReadWrite);

        // Pause de 1 seconde
        QThread::msleep(1000);

        // Lire la valeur du capteur de gaz
        QByteArray data = arduino.readLine();
        QString gasValue = QString::fromLatin1(data).trimmed();


        double gasValueNum = gasValue.toDouble();


        QSqlQuery query;
        query.prepare("UPDATE VEHICULE SET GASVALUE = :gasValue WHERE ID_LABORATOIRE = :labID");
        query.bindValue(":gasValue", gasValueNum);
        query.bindValue(":labID", labID);
        if (!query.exec()) {
            qWarning() << "Database query failed:" << query.lastError().text();
            return;
        }

      qDebug() << "Gas value saved to database";*/}





void jawher::on_saveButton_clicked()
{
  /*  QString portName = "COM7";
    QString labID = ui->lineEdit_12->text();
    readGasSensorAndSaveToDatabase(portName, labID);*/
}
