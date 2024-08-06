#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <string>
#include <iostream>
#include <map>
class server:public QTcpServer{
    Q_OBJECT
public:
    server();
    QTcpSocket *socket;
private:
    QVector <QTcpSocket*> sockets;
    std::map <QString, QString> nicknames;
    QByteArray Data;
    void SendClient(QString str);
    int IsNicknameAvailable(std::map <QString, QString> nicknames, QString possiblenickname);
    QString whatIP_reserved_nicname(std::map <QString, QString> nicknames, QString looking_for_nickname);
    int IsIPInList(std::map <QString, QString> nicknames, QString ip_to_check);

private slots:
    void incomingConnection(qintptr descr);
    void readytoread();
};

#endif // SERVER_H
