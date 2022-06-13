#ifndef USER_H
#define USER_H

#include <QByteArray>
#include <QStringList>
#include <QHostAddress>
#include <QTcpSocket>
class User
{
public:
    QHostAddress userIP;
    QMap<QString, QByteArray> fileNamesAndChecksums;

    User(QHostAddress userIP);
    User(QHostAddress userIP, QByteArray checksums, QTcpSocket *socket);

    QHostAddress getUserIP();
    QMap<QString, QByteArray> getfileNamesAndChecksums();
    void setChecksums(QByteArray checksums, QTcpSocket *socket);
};

#endif // USER_H
