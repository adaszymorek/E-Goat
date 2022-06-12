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
    User* newUser = new User(NULL);

    //ALL OF E GOAT SERVER ACTIONS SHOULD BE IMPLEMENTED HERE
    socketWriteString("Hello client! Select your name. Write q to exit \n", socket);

    socket->waitForReadyRead();
    coutWrite(socket->readAll());

    coutWrite(QString("Ready to get username \n"));

    socket->waitForReadyRead();
    while(socket->bytesAvailable())
    {
        coutWrite(QString("user created: "));
        *out << socket->readAll();
        newUser = new User(block);
        coutWrite(newUser->username);

        coutWrite(QString("\nReady to get checksums"));
        socket->waitForReadyRead();
        *out << socket->readAll();
        newUser->setChecksums(block);

        socketWriteString("\nsome users", socket);
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
std::string EGoatTcpServer::sum()
{
    int liczba = hashLength(QCryptographicHash::Sha3_512);
    std::string suma = std::to_string(liczba);
    return suma;
}
QFileInfoList EGoatTcpServer::getFilesChecksums()
{
    QDir("D:/qt prace");
    QDir dir;
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    QFileInfoList listsuma = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        listsuma.at(i) = sum();
    }
    return list;
    return listsuma;
}
