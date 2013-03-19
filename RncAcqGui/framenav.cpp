#include "framenav.h"

int k = 150;
int xp1 = 15;
int yp1 = 20;

FrameNav::FrameNav(QWidget *t) : QFrame(t)
{
	mprimeiroPonto = 0;
}

void FrameNav::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

//	DesenhaCursor(painter);

	DesenhaPontosNotaveis(painter);
}

void FrameNav::ConverteOrigemX(int xCartesiano, int &xOrigem)
{
	//converte coordenadas globais em sentido cartesiano normal
	xOrigem = width() - xCartesiano;
}

void FrameNav::ConverteOrigemY(int yCartesiano, int &yOrigem)
{
	//converte coordenadas globais em sentido cartesiano normal
	yOrigem = height() - yCartesiano;
}

void FrameNav::SetOrigem(int x, int y)
{
	//todos os pontos são referenciados à origem
	mOrigemX = x;
	mOrigemY = y;
}

/*
void ConvertePontoRelacaoOrigem(int x, int y)
{
	//calcula ponto x, y em função do valor de origem e das
	//coordenadas de origem de início da plotagem
	//nesta versão é o centro do frame

	int xnovo = (x - mOrigemX + width() / 2);
	int ynovo = (y - mOrigemY + height() / 2);
}*/

void FrameNav::SetCursor(int x, int y)
{
	mCursorX = x;
	mCursorY = y;
}

void FrameNav::DesenhaCursor(QPainter &painter)
{
	//desenha um cursor no centro do frame
	painter.drawEllipse(QPoint(mCursorX, mCursorY), 10, 10);

    painter.drawLine(mCursorX - 7, mCursorY + 7, mCursorX + 7, mCursorY - 7);
	painter.drawLine(mCursorX - 7, mCursorY - 7, mCursorX + 7, mCursorY + 7);
}


bool FrameNav::ComparaLatitudeMaior(COORDENADAS coord1, COORDENADAS coord2)
{
   bool retval = (coord1.latitude > coord2.latitude);
   return retval;
}

bool FrameNav::ComparaLongitudeMaior(COORDENADAS coord1, COORDENADAS coord2)
{
   bool retval = (coord1.longitude > coord2.longitude);
   return retval;
}

bool FrameNav::ComparaLatitudeMenor(COORDENADAS coord1, COORDENADAS coord2)
{
   bool retval = (coord1.latitude < coord2.latitude);
   return retval;
}

bool FrameNav::ComparaLongitudeMenor(COORDENADAS coord1, COORDENADAS coord2)
{
   bool retval = (coord1.longitude < coord2.longitude);
   return retval;
}

void FrameNav::DesenhaSb(QPainter &painter, int x1, int coordy, int x2, std::string nomeSb)
{
	QBrush brush;

	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);

	painter.setBrush(brush);
	painter.setPen(Qt::blue);
	//largura da linha de sb em pixels
	int tam = 24;
	coordy = coordy - tam / 2;

	painter.drawRect(x1, coordy, x2 - x1, tam);

	painter.setPen(Qt::white);
	painter.drawText(x1 + 10, coordy + 2 * (tam / 3), QString(nomeSb.c_str()));
}

void FrameNav::DesenhaLinhaPrincipal(QPainter &painter, int x1, int coordy, int x2)
{
	QBrush brush;

	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::blue);
	//largura da linha de sb em pixels
	int tam = 24;
	coordy = coordy - tam / 2;

	painter.drawRect(x1, coordy, x2 - x1, tam);
}


