#include "server.h"

Server::Server(const QString &address, int port)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::Any, 9999);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

Server::~Server()
{
    delete socket;
}

void Server::run()
{
    qDebug() << "Started";
    while(true)
    {

    }
    qDebug() << "Ended";
}

void Server::processDatagram(QNetworkDatagram datagram)
{
    QByteArray buffer = datagram.data();
    QHostAddress address = datagram.senderAddress();
    int port = datagram.senderPort();

    switch(getMessageType(buffer[0]))
    {
    case MessageTypes::HELLO:
    {
        addConnection(address, port, buffer);
    } break;
    case MessageTypes::CLIENT_MESSAGE:
    {
        Connection connection = findConnectionByAddressAndPort(address, port);
        QString message = QString(&buffer.constData()[1]);
        buffer.clear();
        buffer.append((char)MessageTypes::CLIENT_MESSAGE);
        buffer.append(connection.getNickname().toUtf8() + ": ");
        buffer.append(message.toUtf8());
        qDebug() << message;
        broadcastMessage(buffer, {  });
    } break;
    };
}

MessageTypes Server::getMessageType(char data) const
{
    return (MessageTypes)data;
}

void Server::addConnection(QHostAddress address, int port, QByteArray buffer)
{
    QString nickname = QString(&buffer.constData()[1]);
    if(nickname.size() == 0)
        qDebug() << nickname << "couldn't be added";
    else
    {
        Connection connection(address, port, nickname);
        connections.push_back(connection);
        qDebug() << nickname << "is added";
        QByteArray buffer;
        buffer.append(nickname.toUtf8());
        buffer.append(" is connected");
        QByteArray connectionWelcomeMessage;
        connectionWelcomeMessage.append((char)MessageTypes::WELCOME);
        for(auto it = connections.begin(); it != connections.end(); it++)
        {
            if(it->getNickname() == nickname)
                writeData(connectionWelcomeMessage, connection);
            else
                writeData(buffer, connection);
        }

    }
}

void Server::writeData(QByteArray buffer, const Connection& reciever)
{
    socket->writeDatagram(buffer, reciever.getAddress(), reciever.getPort());
}

Connection Server::findConnectionByAddressAndPort(QHostAddress address, int port)
{
    for(Connection connection : connections)
    {
        if(connection.getAddress() == address && connection.getPort() == port)
            return connection;
    }
}

void Server::broadcastMessage(QByteArray buffer, const QString &exceptionNickname)
{
    for(auto it = connections.begin(); it != connections.end(); it++)
    {

        writeData(buffer, *it);
    }
}

void Server::readData()
{
    while(socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        processDatagram(datagram);
    }
}






































