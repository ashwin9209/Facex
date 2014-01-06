/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cqtopencvviewergl.h"

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    CQtOpenCVViewerGl *cameraWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_fullFace;
    QCheckBox *checkBox_eyes;
    QCheckBox *checkBox_mouth;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuCamera;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QStringLiteral("CMainWindow"));
        CMainWindow->resize(400, 300);
        actionStart = new QAction(CMainWindow);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionStop = new QAction(CMainWindow);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cameraWidget = new CQtOpenCVViewerGl(centralWidget);
        cameraWidget->setObjectName(QStringLiteral("cameraWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraWidget->sizePolicy().hasHeightForWidth());
        cameraWidget->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cameraWidget, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        checkBox_fullFace = new QCheckBox(groupBox);
        checkBox_fullFace->setObjectName(QStringLiteral("checkBox_fullFace"));

        verticalLayout->addWidget(checkBox_fullFace);

        checkBox_eyes = new QCheckBox(groupBox);
        checkBox_eyes->setObjectName(QStringLiteral("checkBox_eyes"));
        checkBox_eyes->setEnabled(false);

        verticalLayout->addWidget(checkBox_eyes);

        checkBox_mouth = new QCheckBox(groupBox);
        checkBox_mouth->setObjectName(QStringLiteral("checkBox_mouth"));
        checkBox_mouth->setEnabled(false);

        verticalLayout->addWidget(checkBox_mouth);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        CMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        CMainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuCamera->menuAction());
        menuCamera->addAction(actionStart);
        menuCamera->addAction(actionStop);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "CMainWindow", 0));
        actionStart->setText(QApplication::translate("CMainWindow", "Start", 0));
        actionStop->setText(QApplication::translate("CMainWindow", "Stop", 0));
        groupBox->setTitle(QApplication::translate("CMainWindow", "Options", 0));
        checkBox_fullFace->setText(QApplication::translate("CMainWindow", "Detect Full Face", 0));
        checkBox_eyes->setText(QApplication::translate("CMainWindow", "Detect Eyes", 0));
        checkBox_mouth->setText(QApplication::translate("CMainWindow", "Detect Mouth", 0));
        menuCamera->setTitle(QApplication::translate("CMainWindow", "Camera", 0));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