void FrameNav::DesenhaPontosNotaveis(QPainter &painter)
{
	//analisa pontos de tras para frente
	//pega elemento mais antigo
//	int inicioPonte;
	int fimPonte;
//	int inicioTunel;
	int fimTunel;

	int inicioLinhaPrincipal = -1;
	int proximoiniciosb = width();

	if(mvecGuiData.size() > 0)
	{
		bool fimPonteEncontrado = false;
		bool fimTunelEncontrado = false;
		bool fimSbEncontrado = false;
		bool existeSbAberta = false;
		int passagemNivel = 0;

		int numsbabertadireita = 0;
		int numsbabertaesquerda = 0;

		struct INICIOFIM_SB
		{
			std::string nomeSb;
			int inicoSb;
			int fimSb;
			int coordY;
			PN_INICIOTIPO desvio;
		};

		std::vector <INICIOFIM_SB> coordYSb;

		unsigned int j;
		unsigned int tamvec = mvecGuiData.size();
		int pontox = width();

		for(j = 0; j < tamvec; j++, pontox--)
		{
			GUI_DATA guiData = mvecGuiData[tamvec - j - 1];

			switch(guiData.pn.pntipo)
			{
			case PN_COORDENADAS:
/*				if(inicioLinhaPrincipal == -1)
				{
					inicioLinhaPrincipal = pontox;
				}
				//desenha linha principal 
				DesenhaSb(painter, inicioLinhaPrincipal, COORDY_LINHAPRINCIPAL, width());
//				painter.drawRect(pontox, COORDY_LINHAPRINCIPAL, width() - pontox, 15);*/
			break;
			case PN_INICIOPONTE:
				//desenha linha de inicio até final
				//se final ainda não foi marcado->desenha até limite do frame
				if(fimPonteEncontrado)
				{
					//desenha linha até o fim da ponte
					painter.drawLine(pontox, COORDY_PN, fimPonte, COORDY_PN);
					fimPonteEncontrado = false;
				}
				else
				{
					painter.drawLine(pontox, COORDY_PN, width(), COORDY_PN);
				}
			break;

			case PN_FIMPONTE:
				fimPonteEncontrado = true;
				fimPonte = pontox;
			break;

			case PN_INICIOTUNEL:
				//desenha linha de inicio até final
				//se final ainda não foi marcado->desenha até limite do frame
				if(fimTunelEncontrado)
				{
					//desenha linha até o fim da ponte
					painter.drawLine(pontox, COORDY_PN, fimTunel, COORDY_PN);
					fimTunelEncontrado = false;
				}
				else
				{
					painter.drawLine(pontox, COORDY_PN, width(), COORDY_PN);
				}
			break;

			case PN_FIMTUNEL:
				fimTunelEncontrado = true;
				fimTunel = pontox;
			break;

			case PN_PASSAGEMNIVEL:
				painter.drawEllipse(QPoint(pontox, COORDY_PN), 10, 10);
			break;

			case PN_INICIOSB:
				{

					proximoiniciosb = pontox;

					//procura pelo fim
					bool fimEncontrado;
					INICIOFIM_SB dsb;

					fimEncontrado = false;

					for(unsigned int i = 0, j = 0; i < coordYSb.size(); i++)
					{
						dsb = coordYSb[i];

						if(dsb.fimSb != -1)
						{
							//esta sb tem um fim encontrado->procura pelo nome
							if(dsb.nomeSb == guiData.pn.Sb)
							{
								fimEncontrado = true;

								//desenha do começo ao fim
								if(guiData.pn.pntipoinicio == PN_DESVIO_DIREITA)
								{
									//desenha linha abaixo da principal
									int coordy = coordYSb[coordYSb.size() - i - 1].coordY = COORDY_LINHAPRINCIPAL + COORDY_DELTA + (numsbabertadireita++ * COORDY_DELTA);
									DesenhaSb(painter, pontox, coordy, dsb.fimSb, guiData.pn.Sb);
								}
								else if(guiData.pn.pntipoinicio == PN_DESVIO_ESQUERDA)
								{
									//desenha linha acima da principal
									int coordy = coordYSb[coordYSb.size() - i - 1].coordY = COORDY_LINHAPRINCIPAL - COORDY_DELTA - (numsbabertaesquerda++ * COORDY_DELTA);
									DesenhaSb(painter, pontox, coordy, dsb.fimSb, guiData.pn.Sb);
								}
								else 
								{
									//desenha na linha principal
									DesenhaSb(painter, pontox, COORDY_LINHAPRINCIPAL, dsb.fimSb, guiData.pn.Sb);
								}

								//removo da lista
								std::vector<INICIOFIM_SB>::iterator it;
								it = coordYSb.begin();
								coordYSb.erase(it + i);

								//reinicio o loop devido ao erase
								i = 0;
							}
						}
					}

					if(fimEncontrado == false)
					{
						//não encontrado fim da sb->inicia o desenho de abertura de sb no pontox até fim do frame
						dsb.inicoSb = pontox;
						dsb.fimSb = -1;
						dsb.desvio = guiData.pn.pntipoinicio;
						dsb.nomeSb = guiData.pn.Sb;

						coordYSb.push_back(dsb);

						//traca linhas conforme numero de sbs abertas
						for(unsigned int i = 0; i < coordYSb.size(); i++)
						{
							//pega sb aberta da mais recente para a mais antiga
							dsb = coordYSb[coordYSb.size() - i - 1];

							if(dsb.nomeSb == guiData.pn.Sb)
							{
								//desenha do começo ao fim
								if(guiData.pn.pntipoinicio == PN_DESVIO_DIREITA)
								{
									//desenha linha abaixo da principal
									int coordy = coordYSb[coordYSb.size() - i - 1].coordY = COORDY_LINHAPRINCIPAL + COORDY_DELTA + (numsbabertadireita++ * COORDY_DELTA);
									DesenhaSb(painter, pontox, coordy, width(), guiData.pn.Sb);
								}
								else if(guiData.pn.pntipoinicio == PN_DESVIO_ESQUERDA)
								{
									//desenha linha acima da principal
									int coordy = coordYSb[coordYSb.size() - i - 1].coordY = COORDY_LINHAPRINCIPAL - COORDY_DELTA - (numsbabertaesquerda++ * COORDY_DELTA);
									DesenhaSb(painter, pontox, coordy, width(), guiData.pn.Sb);
								}
								else 
								{
									DesenhaSb(painter, pontox, COORDY_LINHAPRINCIPAL, width(), guiData.pn.Sb);
								}
							}
						}
					}
				}
			break;

			case PN_FIMSB:
				{
					//adiciona Sb na fila de sbs para abrir
					INICIOFIM_SB dsb;

					dsb.nomeSb = guiData.pn.Sb;
					dsb.fimSb = pontox;
					coordYSb.push_back(dsb);

					painter.setBrush(Qt::FDiagPattern);
					painter.setPen(Qt::gray);

					//desenha até o fim do frame indicação de sb fechada
					//painter.drawRect(dsb.fimSb, 0, proximoiniciosb - dsb.fimSb, height());

				}
			break;

			case PN_MARCO:
				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 
			break;

			case PN_MARCOAUTOMATICO:
				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 
			break;

			case PN_MARCOINICIAL:
				painter.setPen(Qt::black);
				painter.setBrush(Qt::VerPattern);

				//desenha linha vertical do marco
				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 

				//desenha linha principal
				DesenhaLinhaPrincipal(painter, pontox, COORDY_LINHAPRINCIPAL, width());
			break;

			}
		}
	}
}

void FrameNav::AddPontos(COORDENADAS coord, PN_DATA pn)
{
	GUI_DATA t;

	t.coord = coord;
	t.pn = pn;

	//processa dados
	switch(pn.pntipo)
	{
	case PN_COORDENADAS:
		//marcação de coordenadas-> a cada 10 leituras
//		if(mpasso > NUMERO_PASSOCOORDENADAS)
		{
			//adiciona o ponto
			mvecGuiData.push_back(t);
//			mpasso = 0;
		}
//		else
//		{
//			mpasso++;
//		}

	break;
	default:
		mvecGuiData.push_back(t);
	break;
	}
}
