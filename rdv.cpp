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
//#include"rendez_vous.h"
//#include"arduino.h"
#include "menu.h"
rdv::rdv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rdv)
{
    ui->setupUi(this);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
  int ret=a.connect_arduino();

      switch(ret){
      case(0):qDebug()<< "arduino is available and connected to : "<< a.getarduino_port_name();
          break;
      case(1):qDebug() << "arduino is available but not connected to :" <<a.getarduino_port_name();
         break;
      case(-1):qDebug() << "arduino is not available";
      }
      QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(on_pushButton_supprimez_2_clicked())); // permet de lancer
       //le slot update_label suite à la reception du signal readyRead (reception des données).
      connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_tableView_clicked(const QModelIndex&)));
  rendez_vous r;
     cc.ouvrirConnexion();
      ui->tableView->setModel(rr.afficher_rdv());
      std::vector<QDate> dates =r.getDatesFromRdvTable();

          // Apply the custom text format to each date in the CalendarWidget
          QTextCharFormat redFormat;
          redFormat.setBackground(QBrush(Qt::red));
          redFormat.setForeground(QColor(Qt::black));

          for (const QDate& date : dates) {
              ui->calendarWidget->setDateTextFormat(date, redFormat);
          }

          // Disable editing for the red dates
          for (const QDate& date : dates) {
              if (ui->calendarWidget->dateTextFormat(date).background().color() == Qt::red) {
                  ui->calendarWidget->setDateEditEnabled(false);
              }
          }
  }

  rdv::~rdv()
  {
      delete ui;
  }




  void rdv::on_tableView_clicked(const QModelIndex &index)
  {
      // Get the updated data from the selected row
      QString id = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toString();
      QTime time = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 2)).toTime();
      QVariant data = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 1));
      QDate dat = data.toDate();

      // Update the corresponding widgets in your UI
      ui->id->setText(id);
      ui->timeEdit->setTime(time);
      ui->calendarWidget->setSelectedDate(dat);
      qDebug() << "Clicked row:" << index.row();



  }








  void rdv::on_toolButton_clicked()
  {
      ui->stackedWidget->setCurrentIndex(1);

  }

  void rdv::on_toolButton_2_clicked()
  {
      ui->stackedWidget->setCurrentIndex(0);

  }

  void rdv::on_toolButton_5_clicked()
  {
      ui->stackedWidget->setCurrentIndex(0);

  }

  void rdv::on_toolButton_6_clicked()
  {
      ui->stackedWidget->setCurrentIndex(1);

  }

  void rdv::on_pushButton_2_clicked()
  {
      QStandardItemModel *model1 = new QStandardItemModel();
            model1->setColumnCount(4);
            model1->setHorizontalHeaderItem(0, new QStandardItem(QString("id")));
            model1->setHorizontalHeaderItem(1, new QStandardItem(QString("calendar")));
            model1->setHorizontalHeaderItem(2, new QStandardItem(QString("time")));
  //          model1->setHorizontalHeaderItem(3, new QStandardItem(QString("MATRICULE")));
            ui->tableView->setModel(model1);

  }




  void rdv::on_pushButton_supprimez_clicked()
  {
      rendez_vous r;
      QString rendezvousleToDelete = ui->id->text();
      QModelIndexList matches = ui->tableView->model()->match(
          ui->tableView->model()->index(0, 0),Qt::DisplayRole,QVariant(rendezvousleToDelete),-1,Qt::MatchExactly);

      if (matches.isEmpty())
      {
          QMessageBox::warning(this, "rendez vous Not Found", "please type a valid id.");
          return;
      }
      else
      {



          bool test=r.supprimer_rdv(rendezvousleToDelete);

          // Search for the row with the matching matricule value


          if(test)
          {
                   ui->id->setText("");


              QMessageBox::information(nullptr,QObject::tr("NOT OK"),QObject::tr("suppresion avec succeeé"),QMessageBox::Cancel);
              ui->tableView->setModel(rr.afficher_rdv());


       }
          else
          {
          QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("supprersion a echoué"),QMessageBox::Cancel);
          }



      }




             }




  void rdv::on_pushButton_ajouter_rdv_clicked()
  {

      QString data1 = ui->id->text();
      //QDAte data2 = ui->mat->text();
      QTime data3 =ui->timeEdit->time();
      QDate data4=ui->calendarWidget->selectedDate();
      QString data2=ui->mat->text();





      rendez_vous r;
      r.setid(data1);
      r.setdate(data4);
      r.setheure(data3);
      r.setmat(data2);



              // Insert the data into the table widget


     if (r.get_date().isNull() || r.get_heure().isNull() || r.get_id().isEmpty() )
          {
              QMessageBox::warning(this, "Missing Information", "Please enter all fields before adding a new rendez vous.");
              return;
          }

     bool test=r.ajouter_rdv(r);
     if(test)
     {
         qDebug() << "id 1st " << r.get_id();
         qDebug() << "id data  " << data1;


         QMessageBox::information(nullptr,QObject::tr("ajout"),QObject::tr("ajout avec succeeé"),QMessageBox::Cancel);
         QTextCharFormat redFormat;
         redFormat.setBackground(QBrush(Qt::red));
         redFormat.setForeground(QColor(Qt::black));


             ui->calendarWidget->setDateTextFormat(data4, redFormat);

             ui->tableView->setModel(rr.trier_rdv("ASC"));

   }
     else
     {
     QMessageBox::critical(nullptr,QObject::tr("ajoout"),QObject::tr("ajout a echoué id existe dejaaaaaaaa"),QMessageBox::Cancel);
     }

  }


  void rdv::on_modifier_rdv_clicked()
  {
      QItemSelectionModel* selectionModel = ui->tableView->selectionModel();

            // Check if a row is currently selected
            if (!selectionModel->hasSelection())
            {
                QMessageBox::warning(this, "No Row Selected", "Please select a row to modify.");
                return;
            }


               else
            {

                QString data1 = ui->id->text();
                 //QDAte data2 = ui->mat->text();
                 QTime data3 =ui->timeEdit->time();
                 QDate data4=ui->calendarWidget->selectedDate();
                         // Insert the data into the table widget

                 rendez_vous r;

                 r.setid(data1);
                 r.setheure(data3);
                 r.setdate(data4);
                 bool test=r.modfier_rdv(r);


                      if(test)
                      {
                          QTextCharFormat redFormat;
                          redFormat.setBackground(QBrush(Qt::red));
                          redFormat.setForeground(QColor(Qt::black));


                              ui->calendarWidget->setDateTextFormat(data4, redFormat);
                          QMessageBox::information(this, "updated succesfully", "your data has been updated.");
                          ui->tableView->setModel(rr.afficher_rdv());


                      }
                      else
                       {
                           QMessageBox::warning(this, "there is an error on update", "please check your data before updating.");
                       }

  }

  }

  void rdv::on_chercher_clicked()
  {

      QString id=ui->id->text();

     rendez_vous r;





         bool test= r.chercher_rdv( id);

         // Search for the row with the matching matricule value


         if(test)
         {
             QModelIndexList matches = ui->tableView->model()->match(
                 ui->tableView->model()->index(0, 0),Qt::DisplayRole,QVariant(id),-1,Qt::MatchExactly);



             int row = matches.first().row();

                 // Select the row in the table view
                 ui->tableView->selectRow(row);

                 // Change the background color of the selected row
                 QPalette palette = ui->tableView->palette();
                 palette.setColor(QPalette::Highlight, QColor(Qt::yellow)); // Change the color to whatever you want
                 ui->tableView->setPalette(palette);
             }



         else
         {
         QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("rendez not  found"),QMessageBox::Cancel);
         }









  }

  void rdv::on_ASC_clicked()
  {
      ui->tableView->setModel(rr.trier_rdv("ASC"));

  }

  void rdv::on_DESC_clicked()
  {
      ui->tableView->setModel(rr.trier_rdv("DESC"));

  }
  void rdv::on_pdf_clicked()
  {
      QString strStream;
      QTextStream out(&strStream);
      const int rowCount = ui->tableView->model()->rowCount();
      const int columnCount = ui->tableView->model()->columnCount();

      out <<  "<html>\n"
              "<head>\n"
              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
              "<style>\n"
              "th, td {border: 1px solid black;padding:40px 60px;}\n"
              "table td {font-size: 30px;}\n"
              "table {width: 100%;border-collapse: collapse;table-layout: fixed;}\n"
              "table {background-color: #87CEEB;}\n"
              "table {width: 100%; border-collapse: collapse; table-layout: fixed;}\n"
              "th, td {padding: 8px; text-align: left; border-bottom: 1px solid #ddd;}\n"
              "thead tr {background-color: #f0f0f0;}\n"
              "</style>\n"
              <<  QString("<title>%1</title>\n").arg("eleve")
              <<  "</head>\n"
              "<body>\n"
                  "<h1>liste des rendez vous en  PDF </h1>\n"
                  "<table>\n";

      // headers
      out << "<thead><tr>";
      for (int column = 0; column < columnCount; column++)
          if (!ui->tableView->isColumnHidden(column))
              out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
      out << "</tr></thead>\n";

      //table change proprites


      // data table
      for (int row = 0; row < rowCount; row++) {
          out << "<tr>";
          for (int column = 0; column < columnCount; column++) {
              if (!ui->tableView->isColumnHidden(column)) {
                  QString data = ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                  out << QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
              }
          }
          out << "</tr>\n";
      }
      out << "</table>\n"
             "</body>\n"
             "</html>\n";

      QTextDocument *document = new QTextDocument();
      document->setHtml(strStream);

      QPrinter printer(QPrinter::PrinterResolution);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setOutputFileName("rdv.pdf");
      document->print(&printer);
      QMessageBox::information(nullptr,QObject::tr("RDV HAS BEEN SAVED"),QObject::tr("rendez a eté enregisté sous le nom rdv.pdf "),QMessageBox::Cancel);

  }



  void rdv::on_proche_clicked()
  {
  rendez_vous r;
  QDate s=r.chercherDateDisponible();
   ui->calendarWidget->setSelectedDate(s);
   qDebug() << "Date disponible: " << s;


  }

  void rdv::on_pushButton_7_clicked()
  {




  }
  void rdv::on_stat_clicked()
  {

      QDialog* dialog = new QDialog(this);
      dialog->setWindowTitle("Statistics");

      // Retrieve the data from the database
      QSqlQuery query;
      query.prepare("SELECT TO_CHAR(date_r, 'Month') AS month, COUNT(*) AS count FROM rdv GROUP BY TO_CHAR(date_r, 'Month');");
      if (!query.exec()) {
          qWarning() << "Failed to execute query:" << query.lastError().text();
          return;
      }

      QPieSeries* series = new QPieSeries();
      int total = 0;
      while (query.next()) {
          QString month = query.value(0).toString();
          int count = query.value(1).toInt();
          total += count;
          series->append(month, count);
      }

      // Calculate the percentage for each slice
      qreal totalPercentage = 0.0;
      for (QPieSlice* slice : series->slices()) {
          qreal percentage = static_cast<qreal>(slice->value()) / total * 100.0;
          slice->setLabel(QString("%1 (%2%)").arg(slice->label()).arg(QString::number(percentage, 'f', 1)));
          totalPercentage += percentage;
      }

      // Adjust the percentage of the last slice to ensure that the total is exactly 100%
      series->slices().last()->setLabel(QString("%1 (%2%)").arg(series->slices().last()->label()).arg(QString::number(100.0 - totalPercentage, 'f', 1)));
      QChart* chart = new QChart();
      chart->addSeries(series);
      chart->legend()->show();
      chart->setTitle("Appointments by Month");
      chart->setTitleBrush(QBrush(QColor(63, 81, 181)));
      chart->setTitleFont(QFont("Arial", 12, QFont::Bold));
      chart->setBackgroundBrush(QBrush(QColor(240, 240, 240)));
      chart->setAnimationOptions(QChart::AllAnimations);
      QChartView* chartView = new QChartView(chart, dialog);
      chartView->setRenderHint(QPainter::Antialiasing);
      chartView->setMinimumSize(400, 400);
      series->setLabelsVisible();
      series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

      // Create a close button
      QPushButton* closeButton = new QPushButton("Close", dialog);
      connect(closeButton, &QPushButton::clicked, dialog, &QDialog::close);

      // Set the layout of the dialog
      QVBoxLayout* layout = new QVBoxLayout(dialog);
      layout->addWidget(chartView);
      layout->addWidget(closeButton);
      dialog->setLayout(layout);

      // Show the dialog
      dialog->exec();
  }


  void rdv::on_pushButton_supprimez_2_clicked()
  {
      rendez_vous rd;
      QByteArray data;
      data = a.read_from_arduino();
      QString id=ui->id->text();


  // ...
      ui->temp->setText(data);

      if(data!="")
      {
          ui->temp->setText(data);
          rd.ajouter_rdv_temp(id,data);

      }
      qDebug()<<data<<"value";

  }

  void rdv::on_enregister_temperature_clicked()
  {
      rendez_vous rd;
      QByteArray data;
      data = a.read_from_arduino();
      QString id=ui->id->text();


  }

  void rdv::on_id_editingFinished()
  {
  rendez_vous rd;
  QString data=rd.matricule_existe(ui->id->text());
  qDebug()<<"value of mat is "<<data;
  ui->mat->setText(data);
  }



void rdv::on_pushButton_clicked()
{
    Arduino A;
    a.close_arduino();
    this->hide();

     menu Menu;
     Menu.setModal(true);

     Menu.exec() ;
}

