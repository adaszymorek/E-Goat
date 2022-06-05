#ifndef EGOATTCPCLIENT_H
#define EGOATTCPCLIENT_H

#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QVector>

class EGoatTcpClient : public QObject
{
    Q_OBJECT
public:
    std::string checksumSelected;
    std::string userSelected;
    std::string usernameSelected;
    QByteArray usersWithFile;

    explicit EGoatTcpClient(QObject *parent = nullptr);
    void doConnect();
    void writeString(QString message, std::string s, QTcpSocket *socket);

signals:

public slots:

private:
    QTcpSocket *socket;
    QDir directoryLoaded;
    QVector<std::string> checksumVector;


};

#endif // EGOATTCPCLIENT_H
