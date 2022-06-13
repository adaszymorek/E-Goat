#include "egoattcpclient.h"


EGoatTcpClient::EGoatTcpClient(QObject *parent)
    : QObject{parent}
{
   out = new QDataStream(&coutBuff, QIODevice::WriteOnly);
   cin = new QTextStream(stdin);
   cout = new QTextStream(stdout);
}
void EGoatTcpClient::doConnect()
{
    socket = new QTcpSocket(this);

    socket->connectToHost("127.0.0.1", 9999);

    if(socket->waitForConnected(5000))
    {
        coutWrite(QString("Connected! \n"));

        // send
        socket->write("Hello server \n");
        socket->flush();
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        if(socket->bytesAvailable())
        {
            *out << socket->readAll();
            coutWrite(coutBuff);
            coutWrite(QString("enter directory path: "));
            QString path;
            *cin >> path;
            QDir directoryLoaded(path);
            setFilesChecksums(directoryLoaded);
            QByteArray preparedQMap = QByteArray(reinterpret_cast<char*>(&fileNamesAndChecksums), sizeof (fileNamesAndChecksums));
            socket->write(preparedQMap);

            socketWriteString(QString("Files checksums loaded. Write name of file to get user IPs of owners of this file.\n"),
                              checksumSelected, socket);

            socket->waitForReadyRead();
            coutWrite(QString("Users with this file:\n"));
            *out << socket->readAll();
            coutWrite(coutBuff);

            socketWriteString(QString("Write a name of user you want to connect to download file:"), userSelected, socket);

        //TODO: connecting with owner and download file

        }
        else
        {
            coutWrite(QString("Checksum upload error"));
        }
        // close the connection
        socket->close();
    }
    else
    {
        coutWrite(QString("Not connected!"));
    }
}
void EGoatTcpClient::coutWrite(QString message)
{
    *cout << message;
    cout->flush();
}
void EGoatTcpClient::coutWrite(QByteArray bytes)
{
    *cout << bytes;
    cout->flush();
}
void EGoatTcpClient::socketWriteString(QString message, QString s, QTcpSocket *socket1)
{
    *cout << message;
    cout->flush();
    *cin >> s;
    socket1->write(s.toUtf8());
    socket1->flush();
    socket1->waitForBytesWritten();
}
void EGoatTcpClient::socketWriteString(const char* s, QTcpSocket *socket1)
{
    socket1->write(s);
    socket1->flush();
    socket1->waitForBytesWritten();
}
QByteArray EGoatTcpClient::fileChecksum(const QString &fileName)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(QCryptographicHash::Sha512);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}
QMap<QString, QByteArray> EGoatTcpClient::setFilesChecksums(QDir dir)
{
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QStringList list = dir.entryList();
    for(int i = 0; i < list.length(); i++)
    {
       fileNamesAndChecksums.insert(list.at(i), fileChecksum(list.at(i)));
    }
    return fileNamesAndChecksums;
}
