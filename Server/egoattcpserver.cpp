#include "egoattcpserver.h"

EGoatTcpServer::EGoatTcpServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    //connect(server, SIGNAL(), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started!";

     out = new QDataStream(&block, QIODevice::WriteOnly);
     cout = new QTextStream(stdout);
}

void EGoatTcpServer::newConnection()
{
    // need to  grab the socket
    QTcpSocket *socket = server->nextPendingConnection();
    User* newUser = new User(socket->peerAddress());


    //ALL OF E GOAT SERVER ACTIONS SHOULD BE IMPLEMENTED HERE
    socketWriteString("Hello client! Write q to exit \n", socket);

    socket->waitForReadyRead();
    coutWrite(socket->readAll());

    coutWrite(QString("Ready to get checksums \n"));

    socket->waitForReadyRead();
    *cout << socket->bytesAvailable();
    while(socket->bytesAvailable())
    {
        *out << socket->readAll();
        newUser->setChecksums(block, socket);
        coutWrite(QString("checksums loaded"));

        socket->waitForReadyRead();
        *out << socket->readAll();
    }
    socket->close();
}
void EGoatTcpServer::coutWrite(QString message)
{
    *cout << message;
    cout->flush();
}
void EGoatTcpServer::coutWrite(QByteArray bytes)
{
    *cout << bytes;
    cout->flush();
}
void EGoatTcpServer::socketWriteString(const char* s, QTcpSocket *socket1)
{
    socket1->write(s);
    socket1->flush();
    socket1->waitForBytesWritten();
}
