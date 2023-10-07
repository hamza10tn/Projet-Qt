#include "samar.h"
#include "ui_samar.h"
#include "client.h"
#include <QMessageBox>
#include <QTextBrowser>
#include <QFileDialog>
#include <QDialog>
#include <QtPrintSupport/QPrintDialog>
#include "menu.h"

samar::samar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::samar)
{
    ui->setupUi(this);
      ui->tableView->setModel(i.afficher());
      ui->lineEdit->setValidator(new QIntValidator(0,99999999,this));
        ui->lineEdit_6->setValidator(new QIntValidator(0,99999999,this));
        m_ratingBar = new Ratingbar(5, ui->stars);


            connect(m_ratingBar, &Ratingbar::ratingChanged, this, &samar::onRatingChanged);
        r=r.getRatingByEmpl(IDEMP);// appelle la fonction getRating by empl
        if(r.getID()!=-1){
            m_ratingBar->setRating(r.getNOTE()); // appelle l fonction setRating

        }
        generateCaptcha();

        ui->pushButton_13->setVisible(false);



   }

   samar::~samar()
   {
       delete ui;
   }

   void samar::on_pushButton_ajouter_clicked()
   {
   }









   void samar::on_pushButton_supprimer_clicked()
   {

   }



   void samar::on_pushButton_clicked()
   {
         int ID_C=ui->lineEdit->text().toInt();
         QString NOM_C=ui->lineEdit_2->text();
           QString PRENOM_C=ui->lineEdit_3->text();
           QString ADRESSE=ui->lineEdit_4->text();
            QString EMAIL_C=ui->lineEdit_5->text();
           int NUM_TEL=ui->lineEdit_6->text().toInt();



   Client i(ID_C,NOM_C,PRENOM_C,ADRESSE,EMAIL_C, NUM_TEL);
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



   void samar::on_pushButton_2_clicked()
   {
       int ID_C=ui->lineEdit_15->text().toInt();
               bool test=i.supprimer(ID_C);
               if (test)
               {     ui->tableView->setModel(i.afficher());
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

   void samar::on_pushButton_4_clicked()
   {
       ui->stackedWidget->setCurrentIndex(2);
   }

   void samar::on_pushButton_3_clicked()
   {
       ui->stackedWidget->setCurrentIndex(1);
   }

   void samar::on_pushButton_8_clicked()
   {
       int ID_C=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt(); // get the selected row id

         QString NOM_C=ui->lineEdit_9->text();
        QString PRENOM_C=ui->lineEdit_10->text();
          QString ADRESSE=ui->lineEdit_11->text();
           QString EMAIL_C=ui->lineEdit_12->text();
            int NUM_TEL=ui->lineEdit_13->text().toInt();
            int FIDELITE=ui->lineEdit_14->text().toInt();

                 Client i(ID_C,NOM_C,PRENOM_C,ADRESSE,EMAIL_C, NUM_TEL);
                    bool test=i.modifier(ID_C);

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

     }
   }
   void samar::on_tableView_doubleClicked(const QModelIndex &index)
   {
       ui->lineEdit_9->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),1)).toString());
     ui->lineEdit_10->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),2)).toString());
      ui->lineEdit_11->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),3)).toString());
      ui->lineEdit_12->setText(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),4)).toString());
        ui->lineEdit_13->setText(QString::number(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),5)).toInt()));
      ui->lineEdit_14->setText(QString::number(ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),6)).toInt()));

   }


   void samar::on_pushButton_6_clicked()
   {
       ui->stackedWidget->setCurrentIndex(0);
   }

   void samar::on_pushButton_7_clicked()
   {
      ui->stackedWidget->setCurrentIndex(1);
   }

   void samar::on_lineEdit_2_textEdited(const QString &arg1)
   {

          /* QString name = ui->lineEdit_2->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

           // Vérification si le champ est vide ou non
           if (name.isstar()) {
               QMessageBox::warning(this, "Champ vide", "Le champ du nom est vide.");
               return;
           }

           // Vérification si le nom contient des caractères non alphabétiques
           QRegularExpression regex("[^a-zA-Z]");
           if (regex.match(name).hasMatch()) {
               QMessageBox::warning(this, "Nom invalide", "Le nom ne doit contenir que des lettres alphabétiques.");
               return;

       }*/
   }

   void samar::on_lineEdit_3_textEdited(const QString &arg1)
   {
       QString prenom = ui->lineEdit_3->text().trimmed(); // Récupération du texte en supprimant les espaces inutiles au début et à la fin

       // Vérification si le champ est vide ou non
       if (prenom.isEmpty()) {
           QMessageBox::warning(this, "Champ vide", "Le champ du prenom est vide.");
           return;
       }

       // Vérification si le prenom contient des caractères non alphabétiques
       QRegularExpression regex("[^a-zA-Z]");
       if (regex.match(prenom).hasMatch()) {
           QMessageBox::warning(this, "Nom invalide", "Le prenom ne doit contenir que des lettres alphabétiques.");
           return;

   }}

   void samar::on_lineEdit_5_editingFinished(){




   QString EMAIL=ui->lineEdit_12->text();
   if
   (!QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(EMAIL).hasMatch()) {
           QMessageBox::critical(this, "Error", "L'adresse mail n'est pas valide.");}
           else
               QMessageBox::information(this,"true","adresse valide");

           return;
   }
   void samar::on_lineEdit_12_editingFinished()
   {
       QString EMAIL=ui->lineEdit_12->text();
       if
       (!QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$").match(EMAIL).hasMatch()) {
               QMessageBox::critical(this, "Error", "L'adresse mail n'est pas valide.");}
               else
                   QMessageBox::information(this,"true","adresse valide");

               return;
           }

   void samar::on_tableView_clicked(const QModelIndex &index)
   {

   }



   void samar::on_lineEdit_8_textChanged(const QString &arg1)
   {
       ui->tableView->setModel(i.Recherche(arg1));
   }

   void samar::on_pushButton_9_clicked()
   {
           ui->tableView->setModel(i.trifidelite()) ;
   }

   void samar::on_pushButton_10_clicked()
   {

       i.exporterpdf(ui->textBrowser) ;
   }

   void samar::on_pushButton_11_clicked()
   {
       s=new Dialog();
       s->setWindowTitle("statistique ");
       s->choix_pie();
       s->show();
   }

   void samar::on_pushButton_12_clicked()
   {
       this->hide();

        menu Menu;
        Menu.setModal(true);
        Menu.exec() ;
   }
   QString samar::randomString(int length)
   {
       const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
       const int randomStringLength = possibleCharacters.length();
       QString randomString;

       // Use the current time to seed the pseudo-random number generator
       std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());//initialise un generateur de nmbr alea

       // Use a uniform distribution to generate random indices
       std::uniform_int_distribution<int> distrib(0, randomStringLength - 1);// definit une distribution uniforme d'entiers

       for(int i = 0; i < length; ++i)
       {
           int index = distrib(gen); //genere un index alea
           QChar nextChar = possibleCharacters.at(index); // recupere le crctr correspondant a lindex alea a partir de la liste possible
           randomString.append(nextChar);// ajouter le crctr a la chaine alea
       }
       return randomString;
   }
   void samar::onRatingChanged(int rating)
   {
       ui->pushButton_13->setVisible(true);
       qDebug()<<rating;//affiche la valeur donnee par l'utlstr pour le debogage
       if(r.getID()!=-1){
           r.setNOTE(rating);


       }else{
          r.setIDEMP(IDEMP);
          r.setNOTE(rating);


       }
   }
   void samar::generateCaptcha(){
       captcha = randomString(6); // generate a random string of 6 characters
       QPixmap captchaImage(200, 50); // create a pixmap with size 200x50
       captchaImage.fill(Qt::white); // fill the pixmap with white color

       QPainter painter(&captchaImage); // create a painter to draw on the pixmap
       painter.setFont(QFont("Arial", 20)); // set the font and size
       painter.setPen(Qt::red); // set the color to use
       painter.drawText(10, 30, captcha); // draw the captcha string

       captchaImage.save("captcha.png"); // save the pixmap as a PNG file
       ui->captchaLabel->setPixmap(captchaImage);
   }

   void samar::on_pushButton_13_clicked()
   {
       QString userInput = ui->captchavalue->text(); // get the user's input from a QLineEdit widget
       if (userInput.compare(captcha, Qt::CaseInsensitive) == 0) // compare the user's input with the original captcha string
       {
           QMessageBox::information(nullptr, QObject::tr("captcha is valid , rating added "),
                       QObject::tr("succes.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


          if(r.getID()!=-1){
              r.Modifier();
          }else{
              r.Add();
               r=r.getRatingByEmpl(IDEMP);
          }
       }
       else
       {
           // user input does not match, generate a new captcha string and display a new image

           QMessageBox::warning(nullptr, QObject::tr("captcha is not valid , rating added "),
                       QObject::tr("not valid.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

       }
       generateCaptcha();
       ui->captchavalue->setText("");
   }

   void samar::on_pushButton_14_clicked()
   {
       ui->stackedWidget->setCurrentIndex(2);
   }

   void samar::on_pushButton_5_clicked()
   {
   ui->stackedWidget->setCurrentIndex(3);
   }



