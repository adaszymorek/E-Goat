#ifndef EGOATTCPSERVER_H
#define EGOATTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "user.h"

class EGoatTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit EGoatTcpServer(QObject *parent = nullptr);

signals:


public slots:
    void newConnection();

private:
    QTcpServer *server;
    QVector<User> usersVector;
};

#endif // EGOATTCPSERVER_H
