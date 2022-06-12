#ifndef USER_H
#define USER_H

#include <QByteArray>
#include <QStringList>
class User
{
public:
    QByteArray username;
    QStringList checksumList;

    User(QByteArray username);
    User(QByteArray username, QByteArray checksums);

    QByteArray getUsername();
    QStringList getChecksums();
    void setChecksums(QByteArray checksums);
};

#endif // USER_H
