#include "clientwindow.h"
#include "./ui_clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

}

ClientWindow::~ClientWindow()
{
    delete client;
    delete ui;
}


void ClientWindow::on_btnConnect_clicked()
{
    client = new Client(ui->editAddress->text(), ui->editPort->text().toInt());
    connect(client, &Client::onMessageRecieve, this, &ClientWindow::onMessageRecieveSlot);
    QByteArray buffer;
    buffer.append((char)MessageTypes::HELLO);
    buffer.append(ui->editName->text().toUtf8());
    client->writeData(buffer);
}

void ClientWindow::onMessageRecieveSlot(const QString &message)
{
    ui->editMessages->append(message);
}


void ClientWindow::on_btnSend_clicked()
{
    QByteArray buffer;
    buffer.append((char)MessageTypes::CLIENT_MESSAGE);
    QString message = ui->editMessage->toPlainText();
    buffer.append(message.toUtf8());
    client->writeData(buffer);
}

