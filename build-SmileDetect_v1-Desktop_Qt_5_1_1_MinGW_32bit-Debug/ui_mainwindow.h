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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *lblVideoSource;
    QCheckBox *checkbox_FaceDetect;
    QCheckBox *checkBox_SmileDetect;
    QPlainTextEdit *textBox_intensity;
    QLabel *label;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QProgressBar *progressBar_Smile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(846, 605);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lblVideoSource = new QLabel(centralWidget);
        lblVideoSource->setObjectName(QStringLiteral("lblVideoSource"));
        lblVideoSource->setGeometry(QRect(40, 10, 451, 331));
        checkbox_FaceDetect = new QCheckBox(centralWidget);
        checkbox_FaceDetect->setObjectName(QStringLiteral("checkbox_FaceDetect"));
        checkbox_FaceDetect->setGeometry(QRect(610, 40, 101, 21));
        checkBox_SmileDetect = new QCheckBox(centralWidget);
        checkBox_SmileDetect->setObjectName(QStringLiteral("checkBox_SmileDetect"));
        checkBox_SmileDetect->setGeometry(QRect(610, 80, 101, 17));
        textBox_intensity = new QPlainTextEdit(centralWidget);
        textBox_intensity->setObjectName(QStringLiteral("textBox_intensity"));
        textBox_intensity->setGeometry(QRect(580, 420, 171, 41));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(580, 390, 151, 16));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(60, 490, 180, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        progressBar_Smile = new QProgressBar(widget);
        progressBar_Smile->setObjectName(QStringLiteral("progressBar_Smile"));
        progressBar_Smile->setValue(24);

        horizontalLayout->addWidget(progressBar_Smile);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 846, 21));
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
        checkbox_FaceDetect->setText(QApplication::translate("MainWindow", "Detect Face", 0));
        checkBox_SmileDetect->setText(QApplication::translate("MainWindow", "Detect Smile", 0));
        label->setText(QApplication::translate("MainWindow", "Value of IntensityZeroOne", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
