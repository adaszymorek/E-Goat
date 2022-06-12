#include "user.h"

User::User(QByteArray username, QByteArray checksums)
{
    this->username = username;
    setChecksums(checksums);
}
User::User(QByteArray username)
{
    this->username = username;
}
QByteArray User::getUsername(){
    return username;
}
QStringList User::getChecksums(){
    return checksumList;
}
void User::setChecksums(QByteArray checksums){
   QString checksumStr = QString(checksums);
    checksumList = checksumStr.split(", ", Qt::SkipEmptyParts);
}
