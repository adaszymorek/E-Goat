#include <QCoreApplication>
#include "egoattcpclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    EGoatTcpClient s;
    s.doConnect();

    return a.exec();
}
