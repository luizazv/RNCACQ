/********************************************************************************
** Form generated from reading UI file 'dialogdefinidousuario.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGDEFINIDOUSUARIO_H
#define UI_DIALOGDEFINIDOUSUARIO_H

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

class Ui_DialogDefinidoUsuario
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *DialogDefinidoUsuario)
    {
        if (DialogDefinidoUsuario->objectName().isEmpty())
            DialogDefinidoUsuario->setObjectName(QStringLiteral("DialogDefinidoUsuario"));
        DialogDefinidoUsuario->resize(400, 300);
        DialogDefinidoUsuario->setMinimumSize(QSize(400, 300));
        DialogDefinidoUsuario->setMaximumSize(QSize(400, 300));
        buttonBox = new QDialogButtonBox(DialogDefinidoUsuario);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(DialogDefinidoUsuario);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(80, 100, 211, 20));
        label = new QLabel(DialogDefinidoUsuario);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 70, 121, 16));

        retranslateUi(DialogDefinidoUsuario);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogDefinidoUsuario, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogDefinidoUsuario, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogDefinidoUsuario);
    } // setupUi

    void retranslateUi(QDialog *DialogDefinidoUsuario)
    {
        DialogDefinidoUsuario->setWindowTitle(QApplication::translate("DialogDefinidoUsuario", "Dialog", 0));
        label->setText(QApplication::translate("DialogDefinidoUsuario", "Nome do Ponto Not\303\241vel", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogDefinidoUsuario: public Ui_DialogDefinidoUsuario {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGDEFINIDOUSUARIO_H
