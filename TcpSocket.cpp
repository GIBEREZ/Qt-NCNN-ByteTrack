//
// Created by 绮名桑 on 2024/7/25.
//

#include "TcpSocket.hpp"

TcpClient::TcpClient(const QString &host, quint16 port, QObject *parent)
    // 基类构造函数初始化，成员变量初始化
    : QObject(parent), host(host), port(port), socket(new QTcpSocket(this)) {
}

void TcpClient::onConnected() {
    std::cout << "Connected to: " << host.toStdString() << ", port: " << port << std::endl;
    sendData("Hello from Windows!"); // 发送初始消息
}

void TcpClient::onDisconnected() {
    std::cout << "Disconnected from: " << host.toStdString() << std::endl;
}

void TcpClient::onReadyRead() {
    QByteArray data = socket->readAll();
    std::cout << "Received: " << data.toStdString() << std::endl;
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    std::cerr << "Error: " << socket->errorString().toStdString() << std::endl;
}

void TcpClient::sendData(const QString &data) {
    // 检查连接状态
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // 发送数据
        socket->write(data.toUtf8());
        // 刷新缓冲区，确保数据已发送
        socket->flush();
    }
}

void TcpClient::sendHexData(const QString &hexData) {
    // 将QString数据转为Hex  例hexData="48656c6c6f20776f726c64"表示为"Hello world"
    QByteArray byteArray = QByteArray::fromHex(hexData.toUtf8());
    // 检查连接状态
    if (socket->state() == QAbstractSocket::ConnectedState) {
        // 发送数据
        socket->write(byteArray);
        // 刷新缓冲区，确保数据已发送
        socket->flush();
    }
}
