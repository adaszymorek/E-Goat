#ifndef EGOATTCPSERVER_H
#define EGOATTCPSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>

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
};

#endif // EGOATTCPSERVER_H
