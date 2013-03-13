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
    QRadioButton *radioButtonChave;
    QRadioButton *radioButtonMarco;
    QGroupBox *groupBox_2;
    QRadioButton *radioButtonCrescente;
    QRadioButton *radioButtonDecrescente;
    QGroupBox *groupBox_3;
    QRadioButton *radioButtonDireita;
    QRadioButton *radioButtonEsquerda;
    QLabel *label;
    QLineEdit *lineEditSb;
    QLabel *label_2;
    QLineEdit *lineEditMarco;

    void setupUi(QDialog *DialogAbrirSB)
    {
        if (DialogAbrirSB->objectName().isEmpty())
            DialogAbrirSB->setObjectName(QStringLiteral("DialogAbrirSB"));
        DialogAbrirSB->resize(400, 300);
        DialogAbrirSB->setMinimumSize(QSize(400, 300));
        DialogAbrirSB->setMaximumSize(QSize(400, 300));
        buttonBox = new QDialogButtonBox(DialogAbrirSB);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(DialogAbrirSB);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 80, 171, 91));
        radioButtonChave = new QRadioButton(groupBox);
        radioButtonChave->setObjectName(QStringLiteral("radioButtonChave"));
        radioButtonChave->setGeometry(QRect(20, 20, 82, 17));
        radioButtonMarco = new QRadioButton(groupBox);
        radioButtonMarco->setObjectName(QStringLiteral("radioButtonMarco"));
        radioButtonMarco->setGeometry(QRect(20, 50, 82, 17));
        groupBox_2 = new QGroupBox(DialogAbrirSB);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(210, 80, 171, 91));
        radioButtonCrescente = new QRadioButton(groupBox_2);
        radioButtonCrescente->setObjectName(QStringLiteral("radioButtonCrescente"));
        radioButtonCrescente->setGeometry(QRect(40, 20, 82, 17));
        radioButtonDecrescente = new QRadioButton(groupBox_2);
        radioButtonDecrescente->setObjectName(QStringLiteral("radioButtonDecrescente"));
        radioButtonDecrescente->setGeometry(QRect(40, 50, 82, 17));
        groupBox_3 = new QGroupBox(DialogAbrirSB);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 180, 171, 91));
        radioButtonDireita = new QRadioButton(groupBox_3);
        radioButtonDireita->setObjectName(QStringLiteral("radioButtonDireita"));
        radioButtonDireita->setGeometry(QRect(20, 20, 82, 17));
        radioButtonEsquerda = new QRadioButton(groupBox_3);
        radioButtonEsquerda->setObjectName(QStringLiteral("radioButtonEsquerda"));
        radioButtonEsquerda->setGeometry(QRect(20, 50, 82, 17));
        label = new QLabel(DialogAbrirSB);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 20, 111, 20));
        lineEditSb = new QLineEdit(DialogAbrirSB);
        lineEditSb->setObjectName(QStringLiteral("lineEditSb"));
        lineEditSb->setGeometry(QRect(170, 20, 113, 20));
        lineEditSb->setFrame(true);
        label_2 = new QLabel(DialogAbrirSB);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 53, 46, 13));
        lineEditMarco = new QLineEdit(DialogAbrirSB);
        lineEditMarco->setObjectName(QStringLiteral("lineEditMarco"));
        lineEditMarco->setGeometry(QRect(170, 50, 113, 20));

        retranslateUi(DialogAbrirSB);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogAbrirSB, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogAbrirSB, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogAbrirSB);
    } // setupUi

    void retranslateUi(QDialog *DialogAbrirSB)
    {
        DialogAbrirSB->setWindowTitle(QApplication::translate("DialogAbrirSB", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("DialogAbrirSB", "Inicio", 0));
        radioButtonChave->setText(QApplication::translate("DialogAbrirSB", "Chave", 0));
        radioButtonMarco->setText(QApplication::translate("DialogAbrirSB", "Marco", 0));
        groupBox_2->setTitle(QApplication::translate("DialogAbrirSB", "Sentido", 0));
        radioButtonCrescente->setText(QApplication::translate("DialogAbrirSB", "Crescente", 0));
        radioButtonDecrescente->setText(QApplication::translate("DialogAbrirSB", "Decrescente", 0));
        groupBox_3->setTitle(QApplication::translate("DialogAbrirSB", "Desvio", 0));
        radioButtonDireita->setText(QApplication::translate("DialogAbrirSB", "Direita", 0));
        radioButtonEsquerda->setText(QApplication::translate("DialogAbrirSB", "Esquerda", 0));
        label->setText(QApplication::translate("DialogAbrirSB", "Nome da SB para abrir", 0));
        lineEditSb->setInputMask(QString());
        label_2->setText(QApplication::translate("DialogAbrirSB", "Marco", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAbrirSB: public Ui_DialogAbrirSB {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGABRIRSB_H
