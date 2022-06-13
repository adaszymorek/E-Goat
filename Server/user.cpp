#include "user.h"

User::User(QHostAddress userIP, QByteArray checksums, QTcpSocket *socket)
{
    this->userIP = userIP;
    setChecksums(checksums, socket);
}
User::User(QHostAddress userIP)
{
    this->userIP = userIP;
}
QHostAddress User::getUserIP(){
    return userIP;
}
QMap<QString, QByteArray> User::getfileNamesAndChecksums(){
    return fileNamesAndChecksums;
}
void User::setChecksums(QByteArray checksums, QTcpSocket *socket){
    QDataStream readStream(socket);
    QMap<QString, QByteArray> map;
    readStream >> map;
    fileNamesAndChecksums = map;
}
