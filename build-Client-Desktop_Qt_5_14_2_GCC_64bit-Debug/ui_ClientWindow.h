/********************************************************************************
** Form generated from reading UI file 'ClientWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTWINDOW_H
#define UI_CLIENTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QAction *actionChange_settings;
    QWidget *centralWidget;
    QComboBox *comboBox;
    QLabel *label;
    QTextEdit *textEdit;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *menuSettings;

    void setupUi(QMainWindow *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(535, 431);
        Client->setMaximumSize(QSize(535, 431));
        QFont font;
        font.setPointSize(9);
        Client->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("main_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Client->setWindowIcon(icon);
        actionChange_settings = new QAction(Client);
        actionChange_settings->setObjectName(QString::fromUtf8("actionChange_settings"));
        actionChange_settings->setCheckable(false);
        centralWidget = new QWidget(Client);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(40, 30, 321, 31));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(400, 40, 100, 100));
        label->setPixmap(QPixmap(QString::fromUtf8("/home/illya/Client/hardware-57-1105855.webp")));
        label->setScaledContents(true);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setEnabled(true);
        textEdit->setGeometry(QRect(40, 90, 321, 271));
        textEdit->setFont(font);
        textEdit->setAutoFillBackground(false);
        textEdit->setReadOnly(true);
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(40, 90, 321, 271));
        Client->setCentralWidget(centralWidget);
        comboBox->raise();
        textEdit->raise();
        tableWidget->raise();
        label->raise();
        menuBar = new QMenuBar(Client);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 535, 20));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        Client->setMenuBar(menuBar);

        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionChange_settings);

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QMainWindow *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        actionChange_settings->setText(QCoreApplication::translate("Client", "Change settings", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Client", "All System Information", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Client", "Hard Disk Information", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Client", "CPU Informatiion", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Client", "RAM Information", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Client", "Network Information", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Client", "Process Information", nullptr));

        label->setText(QString());
        menuSettings->setTitle(QCoreApplication::translate("Client", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTWINDOW_H
