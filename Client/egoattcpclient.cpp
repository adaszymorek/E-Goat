#include "egoattcpclient.h"

EGoatTcpClient::EGoatTcpClient(QObject *parent)
    : QObject{parent}
{

}
void EGoatTcpClient::doConnect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 9999);

    if(socket->waitForConnected(5000))
    {
        qDebug() << "Connected!";

        // send
        socket->write("Hello server");
        socket->flush();
        socket->waitForBytesWritten();
        if(socket->waitForReadyRead())
        {
            writeString("Enter your username:", usernameSelected, socket);

            writeString("Files checksums loaded. Write checksum (sha512) of file to get usernames of owners of this file.",
                        checksumSelected, socket);

            socket->waitForReadyRead();
            qDebug() << "Users with this file:";
            usersWithFile = socket->readAll();
            qDebug() << usersWithFile;

            writeString("Write a name of user you want to connect to download file:", userSelected, socket);

        //TODO: connecting with owner and download file

        }
        else qDebug() << "Checksum upload error";

        // close the connection
        socket->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }
}
void writeString(QString message, std::string s, QTcpSocket *socket)
{
    qDebug() << message;
    std::cin >> s;
    socket->write(QByteArray::fromStdString(s));
    socket->flush();
    socket->waitForBytesWritten();
}
