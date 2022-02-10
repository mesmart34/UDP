#include <server.h>
#include <QCoreApplication>

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    Server server = Server("127.0.0.1", 4444);
    return a.exec();
}
