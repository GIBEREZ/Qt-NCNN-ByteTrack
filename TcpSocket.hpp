//
// Created by 绮名桑 on 2024/7/25.
//

#ifndef WIFI_QT_TCPSOCKET_HPP
#define WIFI_QT_TCPSOCKET_HPP


#include <QObject>
#include <QTcpSocket>
#include <iostream>
#include "ui.hpp"
#include "GUI.hpp"

class GUI;

/*
 * Tcp网络连接基类，根据不同用处派生类重写信号虚函数
 */
class TcpClient : public QObject {
    Q_OBJECT
public:
    TcpClient(const QString &host, quint16 port, QObject *parent = nullptr);
    // 发送数据到服务器
    void sendData(const QString &data);
    void sendHexData(const QString &hexData);
    QString host; // 保存主机地址
    quint16 port; // 保存端口号
    QTcpSocket *socket; // 定义 QTcpSocket 对象
public slots:
    virtual void onConnected();
    virtual void onDisconnected();
    virtual void onReadyRead();
    virtual void onErrorOccurred(QAbstractSocket::SocketError socketError);
private:
};

class TcpUI : public TcpClient {
Q_OBJECT
public:
    TcpUI(const QString &host, quint16 port, GUI *gui, QObject *parent = nullptr);
protected slots:
    // 重写基类中的虚函数
    void onConnected() override;
    void onDisconnected() override;
    void onReadyRead() override;
    void onErrorOccurred(QAbstractSocket::SocketError socketError) override;
private:
    GUI *gui;
};


#endif //WIFI_QT_TCPSOCKET_HPP
