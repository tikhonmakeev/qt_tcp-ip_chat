#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ReadytoRead();

private slots:
    void on_pushButton_clicked();

    void on_sendBtn_clicked();

    void keyPressEvent(QKeyEvent *e);

    void on_username_editingFinished();

    void on_hostAddress_editingFinished();

    void on_userMsg_editingFinished();

private:
    QTcpSocket *socket;
    QByteArray Data;
    Ui::MainWindow *ui;
    void SendToServer(QString str);
    QString my_nick;
    int connect_to_server();
    void inform_client_lost_con();
};
#endif // MAINWINDOW_H
