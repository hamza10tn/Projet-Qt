#include "hamza.h"
#include "ui_hamza.h"
#include<QSortFilterProxyModel>
#include <QSqlQuery>
#include <QSqlError>
#include"QMessageBox"
#include"connexion.h"
#include"QtDebug"
#include"QStandardItemModel"
#include <QtPrintSupport/QPrinter>
#include"QTimer"
#include"QDateTime"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include<QBarSeries>
#include<QBarSet>
#include<QtCharts/QBarSet>
#include<QIntValidator>
#include <QDebug>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QFile>
#include <QPdfWriter>
#include <QDialog>
#include <QtDebug>
#include <QSqlQuery>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QDesktopServices>
#include <QUrl>
#include <QAbstractItemModel>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtCharts>
#include<QPixmap>
#include<QtSql/QSqlTableModel>
#include <QtCharts/QPieSlice>
#include"arduino.h"
hamza::hamza(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hamza)
{
    ui->setupUi(this);
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


      ui->tableView->setModel(V.afficher());
      ui->tableView_2->setModel(V.afficher());
      ui->stackedWidget->setCurrentIndex(0);
  //time
     QTimer *timer=new QTimer(this);
     connect (timer , SIGNAL (timeout()) ,this ,SLOT(showTime()));
     timer->start();
  //date
     QDateTime dateTime=QDateTime::currentDateTime();
     QString datetimetext=dateTime.toString("yyyy-MM-dd");
     ui->DATE->setText(datetimetext);

      /* Définir la hauteur par défaut pour toutes les lignes
      ui->tableView->verticalHeader()->setDefaultSectionSize(50);
      ui->tableView_2->verticalHeader()->setDefaultSectionSize(50);
      // Définir la largeur par défaut pour toutes les colonnes
      ui->tableView->horizontalHeader()->setDefaultSectionSize(170);
       ui->tableView_2->horizontalHeader()->setDefaultSectionSize(170);
  */
       //to view the pic in the label
       QPixmap pix("/Users/hamza/Downloads");
       ui->label_pic->setPixmap(pix);

  /*
       // Create a new QSqlTableModel instance and set the database connection
       QSqlTableModel *model = new QSqlTableModel(this);
       model->setTable("your_table_name"); // Replace "your_table_name" with the actual name of your table
       model->setEditStrategy(QSqlTableModel::OnManualSubmit); // Set the edit strategy to manual submit

       // Set the column names to be displayed in the table view
       model->setHeaderData(0, Qt::Horizontal, tr("Matricule ID"));
       model->setHeaderData(1, Qt::Horizontal, tr("Image"));

       // Populate the model with data from the database
       if (!model->select()) {
           qDebug() << "Failed to load data from table!";
       }

       // Set the model to the table view
       ui->tableView->setModel(model);

       // Set the column widths to fit the contents
       ui->tableView->resizeColumnsToContents();
       */
  }

  hamza::~hamza()
  {
      delete ui;
  }





  void hamza::on_pushButton_ajouter_clicked()
  {

      QString matricule=ui->lineEdit_matricule->text();
      QString modele=ui->lineEdit_modele->text();
      QString type=ui->comboBox_type->currentText();
      QString etat=ui->plainTextEdit_etat->toPlainText();
      Vehicule V(matricule,modele,type,etat);
       // Check if the matricule already exists
       if (V.matriculeExists(matricule)) {
           QMessageBox::warning(this, "Duplicate Matricule", "Matricule existe deja.");
       } else {
           // Attempt to add the new vehicule
       V.ajouter();
       // Check if any item is empty
       if (V.get_matricule().isEmpty() || V.get_modele().isEmpty() || V.get_type().isEmpty())
       {
           QString errorMessage = "Entrer les information restants:\n\n";
           if (V.get_matricule().isEmpty()) errorMessage += "- Matricule\n";
           if (V.get_modele().isEmpty()) errorMessage += "- Modele\n";
           if (V.get_type().isEmpty()) errorMessage += "- Type\n";

           QMessageBox::warning(this, "Missing Information", errorMessage);
       }
       else
       {
           QMessageBox::information(this, "Ajouter!", "Added successfully.");
           ui->tableView->setModel(V.afficher()) ;
           ui->tableView_2->setModel(V.afficher()) ;
       }

  }

  }

  void hamza::on_pushButton_supprimer_clicked()
  {
      Vehicule V;
      V.setmatricule(ui->lineEdit_matriculeSupprimer->text());

      bool test=V.supprimer(V.get_matricule());


      if (test){
          QMessageBox::information(nullptr, QObject::tr("ok"),
                  QObject::tr("delete successful. \n"
                              "click cancel to exit."), QMessageBox::Cancel);
      }
          else
             { QMessageBox::critical(nullptr, QObject::tr("not OK"),
                          QObject::tr("cette matricule n'existe pas.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
  }
          ui->tableView_2->setModel(V.afficher()) ;
           ui->tableView->setModel(V.afficher()) ;

  }




  void hamza::on_pushButton_page1_clicked()
  {
      ui->stackedWidget->setCurrentIndex(0);
  }

  void hamza::on_pushButton_page2_clicked()
  {
      ui->stackedWidget->setCurrentIndex(1);
  }
  void hamza::on_pushButton_page3_clicked()
  {
      ui->stackedWidget->setCurrentIndex(2);
  }

  void hamza::on_pushButton_page4_clicked()
  {
          ui->stackedWidget->setCurrentIndex(3);
  }


  void hamza::on_pushButton_quitter_clicked()
  {
           QApplication::quit();
  }



  void hamza::on_pushButton_modifier_clicked()
  {


      Vehicule V;
          V.setmatricule(ui->lineEdit_matricule->text());
          V.setmodele(ui->lineEdit_modele->text());
          V.settype(ui->comboBox_type->currentText());
          V.setetat(ui->plainTextEdit_etat->toPlainText());


      bool test = V.modifier(V.get_matricule(),V.get_modele(),V.get_type(),V.get_etat());

      if (test) {
          QMessageBox::information(nullptr, QObject::tr("OK"),
              QObject::tr("Modification successful. \nClick Cancel to exit."),
              QMessageBox::Cancel);
      } else {
          QMessageBox::critical(nullptr, QObject::tr("Not OK"),
              QObject::tr("Matricule n'existe pas ou informations manquantes.\nClick Cancel to exit."),
              QMessageBox::Cancel);
      }

      ui->tableView_2->setModel(V.afficher());
      ui->tableView->setModel(V.afficher());
  }






  void hamza::on_pushButton_chercher_clicked()
  {
      QString searchMatricule = ui->lineEdit_recherche->text();

      // Set the data model for the table view
      ui->tableView_2->setModel(V.afficher());

      // Create a QSortFilterProxyModel to filter the records by matricule
      QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
      proxyModel->setSourceModel(ui->tableView_2->model());
      proxyModel->setFilterKeyColumn(0); // assuming the matricule column is 0
      proxyModel->setFilterRegExp(QRegExp(searchMatricule, Qt::CaseInsensitive, QRegExp::FixedString));

      // Set the filtered data model for the table view
      ui->tableView_2->setModel(proxyModel);
  }






  void hamza::on_pushButton_pdf_clicked()
  {

      // Créer une instance de la classe QPrinter
      QPrinter printer(QPrinter::PrinterResolution);

      // Demander à l'utilisateur de choisir le nom et le chemin du fichier PDF à générer
      QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "untitled.pdf", tr("Fichiers PDF (*.pdf);;Tous les fichiers (*.*)"));

      if (fileName.isEmpty()) {
          return;
      }

      // Configurer l'imprimante
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName(fileName);

      // Créer un document PDF et le lier à l'imprimante
      QTextDocument doc;

      QString html;
      QAbstractItemModel* model = ui->tableView_2->model();

      html += "<table border='1' cellpadding='2'>";

      // Ajouter les en-têtes de colonne
      html += "<tr>";
      for (int i = 0; i < model->columnCount(); i++) {
          html += "<th>" + model->headerData(i, Qt::Horizontal).toString() + "</th>";
      }
      html += "</tr>";

      // Ajouter les données de chaque ligne
      for (int i = 0; i < model->rowCount(); i++) {
          html += "<tr>";
          for (int j = 0; j < model->columnCount(); j++) {
              QVariant data = model->data(model->index(i, j));
              if (data.type() == QVariant::ByteArray) {
                  // This column contains an image
                  QByteArray imageData = data.toByteArray();
                  QImage image;
                  image.loadFromData(imageData);
                  QString base64Image = QString(imageData.toBase64());
                  html += "<td><img style='width: 20px;' src='data:image/png;base64," + base64Image + "'/></td>";
              } else {
                  // This column contains text
                  html += "<td>" + data.toString() + "</td>";
              }
          }
          html += "</tr>";
      }


      html += "</table>";

      doc.setHtml(html);

      // Imprimer le document sur l'imprimante
      doc.print(&printer);
  }

  void hamza::showTime()
  {
  QTime time=QTime::currentTime();
  QString time_text=time.toString("hh:mm:ss");
  ui->Digital_clock->setText(time_text);

  }





  void hamza::on_pushButton_tri_modeleAZ_clicked()
  {
      Vehicule v;
      ui->tableView_2->setModel(V.triB());


  }

  void hamza::on_pushButton_tri_modeleZA_clicked()
  {
      Vehicule v;
      ui->tableView_2->setModel(V.triA());


  }




  void hamza::on_pushButton_browseimage_clicked()
  {

      QFileDialog dialog(this);
          dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
          dialog.setViewMode(QFileDialog::Detail);
          QString fileName = dialog.getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.xpm *.jpg)"));
          if(!fileName.isEmpty())
          {
              QImage image(fileName);
              if(image.isNull())
              {
                  QMessageBox::warning(this, tr("Open Image"), tr("Cannot load .").arg(fileName));
                  return;
              }
              QPixmap pix(QPixmap::fromImage(image));
              ui->label_pic->setPixmap(pix);
              image.save("image.png"); // sauvegarder l'image dans un fichier
   }
    /*  QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files (*.png *.jpg *.bmp)"));
         if (!imagePath.isEmpty()) {
             QPixmap image(imagePath);
             ui->label_pic->setPixmap(image);
         }
  */
  /* Vehicule V;
      QString imageFile = QFileDialog ::getOpenFileName(this, tr("choose"), "", tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

      QFileInfo info(imageFile);
      QFileInfo  filename = info.fileName(); //path de l'image

      QPixmap image (imageFile);
      ui->label_pic->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored );
      image = image.scaledToWidth(ui->label_pic->width(), Qt::SmoothTransformation);
     // image = image.scaled(391,321,Qt::IgnoreAspectRatio,Qt::FastTransformation);
      ui->label_pic->setPixmap(image);
      ui->label_pic->show();


      V.get_image() = imageFile;

    qDebug()<<  V.get_image();
  */
  }
  void hamza::on_pushButton_insertion_image_clicked()
  {
      // Open a file dialog to choose an image file
            QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image File"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

            // Get the matricule ID from the user input
            QString matricule = QInputDialog::getText(this, tr("Enter Matricule ID"), tr("Matricule ID:"));

            // Load the image from the file path
            QImage image;
            if (!image.load(imagePath)) {
                qDebug() << "Failed to load image from file!";
                return;
            }

            // Convert the image to a byte array
            QByteArray imageData;
            QBuffer buffer(&imageData);
            buffer.open(QIODevice::WriteOnly);
            image.save(&buffer, "PNG");

            // Execute the SQL insert statement to insert the image data and matricule ID into the table
            QSqlQuery query;
            query.prepare("INSERT INTO VEHICULE (matricule, image2) VALUES (:matricule, :image)");
            query.bindValue(":matricule", matricule);
            query.bindValue(":image", imageData);
            if(!query.exec()){
                qDebug() << "Failed to insert image data into the database!";
            }else{
                qDebug() << "Image data inserted into the database successfully!";
            }

            // Add a new row to the table widget and set the values of the corresponding columns
            int rowCount = ui->tableWidget_Image_List_From_Database->rowCount();
            ui->tableWidget_Image_List_From_Database->insertRow(rowCount);
            ui->tableWidget_Image_List_From_Database->setItem(rowCount, 0, new QTableWidgetItem(matricule));

            // Set the image as the decoration role of the table item
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setData(Qt::DecorationRole, QPixmap::fromImage(image).scaled(100, 100));
            ui->tableWidget_Image_List_From_Database->setItem(rowCount, 1, item);

            // Set the size of the row header
            ui->tableWidget_Image_List_From_Database->verticalHeader()->setDefaultSectionSize(100);

      }


  void hamza::on_pushButton_stat_clicked()
  {

      QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from VEHICULE where type = 'Voitures'");
        float voitureCount=model->rowCount();
        model->setQuery("select * from VEHICULE where type = 'Camions'");
        float camionCount=model->rowCount();
        model->setQuery("select * from VEHICULE where type = 'Motocyclettes et scooters'");
        float motoCount=model->rowCount();
        model->setQuery("select * from VEHICULE where type = 'Tracteurs'");
        float tracteurCount=model->rowCount();
        model->setQuery("select * from VEHICULE where type = 'Bus'");
        float busCount=model->rowCount();
        float total=voitureCount+camionCount+motoCount+tracteurCount+busCount;

        QString a=QString("Voitures: "+QString::number((voitureCount*100)/total,'f',2)+"%" );
        QString b=QString("Camions: "+QString::number((camionCount*100)/total,'f',2)+"%" );
        QString c=QString("Moto/Scouteur: "+QString::number((motoCount*100)/total,'f',2)+"%" );
        QString d=QString("Tracteur: "+QString::number((tracteurCount*100)/total,'f',2)+"%" );
        QString e=QString("Bus: "+QString::number((busCount*100)/total,'f',2)+"%" );

        QPieSeries *series = new QPieSeries();
        series->append(a,voitureCount);
        series->append(b,camionCount);
        series->append(c,motoCount);
        series->append(d,tracteurCount);
        series->append(e,busCount);

        if (voitureCount!=0)
        {
            QPieSlice *slice = series->slices().at(0);
            slice->setLabelVisible();
            slice->setPen(QPen(Qt::red));
        }
        if (camionCount!=0)
        {
            QPieSlice *slice1 = series->slices().at(1);
            slice1->setLabelVisible();
        }
        if (motoCount!=0)
        {
            QPieSlice *slice2 = series->slices().at(2);
            slice2->setLabelVisible();
        }
        if (tracteurCount!=0)
        {
            QPieSlice *slice3 = series->slices().at(3);
            slice3->setLabelVisible();
        }
        if (busCount!=0)
        {
            QPieSlice *slice4 = series->slices().at(4);
            slice4->setLabelVisible();
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Nombre des véhicules "+ QString::number(total));
        chart->legend()->hide();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();
  }

  void hamza::on_pushButton_temp_clicked()
  {


      qDebug()<<ui->lineEdit_temp->text();




         if(A.chercherH(ui->lineEdit_temp->text())==1)
         {QString nom=A.chercher(ui->lineEdit_temp->text());
             qDebug() << nom ;
             QByteArray x=nom.toUtf8();
             qDebug() << x ;
             A.write_to_arduino(x);
             qDebug()<<"valdie";
        qDebug()<<nom;
  }
         else
         { A.write_to_arduino("0"); qDebug()<<"invaldie"; }


      }

void hamza::on_pushButton_2_clicked()
{
    // Open a file dialog to choose an image file
          QString imagePath = QFileDialog::getOpenFileName(this, tr("Choose Image File"), "", tr("Images (*.png *.jpg *.jpeg *.bmp)"));

          // Get the matricule ID from the user input
          QString matricule = QInputDialog::getText(this, tr("Enter Matricule ID"), tr("Matricule ID:"));

          // Load the image from the file path
          QImage image;
          if (!image.load(imagePath)) {
              qDebug() << "Failed to load image from file!";
              return;
          }

          // Convert the image to a byte array
          QByteArray imageData;
          QBuffer buffer(&imageData);
          buffer.open(QIODevice::WriteOnly);
          image.save(&buffer, "PNG");

          // Execute the SQL insert statement to insert the image data and matricule ID into the table
          QSqlQuery query;
          query.prepare("INSERT INTO VEHICULE (matricule, image) VALUES (:matricule, :image)");
          query.bindValue(":matricule", matricule);
          query.bindValue(":image", imageData);
          if(!query.exec()){
              qDebug() << "Failed to insert image data into the database!";
          }else{
              qDebug() << "Image data inserted into the database successfully!";
          }

          // Add a new row to the table widget and set the values of the corresponding columns
          int rowCount = ui->tableWidget_Image_List_From_Database->rowCount();
          ui->tableWidget_Image_List_From_Database->insertRow(rowCount);
          ui->tableWidget_Image_List_From_Database->setItem(rowCount, 0, new QTableWidgetItem(matricule));

          // Set the image as the decoration role of the table item
          QTableWidgetItem* item = new QTableWidgetItem();
          item->setData(Qt::DecorationRole, QPixmap::fromImage(image).scaled(100, 100));
          ui->tableWidget_Image_List_From_Database->setItem(rowCount, 1, item);

          // Set the size of the row header
          ui->tableWidget_Image_List_From_Database->verticalHeader()->setDefaultSectionSize(100);

    }

