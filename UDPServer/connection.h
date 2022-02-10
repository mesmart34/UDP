#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QString>
#include <QHostAddress>

class Connection
{
public:
    Connection() = default;
    Connection(QHostAddress address, int port, QString nickname);

    QString getNickname() const;
    int getPort() const;
    QHostAddress getAddress() const;

private:
    QString m_nickname;
    QHostAddress m_address;
    int m_port;

};

#endif // CONNECTION_H
