/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QToolButton *letterDice;
    QLabel *photo;
    QLabel *output;
    QToolButton *numberplate;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1056, 627);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        letterDice = new QToolButton(centralWidget);
        letterDice->setObjectName(QString::fromUtf8("letterDice"));
        letterDice->setGeometry(QRect(40, 30, 221, 22));
        photo = new QLabel(centralWidget);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(40, 130, 981, 431));
        photo->setAlignment(Qt::AlignCenter);
        output = new QLabel(centralWidget);
        output->setObjectName(QString::fromUtf8("output"));
        output->setGeometry(QRect(520, 30, 451, 16));
        output->setAlignment(Qt::AlignCenter);
        numberplate = new QToolButton(centralWidget);
        numberplate->setObjectName(QString::fromUtf8("numberplate"));
        numberplate->setGeometry(QRect(270, 30, 221, 22));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1056, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        letterDice->setText(QApplication::translate("MainWindow", "Letter dice", nullptr));
        photo->setText(QApplication::translate("MainWindow", "photo", nullptr));
        output->setText(QApplication::translate("MainWindow", "output", nullptr));
        numberplate->setText(QApplication::translate("MainWindow", "Numberplate", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
