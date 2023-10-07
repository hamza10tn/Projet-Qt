#include "maissa.h"
#include "ui_maissa.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
//#include "type_service.h"
#include <QSqlError>
#include <QMessageBox>
#include <QIntValidator>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlQueryModel>
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
//#include "reduction.h"
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QVBoxLayout>
//#include "stat.h"
#include <QtCharts>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QStandardItemModel>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QIntValidator>
#include "QSqlQuery"
#include "QStringListModel"
#include<QFileDialog>
#include<QTextDocument>
#include<QTextStream>
#include<QGraphicsView>
#include<QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QSystemTrayIcon>
#include<QUrlQuery>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include <QDate>
#include <QTime>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QTableWidgetItem>
#include <QtPrintSupport/QPrinter>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QCoreApplication>
#include <QtGlobal>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrlQuery>
#include "arduino.h"
#include "menu.h"

maissa::maissa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maissa)
{
    ui->setupUi(this);
    ui->refresh->setIcon((QIcon(":/images/refresh1.png")));
       ui->refresh->setIconSize(ui->refresh->size());
       ui->refresh->setCheckable(true);
        ui->refresh_2->setIcon((QIcon(":/images/refresh1.png")));
        ui->refresh_2->setIconSize(ui->refresh_2->size());
        ui->refresh_2->setCheckable(true);
        ui->refresh_4->setIcon((QIcon(":/images/refresh1.png")));
        ui->refresh_4->setIconSize(ui->refresh_4->size());
        ui->refresh_4->setCheckable(true);
        ui->refresh_6->setIcon((QIcon(":/images/refresh1.png")));
        ui->refresh_6->setIconSize(ui->refresh_6->size());
        ui->refresh_6->setCheckable(true);
        display_listes();

        //arduino:::

               int ret=A.connect_arduino(); // lancer la connexion & arduino
               switch (ret){
                case (0):qDebug ()<< "arduino is available and connected to :"<<A.getarduino_port_name();
                    break;
                case (1) : qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
                   break;
                case (-1) :qDebug () << "arduino is not available";
                }

               QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(detectFlamme()));
               //QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(on_pushButton_on_clicked()));
               //QObject::connect(A.getserial(), SIGNAL(readyRead()), this, SLOT(on_pushButton_of_clicked()));



             //*****


        }
        void maissa::detectFlamme(){

           ui->lineEdit_arduino->setText("SERVICE ajouter");

           data=A.read_from_arduino();
            qDebug() << data;
               if(data=="val:31\r\n1\r\n"){
                    QSqlQuery query;
                    query.prepare("UPDATE SERVICE SET ETAT = '1' WHERE ID=:id");
                    query.bindValue(":id", ui->ID_arduino->text());
                    query.exec();
               }
        }

        maissa::~maissa()
        {
            delete ui;
        }


        void maissa::display_listes()
        {
            ui->tab1->setModel(tmp_tab1.afficher());
            ui->tab1_2->setModel(tmp_tab2.afficher());
            ui->id_combo->setModel(tmp_tab1.combo_box());

            //test
            ui->comboBox->setModel(tmp_tab1.combo_box());

            ui->lineeditid->clear();
            ui->lineEditadres->clear();
            ui->sup_id_2->clear();
            ui->sup_id->clear();
            ui->lineeditid_3->clear();
            ui->typeservice->setModel(tmp_tab3.combo_box());

            ui->tab1_5->setModel(tmp_tab4.afficher());

            ui->comboBox_6_id->setModel(tmp_tab3.combo_box_2());
            ui->typeservice_2->setModel(tmp_tab3.combo_box());
            ui->lineEditadres_5->clear();
            ui->lineEditadres_4->clear();
            ui->lineEditbudget_2->clear();
            ui->tabcha_2->setModel(tmp_tab3.afficher());
            ui->lineEdit_24->clear();
            mainLayout=new QVBoxLayout ;
            mainLayout->addWidget(s.Preparechart());
            ui->widget->setLayout(mainLayout);
        ui->lineEditbudget_4->setVisible(false);
                ui->lineEditadres_6->setVisible(false);
        refresh_stat();

        ui->lineeditid_6->clear();

        ui->lineEditbudget_4->clear();

        ui->lineEditbudget_3->clear();

        ui->lineEditadres_8->clear();



            ui->sup_id_5->clear();

        }

        void maissa::refresh_stat()
        {
            if ( ui->widget->layout() != NULL )
            {
            QLayoutItem* item;
            while ( ( item = ui->widget->layout()->takeAt( 0 ) ) != NULL )
            {
            delete item->widget();
            delete item;
            }
            delete ui->widget->layout();
            }
            mainLayout = new QVBoxLayout;
            mainLayout->addWidget(s.Preparechart());
            ui->widget->setLayout(mainLayout);
        }
        void maissa::on_addTypeService_clicked()
        {
            int i=ui->lineeditid->text().toInt();
            QString p=ui->lineEditadres->text();
            type_service c(i,p);


            if ((i!='\0')&&(p!='\0'))
            {

            bool test = c.ajouter();
            if(test)

            {
                display_listes();

                QMessageBox::information(nullptr,("Ajout Type service"),("Type service ajouté"));}
        else
             {QMessageBox::warning(nullptr,("Ajout Type service"),("Type service non ajouté"));}
            }

            else QMessageBox::warning(nullptr,("Ajout Type service"),("pas de données"));
        }



        void maissa::on_refresh_toggled(bool checked)
        {
            if (checked){
                ui->refresh->setIcon((QIcon(":/images/refresh2.png")));
                ui->refresh->setIconSize(ui->refresh->size());
                display_listes();
            }
           else  {
                ui->refresh->setIcon((QIcon(":/images/refresh1.png")));
                ui->refresh->setIconSize(ui->refresh->size());
                display_listes();
            }
        }


        void maissa::on_modifierTypeService_clicked()
        {
            int i=ui->id_combo->currentText().toInt();
            QString b=ui->ad_chmo->text();
            type_service c(i,b);
            bool test=c.modifier();
            if(test)
            {
                 display_listes();
                QMessageBox::information(nullptr, QObject::tr("Modifier un Type service\n"),
                            QObject::tr("Type service modifier modifié.\n"
                                        "Cliquez sur Ok pour continuer."), QMessageBox::Ok);
            }
            else

               QMessageBox::critical(nullptr, QObject::tr("Modifier un Type service"),
                           QObject::tr("Erreur!\n"
                                       "Erreur de modification de le Type service.\n Veuillez réessayer."), QMessageBox::Ok);


        }


        void maissa::on_supprimerchantier_clicked()
        {
            QString a=ui->sup_id->text();
            bool test=tmp_tab1.supprimer(a);

            if (a!='\0'){
            QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {

                if(test)
                {
                    display_listes();
                    QMessageBox::information(nullptr, QObject::tr("Supprimer un Type service"),
                                QObject::tr("Type service supprimé.\n"
                                            "Click Ok to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer un Type service"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else  return;}



        }


        void maissa::on_tab1_activated(const QModelIndex &index)
        {
            QString a=ui->tab1->model()->data(index).toString();
            QSqlQuery query;
            query.prepare("select * from type_service where id=:id");
            query.bindValue(":id", a);

            if (query.exec())
            {
                while (query.next()) {
                    ui->sup_id->setText(query.value(0).toString());
                }
            }
        }


        void maissa::sendSMS(QString recipient, QString message)
        {
            QUrl url("https://rest.nexmo.com/sms/json");
            QNetworkRequest request(url);

            QByteArray postData;
            postData.append("api_key=8a21c679&api_secret=UN4Umph6p1SlwND9");
            postData.append("&to=" + recipient);
            postData.append("&from=Vonage APIs");
            postData.append("&text=" + message);

            QNetworkAccessManager manager;
            QNetworkReply* reply = manager.post(request, postData);
            QEventLoop loop;
            qDebug() << postData;
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            loop.exec();

            QByteArray response = reply->readAll();
            qDebug() << response;
        }


        void maissa::on_addTypeService_2_clicked()
        {
            const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
            const int codeLength = 6;
            QString randomCode;

            for (int i = 0; i < codeLength; ++i) {
                const int index = qrand() % possibleCharacters.length();
                randomCode.append(possibleCharacters.at(index));
            }

            int i = ui->lineeditid_3->text().toInt();
            reduction c(i, randomCode);

            if (i != '\0' && !randomCode.isEmpty()) {
                bool test = c.ajouter();
                qDebug() << QSslSocket::sslLibraryVersionString();
                if (test) {
                    display_listes();
                    sendSMS("21692850334", randomCode);
                    QMessageBox::information(nullptr, ("Ajout reduction"), ("reduction ajouté"));
                } else {
                    QMessageBox::warning(nullptr, ("Ajout reduction"), ("reduction non ajouté"));
                }
            } else {
                QMessageBox::warning(nullptr, ("Ajout reduction"), ("pas de données"));
            }
        }



        void maissa::on_supprimerchantier_2_clicked()
        {
            QString a=ui->sup_id_2->text();
            bool test=tmp_tab2.supprimer(a);

            if (a!='\0'){
            QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {

                if(test)
                {
                    display_listes();
                    QMessageBox::information(nullptr, QObject::tr("Supprimer un reduction"),
                                QObject::tr("reduction supprimé.\n"
                                            "Click Ok to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer un reduction"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else  return;}


        }


        void maissa::on_tab1_2_activated(const QModelIndex &index)
        {
            QString a=ui->tab1_2->model()->data(index).toString();
            QSqlQuery query;
            query.prepare("select * from reduction where id=:id");
            query.bindValue(":id", a);

            if (query.exec())
            {
                while (query.next()) {
                    ui->sup_id_2->setText(query.value(0).toString());
                }
            }
        }



        void maissa::on_refresh_2_toggled(bool checked)
        {
            if (checked){
                ui->refresh_2->setIcon((QIcon(":/images/refresh2.png")));
                ui->refresh_2->setIconSize(ui->refresh_2->size());
                display_listes();


            }
           else  {
                ui->refresh_2->setIcon((QIcon(":/images/refresh1.png")));
                ui->refresh_2->setIconSize(ui->refresh_2->size());
                display_listes();
            }
        }





        void maissa::on_addServiceButton_clicked()
        {
            int id=ui->lineeditid_2->text().toInt();
            QString nom=ui->lineEditadres_2->text();
            QString type=ui->typeservice->currentText();
            QString description=ui->lineEditadres_3->text();
            float prix=ui->lineEditbudget->text().toFloat();



            service c(id,nom,type,description,prix);

            bool test = c.ajouter();

            if ((id!='\0')&&(nom!='\0')&&(type!='\0')&&(description!='\0')&&(prix!='\0'))
            {

            if(test)

            {
                display_listes();

                QMessageBox::information(nullptr,("Ajout service"),("service ajouté"));}
        else
             {QMessageBox::warning(nullptr,("Ajout service"),("service non ajouté"));}
            }

            else QMessageBox::warning(nullptr,("Ajout service"),("pas de données"));
        }


        void maissa::on_id_combo_activated(const QString &)
        {
            QString a=ui->id_combo->currentText();
             QSqlQuery query;
             query.prepare("select * from type_service where id =:idd");
             query.bindValue(":idd", a);

             if (query.exec())
             {

                 while (query.next()) {

                      ui->id_combo->setCurrentText(query.value(0).toString());
                      ui->ad_chmo->setText(query.value(1).toString());
                 }
             }
        }


        void maissa::on_comboBox_6_id_activated(const QString &)
        {
            QString a=ui->comboBox_6_id->currentText();
             QSqlQuery query;
             query.prepare("select * from service where id =:idd");
             query.bindValue(":idd", a);

             if (query.exec())
             {

                 while (query.next()) {

                     ui->comboBox_6_id->setCurrentText(query.value(0).toString());
                     ui->lineEditadres_5->setText(query.value(1).toString());
                     ui->typeservice_2->setCurrentText(query.value(2).toString());
                     ui->lineEditadres_4->setText(query.value(3).toString());
                     ui->lineEditbudget_2->setText(query.value(4).toString());
                 }
             }
        }


        void maissa::on_modifierchantier_6_clicked()
        {
            int id=ui->comboBox_6_id->currentText().toInt();
            QString nom=ui->lineEditadres_5->text();
            QString type=ui->typeservice_2->currentText();
            QString description=ui->lineEditadres_4->text();
            float prix=ui->lineEditbudget_2->text().toFloat();



            service c(id,nom,type,description,prix);



            if ((nom!='\0')&&(description!='\0')&&(prix!='\0'))
            {
        bool test = c.modifier();
            if(test)

            {
                display_listes();

                QMessageBox::information(nullptr,("modifer service"),("service modifer"));}
        else
             {QMessageBox::warning(nullptr,("modifer service"),("service non modifer"));}
            }

            else QMessageBox::warning(nullptr,("modifer service"),("pas de données"));
        }

        void maissa::on_tabcha_2_activated(const QModelIndex &index)
        {
            QString a=ui->tabcha_2->model()->data(index).toString();
            QSqlQuery query;
            query.prepare("select * from service where id=:id");
            query.bindValue(":id", a);

            if (query.exec())
            {
                while (query.next()) {
                    ui->lineEdit_24->setText(query.value(0).toString());
                             ui->lineEditadres_6->setText(query.value(0).toString());
                }
            }
        }


        void maissa::on_supprimerservice_clicked()
        {
            QString a=ui->lineEdit_24->text();
            bool test=tmp_tab3.supprimer(a);

            if (a!='\0'){
            QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {

                if(test)
                {
                    display_listes();
                    QMessageBox::information(nullptr, QObject::tr("Supprimer un service"),
                                QObject::tr("service supprimé.\n"
                                            "Click Ok to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer un service"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else  return;}


        }

        void maissa::on_refresh_4_toggled(bool checked)
        {
            if (checked){
                ui->refresh_4->setIcon((QIcon(":/images/refresh2.png")));
                ui->refresh_4->setIconSize(ui->refresh_4->size());
                display_listes();


            }
           else  {
                ui->refresh_4->setIcon((QIcon(":/images/refresh1.png")));
                ui->refresh_4->setIconSize(ui->refresh_4->size());
                display_listes();
            }
        }


        void maissa::on_comboBox_2_activated(const QString &arg1)
        {

            if(arg1!="Select"){
                if (ui->radioButton_9->isChecked())
                {
                    ui->tabcha_2->setModel(tmp_tab3.trier(arg1,"ASC"));

                }
                else if (ui->radioButton_10->isChecked())
                {
                    ui->tabcha_2->setModel(tmp_tab3.trier(arg1,"DESC"));

                }else{
                     ui->tabcha_2->setModel(tmp_tab3.trier(arg1,"DESC"));
                }
            }




        }


        void maissa::on_pb_ok1_2_clicked()
        {
                QString type= ui->lineEdit_19->text() ;
                ui->tabcha_2->setModel(tmp_tab3.recherche(type));
        }





        void maissa::on_pushButton_11_clicked()
        {
             QString id = ui->lineEditadres_6->text();

             if(id!=NULL){
                 QString strStream;
                 QTextStream out(&strStream);

                 QVector <QString> information=tmp_tab3.getinforamation(id);


                 out <<  "<html>\n"
                     "<head>\n"
                     "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg("service")
                     <<  "</head>\n"
                     "<body  bgcolor=#ffffff link=#5000A0>\n";
                         out << "<h1 style='color: red;text-align: center;'>Fiche de Service</h1>";
                         out << "<span style='text-align: center; display: inline;'><h2>Nom:"<<QString("  %1 </h2></span>").arg(information.at(0));
                         out << "<span style='text-align: center;'><h2>Type:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(1));
                         out << "<span style='text-align: center;'><h2>Description:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(2));
                         out << "<span style='text-align: center;'><h2>Prix:</h2>" <<QString("<h3>%1</p></h3>").arg(information.at(3));

                     "</body>\n"
                     "</html>\n";

                         QPrinter printer(QPrinter::HighResolution);
                         printer.setPageSize(QPrinter::A4);
                         QPrintDialog *dialog = new QPrintDialog(&printer,this);
                         if (dialog->exec() == QDialog::Accepted)
                         {
                             QPainter painter(&printer);
                             painter.begin(&printer);
                             quint32 iYPos = 0;
                             quint32 iWidth = printer.width();
                             quint32 iHeight = printer.height();

                             QSize s(iWidth/3, iHeight/5);

                             QFont f;
                             f.setPointSize(16); // reduced font size
                             f.setBold(true);
                             f.setItalic(true);
                             painter.setFont(f);

                             // Set up table
                             const int margin = 150; // increased margins
                             const int tableWidth = iWidth - 2*margin;
                             const int tableHeight = 500;
                             const int tableX = margin;
                             const int tableY = 400; // adjusted Y position
                             const int columnWidth = tableWidth / 4;

                             // Draw table header
                             painter.setPen(Qt::white);
                             painter.setBrush(QColor(50, 205, 50));
                             painter.drawRect(tableX, tableY, tableWidth, 100);
                             painter.drawText(tableX + 20, tableY + 90, "Nom");
                             painter.drawText(tableX + columnWidth + 20, tableY + 90, "Type");
                             painter.drawText(tableX + columnWidth * 2 + 20, tableY + 90, "Description");
                             painter.drawText(tableX + columnWidth * 3 + 20, tableY + 90, "Prix");

                             // Draw table content
                             f.setPointSize(12); // reduced font size
                             painter.setFont(f);
                             painter.setPen(Qt::black);
                             painter.setBrush(Qt::NoBrush);
                             painter.drawRect(tableX, tableY + 100, tableWidth, tableHeight);

                             painter.drawText(tableX + 20, tableY + 240, information.at(0));
                             painter.drawText(tableX + columnWidth + 20, tableY + 240, information.at(1));
                             painter.drawText(tableX + columnWidth * 2 + 20, tableY + 240, information.at(2));
                             painter.drawText(tableX + columnWidth * 3 + 20, tableY + 240, information.at(3));

                             // Add some styling
                             f.setPointSize(24);
                             painter.setFont(f);
                             painter.setPen(Qt::white);
                             painter.setBrush(QColor(50,205,50));
                             int titleX = (iWidth - 500) / 3;
                             painter.drawRect(0, 0, iWidth, 150);
                             painter.drawText(titleX, 100, "Fiche de Service");

                             // End painting
                             painter.end();
                         }


             }        else
             {
                 QMessageBox::critical(nullptr, QObject::tr("Imprimer service"),
                             QObject::tr("Erreur !.\n"
                                         "Veuillez selectionner un id d'un service à imprimer .\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);}


        }


        void maissa::on_addTypeService_5_clicked()
        {
            // Get input values from UI
            int id = ui->lineeditid_6->text().toInt();

            int id_service = ui->comboBox->currentText().toInt();


            float prix = ui->lineEditbudget_3->text().toFloat();
            QString promoCodes = ui->lineEditadres_8->text();

            // Check if input values are valid
            if (id != 0 && id_service != 0 && prix != 0) {
                if (promoCodes.isEmpty()) {
                    // If no promo code entered, create a new purchase without discount
                    achat a(id, id_service, prix);

                    bool test = a.ajouter();

                    if (test) {
                        display_listes();
                        QMessageBox::information(nullptr, "Achat", "Achat effectué");
                    } else {
                        QMessageBox::warning(nullptr, "Achat", "Achat non effectué");
                    }
                } else {
                    // If a promo code is entered, check if it exists in the database
                    QSqlQuery query;
                    query.prepare("select code from reduction where code = :idd");
                    query.bindValue(":idd", promoCodes);

                    if (query.exec()) {
                        // If promo code exists in database, apply 20% discount to purchase
                        if (query.next()) {
                            if (promoCodes == query.value(0).toString()) {
                                achat a(id, id_service, prix - (prix * 0.2));

                                bool test = a.ajouter();

                                if (test) {
                                    tmp_tab2.supprimerParCode(promoCodes);
                                    display_listes();
                                    QMessageBox::information(nullptr, "Achat", "Achat effectué avec une réduction de 20%");
                                } else {
                                    QMessageBox::warning(nullptr, "Achat", "Achat non effectué");
                                }
                            }
                        }else {
                             // If promo code doesn't exist in database, show an error message
                             QMessageBox::warning(nullptr, "Achat", "Code promo incorrect");
                             ui->lineEditadres_8->clear();
                         }
                    }
                }
            } else {
                // If input values are not valid, show an error message
                QMessageBox::warning(nullptr, "Achat", "Pas de données");
            }
        }


        void maissa::on_typeservice_3_activated(const QString &)
        {

             QSqlQuery query;
             query.prepare("select * from service where nom =:idd");


             if (query.exec())
             {
                 while (query.next()) {
                      ui->lineEditbudget_4->setText(query.value(0).toString());
                      ui->lineEditbudget_3->setText(query.value(4).toString());
                 }
             }
        }


        void maissa::on_supprimerchantier_5_clicked()
        {
            QString a=ui->sup_id_5->text();
            bool test=tmp_tab4.supprimer(a);

            if (a!='\0'){
            QMessageBox::StandardButton reponse = QMessageBox::question(this,"suppression","confirmer la suppression",QMessageBox::Yes | QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {

                if(test)
                {
                    display_listes();
                    QMessageBox::information(nullptr, QObject::tr("Supprimer un achat"),
                                QObject::tr("achat supprimé.\n"
                                            "Click Ok to exit."), QMessageBox::Cancel);

                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Supprimer un achat"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else  return;}


        }


        void maissa::on_tab1_5_activated(const QModelIndex &index)
        {
            QString a=ui->tab1_5->model()->data(index).toString();
            QSqlQuery query;
            query.prepare("select * from achat where id=:id");
            query.bindValue(":id", a);

            if (query.exec())
            {
                while (query.next()) {
                    ui->sup_id_5->setText(query.value(0).toString());
                }
            }
        }


        void maissa::on_refresh_6_toggled(bool checked)
        {
            if (checked){
                ui->refresh_6->setIcon((QIcon(":/images/refresh2.png")));
                ui->refresh_6->setIconSize(ui->refresh->size());
                display_listes();
            }
           else  {
                ui->refresh_6->setIcon((QIcon(":/images/refresh1.png")));
                ui->refresh->setIconSize(ui->refresh_6->size());
                display_listes();
            }
        }


        void maissa::on_pushButton_clicked()
        {
            QSqlQuery query;
              query.prepare("UPDATE SERVICE SET ETAT = '0' WHERE ID=:id");
              query.bindValue(":id", ui->ID_arduino->text());
              query.exec();
              A.write_to_arduino("s");
        }










void maissa::on_pushButton_2_clicked()
{
    this->hide();

     menu Menu;
     Menu.setModal(true);
     Menu.exec() ;
}
