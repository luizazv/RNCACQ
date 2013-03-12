/********************************************************************************
** Form generated from reading UI file 'dialogmarco.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGMARCO_H
#define UI_DIALOGMARCO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogMarco
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditMarco;
    QLabel *label;

    void setupUi(QDialog *DialogMarco)
    {
        if (DialogMarco->objectName().isEmpty())
            DialogMarco->setObjectName(QStringLiteral("DialogMarco"));
        DialogMarco->resize(319, 245);
        DialogMarco->setMinimumSize(QSize(319, 245));
        DialogMarco->setMaximumSize(QSize(319, 245));
        buttonBox = new QDialogButtonBox(DialogMarco);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(80, 180, 201, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEditMarco = new QLineEdit(DialogMarco);
        lineEditMarco->setObjectName(QStringLiteral("lineEditMarco"));
        lineEditMarco->setGeometry(QRect(70, 100, 113, 20));
        label = new QLabel(DialogMarco);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 70, 111, 16));

        retranslateUi(DialogMarco);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogMarco, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogMarco, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogMarco);
    } // setupUi

    void retranslateUi(QDialog *DialogMarco)
    {
        DialogMarco->setWindowTitle(QApplication::translate("DialogMarco", "Dialog", 0));
        lineEditMarco->setInputMask(QApplication::translate("DialogMarco", "99999999", 0));
        label->setText(QApplication::translate("DialogMarco", "Marco Inicial", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogMarco: public Ui_DialogMarco {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGMARCO_H
