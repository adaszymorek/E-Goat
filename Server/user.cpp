#include "user.h"

User::User(QByteArray username, QByteArray checksums)
{
    this->username = username;

}
User::User(QByteArray username)
{
    this->username = username;
}
QByteArray User::getUsername(){
    return username;
}
QVector<std::string> User::getChecksums(){
    return checksumVector;
}
void User::setChecksums(QByteArray checksums){
   std::string checksumStr = checksums.toStdString();


}
std::string User::searchChecksums(){

}
