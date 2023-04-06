#include "sendmailer.h"

sendMailer::sendMailer()
{

}
int sendMailer::send(QString email,QString object,QString body){
    QString smtpServer = "smtp.gmail.com";
        quint16 smtpPort = 465;

        // Define the sender and recipient email addresses
        QString fromEmail = "ferjani.eya@esprit.tn";
        QString toEmail = email;

        // Define the email message
        QString message = "From: " + fromEmail + "\n";
        message += "To: " + toEmail + "\n";
        message += "Subject: "+object+" \n\n";
        message += body;
        QSslSocket socket;

        socket.connectToHostEncrypted(smtpServer, smtpPort);

            // Check if the connection is established
            if (!socket.waitForConnected(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the EHLO command
            socket.write("EHLO gmail.com\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the AUTH LOGIN command
            socket.write("AUTH LOGIN\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the Base64-encoded username
            QString username = "ferjani.eya@esprit.tn";
            socket.write(username.toUtf8().toBase64() + "\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the Base64-encoded password
            QString password = "211JFT5569";
            socket.write(password.toUtf8().toBase64() + "\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }
            socket.write("MAIL FROM: " + fromEmail.toUtf8() +"\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
            qWarning() << "Error: " << socket.errorString();
            return 1;
            }
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the RCPT TO command
            socket.write("RCPT TO: " + toEmail.toUtf8() + "\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the DATA command
            socket.write("DATA\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the email message
            socket.write(message.toUtf8() + "\r\n.\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Wait for the server to respond
            if (!socket.waitForReadyRead(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Send the QUIT command
            socket.write("QUIT\r\n");
            if (!socket.waitForBytesWritten(5000))
            {
                qWarning() << "Error: " << socket.errorString();
                return 1;
            }

            // Close the socket
            socket.close();




}
