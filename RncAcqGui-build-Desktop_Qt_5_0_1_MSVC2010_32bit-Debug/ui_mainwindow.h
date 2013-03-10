/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLineEdit *lineEdit;
    QLabel *label;
    QComboBox *comboBoxSerial;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *ButtonStop;
    QToolButton *ButtonIniciar;
    QToolButton *ButtonPause;
    QToolButton *ButtonRec;
    QLCDNumber *lcdNumber;
    QFrame *frame_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_8;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_9;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_10;
    QLabel *label_3;
    QFrame *frameBase;
    QGroupBox *groupBox;
    QFrame *frame_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_5;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1284, 788);
        MainWindow->setMinimumSize(QSize(1284, 788));
        MainWindow->setMaximumSize(QSize(1284, 788));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(850, 480, 401, 221));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(220, 40, 113, 31));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        lineEdit->setFont(font);
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 20, 61, 16));
        comboBoxSerial = new QComboBox(frame);
        comboBoxSerial->setObjectName(QStringLiteral("comboBoxSerial"));
        comboBoxSerial->setGeometry(QRect(40, 40, 101, 22));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 20, 81, 16));
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 130, 341, 68));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ButtonStop = new QToolButton(layoutWidget);
        ButtonStop->setObjectName(QStringLiteral("ButtonStop"));
        QIcon icon;
        icon.addFile(QStringLiteral("../Imagens/botaoStop.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonStop->setIcon(icon);
        ButtonStop->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonStop);

        ButtonIniciar = new QToolButton(layoutWidget);
        ButtonIniciar->setObjectName(QStringLiteral("ButtonIniciar"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../Imagens/Iniciar.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonIniciar->setIcon(icon1);
        ButtonIniciar->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonIniciar);

        ButtonPause = new QToolButton(layoutWidget);
        ButtonPause->setObjectName(QStringLiteral("ButtonPause"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../Imagens/botaoPause.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonPause->setIcon(icon2);
        ButtonPause->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonPause);

        ButtonRec = new QToolButton(layoutWidget);
        ButtonRec->setObjectName(QStringLiteral("ButtonRec"));
        ButtonRec->setAcceptDrops(false);
        ButtonRec->setLayoutDirection(Qt::LeftToRight);
        ButtonRec->setAutoFillBackground(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral("../Imagens/botaoGravar.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonRec->setIcon(icon3);
        ButtonRec->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonRec);

        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(830, 70, 401, 171));
        lcdNumber->setFrameShape(QFrame::Panel);
        lcdNumber->setFrameShadow(QFrame::Sunken);
        frame_3 = new QFrame(centralWidget);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(240, 610, 541, 91));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        lineEdit_2 = new QLineEdit(frame_3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(430, 60, 91, 20));
        lineEdit_3 = new QLineEdit(frame_3);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(10, 60, 91, 20));
        lineEdit_4 = new QLineEdit(frame_3);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(220, 60, 91, 20));
        layoutWidget1 = new QWidget(frame_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 521, 42));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_8 = new QPushButton(layoutWidget1);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        horizontalLayout->addWidget(pushButton_8);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        horizontalLayout->addItem(verticalSpacer);

        pushButton_9 = new QPushButton(layoutWidget1);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        horizontalLayout->addWidget(pushButton_9);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        horizontalLayout->addItem(verticalSpacer_2);

        pushButton_10 = new QPushButton(layoutWidget1);
        pushButton_10->setObjectName(QStringLiteral("pushButton_10"));

        horizontalLayout->addWidget(pushButton_10);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(840, 40, 111, 16));
        frameBase = new QFrame(centralWidget);
        frameBase->setObjectName(QStringLiteral("frameBase"));
        frameBase->setGeometry(QRect(240, 40, 541, 551));
        frameBase->setFrameShape(QFrame::Panel);
        frameBase->setFrameShadow(QFrame::Sunken);
        frameBase->setMidLineWidth(0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 191, 401));
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 20, 171, 371));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        layoutWidget2 = new QWidget(frame_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 133, 341));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout->addWidget(pushButton_4);

        pushButton_6 = new QPushButton(layoutWidget2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);

        pushButton_7 = new QPushButton(layoutWidget2);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout->addWidget(pushButton_7);

        pushButton_5 = new QPushButton(layoutWidget2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout->addWidget(pushButton_5);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1284, 21));
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
        lineEdit->setInputMask(QApplication::translate("MainWindow", "0000", 0));
        lineEdit->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Marco Inicial", 0));
        comboBoxSerial->clear();
        comboBoxSerial->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Serial 1", 0)
         << QApplication::translate("MainWindow", "Serial 2", 0)
         << QApplication::translate("MainWindow", "Serial 3", 0)
         << QApplication::translate("MainWindow", "Serial 4", 0)
         << QApplication::translate("MainWindow", "Serial 5", 0)
         << QApplication::translate("MainWindow", "Serial 6", 0)
         << QApplication::translate("MainWindow", "Serial 7", 0)
         << QApplication::translate("MainWindow", "Serial 8", 0)
         << QApplication::translate("MainWindow", "Serial 9", 0)
         << QApplication::translate("MainWindow", "Serial 10", 0)
        );
        label_2->setText(QApplication::translate("MainWindow", "Interface Serial", 0));
        ButtonStop->setText(QApplication::translate("MainWindow", "PAUSE", 0));
        ButtonIniciar->setText(QApplication::translate("MainWindow", "PAUSE", 0));
        ButtonPause->setText(QApplication::translate("MainWindow", "PAUSE", 0));
        ButtonRec->setText(QApplication::translate("MainWindow", "GRAVAR", 0));
        pushButton_8->setText(QApplication::translate("MainWindow", "INICIO DE SB", 0));
        pushButton_9->setText(QApplication::translate("MainWindow", "FIM DE SB", 0));
        pushButton_10->setText(QApplication::translate("MainWindow", "MARCO", 0));
        label_3->setText(QApplication::translate("MainWindow", "VELOCIDADE (KM/H)", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Pontos Not\303\241veis (sem edi\303\247\303\243o)", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "PONTE [F1]", 0));
        pushButton_4->setText(QApplication::translate("MainWindow", "TUNEL [F2]", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "PASSAGEM DE NIVEL [F3]", 0));
        pushButton_7->setText(QApplication::translate("MainWindow", "DEFINIDO USUARIO 1", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "DEFINIDO USUARIO 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
