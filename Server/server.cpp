#include "server.h"
#include <QDataStream>
#include <iostream>
#include <string>
int server::IsNicknameAvailable(std::map <QString, QString> nicknames, QString possiblenickname){
    for (auto it = nicknames.begin(); it != nicknames.end(); it++){
        if (it->second == possiblenickname){
            qDebug()<<"nickname is in list";
//            socket->disconnect();
            return 0;
        }
    }
    return 1;
}

QString server::whatIP_reserved_nicname(std::map <QString, QString> nicknames, QString looking_for_nickname){
    for (auto it = nicknames.begin(); it != nicknames.end(); it++){
        if (it->second == looking_for_nickname){
            qDebug()<<"nickname is reserved by ip " + it->first;
//            socket->disconnect();
            return it->first;
        }
    }
    return 0;
}

int server::IsIPInList(std::map <QString, QString> nicknames, QString ip_to_check){
    for (auto it = nicknames.begin(); it != nicknames.end(); it++){
        if (it->first == ip_to_check){
            qDebug()<<"IP is already in list";
//            SendClient("IP "+ip+" was used");
            return 1;
        }
    }
    return 0;
}

QString ListToString(std::map <QString, QString> nicknames){
    QString newStr;
    for(auto it = nicknames.begin(); it != nicknames.end(); it++){
        auto curNick = it->second;
        newStr += " " + curNick;
    }
    return newStr;
}
server::server(){
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug() << "start";
    }
    else{
        qDebug() << "error";
    }
}
void server::incomingConnection(qintptr descr){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(descr);
    connect(socket, &QTcpSocket::readyRead, this, &server::readytoread);
//    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug() << "New connection - " << descr;
}
void server::readytoread(){
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    if (in.status() == QDataStream::Ok){
        qDebug()<<"read...";
        QString str;
        in>>str;

        auto string = socket->peerAddress().toString();
//        qDebug()<<string;
        QString ip = QString::fromStdString(string.toStdString().substr(7, string.size() - 1));
        if ("\r" == str.toStdString().substr(0, 1)){

        }
        else if ("\a" == str.toStdString().substr(0, 1)){
            QString possiblenickname = QString::fromStdString(str.toStdString().substr(1, str.size() - 1));

            qDebug()<<"trying NICKNAME"<<possiblenickname;
            if (IsNicknameAvailable(nicknames, possiblenickname)){
                if (IsIPInList(nicknames, ip)){
                    auto ip_pos = nicknames.find(ip);
                    QString prev_nick = ip_pos->second;
                    qDebug()<<"deleting prev nick: " + prev_nick + " from list. New nick  will be: " + possiblenickname;

                    nicknames.erase(ip_pos);
                }
                nicknames.insert(std::make_pair(ip, possiblenickname));
                for (auto it = nicknames.begin(); it != nicknames.end(); it++) {
                    if (it->first == ip && it->second == possiblenickname){

                        qDebug()<<"Succesfull reservation of nickname: " + possiblenickname;
                        SendClient("\vNew nickname " + possiblenickname + " with IP: " + ip + " " + ListToString(nicknames));

                    }
                }
                qDebug()<<"list of reserved nicknames";
                for (auto it = nicknames.begin(); it != nicknames.end(); it++) {
                    qDebug()<< "{" << it->first << ", " << it->second << "}";
                }
            }
            else if (whatIP_reserved_nicname(nicknames, possiblenickname) == ip){
                qDebug()<<"Succesfull returning of nickname: " + possiblenickname + " to user with ip " + ip;
                SendClient("\vReturn nickname " + possiblenickname + " with IP: " + ip + " " + ListToString(nicknames));
            }
            else{
                SendClient("\anick is busy with ip: " + ip + " with nick: " + possiblenickname);

            }


        }
        else{
            SendClient(nicknames[ip]+" "+str);
            qDebug()<<str;
        }
    }
    else{
        qDebug()<<"DataStream error";
    }

}
void server::SendClient(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out<<str;
//    socket->write(Data);
    for (int i = 0; i < sockets.size(); i++){
        sockets[i]->write(Data);
    }
}
