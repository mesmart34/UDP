#include "client.h"

Client::Client(const QString& address, int port)
{
    this->address = QHostAddress(address);
    this->port = port;
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 1111);
    connect(socket, &QUdpSocket::readyRead, this, &Client::readData);
}

Client::~Client()
{
    delete socket;
}

void Client::writeData(QByteArray buffer)
{
    socket->writeDatagram(buffer, address, port);
}

void Client::readData()
{
    QNetworkDatagram datagram = socket->receiveDatagram();
    QByteArray bytes = datagram.data();
    MessageTypes messageType = (MessageTypes)bytes[0];
    switch (messageType) {
        case MessageTypes::WELCOME:
        {
            qDebug() << "You are connected to " << datagram.senderAddress() << ":" << datagram.senderPort();
            m_connectedToServer = true;
        } break;
        case MessageTypes::CLIENT_MESSAGE:
        {
            qDebug() << QString::fromUtf8(bytes);
            emit onMessageRecieve(QString(&bytes.constData()[1]));
        } break;
    }
}

















