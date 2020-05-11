/********************************************************************************
** Form generated from reading UI file 'SettingsWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_7;
    QLabel *label_3;
    QLineEdit *lineEdit_3;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(475, 191);
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(200, 140, 93, 28));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 40, 292, 89));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_7 = new QLineEdit(layoutWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        gridLayout->addWidget(lineEdit_7, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(layoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setStyleSheet(QString::fromUtf8("color: rgb(122, 122, 122)"));

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        QWidget::setTabOrder(lineEdit, pushButton);
        QWidget::setTabOrder(pushButton, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, lineEdit_7);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Settings", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog", "Submit", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Set port", nullptr));
        lineEdit->setText(QCoreApplication::translate("Dialog", "8080", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Set IP adress", nullptr));
        lineEdit_7->setInputMask(QString());
        lineEdit_7->setText(QCoreApplication::translate("Dialog", "127.0.0.1", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "Set timecycle(in seconds)", nullptr));
        lineEdit_3->setInputMask(QString());
        lineEdit_3->setText(QCoreApplication::translate("Dialog", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
