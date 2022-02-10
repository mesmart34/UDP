#include "connection.h"

Connection::Connection(QHostAddress address, int port, QString nickname)
    : m_address(address), m_port(port), m_nickname(nickname)
{

}

QString Connection::getNickname() const
{
    return m_nickname;
}

int Connection::getPort() const
{
    return m_port;
}

QHostAddress Connection::getAddress() const
{
    return m_address;
}
