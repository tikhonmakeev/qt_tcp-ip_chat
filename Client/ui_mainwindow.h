/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *hostAddress;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLineEdit *username;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *otherMsgs;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QLineEdit *userMsg;
    QPushButton *sendBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(441, 453);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        hostAddress = new QLineEdit(centralwidget);
        hostAddress->setObjectName("hostAddress");
        hostAddress->setClearButtonEnabled(true);

        verticalLayout_2->addWidget(hostAddress);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(150, 0));
        pushButton->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(pushButton);

        username = new QLineEdit(centralwidget);
        username->setObjectName("username");
        username->setClearButtonEnabled(true);

        horizontalLayout->addWidget(username);


        verticalLayout_3->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        otherMsgs = new QTextBrowser(centralwidget);
        otherMsgs->setObjectName("otherMsgs");

        verticalLayout_4->addWidget(otherMsgs);


        gridLayout->addLayout(verticalLayout_4, 2, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        userMsg = new QLineEdit(centralwidget);
        userMsg->setObjectName("userMsg");
        userMsg->setClearButtonEnabled(true);

        gridLayout_3->addWidget(userMsg, 0, 0, 1, 1);

        sendBtn = new QPushButton(centralwidget);
        sendBtn->setObjectName("sendBtn");
        QIcon icon;
        icon.addFile(QString::fromUtf8("../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/sendMsg.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8("../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/sendedMsg.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QString::fromUtf8("../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/sendMsg.png"), QSize(), QIcon::Active, QIcon::On);
        icon.addFile(QString::fromUtf8("../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/sendMsg.png"), QSize(), QIcon::Selected, QIcon::Off);
        sendBtn->setIcon(icon);

        gridLayout_3->addWidget(sendBtn, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 441, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        hostAddress->setText(QString());
        hostAddress->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter your server IP address", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Connect as...", nullptr));
        username->setInputMask(QString());
        username->setText(QString());
        username->setPlaceholderText(QCoreApplication::translate("MainWindow", "your nickname(eng only)", nullptr));
        sendBtn->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
