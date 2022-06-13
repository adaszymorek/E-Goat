#ifndef EGOATTCPSERVER_H
#define EGOATTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QDir>
#include <QCryptographicHash>
#include <iostream>
#include "user.h"

class EGoatTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit EGoatTcpServer(QObject *parent = nullptr);
    void coutWrite(QString message);
    void coutWrite(QByteArray bytes);
    void socketWriteString(const char* s, QTcpSocket *socket1);


signals:


public slots:
    void newConnection();

private:
    QTcpServer *server;
    QList<User> usersList;
    QByteArray block;
    QDataStream *out;
    QTextStream *cout;
};

#endif // EGOATTCPSERVER_H
