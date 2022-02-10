#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QNetworkDatagram>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "connection.h"
#include "messagetypes.h"
#include <utility>

class Server : public QObject
{
    Q_OBJECT
public:
    Server(const QString& address, int port);
    ~Server();

private:
     void run();
     void processDatagram(QNetworkDatagram datagram);
     inline MessageTypes getMessageType(char data) const;
     void addConnection(QHostAddress address, int port, QByteArray buffer);
     void writeData(QByteArray buffer, const Connection& reciever);
     Connection findConnectionByAddressAndPort(QHostAddress address, int port);
     void broadcastMessage(QByteArray buffer, const QString &exceptionNickname);

     QUdpSocket* socket;
     std::vector<Connection> connections;

private slots:
    void readData();
};

#endif // SERVER_H
