#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClientWindow; }
QT_END_NAMESPACE

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

public slots:
    void on_btnConnect_clicked();
    void onMessageRecieveSlot(const QString& message);
    void on_btnSend_clicked();

private:
    Ui::ClientWindow *ui;
    Client* client;
};
#endif // CLIENTWINDOW_H
