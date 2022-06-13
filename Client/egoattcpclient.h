#ifndef EGOATTCPCLIENT_H
#define EGOATTCPCLIENT_H

#include <iostream>
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QVector>
#include <QCryptographicHash>
#include <QFileDialog>

class EGoatTcpClient : public QObject
{
    Q_OBJECT
public:
    QString checksumSelected;
    QString userSelected;
    QByteArray usersWithFile;
    QString m3 = "Write a name of user you want to connect to download file:";


    explicit EGoatTcpClient(QObject *parent = nullptr);
    void doConnect();
    void socketWriteString(QString message, QString s, QTcpSocket *socket1);
    void socketWriteString(const char *s, QTcpSocket *socket1);
    void coutWrite(QString message);
    void coutWrite(QByteArray bytes);
    QByteArray fileChecksum(const QString &fileName);
    QMap<QString, QByteArray> setFilesChecksums(QDir dir);

signals:

public slots:

private:
    QTcpSocket *socket;
    QDir directoryLoaded;
    QMap<QString, QByteArray> fileNamesAndChecksums;
    QByteArray coutBuff = NULL;
    QDataStream *out;
    QTextStream *cin;
    QTextStream *cout;


};

#endif // EGOATTCPCLIENT_H
