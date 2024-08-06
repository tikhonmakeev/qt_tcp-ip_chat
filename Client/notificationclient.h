#ifndef NOTIFICATIONCLIENT_H
#define NOTIFICATIONCLIENT_H

#include <QObject>
#ifndef __ANDROID__
#include <QSystemTrayIcon>
#endif

class NotificationClient : public QObject
{
    Q_OBJECT
public:
    explicit NotificationClient(QObject *parent = 0);

    void setNotification(QString notification);
    QString notification() const;

signals:
    void notificationChanged();

private slots:
    void updateNotification();

private:
    QString m_notification;
#ifndef __ANDROID__
    QSystemTrayIcon *trayIcon;
#endif
};

#endif // NOTIFICATIONCLIENT_H

