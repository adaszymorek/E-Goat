#include <QCoreApplication>
#include "egoattcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // create EGoatTcpServer
    // EGoatTcpServer constructor will create QTcpServer
    EGoatTcpServer server;

    return a.exec();
}
