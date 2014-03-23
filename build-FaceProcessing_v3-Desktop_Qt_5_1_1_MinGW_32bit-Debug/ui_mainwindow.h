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
    QLabel *lblVideo;
    QGroupBox *groupBox;
    QCheckBox *checkBox_fullFace;
    QCheckBox *checkBox_eyes;
    QCheckBox *checkBox_mouth;
    QCheckBox *checkBox_performPreProcessing;
    QLabel *lblProcessFaceFrame;
    QLabel *lblProcessEyeFrame;
    QLabel *lblProcessMouthFrame;
    QPushButton *btnSnapshot;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(748, 618);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblVideo = new QLabel(centralWidget);
        lblVideo->setObjectName(QStringLiteral("lblVideo"));
        lblVideo->setGeometry(QRect(40, 50, 341, 321));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(390, 40, 291, 131));
        checkBox_fullFace = new QCheckBox(groupBox);
        checkBox_fullFace->setObjectName(QStringLiteral("checkBox_fullFace"));
        checkBox_fullFace->setGeometry(QRect(20, 40, 91, 21));
        checkBox_eyes = new QCheckBox(groupBox);
        checkBox_eyes->setObjectName(QStringLiteral("checkBox_eyes"));
        checkBox_eyes->setGeometry(QRect(110, 40, 81, 21));
        checkBox_mouth = new QCheckBox(groupBox);
        checkBox_mouth->setObjectName(QStringLiteral("checkBox_mouth"));
        checkBox_mouth->setGeometry(QRect(200, 40, 91, 21));
        checkBox_performPreProcessing = new QCheckBox(groupBox);
        checkBox_performPreProcessing->setObjectName(QStringLiteral("checkBox_performPreProcessing"));
        checkBox_performPreProcessing->setGeometry(QRect(20, 80, 141, 17));
        lblProcessFaceFrame = new QLabel(centralWidget);
        lblProcessFaceFrame->setObjectName(QStringLiteral("lblProcessFaceFrame"));
        lblProcessFaceFrame->setGeometry(QRect(400, 180, 251, 161));
        lblProcessEyeFrame = new QLabel(centralWidget);
        lblProcessEyeFrame->setObjectName(QStringLiteral("lblProcessEyeFrame"));
        lblProcessEyeFrame->setGeometry(QRect(410, 350, 171, 91));
        lblProcessMouthFrame = new QLabel(centralWidget);
        lblProcessMouthFrame->setObjectName(QStringLiteral("lblProcessMouthFrame"));
        lblProcessMouthFrame->setGeometry(QRect(410, 450, 181, 101));
        btnSnapshot = new QPushButton(centralWidget);
        btnSnapshot->setObjectName(QStringLiteral("btnSnapshot"));
        btnSnapshot->setGeometry(QRect(30, 450, 101, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 748, 21));
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
        lblVideo->setText(QApplication::translate("MainWindow", "Source Video Frame", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Options", 0));
        checkBox_fullFace->setText(QApplication::translate("MainWindow", "Detect Face", 0));
        checkBox_eyes->setText(QApplication::translate("MainWindow", "Detect Eyes", 0));
        checkBox_mouth->setText(QApplication::translate("MainWindow", "Detect Mouth", 0));
        checkBox_performPreProcessing->setText(QApplication::translate("MainWindow", "Perform Pre - Processing", 0));
        lblProcessFaceFrame->setText(QApplication::translate("MainWindow", "Face Frame", 0));
        lblProcessEyeFrame->setText(QApplication::translate("MainWindow", "Eye Frame", 0));
        lblProcessMouthFrame->setText(QApplication::translate("MainWindow", "MouthFrame", 0));
        btnSnapshot->setText(QApplication::translate("MainWindow", "Take Snapshot", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
