#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QNetworkDatagram>
#include "../UDPServer/messagetypes.h"

class Client : public QObject
{
    Q_OBJECT
public:
    Client(const QString& address, int port);
    ~Client();

    void writeData(QByteArray buffer);

private:

    QUdpSocket* socket;
    QHostAddress address;
    int port;
    bool m_connectedToServer;

signals:
    void onMessageRecieve(const QString& message);

private slots:
    void readData();


};

#endif // CLIENT_H
