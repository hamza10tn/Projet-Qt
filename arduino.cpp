#include "arduino.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QObject>
//QSerialPort est une classe de la bibliothèque Qt qui permet de communiquer avec un port série, tel que celui utilisé pour la communication avec une carte Arduino.
Arduino::Arduino()
{
   // data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
    //Cet objet est utilisé pour communiquer avec l'Arduino via un port série.
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
//connect a une carte arduino
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    serialbuffer="";
    //parcourt lel port pour voir le port disponible
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        //elle vérifie si celui-ci possède un identifiant de vendeur et de produit correspondant à ceux d'une carte Arduino Uno. Si c'est le cas, elle enregistre le nom du port série et met à jour la variable "arduino_is_available" à "true".
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;//carte arduino n'a ete trouve
}
//arrreter la communiction serie avec la carte arduino
int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}





 int Arduino::chercherid(QString id){

     QSqlDatabase bd = QSqlDatabase::database();

         QSqlQuery query;
         query.prepare("SELECT ID_R  FROM RDV WHERE ID_R =:id");
  query.bindValue(":id", id);

         query.exec();
         if (query.next())
         {


              return 1;
         }
         else {
             return -1;
         }

 }
/* QByteArray Arduino::getdata()
 {
     return data;
 }*/
int Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}

