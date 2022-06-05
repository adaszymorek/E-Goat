#ifndef USER_H
#define USER_H

#include <QByteArray>
#include <QVector>

class User
{
public:
    QByteArray username;
    QVector<std::string> checksumVector;


    User();
    User(QByteArray username);
    User(QByteArray username, QByteArray checksums);

    QByteArray getUsername();
    QVector<std::string> getChecksums();
    void setChecksums(QByteArray checksums);
    std::string searchChecksums();
};

#endif // USER_H
