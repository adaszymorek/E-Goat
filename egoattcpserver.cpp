#include "egoattcpserver.h"

EGoatTcpServer::EGoatTcpServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 9999))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started!";
}

void EGoatTcpServer::newConnection()
{
    // need to grab the socket
    QTcpSocket *socket = server->nextPendingConnection();

    //ALL OF E GOAT SERVER ACTIONS SHOULD BE IMPLEMENTED HERE
    socket->write("Hello client \r\n");
    socket->flush();

    socket->waitForBytesWritten();
    socket->waitForReadyRead(3000);

    qDebug() << "Reading: " << socket->bytesAvailable();

    // get the data
    qDebug() << socket->readAll();

    socket->close();
}
