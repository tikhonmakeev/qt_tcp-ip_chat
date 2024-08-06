#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notificationclient.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStyleFactory>
#include <QKeyEvent>
#include <QThread>
#include <QTime>
#include <vector>
#include <fstream>

void MainWindow::setDarkPalette(){
    // Создаём палитру для тёмной темы оформления
    QPalette darkPalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::PlaceholderText, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);


    qApp->setPalette(darkPalette);
}


void MainWindow::setLitePalette(){
    QPalette litePalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    litePalette.setColor(QPalette::Window, QColor(245, 245, 245));
    litePalette.setColor(QPalette::WindowText, Qt::black);
    litePalette.setColor(QPalette::Base, Qt::white);
    litePalette.setColor(QPalette::AlternateBase, Qt::white);
    litePalette.setColor(QPalette::ToolTipBase, Qt::black);
    litePalette.setColor(QPalette::ToolTipText, Qt::black);
    litePalette.setColor(QPalette::Text, Qt::black);
    litePalette.setColor(QPalette::Button, QColor(230, 230, 230));
    litePalette.setColor(QPalette::ButtonText, Qt::black);
    litePalette.setColor(QPalette::BrightText, Qt::red);
    litePalette.setColor(QPalette::Link, Qt::white);
    litePalette.setColor(QPalette::Highlight, Qt::white);
    litePalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(litePalette);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::setDarkPalette(); // Устанавливаем темную тему

    socket = new QTcpSocket(this);

    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            qDebug() <<"My IP"<<address.toString();
    }

    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::ReadytoRead);
    // connect(socket, &QTcpSocket::readyRead, []() {
    //     NotificationClient().setNotification("You've just receieved a message!");
    // });
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::inform_client_lost_con);

    ui->hostAddress->setFocus();
    std::string previousHostIp;
    std::string previousUsername;
    std::ifstream f("./prevHostIp.txt");
    if (f.is_open()){
        std::getline(f, previousHostIp);
        std::getline(f, previousUsername);
        f.close();
    }
    if (previousHostIp != "") ui->hostAddress->setText(QString::fromStdString(previousHostIp));
    if (previousUsername != "") ui->username->setText(QString::fromStdString(previousUsername));
    this->setWindowTitle("Medved Chat");

}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector <QString> ListFromString(QStringList strlist){
    auto it = strlist.begin();
    std::advance(it, 7);
    std::vector <QString> nicksOnServ;
    for(it; it != strlist.end(); it++){
        nicksOnServ.push_back(*it);
    }
    return nicksOnServ;
}

void delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(10);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::inform_client_lost_con(){
    ui->otherMsgs->setText("Connection lost, try to reconnect.");
    ui->otherMsgs->append("Connection lost, try to reconnect.");
}

int MainWindow::connect_to_server(){
    socket->disconnectFromHost();
    socket->connectToHost(ui->hostAddress->text(), 2323);
    SendToServer("\a" + ui->username->text());
//    qDebug()<<"State of connecting to host: " + socket->ConnectedState;
//    qDebug()<<socket->state();
    while (socket->state() == QAbstractSocket::ConnectingState) {
        delay();
    }
    if (socket->state() == QAbstractSocket::ConnectedState){
        return 1;
    }
    else{
        return 0;
    }
}

void MainWindow::SendToServer(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out<<str;
    socket->write(Data);
}

QString make_text_italic(QString string){
    QString italic_start = "<em>";
    QString italic_end = "</em>";
    return italic_start + string + italic_end;
}

QString make_text_bold(QString string){
    QString bold_start = "<b>";
    QString bold_end = "</b>";
    return bold_start + string + bold_end;
}

