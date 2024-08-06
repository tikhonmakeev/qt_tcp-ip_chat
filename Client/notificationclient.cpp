#include "notificationclient.h"
//В зависимости от платформы подгружаем разные классы
#ifdef __ANDROID__
#include <QtCore/qjniobject.h>
#include <QtCore/qcoreapplication.h>
#else
#include <QSystemTrayIcon>
#endif

NotificationClient::NotificationClient(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(notificationChanged()), this, SLOT(updateNotification()));
    m_notification = "";
// Если не андройд то создаём TrayIcon и наполняем его
#ifndef __ANDROID__
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("burning-bear.ico"));
    trayIcon->show();
#endif
}

void NotificationClient::setNotification(QString notification)
{
    if (m_notification == notification)
        return;

    m_notification = notification;
    emit notificationChanged();
}

QString NotificationClient::notification() const
{
    return m_notification;
}

//Две версии класса показа уведомлений - одну для Android другую для Desktop
#ifdef __ANDROID__
void NotificationClient::updateNotification()
{
    QJniObject javaNotification = QJniObject::fromString(m_notification);
    //Обратите внимание на путь он нам сильно понадобиться далее!
    QJniObject::callStaticMethod<void>("org/qtproject/tcpClient/NotificationClient",
                                              "notify",
                                              "(Ljava/lang/String;)V",
                                              javaNotification.object<jstring>());
}

#else
void NotificationClient::updateNotification()
{
    trayIcon->showMessage(QString("Test"),m_notification,QSystemTrayIcon::Information);
}
#endif
