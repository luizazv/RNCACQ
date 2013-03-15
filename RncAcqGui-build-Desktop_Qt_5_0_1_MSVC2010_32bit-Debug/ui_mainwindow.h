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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QFrame *frame_8;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *ButtonStop;
    QToolButton *ButtonIniciar;
    QFrame *frame_9;
    QComboBox *comboBoxSerial;
    QLabel *label_2;
    QLabel *label_5;
    QFrame *frameEstadoGps;
    QFrame *line;
    QLabel *labelLed;
    QFrame *frameBase;
    QGroupBox *groupBox;
    QFrame *frame_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonInicioSb;
    QPushButton *pushButtonFimSb;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButtonTunel;
    QPushButton *pushButtonTunel_2;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButtonPonte;
    QPushButton *pushButtonPonte_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButtonPN;
    QSpacerItem *verticalSpacer_6;
    QPushButton *pushButtonMarco;
    QSpacerItem *verticalSpacer_7;
    QPushButton *pushButtonUsuario;
    QLabel *labelProximoMarco;
    QLabel *label_6;
    QLabel *labelMarcoAtual;
    QLabel *label;
    QLabel *labelDistanciaProximoMarco;
    QLabel *label_9;
    QToolButton *toolButtonProximoMarco;
    QLabel *label_7;
    QToolButton *toolButtonMarcoAtual;
    QFrame *frame_5;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QFrame *frame_7;
    QFrame *frame_4;
    QWidget *widget_3;
    QFrame *frame_6;
    QWidget *widget_4;
    QSlider *horizontalSliderHdop;
    QLabel *label_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 680);
        MainWindow->setMinimumSize(QSize(1024, 680));
        MainWindow->setMaximumSize(QSize(1024, 680));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(680, 400, 331, 211));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        frame_8 = new QFrame(frame);
        frame_8->setObjectName(QStringLiteral("frame_8"));
        frame_8->setGeometry(QRect(10, 110, 311, 91));
        frame_8->setFrameShape(QFrame::Panel);
        frame_8->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(frame_8);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 291, 68));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ButtonStop = new QToolButton(layoutWidget);
        ButtonStop->setObjectName(QStringLiteral("ButtonStop"));
        ButtonStop->setEnabled(false);
        QIcon icon;
        icon.addFile(QStringLiteral("../Imagens/botaoStop.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonStop->setIcon(icon);
        ButtonStop->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonStop);

        ButtonIniciar = new QToolButton(layoutWidget);
        ButtonIniciar->setObjectName(QStringLiteral("ButtonIniciar"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../Imagens/botaoGravar.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        ButtonIniciar->setIcon(icon1);
        ButtonIniciar->setIconSize(QSize(60, 60));

        horizontalLayout_2->addWidget(ButtonIniciar);

        frame_9 = new QFrame(frame);
        frame_9->setObjectName(QStringLiteral("frame_9"));
        frame_9->setGeometry(QRect(10, 10, 311, 91));
        frame_9->setFrameShape(QFrame::Panel);
        frame_9->setFrameShadow(QFrame::Sunken);
        comboBoxSerial = new QComboBox(frame_9);
        comboBoxSerial->setObjectName(QStringLiteral("comboBoxSerial"));
        comboBoxSerial->setGeometry(QRect(20, 50, 101, 22));
        label_2 = new QLabel(frame_9);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 20, 81, 16));
        label_5 = new QLabel(frame_9);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(160, 20, 71, 16));
        frameEstadoGps = new QFrame(frame_9);
        frameEstadoGps->setObjectName(QStringLiteral("frameEstadoGps"));
        frameEstadoGps->setGeometry(QRect(250, 10, 41, 31));
        frameEstadoGps->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        frameEstadoGps->setFrameShape(QFrame::Panel);
        frameEstadoGps->setFrameShadow(QFrame::Plain);
        frameEstadoGps->setLineWidth(3);
        line = new QFrame(frame_9);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(130, 10, 20, 51));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        labelLed = new QLabel(frame_9);
        labelLed->setObjectName(QStringLiteral("labelLed"));
        labelLed->setGeometry(QRect(190, 50, 101, 20));
        labelLed->setFrameShape(QFrame::WinPanel);
        labelLed->setFrameShadow(QFrame::Raised);
        labelLed->setTextFormat(Qt::PlainText);
        labelLed->setPixmap(QPixmap(QString::fromUtf8("../Imagens/led1.bmp")));
        labelLed->setScaledContents(true);
        frameBase = new QFrame(centralWidget);
        frameBase->setObjectName(QStringLiteral("frameBase"));
        frameBase->setGeometry(QRect(180, 20, 491, 591));
        frameBase->setFrameShape(QFrame::Panel);
        frameBase->setFrameShadow(QFrame::Sunken);
        frameBase->setMidLineWidth(15);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 161, 601));
        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 20, 141, 571));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        layoutWidget1 = new QWidget(frame_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 121, 381));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonInicioSb = new QPushButton(layoutWidget1);
        pushButtonInicioSb->setObjectName(QStringLiteral("pushButtonInicioSb"));

        verticalLayout->addWidget(pushButtonInicioSb);

        pushButtonFimSb = new QPushButton(layoutWidget1);
        pushButtonFimSb->setObjectName(QStringLiteral("pushButtonFimSb"));

        verticalLayout->addWidget(pushButtonFimSb);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        pushButtonTunel = new QPushButton(layoutWidget1);
        pushButtonTunel->setObjectName(QStringLiteral("pushButtonTunel"));

        verticalLayout->addWidget(pushButtonTunel);

        pushButtonTunel_2 = new QPushButton(layoutWidget1);
        pushButtonTunel_2->setObjectName(QStringLiteral("pushButtonTunel_2"));

        verticalLayout->addWidget(pushButtonTunel_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        pushButtonPonte = new QPushButton(layoutWidget1);
        pushButtonPonte->setObjectName(QStringLiteral("pushButtonPonte"));
        pushButtonPonte->setCheckable(false);
        pushButtonPonte->setChecked(false);

        verticalLayout->addWidget(pushButtonPonte);

        pushButtonPonte_2 = new QPushButton(layoutWidget1);
        pushButtonPonte_2->setObjectName(QStringLiteral("pushButtonPonte_2"));
        pushButtonPonte_2->setCheckable(false);
        pushButtonPonte_2->setChecked(false);

        verticalLayout->addWidget(pushButtonPonte_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButtonPN = new QPushButton(layoutWidget1);
        pushButtonPN->setObjectName(QStringLiteral("pushButtonPN"));

        verticalLayout->addWidget(pushButtonPN);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        pushButtonMarco = new QPushButton(layoutWidget1);
        pushButtonMarco->setObjectName(QStringLiteral("pushButtonMarco"));

        verticalLayout->addWidget(pushButtonMarco);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        pushButtonUsuario = new QPushButton(layoutWidget1);
        pushButtonUsuario->setObjectName(QStringLiteral("pushButtonUsuario"));

        verticalLayout->addWidget(pushButtonUsuario);

        labelProximoMarco = new QLabel(frame_2);
        labelProximoMarco->setObjectName(QStringLiteral("labelProximoMarco"));
        labelProximoMarco->setGeometry(QRect(10, 470, 91, 21));
        labelProximoMarco->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelProximoMarco->setFrameShape(QFrame::Panel);
        labelProximoMarco->setFrameShadow(QFrame::Plain);
        labelProximoMarco->setLineWidth(1);
        label_6 = new QLabel(frame_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 450, 81, 16));
        labelMarcoAtual = new QLabel(frame_2);
        labelMarcoAtual->setObjectName(QStringLiteral("labelMarcoAtual"));
        labelMarcoAtual->setGeometry(QRect(10, 420, 91, 21));
        labelMarcoAtual->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelMarcoAtual->setFrameShape(QFrame::Panel);
        labelMarcoAtual->setFrameShadow(QFrame::Plain);
        labelMarcoAtual->setLineWidth(1);
        label = new QLabel(frame_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 400, 61, 16));
        labelDistanciaProximoMarco = new QLabel(frame_2);
        labelDistanciaProximoMarco->setObjectName(QStringLiteral("labelDistanciaProximoMarco"));
        labelDistanciaProximoMarco->setGeometry(QRect(10, 540, 91, 21));
        labelDistanciaProximoMarco->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        labelDistanciaProximoMarco->setFrameShape(QFrame::Panel);
        labelDistanciaProximoMarco->setFrameShadow(QFrame::Plain);
        labelDistanciaProximoMarco->setLineWidth(1);
        label_9 = new QLabel(frame_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 500, 151, 16));
        toolButtonProximoMarco = new QToolButton(frame_2);
        toolButtonProximoMarco->setObjectName(QStringLiteral("toolButtonProximoMarco"));
        toolButtonProximoMarco->setGeometry(QRect(102, 471, 25, 19));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 520, 71, 16));
        toolButtonMarcoAtual = new QToolButton(frame_2);
        toolButtonMarcoAtual->setObjectName(QStringLiteral("toolButtonMarcoAtual"));
        toolButtonMarcoAtual->setGeometry(QRect(102, 420, 25, 19));
        frame_5 = new QFrame(centralWidget);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(680, 20, 331, 191));
        frame_5->setFrameShape(QFrame::Panel);
        frame_5->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_5);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 111, 16));
        lcdNumber = new QLCDNumber(frame_5);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(10, 40, 311, 141));
        lcdNumber->setFrameShape(QFrame::Panel);
        lcdNumber->setFrameShadow(QFrame::Sunken);
        frame_7 = new QFrame(centralWidget);
        frame_7->setObjectName(QStringLiteral("frame_7"));
        frame_7->setGeometry(QRect(680, 220, 331, 171));
        frame_7->setFrameShape(QFrame::Panel);
        frame_7->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(frame_7);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(10, 40, 311, 121));
        frame_4->setLayoutDirection(Qt::LeftToRight);
        frame_4->setAutoFillBackground(true);
        frame_4->setFrameShape(QFrame::Panel);
        frame_4->setFrameShadow(QFrame::Sunken);
        widget_3 = new QWidget(frame_4);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(150, 20, 81, 71));
        widget_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
        frame_6 = new QFrame(frame_4);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setGeometry(QRect(230, 20, 71, 71));
        frame_6->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 0);"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        widget_4 = new QWidget(frame_4);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(10, 20, 141, 71));
        widget_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 0);"));
        horizontalSliderHdop = new QSlider(frame_4);
        horizontalSliderHdop->setObjectName(QStringLiteral("horizontalSliderHdop"));
        horizontalSliderHdop->setEnabled(false);
        horizontalSliderHdop->setGeometry(QRect(10, 20, 291, 71));
        horizontalSliderHdop->setMinimum(0);
        horizontalSliderHdop->setValue(0);
        horizontalSliderHdop->setSliderPosition(0);
        horizontalSliderHdop->setTracking(true);
        horizontalSliderHdop->setOrientation(Qt::Horizontal);
        horizontalSliderHdop->setInvertedAppearance(false);
        horizontalSliderHdop->setInvertedControls(false);
        horizontalSliderHdop->setTickPosition(QSlider::TicksBothSides);
        horizontalSliderHdop->setTickInterval(5);
        label_4 = new QLabel(frame_7);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 20, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
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
        ButtonStop->setText(QApplication::translate("MainWindow", "PAUSE", 0));
        ButtonIniciar->setText(QApplication::translate("MainWindow", "PAUSE", 0));
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
        label_5->setText(QApplication::translate("MainWindow", "Estado do GPS", 0));
        labelLed->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Pontos Not\303\241veis", 0));
        pushButtonInicioSb->setText(QApplication::translate("MainWindow", "INICIO DE SB", 0));
        pushButtonFimSb->setText(QApplication::translate("MainWindow", "FIM DE SB", 0));
        pushButtonTunel->setText(QApplication::translate("MainWindow", "INICIO DE TUNEL", 0));
        pushButtonTunel_2->setText(QApplication::translate("MainWindow", "FIM DE TUNEL", 0));
        pushButtonPonte->setText(QApplication::translate("MainWindow", "INICIO DE PONTE", 0));
        pushButtonPonte_2->setText(QApplication::translate("MainWindow", "FIM DE PONTE", 0));
        pushButtonPN->setText(QApplication::translate("MainWindow", "PASSAGEM DE NIVEL", 0));
        pushButtonMarco->setText(QApplication::translate("MainWindow", "MARCO", 0));
        pushButtonUsuario->setText(QApplication::translate("MainWindow", "USU\303\201RIO", 0));
        labelProximoMarco->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Pr\303\263ximo Marco", 0));
        labelMarcoAtual->setText(QString());
        label->setText(QApplication::translate("MainWindow", "Marco Atual", 0));
        labelDistanciaProximoMarco->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Dist\303\242ncia para Pr\303\263ximo", 0));
        toolButtonProximoMarco->setText(QApplication::translate("MainWindow", "...", 0));
        label_7->setText(QApplication::translate("MainWindow", "Marco (m)", 0));
        toolButtonMarcoAtual->setText(QApplication::translate("MainWindow", "...", 0));
        label_3->setText(QApplication::translate("MainWindow", "VELOCIDADE (KM/H)", 0));
        label_4->setText(QApplication::translate("MainWindow", "HDOP", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
