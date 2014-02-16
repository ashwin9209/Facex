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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
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
    QPushButton *actionStart;
    QPushButton *actionStop;
    QPushButton *actionLoadVideo;
    QLabel *lblVideo;
    QGroupBox *groupBox;
    QCheckBox *checkBox_fullFace;
    QCheckBox *checkBox_eyes;
    QCheckBox *checkBox_mouth;
    QPushButton *btnProcessFrame;
    QLabel *lblProcessFrame;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(766, 482);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        actionStart = new QPushButton(centralWidget);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionStart->setGeometry(QRect(0, 0, 75, 23));
        actionStop = new QPushButton(centralWidget);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionStop->setGeometry(QRect(70, 0, 75, 23));
        actionLoadVideo = new QPushButton(centralWidget);
        actionLoadVideo->setObjectName(QStringLiteral("actionLoadVideo"));
        actionLoadVideo->setGeometry(QRect(140, 0, 75, 23));
        lblVideo = new QLabel(centralWidget);
        lblVideo->setObjectName(QStringLiteral("lblVideo"));
        lblVideo->setGeometry(QRect(40, 50, 341, 321));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(400, 40, 161, 151));
        checkBox_fullFace = new QCheckBox(groupBox);
        checkBox_fullFace->setObjectName(QStringLiteral("checkBox_fullFace"));
        checkBox_fullFace->setGeometry(QRect(20, 40, 91, 21));
        checkBox_eyes = new QCheckBox(groupBox);
        checkBox_eyes->setObjectName(QStringLiteral("checkBox_eyes"));
        checkBox_eyes->setGeometry(QRect(20, 70, 81, 21));
        checkBox_mouth = new QCheckBox(groupBox);
        checkBox_mouth->setObjectName(QStringLiteral("checkBox_mouth"));
        checkBox_mouth->setGeometry(QRect(20, 100, 91, 21));
        btnProcessFrame = new QPushButton(centralWidget);
        btnProcessFrame->setObjectName(QStringLiteral("btnProcessFrame"));
        btnProcessFrame->setGeometry(QRect(210, 0, 91, 23));
        lblProcessFrame = new QLabel(centralWidget);
        lblProcessFrame->setObjectName(QStringLiteral("lblProcessFrame"));
        lblProcessFrame->setGeometry(QRect(410, 220, 231, 171));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 766, 21));
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
        actionStart->setText(QApplication::translate("MainWindow", "Start Camera", 0));
        actionStop->setText(QApplication::translate("MainWindow", "Stop Camera", 0));
        actionLoadVideo->setText(QApplication::translate("MainWindow", "Open File...", 0));
        lblVideo->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Options", 0));
        checkBox_fullFace->setText(QApplication::translate("MainWindow", "Detect Face", 0));
        checkBox_eyes->setText(QApplication::translate("MainWindow", "Detect Eyes", 0));
        checkBox_mouth->setText(QApplication::translate("MainWindow", "Detect Mouth", 0));
        btnProcessFrame->setText(QApplication::translate("MainWindow", "Process Frame", 0));
        lblProcessFrame->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