void MainWindow::ReadytoRead(){
    QDataStream in(socket);
    if (in.status() == QDataStream::Ok){
        QString str;
        in>>str;

        // //! [Отправка уведомления юзеру]
        // NotificationClient().setNotification("You've just recevied a new message!");
        NotificationClient *Notification = new NotificationClient();

        QStringList stringlist = str.split(" ");
        bool isMyMsg;
        QString local_ip;
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
                local_ip = address.toString();
        }

        if ("\a" == str.toStdString().substr(0, 1)){
            QString error_nick = stringlist[8];
            for (int i = 9; i < stringlist.size(); i++){
                error_nick += " " + stringlist[i];
            }
            QString error_ip = stringlist[5];
            qDebug()<<"err_ip"<<error_ip<<"err_nick"<<error_nick;
            qDebug()<<"local_ip to compare"<<local_ip;
            if (error_ip == local_ip){
                QString serviceMsg = QString::fromStdString(str.toStdString().substr(1, str.size() - 1));
                ui->otherMsgs->setText("Your nick \"" + error_nick + "\" is busy, chose another one and connect again");
            }
        }
        else if ("\v" == str.toStdString().substr(0, 1)){
//            for (QString i : stringlist){
//                qDebug()<<"слова уведомления "+i;
//            }
            std::string new_or_returnBack = stringlist[0].toStdString().substr(1, stringlist[0].toStdString().size() - 1);
            QString new_nick = stringlist[2];
            QString new_nick_ip = stringlist[5];
//            for (int i = 0; i <= stringlist.size(); i++){
//                qDebug()<<stringlist[i];
//            }
//            qDebug()<<"new nick: " + new_nick + " new nick ip: " + new_nick_ip;
            if (new_nick_ip == local_ip && new_or_returnBack == "New") {

                ui->otherMsgs->setText("Now your nickname is \"" + new_nick + "\". You're welcome!");
                ui->otherMsgs->append("List of person already here:");
                ui->otherMsgs->append("");
                std::vector <QString> nicksAlreadyOnServ = ListFromString(stringlist);
                for (auto it = nicksAlreadyOnServ.begin(); it != nicksAlreadyOnServ.end(); it++){
                    ui->otherMsgs->append(*it);
                }

                my_nick = new_nick;
                qDebug()<<my_nick;
            }

            else if (new_nick_ip == local_ip && new_or_returnBack == "Return") {
                ui->otherMsgs->setText("\"" + new_nick + "\", welcome back!");
                ui->otherMsgs->append("List of person already here:");
                ui->otherMsgs->append("");
                std::vector <QString> nicksAlreadyOnServ = ListFromString(stringlist);
                for (auto it = nicksAlreadyOnServ.begin(); it != nicksAlreadyOnServ.end(); it++){
                    ui->otherMsgs->append(*it);
                }

                my_nick = new_nick;
                qDebug()<<my_nick;

            }

            if (new_nick_ip != local_ip) ui->otherMsgs->append("Say hello to new person \"" + new_nick + "\"");
        }
        else {
            QTextCursor cursor = ui->otherMsgs->textCursor();
            cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);

            QString italic_start = "<em>";
            QString italic_end = "</em>";
            QString bold_start = "<b>";
            QString bold_end = "</b>";
            //вынести в отдельную функцию применение стилей


            QString sender_nick = stringlist[0];
            QString sended_msg = stringlist[1];

            for (int i = 2; i < stringlist.size(); i++){
                sended_msg += " " + stringlist[i];
            }
            QString tab = ":\t";
            QString string_to_show;

//            qDebug()<<"my nick " + my_nick + " sender nick: " + sender_nick;
            if (sender_nick == my_nick) {
                sender_nick = "You";
                isMyMsg = true;
//                cursor.beginEditBlock();
//                QTextBlockFormat textBlockFormat = cursor.blockFormat();
//                textBlockFormat.setAlignment(Qt::AlignRight);//or another alignment

//                cursor.mergeBlockFormat(textBlockFormat);
                string_to_show = "<font color=\"#a3a3a3\">" + make_text_bold(sender_nick) + tab + make_text_italic(sended_msg) + "</font>";
//                cursor.endEditBlock();
                //а тут цвет почему-то применяется после реконнекта к приветственному сообщению
            }
            else {
                isMyMsg = false;
//                cursor.beginEditBlock();
//                QTextBlockFormat textBlockFormat = cursor.blockFormat();
//                textBlockFormat.setAlignment(Qt::AlignLeft);//or another alignment

//                cursor.mergeBlockFormat(textBlockFormat);

                string_to_show = "<br>" + sender_nick + tab + italic_start + sended_msg + italic_end;
//                cursor.endEditBlock();

//                ui->otherMsgs->append(string_to_show);
            }

            ui->otherMsgs->append("");
            ui->otherMsgs->undo(); //не работает


            // NotificationClient *Notification = new NotificationClient();
            // Notification->setNotification(QString("Hello World!"));

            cursor.insertHtml(string_to_show);
            if (not isMyMsg)Notification->setNotification(sender_nick + ":\t" + sended_msg);
            //Уведомление, если отправитель не сам юзер


            if (isMyMsg) {
                cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
//                qDebug()<<socket->state();
                QTextBlockFormat textBlockFormat = cursor.blockFormat();
                textBlockFormat.setAlignment(Qt::AlignRight);//or another alignment

                cursor.mergeBlockFormat(textBlockFormat);
            }
            else {


                cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);

                QTextBlockFormat textBlockFormat = cursor.blockFormat();
                textBlockFormat.setAlignment(Qt::AlignLeft);//or another alignment

                cursor.mergeBlockFormat(textBlockFormat);

            }
        }
    }
    else{
        ui->otherMsgs->append("error");
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (connect_to_server()){
        qDebug()<<"Succesfully connected";
    }
    else{
        qDebug()<<"Error while connecting to host";
        ui->otherMsgs->setText("Error 521: Server Is Down.");
        ui->otherMsgs->append("Check server or try to reconnect later");
    }
    std::ofstream out;          // поток для записи
    out.open("./prevHostIp.txt", std::ios::trunc);      // файл для записи
    if (out.is_open())
    {
        out.clear();
        out << ui->hostAddress->text().toStdString() << std::endl;
        out << ui->username->text().toStdString() << std::endl;
    }

    out.close();
    ui->userMsg->setFocus();

}

void MainWindow::on_sendBtn_clicked()
{
    SendToServer(ui->userMsg->text());
    ui->userMsg->setText("");
    ui->userMsg->setFocus();

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape) {
        this->close();
    }
}

void MainWindow::on_username_editingFinished()
{
    ui->pushButton->click();
}


void MainWindow::on_hostAddress_editingFinished()
{
    ui->username->setFocus();
}


void MainWindow::on_userMsg_editingFinished()
{
    if (ui->userMsg->text() != "")SendToServer(ui->userMsg->text());
    ui->userMsg->setText("");
    ui->userMsg->setFocus();
}

