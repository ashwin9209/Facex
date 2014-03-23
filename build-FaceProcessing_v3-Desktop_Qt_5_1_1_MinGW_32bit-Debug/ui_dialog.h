/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *lblDialogUI_GrayScaleImage;
    QLabel *lblDialogUI_HistEquImage;
    QLabel *lblDialogUI_HSV;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(870, 661);
        lblDialogUI_GrayScaleImage = new QLabel(Dialog);
        lblDialogUI_GrayScaleImage->setObjectName(QStringLiteral("lblDialogUI_GrayScaleImage"));
        lblDialogUI_GrayScaleImage->setGeometry(QRect(40, 50, 281, 281));
        lblDialogUI_HistEquImage = new QLabel(Dialog);
        lblDialogUI_HistEquImage->setObjectName(QStringLiteral("lblDialogUI_HistEquImage"));
        lblDialogUI_HistEquImage->setGeometry(QRect(440, 50, 351, 271));
        lblDialogUI_HSV = new QLabel(Dialog);
        lblDialogUI_HSV->setObjectName(QStringLiteral("lblDialogUI_HSV"));
        lblDialogUI_HSV->setGeometry(QRect(40, 370, 331, 251));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        lblDialogUI_GrayScaleImage->setText(QApplication::translate("Dialog", "Processed Image 1 - GrayScale Image", 0));
        lblDialogUI_HistEquImage->setText(QApplication::translate("Dialog", "Processed Image 2 - Histogram Equalization", 0));
        lblDialogUI_HSV->setText(QApplication::translate("Dialog", "Processed Image 3 - HSV Color Model", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
