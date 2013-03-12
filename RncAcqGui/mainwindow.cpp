#include "mainwindow.h"
#include "dialogmarco.h"
#include <QtGui\QPainter>
#include <string>
#include <QtWidgets\QMessageBox>

#include "c:/dados/projetos daiken/rncacq/rncacq/MVP.h"
#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"


class FrameNav : public QFrame
{
public:
    FrameNav(QWidget *t) : QFrame(t)
    {
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        //First Circle:
        //width&height:150px
        //Beginning(x/y):50px/30px
        //Each step for Angle parameter is 1/16th of a Degree
        //so multiply Angle Value with 16
        painter.drawArc(5,5,150,150,0,16*360);
        painter.drawRect(0, 0, 10, 10);
    }


};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    FrameNav *frameNav = new FrameNav(frameBase);
    frameNav->setGeometry(50, 50, 100, 100);
    frameNav->setFrameShape(QFrame::NoFrame);
    frameNav->setFrameShadow(QFrame::Sunken);

}

void MainWindow::on_ButtonRec_clicked()
{
    DialogMarco d;

    if(d.exec() == 1)
    {
        labelMarcoInicial->setText(d.GetMarco());
        //valor aceito
        ButtonStop->setEnabled(true);
        ButtonRec->setEnabled(false);
        ButtonPause->setEnabled(true);
        ButtonIniciar->setEnabled(false);
        mpresenter->IniciarCaptura();
    }
    else
    {
        QMessageBox::information(NULL, "Erro", "Faltou Entrar com Marco Inicial");
    }
}

void MainWindow::SentencaOk()
{
    //recebimento ok->liga o verde
	if(mestadoGps != ESTADO_VERDE)
	{
        frameEstadoGps->setStyleSheet("background-color:green");
		mestadoGps = ESTADO_VERDE;
	}

	if(ButtonStop->isEnabled() == false ||
		ButtonRec->isEnabled() == false ||
		ButtonPause->isEnabled() == false ||
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(true);
		ButtonRec->setEnabled(true);
		ButtonPause->setEnabled(true);
		ButtonIniciar->setEnabled(false);
	}
}

void MainWindow::ErroGpsSentencaInvalida()
{
    //recebeu sentenca mas de algum modo invalida->icone amarelo
	if(mestadoGps != ESTADO_AMARELO)
	{
        frameEstadoGps->setStyleSheet("background-color:yellow");
		mestadoGps = ESTADO_AMARELO;
	}

    if(ButtonStop->isEnabled() == false ||
		ButtonRec->isEnabled() == true ||
		ButtonPause->isEnabled() == true ||
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(true);
		ButtonRec->setEnabled(false);
		ButtonPause->setEnabled(false);
		ButtonIniciar->setEnabled(false);
	}
}

void MainWindow::ErroGpsFalhaSentenca()
{
    //sentenca não recebida->icone vermelho
	if(mestadoGps != ESTADO_VERMELHO)
	{
        frameEstadoGps->setStyleSheet("background-color:red");
		mestadoGps = ESTADO_VERMELHO;
	}

	if(ButtonStop->isEnabled() == true ||
		ButtonRec->isEnabled() == true ||
		ButtonPause->isEnabled() == true ||
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(false);
		ButtonRec->setEnabled(false);
		ButtonPause->setEnabled(false);
		ButtonIniciar->setEnabled(false);
	}
}

void MainWindow::ErroGps()
{
    //falha geral->thread GPS terminada, ativar botão para reiniciar
    if(mestadoGps != ESTADO_VERMELHO)
	{
        frameEstadoGps->setStyleSheet("background-color:red");
		mestadoGps = ESTADO_VERMELHO;
	}

	if(ButtonStop->isEnabled() == true ||
		ButtonRec->isEnabled() == true ||
		ButtonPause->isEnabled() == true ||
        ButtonIniciar->isEnabled() == false)
	{
		ButtonStop->setEnabled(false);
		ButtonRec->setEnabled(false);
		ButtonPause->setEnabled(false);
		ButtonIniciar->setEnabled(true);
	}
}

void MainWindow::SetHdop(int valor)
{
	horizontalSliderHdop->setValue(valor);
}

void MainWindow::SendMsg(const char *msg)
{
//	labelSentenca->setText(msg);
}


void MainWindow::on_ButtonIniciar_clicked()
{
    //inicia thread GPS
    ButtonStop->setEnabled(false);
    ButtonRec->setEnabled(false);
    ButtonPause->setEnabled(false);
    ButtonIniciar->setEnabled(false);

    string strSerial = comboBoxSerial->currentText().toLocal8Bit();

    mpresenter->IniciaGps(strSerial);
}

void MainWindow::on_ButtonStop_clicked()
{
    //termina captura
    mpresenter->TerminarCaptura();

    ButtonIniciar->setEnabled(true);
    ButtonPause->setEnabled(false);
    ButtonRec->setEnabled(false);
    ButtonPause->setEnabled(false);
}

void MainWindow::on_pushButtonPonte_clicked()
{
    mpresenter->ProcessaPN(PN_PONTE);
}

void MainWindow::on_pushButtonTunel_clicked()
{
    mpresenter->ProcessaPN(PN_TUNEL);
}

void MainWindow::on_pushButtonPN_clicked()
{
    mpresenter->ProcessaPN(PN_PASSAGEMNIVEL);
}

void MainWindow::on_pushButtonInicioSb_clicked()
{
}
