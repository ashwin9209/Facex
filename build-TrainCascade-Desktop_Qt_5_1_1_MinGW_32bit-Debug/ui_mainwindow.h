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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *camInputlbl;
    QLabel *label;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QPushButton *btnCaptureImage;
    QLabel *lblInput;
    QLabel *lblProcessed;
    QPushButton *btnStartCamera;
    QPlainTextEdit *txtBoxError;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(944, 482);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        camInputlbl = new QLabel(centralWidget);
        camInputlbl->setObjectName(QStringLiteral("camInputlbl"));
        camInputlbl->setGeometry(QRect(40, 200, 221, 181));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 50, 81, 16));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(170, 40, 371, 31));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(170, 80, 371, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 90, 61, 16));
        btnCaptureImage = new QPushButton(centralWidget);
        btnCaptureImage->setObjectName(QStringLiteral("btnCaptureImage"));
        btnCaptureImage->setGeometry(QRect(40, 140, 91, 23));
        lblInput = new QLabel(centralWidget);
        lblInput->setObjectName(QStringLiteral("lblInput"));
        lblInput->setGeometry(QRect(20, 190, 331, 211));
        lblInput->setAutoFillBackground(false);
        lblProcessed = new QLabel(centralWidget);
        lblProcessed->setObjectName(QStringLiteral("lblProcessed"));
        lblProcessed->setGeometry(QRect(440, 180, 281, 231));
        btnStartCamera = new QPushButton(centralWidget);
        btnStartCamera->setObjectName(QStringLiteral("btnStartCamera"));
        btnStartCamera->setGeometry(QRect(140, 140, 81, 23));
        txtBoxError = new QPlainTextEdit(centralWidget);
        txtBoxError->setObjectName(QStringLiteral("txtBoxError"));
        txtBoxError->setGeometry(QRect(580, 10, 161, 111));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 944, 21));
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
        camInputlbl->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Haar Face", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#008000;\">C:\\haarcascade_face.xml</span></p></body></html>", 0));
        textEdit_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">C:\\haarcascade_eye.xml</span></p></body></html>", 0));
        label_2->setText(QApplication::translate("MainWindow", "Haar Eye", 0));
        btnCaptureImage->setText(QApplication::translate("MainWindow", "Capture Image", 0));
        lblInput->setText(QApplication::translate("MainWindow", "Input", 0));
        lblProcessed->setText(QApplication::translate("MainWindow", "Processed", 0));
        btnStartCamera->setText(QApplication::translate("MainWindow", "Start Camera", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
