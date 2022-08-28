#include "socketserver.h"
#include"settingdata.h"
#include<QApplication>

QTcpSocket * socket=new QTcpSocket;

SocketServer::SocketServer(QObject *parent):
    QObject(parent)
{

    socket->connectToHost(QHostAddress(_serverip), _ipport);

    connect(socket, &QTcpSocket::connected, this, &SocketServer::connect_success);
    connect(socket, &QTcpSocket::readyRead, this, &SocketServer::server_reply);
}

void SocketServer::connect_success()
{
    QMessageBox::information(QApplication::activeWindow(), "连接提示", "连接服务器成功");
}

void SocketServer::server_reply()
{
    QByteArray ba = socket->readAll();
    QJsonObject obj = QJsonDocument::fromJson(ba).object();
    QString cmd = obj.value("cmd").toString();
    if (cmd == "register_reply")
    {
    }
    else if (cmd == "login_reply")
    {
    }
}
