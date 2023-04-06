#ifndef SENDMAILER_H
#define SENDMAILER_H

#include<QString>
#include <QtNetwork>
#include <QtNetwork/QSslSocket>
class sendMailer
{
public:
    sendMailer();
    static int send(QString email,QString object,QString body );

};

#endif // SENDMAILER_H
