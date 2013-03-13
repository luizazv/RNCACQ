#include "mainwindow.h"
#include "dialogmarco.h"
#include "dialogabrirsb.h"
#include "dialogfecharsb.h"
#include "dialogdefinidousuario.h"
#include <QtGui\QPainter>
#include <string>
#include <QtWidgets\QMessageBox>
#include <QtCore\QTimer>

#include "c:/dados/projetos daiken/rncacq/rncacq/MVP.h"
#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"

int k = 150;
int xp1 = 15;
int yp1 = 20;

std::vector< int > xp;
std::vector< int > xy;

class FrameNav : public QFrame
{
public:
    FrameNav(QWidget *t) : QFrame(t)
    {
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        xp1++;
        xp.push_back(xp1);
        yp1++;
        xy.push_back(yp1);


        //First Circle:
        //width&height:150px
        //Beginning(x/y):50px/30px
        //Each step for Angle parameter is 1/16th of a Degree
        //so multiply Angle Value with 16
        painter.drawArc(5,5, k+= 15,150,0,16*360);
        painter.drawRect(0, 0, 10, 10);

        for(unsigned int i = 0; i < xp.size(); i++)
        {
            painter.drawPoint(xp[i], xy[i]);
        }
    }


};

FrameNav *frameNav;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    frameNav = new FrameNav(frameBase);
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
//	QMessageBox::information(NULL, "ATENCAO", msg);

    QMessageBox *mbox = new QMessageBox;
    mbox->setWindowTitle("ATENCAO");
    mbox->setText(msg);
    mbox->show();
	QTimer::singleShot(5000, mbox, SLOT(hide()));
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
	PN_DATA data;

	data.pntipo = PN_INICIOPONTE;

    mpresenter->ProcessaPN(data);
}

void MainWindow::on_pushButtonPonte_2_clicked()
{
    PN_DATA data;

    data.pntipo = PN_FIMPONTE;

    mpresenter->ProcessaPN(data);
}

void MainWindow::on_pushButtonTunel_clicked()
{
	PN_DATA data;

	data.pntipo = PN_INICIOTUNEL;

    mpresenter->ProcessaPN(data);
}

void MainWindow::on_pushButtonTunel_2_clicked()
{
    PN_DATA data;

    data.pntipo = PN_FIMTUNEL;

    mpresenter->ProcessaPN(data);
}


void MainWindow::on_pushButtonPN_clicked()
{
	PN_DATA data;

	data.pntipo = PN_PASSAGEMNIVEL;


    mpresenter->ProcessaPN(data);
}

void MainWindow::on_pushButtonInicioSb_clicked()
{
    DialogAbrirSB dialogAbrir;

    if(dialogAbrir.exec() == 1)
    {
        //valida e envia para controle de pontos notaveis
		PN_DATA pn;

		pn.Marco = dialogAbrir.Marco();
		pn.Sb = dialogAbrir.Sb();

		//select = true-> um dos elementos foi selecionado
		bool select = dialogAbrir.SelecaoInicio(pn.pntipoinicio);

		if(select)
		{
			select = dialogAbrir.SelecaoDesvio(pn.pndesvio);
		}

		if(select)
		{
			select = dialogAbrir.SelecaoSentido(pn.pnsentido);
		}

		//verifica se algum dos radiobutton está selecionado
		if(select)
		{
			//um dos elementos foi selecionado->processa
			mpresenter->ProcessaPN(pn);

			ListaSbsAbertas.push_back(pn.Sb);
		}
		else
		{
            QMessageBox::information(this, "ATENCAO", "FALTOU SELECIONAR ALGUM ELEMENTO AO MARCAR FECHAMENTO DE SB");
		}
    }
}

void MainWindow::on_pushButtonFimSb_clicked()
{
    DialogFecharSB dialogFechar;

    if(dialogFechar.exec() == 1)
    {
        //dados ok->valida e envia para controle de pontos notaveis
        //valida e envia para controle de pontos notaveis
        PN_DATA pn;

        pn.Sb = dialogFechar.SbParaFechar();

        //select = true-> um dos elementos foi selecionado
		bool select = dialogFechar.SelecaoChave(pn.pnchave);

        //verifica se todos os radiobutton foram selecionados
        if(select)
        {
            //um dos elementos foi selecionado->processa
            mpresenter->ProcessaPN(pn);

			//retira SB da lista
			for(unsigned int i = 0; i < ListaSbsAbertas.size(); i++)
			{
				if(ListaSbsAbertas[i] == pn.Sb)
				{
					//retira da lista
					ListaSbsAbertas.erase(ListaSbsAbertas.begin() + i);
					break;
				}
			}
        }
        else
        {
            QMessageBox::information(this, "ATENCAO", "FALTOU SELECIONAR ALGUM ELEMENTO AO MARCAR ABERTURA DE SB");
        }
    }
}

void MainWindow::on_pushButtonMarco_clicked()
{
    DialogMarco dialogMarco;

    if(dialogMarco.exec() == 1)
    {

    }
}

void MainWindow::on_pushButtonUsuario_clicked()
{
    DialogDefinidoUsuario dialogUser;

    if(dialogUser.exec() == 1)
    {

    }

}



void MainWindow::on_pushButton_clicked()
{
    frameNav->repaint();
}
