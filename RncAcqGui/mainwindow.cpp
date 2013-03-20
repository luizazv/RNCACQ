#include "mainwindow.h"
#include "dialogmarco.h"
#include "dialogabrirsb.h"
#include "dialogfecharsb.h"
#include "dialogdefinidousuario.h"
#include "framenav.h"

#include <QtGui\QPainter>
#include <string>
#include <QtWidgets\QMessageBox>
#include <QtCore\QTimer>
#include <algorithm>
#include <sstream>

#include "c:/dados/projetos daiken/rncacq/rncacq/MVP.h"
#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"

FrameNav *frameNav;

static COORDENADAS tempCoord;
static PN_DATA tempPn;
static float tempVel;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    frameNav = new FrameNav(frameBase);
    frameNav->setGeometry(frameBase->geometry());
    frameNav->setGeometry(QRect(0, 0, frameBase->width(), frameBase->height()));

	int w = frameNav->width() / 2;
	int h = frameNav->height() / 2;

    frameNav->setFrameShape(QFrame::NoFrame);
    frameNav->setFrameShadow(QFrame::Sunken);

    mdistanciaUltimoMarco = 0;
    mmarcoAtual = 0;

	//conecta signal e slot para evitar que thread atue sobre a janela principal
    connect(this, SIGNAL(PlotaCoordenadas()), this, SLOT(on_PlotaCoordenadas()));

	//conecta signal e slot para evitar que thread atue sobre a janela principal
    connect(this, SIGNAL(AbreMsgBox(const char*, int)), this, SLOT(on_AbreMsgBox(const char*, int)));
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
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(true);
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
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(true);
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
        ButtonIniciar->isEnabled() == true)
	{
		ButtonStop->setEnabled(true);
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
        ButtonIniciar->isEnabled() == false)
	{
		ButtonStop->setEnabled(false);
		ButtonIniciar->setEnabled(true);
	}
}

void MainWindow::SetHdop(int valor)
{
	horizontalSliderHdop->setValue(valor);
}

void MainWindow::on_PlotaCoordenadas()
{
	static bool backgroundRed = false;
	//adiciona no vetor de coordenadas
	mutex.lock();
	frameNav->AddPontos(tempCoord, tempPn);
	mutex.unlock();

	//atualiza velocidade
    lcdNumberVel->display(tempVel);
	//verifica se vel > 30
	if(tempVel > 30)
	{
		if(backgroundRed == false)
		{
			lcdNumberVel->setStyleSheet("background-color: red");
			backgroundRed = true;
		}
	}
	else
	{
		if(backgroundRed == true)
		{
			lcdNumberVel->setStyleSheet("background-color: rgb(217, 217, 217)");
			backgroundRed = false;
		}
	}

	//plota na metade da tela 
	frameNav->repaint();
}

void MainWindow::Plota(COORDENADAS coord, PN_DATA pn)
{
	//signals com estruturas como parâmetros não consegue ativar o slot
	//usar variável temporaria para passar parametros complexos para GUI
	mutex.lock();
	tempCoord = coord;
	tempPn = pn;
	tempVel = coord.velocidade;
	mutex.unlock();

	//aciona slot on_plotaCoordenadas
	emit PlotaCoordenadas();
}


void MainWindow::on_AbreMsgBox(const char *msg, int timer)
{
	//slot ativado pelo signal AbreMsgBox
	QMessageBox *mbox = new QMessageBox(this);

	if(timer == 0)
	{
		//timer = tempo em milisegundos
		mbox->setWindowTitle("ATENCAO");
		mbox->setText(msg);
		mbox->setStandardButtons(QMessageBox::Ok);
	}
	else
	{
		//timer = tempo em milisegundos
		QTimer::singleShot(timer, mbox, SLOT(hide()));
		mbox->setWindowTitle("ATENCAO");
		mbox->setText(msg);
		mbox->setStandardButtons(QMessageBox::NoButton);
	}
    mbox->show();
}

