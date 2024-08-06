QT       += core gui
QT += core network
#if defined(Q_OS_ANDROID)
#include <QtAndroid>
#include <QAndroidJniObject>
#endif


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    notificationclient.cpp

HEADERS += \
    Client_resource.rc \
    mainwindow.h \
    notificationclient.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/org/qtproject/tcpClient/NotificationClient.java \
    burning-bear.ico \
    icon.ico \
    icon_white.ico \
    images/happy.png \
    images/sad.png \
    prevHostIp.txt

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

# RC_ICONS = icon.ico
# RC_ICONS = icon_white.ico
RC_ICONS = burning-bear.ico
RC_FILE = Client_resource.rc
