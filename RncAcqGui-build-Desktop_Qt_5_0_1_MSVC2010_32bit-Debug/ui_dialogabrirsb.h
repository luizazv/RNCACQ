/********************************************************************************
** Form generated from reading UI file 'dialogabrirsb.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGABRIRSB_H
#define UI_DIALOGABRIRSB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAbrirSB
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QRadioButton *radioButtonChaveDireita;
    QRadioButton *radioButtonMarco;
    QLineEdit *lineEditMarco;
    QRadioButton *radioButtonChaveEsquerda;
    QLabel *label;
    QLineEdit *lineEditSb;

    void setupUi(QDialog *DialogAbrirSB)
    {
        if (DialogAbrirSB->objectName().isEmpty())
            DialogAbrirSB->setObjectName(QStringLiteral("DialogAbrirSB"));
        DialogAbrirSB->resize(400, 270);
        DialogAbrirSB->setMinimumSize(QSize(400, 270));
        DialogAbrirSB->setMaximumSize(QSize(400, 270));
        buttonBox = new QDialogButtonBox(DialogAbrirSB);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(200, 210, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(DialogAbrirSB);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 70, 171, 181));
        radioButtonChaveDireita = new QRadioButton(groupBox);
        radioButtonChaveDireita->setObjectName(QStringLiteral("radioButtonChaveDireita"));
        radioButtonChaveDireita->setGeometry(QRect(20, 30, 121, 17));
        radioButtonMarco = new QRadioButton(groupBox);
        radioButtonMarco->setObjectName(QStringLiteral("radioButtonMarco"));
        radioButtonMarco->setGeometry(QRect(20, 110, 82, 17));
        lineEditMarco = new QLineEdit(groupBox);
        lineEditMarco->setObjectName(QStringLiteral("lineEditMarco"));
        lineEditMarco->setGeometry(QRect(30, 140, 113, 20));
        radioButtonChaveEsquerda = new QRadioButton(groupBox);
        radioButtonChaveEsquerda->setObjectName(QStringLiteral("radioButtonChaveEsquerda"));
        radioButtonChaveEsquerda->setGeometry(QRect(20, 70, 131, 17));
        label = new QLabel(DialogAbrirSB);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 111, 20));
        lineEditSb = new QLineEdit(DialogAbrirSB);
        lineEditSb->setObjectName(QStringLiteral("lineEditSb"));
        lineEditSb->setGeometry(QRect(170, 20, 113, 20));
        lineEditSb->setFrame(true);

        retranslateUi(DialogAbrirSB);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAbrirSB, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAbrirSB, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAbrirSB);
    } // setupUi

    void retranslateUi(QDialog *DialogAbrirSB)
    {
        DialogAbrirSB->setWindowTitle(QApplication::translate("DialogAbrirSB", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DialogAbrirSB", "Inicio", 0));
        radioButtonChaveDireita->setText(QApplication::translate("DialogAbrirSB", "Chave \303\240 Direita", 0));
        radioButtonMarco->setText(QApplication::translate("DialogAbrirSB", "Marco", 0));
        radioButtonChaveEsquerda->setText(QApplication::translate("DialogAbrirSB", "Chave \303\240 Esquerda", 0));
        label->setText(QApplication::translate("DialogAbrirSB", "Nome da SB para abrir", 0));
        lineEditSb->setInputMask(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogAbrirSB: public Ui_DialogAbrirSB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABRIRSB_H
