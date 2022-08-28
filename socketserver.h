#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include<QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

extern QTcpSocket *socket;

class SocketServer:public QObject
{
    Q_OBJECT
public:

    explicit SocketServer(QObject *parent = nullptr);

    void connect_success();
    void server_reply();

};

#endif // SOCKETSERVER_H
