/********************************************************************************
** Form generated from reading UI file 'dialogfecharsb.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGFECHARSB_H
#define UI_DIALOGFECHARSB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_DialogFecharSB
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QRadioButton *radioButtonSim;
    QRadioButton *radioButtonNao;

    void setupUi(QDialog *DialogFecharSB)
    {
        if (DialogFecharSB->objectName().isEmpty())
            DialogFecharSB->setObjectName(QStringLiteral("DialogFecharSB"));
        DialogFecharSB->resize(366, 280);
        DialogFecharSB->setMinimumSize(QSize(366, 280));
        DialogFecharSB->setMaximumSize(QSize(366, 280));
        buttonBox = new QDialogButtonBox(DialogFecharSB);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 230, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(DialogFecharSB);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(70, 30, 151, 16));
        comboBox = new QComboBox(DialogFecharSB);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(70, 60, 121, 22));
        groupBox = new QGroupBox(DialogFecharSB);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 110, 271, 91));
        radioButtonSim = new QRadioButton(groupBox);
        radioButtonSim->setObjectName(QStringLiteral("radioButtonSim"));
        radioButtonSim->setGeometry(QRect(70, 20, 82, 17));
        radioButtonNao = new QRadioButton(groupBox);
        radioButtonNao->setObjectName(QStringLiteral("radioButtonNao"));
        radioButtonNao->setGeometry(QRect(70, 60, 82, 17));

        retranslateUi(DialogFecharSB);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogFecharSB, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogFecharSB, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogFecharSB);
    } // setupUi

    void retranslateUi(QDialog *DialogFecharSB)
    {
        DialogFecharSB->setWindowTitle(QApplication::translate("DialogFecharSB", "Dialog", 0));
        label->setText(QApplication::translate("DialogFecharSB", "Nome da SB sendo fechada", 0));
        groupBox->setTitle(QApplication::translate("DialogFecharSB", "Chave \303\240 Frente?", 0));
        radioButtonSim->setText(QApplication::translate("DialogFecharSB", "Sim", 0));
        radioButtonNao->setText(QApplication::translate("DialogFecharSB", "N\303\243o", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogFecharSB: public Ui_DialogFecharSB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGFECHARSB_H
