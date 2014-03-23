/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblVideoSource;
    QPushButton *btnCameraStart;
    QLabel *lblError;
    QPushButton *btnCameraStop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(696, 550);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblVideoSource = new QLabel(centralWidget);
        lblVideoSource->setObjectName(QStringLiteral("lblVideoSource"));
        lblVideoSource->setGeometry(QRect(150, 10, 401, 351));
        btnCameraStart = new QPushButton(centralWidget);
        btnCameraStart->setObjectName(QStringLiteral("btnCameraStart"));
        btnCameraStart->setGeometry(QRect(80, 400, 161, 41));
        lblError = new QLabel(centralWidget);
        lblError->setObjectName(QStringLiteral("lblError"));
        lblError->setGeometry(QRect(520, 420, 151, 31));
        btnCameraStop = new QPushButton(centralWidget);
        btnCameraStop->setObjectName(QStringLiteral("btnCameraStop"));
        btnCameraStop->setGeometry(QRect(260, 400, 141, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 696, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        lblVideoSource->setText(QApplication::translate("MainWindow", "Video Source", 0));
        btnCameraStart->setText(QApplication::translate("MainWindow", "Start Camera", 0));
        lblError->setText(QApplication::translate("MainWindow", "Error Box", 0));
        btnCameraStop->setText(QApplication::translate("MainWindow", "Stop Camera", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