void MainWindow::SendMsg(const char *msg, int timer)
{
	//envia sinal on_MsgBox_clicked
    emit AbreMsgBox(msg, timer);
}

void MainWindow::on_ButtonIniciar_clicked()
{
	//se marco inicial não estiver configurado não inicia gravação
	if(labelMarcoAtual->text().size() == 0)
	{
		QMessageBox::information(NULL, "ERRO", "Faltou Configurar Marco Atual");
	}
    else
    {
        //inicia thread GPS
        ButtonStop->setEnabled(true);
        ButtonIniciar->setEnabled(false);

        string strSerial = comboBoxSerial->currentText().toLocal8Bit();

        mpresenter->IniciaGps(strSerial);
    }
}

void MainWindow::on_ButtonStop_clicked()
{
    //termina captura
    mpresenter->TerminarCaptura();

    ButtonIniciar->setEnabled(true);
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

		pn.pntipo = PN_INICIOSB;
		pn.Marco = dialogAbrir.Marco().toLocal8Bit();
		pn.Sb = dialogAbrir.Sb().toLocal8Bit();

		//select = true-> um dos elementos foi selecionado
		bool select = dialogAbrir.SelecaoInicio(pn.pntipoinicio);

		//verifica se algum dos radiobutton está selecionado
		if(select)
		{
			//um dos elementos foi selecionado->processa
			mpresenter->ProcessaPN(pn);

			ListaSbsAbertas.push_back(pn.Sb);
		}
		else
		{
            QMessageBox::information(this, "ATENCAO", "FALTOU SELECIONAR ALGUM ELEMENTO AO MARCAR ABERTURA DE SB");
		}
    }
}

void MainWindow::on_pushButtonFimSb_clicked()
{
    DialogFecharSB dialogFechar;

	dialogFechar.CarregaSbAberta(ListaSbsAbertas);

    if(dialogFechar.exec() == 1)
    {
        //dados ok->valida e envia para controle de pontos notaveis
        //valida e envia para controle de pontos notaveis
        PN_DATA pn;

		pn.pntipo = PN_FIMSB;
		pn.Sb = dialogFechar.SbParaFechar().toLocal8Bit();

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
            QMessageBox::information(this, "ATENCAO", "FALTOU SELECIONAR ALGUM ELEMENTO AO MARCAR FECHAMENTO DE SB");
        }
    }
}

void MainWindow::on_pushButtonMarco_clicked()
{
    PN_DATA data;

    data.pntipo = PN_MARCO;

    if(mdistanciaUltimoMarco > 500)
    {
        //incrementa marco automaticamente se distancia maior que 500 do marco anterior
        mmarcoAtual++;
    }

	QString qStr = QString::number(mmarcoAtual);

	data.Marco = qStr.toLocal8Bit();

    mpresenter->ProcessaMQ(data);
}

void MainWindow::on_pushButtonUsuario_clicked()
{
    DialogDefinidoUsuario dialogUser;

    if(dialogUser.exec() == 1)
    {

    }

}

void MainWindow::SetDistanciaProximoMarco(int distancia)
{
	labelDistanciaProximoMarco->setText(QString().setNum(distancia));
}

void MainWindow::on_toolButtonProximoMarco_clicked()
{
    DialogMarco dialogMarco;

    if(dialogMarco.exec() == 1)
    {
        //atualiza marco atual com o novo valor
        labelProximoMarco->setText(dialogMarco.GetMarco());
    }
}

void MainWindow::on_toolButtonMarcoAtual_clicked()
{
    DialogMarco dialogMarco;

    if(dialogMarco.exec() == 1)
    {
        labelMarcoAtual->setText(dialogMarco.GetMarco());
        mmarcoAtual = labelMarcoAtual->text().toInt();
        mproximoMarco = mmarcoAtual + 1;
        std::stringstream marco;
        marco << mproximoMarco;
        labelProximoMarco->setText(marco.str().c_str());

        mpresenter->SalvaMarcoAtual(mmarcoAtual);
    }
}
