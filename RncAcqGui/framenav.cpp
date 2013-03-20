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

	DesenhaPontosNotaveis(painter);
}

void FrameNav::DesenhaSb(QPainter &painter, int x1, int coordy, int x2, std::string nomeSb)
{
	QBrush brush;

	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::red);

	painter.setBrush(brush);
	painter.setPen(Qt::blue);
	//largura da linha de sb em pixels
	int tam = TAM_SB;
	coordy = coordy - tam / 2;

	painter.drawRect(x1, coordy, x2 - x1, tam);

	painter.setPen(Qt::white);
	painter.drawText(x1 + 15, coordy + 2 * (tam / 3), QString(nomeSb.c_str()));
}

void FrameNav::DesenhaLinhaPrincipal(QPainter &painter, int x1, int x2)
{
	QBrush brush;

	painter.setBrush(Qt::NoBrush);
	painter.setPen(Qt::blue);
	//largura da linha de sb em pixels
	int tam = TAM_SB;
	int coordy = COORDY_LINHAPRINCIPAL;
	coordy = coordy - tam / 2;

	painter.drawLine(x1, coordy, x2, coordy);
	painter.drawLine(x1, coordy + tam, x2, coordy + tam);

//	painter.drawRect(x1, COORDY_LINHAPRINCIPAL, x2 - x1, tam);
}

void FrameNav::DesenhaPn(QPainter &painter, int x1, int x2, PN_TIPO pn)
{
	QBrush brush;

	if(pn == PN_INICIOPONTE || pn == PN_FIMPONTE)
	{
		brush.setColor(Qt::green);
		brush.setStyle(Qt::SolidPattern);
	}
	else
	{
		brush.setColor(Qt::yellow);
		brush.setStyle(Qt::SolidPattern);
	}

	painter.setBrush(brush);
	painter.setPen(Qt::black);
	
	painter.drawRect(x1, COORDY_PN, x2 - x1, TAM_PN);
}


void FrameNav::DesenhaPontosNotaveis(QPainter &painter)
{
	std::vector <int> coordenadaEmUsoDireita;
	std::vector <int> coordenadaEmUsoEsquerda;

	unsigned int tamvec = mvecGuiData.size();

//	if(tamvec > ((unsigned int)width() + 400))
	if(tamvec > ((unsigned int)width() -100))
	{
		//vetor de dados maior que a tela + tolerancia, descarta pontos mais antigos
		mvecGuiData.erase(mvecGuiData.begin(), mvecGuiData.begin() + 1/*300*/);
		tamvec = mvecGuiData.size();
	}

	std::vector <GUI_DATA> guiData = mvecGuiData;

	if(guiData.size() > 0)
	{
		bool fimPonteEncontrado = false;
		bool fimTunelEncontrado = false;

		//desenha indicador de leitura
		QBrush brush;
		static int counter = 0;

		brush.setStyle(Qt::SolidPattern);
		brush.setColor(Qt::red);
		painter.setBrush(brush);
		painter.setPen(Qt::black);
		painter.drawEllipse(QRect( 8, 8, 34, 34));

		brush.setStyle(Qt::Dense4Pattern);
		brush.setColor(Qt::white);
		painter.setBrush(brush);
		painter.setPen(Qt::black);
		painter.drawPie(QRect(12, 12, 28, 28), (10 *counter++) * 16, (10 *counter++) * 16);
		if(counter > 36)
			counter = 0;



		int pontox = width() - tamvec- 2;
		for(unsigned int index = 0; index < tamvec; index++, pontox++)
		{
			switch(guiData[index].pn.pntipo)
			{
			case PN_COORDENADAS:
				//desenha linha principal 
				DesenhaLinhaPrincipal(painter, pontox, width());
			break;

			case PN_MARCOINICIAL:
				painter.setPen(Qt::black);
				painter.setBrush(Qt::VerPattern);

				//desenha linha vertical do marco
				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 
			break;

			case PN_INICIOPONTE:
				//procura final da ponte
				int fimPonte;
				
				fimPonte = pontox;
				fimPonteEncontrado = false;

				for(auto ptrponte = guiData.begin() + index; ptrponte != guiData.end(); ptrponte++, fimPonte++)
				{
					if((*ptrponte).pn.pntipo == PN_FIMPONTE)
					{
						fimPonteEncontrado = true;
						break;
					}
				}

				//desenha ponte at� o fim da ponte ou fim do frame
				DesenhaPn(painter, pontox, fimPonte, PN_INICIOPONTE);
			break;

			case PN_FIMPONTE:
				if(!fimPonteEncontrado)
				{
					//fim de ponte n�o foi encontrado->n�o tem inicio de ponte no vetor
					//desenha at� come�o do frame
					DesenhaPn(painter, x(), pontox, PN_FIMPONTE);
				}
				else
				{
					//fim de ponte j� encontrado porque inicio j� foi processado->nada precisa fazer
				}
			break;

			case PN_INICIOTUNEL:
				//procura final da ponte
				int fimTunel;
				
				fimTunel = pontox;
				fimTunelEncontrado = false;

				for(auto ptrtunel = guiData.begin() + index; ptrtunel != guiData.end(); ptrtunel++, fimTunel++)
				{
					if((*ptrtunel).pn.pntipo == PN_FIMTUNEL)
					{
						fimTunelEncontrado = true;
						break;
					}
				}

				//desenha
				DesenhaPn(painter, pontox, fimTunel, PN_INICIOTUNEL);

			break;

			case PN_FIMTUNEL:
				if(!fimTunelEncontrado)
				{
					//fim de tunel n�o foi encontrado->n�o tem inicio de ponte no vetor
					//desenha at� come�o do frame
					DesenhaPn(painter, x(), pontox, PN_FIMTUNEL);
				}
				else
				{
					//fim de tunel j� encontrado porque inicio j� foi processado->nada precisa fazer
				}
			break;

			case PN_PASSAGEMNIVEL:
				painter.drawEllipse(QPoint(pontox, COORDY_PN), 10, 10);
			break;

			case PN_INICIOSB:
				//procura final da sb
				int fimSb;
				fimSb = pontox;

				for(auto ptrsb = guiData.begin() + index; ptrsb != guiData.end(); ptrsb++, fimSb++)
				{
					if((*ptrsb).pn.pntipo == PN_FIMSB)
					{
						//verifica se foi encontrado fim desta sb
						if((*ptrsb).pn.Sb == guiData[index].pn.Sb)
						{
							fimPonteEncontrado = true;
							break;
						}
					}
				}

				int coordy;
				int delta;
				
				delta = 0;
				//desenha do come�o ao fim
				if(guiData[index].pn.pntipoinicio == PN_DESVIO_DIREITA)
				{
					//desenha linha abaixo da principal->verifica qual coordenada Y n�o est� em uso

					for(delta = 0; delta < 5; delta++)
					{
						bool emUso = false;
						for(unsigned int i = 0; i < coordenadaEmUsoDireita.size(); i++)
						{
							if(coordenadaEmUsoDireita[i] == delta)
							{
								//coordenada em uso->pula para proxima
								emUso = true;
								break;
							}
						}
						if(!emUso)
						{
							break;
						}
					}
					
					//guarda coordenada como em uso
					coordenadaEmUsoDireita.push_back(delta);

					coordy = COORDY_LINHAPRINCIPAL + COORDY_DELTA + delta * COORDY_DELTA;
				}
				else if(guiData[index].pn.pntipoinicio == PN_DESVIO_ESQUERDA)
				{
					for(delta = 0; delta < 5; delta++)
					{
						bool emUso = false;
						for(unsigned int i = 0; i < coordenadaEmUsoEsquerda.size(); i++)
						{
							if(coordenadaEmUsoEsquerda[i] == delta)
							{
								//coordenada em uso->pula para proxima
								emUso = true;
								break;
							}
						}
						if(!emUso)
						{
							break;
						}
					}
					
					//guarda coordenada como em uso
					coordenadaEmUsoEsquerda.push_back(delta);

					//desenha linha acima da principal
					coordy = COORDY_LINHAPRINCIPAL - COORDY_DELTA - delta * COORDY_DELTA;
				}
				else 
				{
					//desenha na linha principal
					coordy = COORDY_LINHAPRINCIPAL;
				}

				DesenhaSb(painter, pontox, coordy, fimSb, guiData[index].pn.Sb);
				//guarda Sb no vetor de come�os de sb
				//se n�o estiver->guarda
				//se j� estiver->atualiza
				{
					bool encontrado = false;
					for(auto ptr = comecoSb.begin(); ptr != comecoSb.end() && encontrado == false; ptr++)
					{
						if((*ptr).nomeSb == guiData[index].pn.Sb)
						{
							//encontrou no vetor->atualiza dados
							(*ptr).coordY = coordy;
							(*ptr).delta = delta;
							encontrado = true;
						}
					}


					if(encontrado == false)
					{
						INICIOFIM_SB sb;
						sb.coordY = coordy;
						sb.delta = delta;
						sb.nomeSb = guiData[index].pn.Sb;
						sb.tipoinicio = guiData[index].pn.pntipoinicio;
						comecoSb.push_back(sb);
						//ajusta tamanho do vetor para guardar at� 100 sbs->apenas seguran�a
						if(comecoSb.size() > 100)
						{
							comecoSb.resize(100);
						}
					}
				}
			break;

			case PN_FIMSB:
				{
					bool comecoEncontrado = false;
					std::string strsb = guiData[index].pn.Sb;

					for(auto ptrsb = guiData.rbegin(); ptrsb != guiData.rend(); ptrsb++)
					{
						if((*ptrsb).pn.Sb == strsb && ((*ptrsb).pn.pntipo == PN_INICIOSB))
						{
							//comeco da sb encontrado
							comecoEncontrado = true;
							break;
						}
					}

					//procura inicio para definir coordenada y do desenho do fim de sb
					for(auto ptrsb = comecoSb.begin(); ptrsb != comecoSb.end(); ptrsb++)
					{
						//se n�o encontrar come�o->ignora fim da sb (tratar no p�s-processamento
						if((*ptrsb).nomeSb == strsb)
						{
							//se come�o encontrado n�o precisa fazer nada, basta desenhar hachurado
							if(!comecoEncontrado)
							{
								//come�o da sb n�o encontrado->desenha at� come�o do frame na coordenada Y
								DesenhaSb(painter, x(), coordy, pontox, guiData[index].pn.Sb);
							}

							//desenha hachurado
							painter.setBrush(Qt::FDiagPattern);
							painter.setPen(Qt::lightGray);
							painter.drawRect(pontox, 0, 20, height());

							if((*ptrsb).tipoinicio == PN_DESVIO_DIREITA)
							{
								//eliminar coordenada em uso->permite desenho da proxima abertura de sb na mesma coordenada
								for(unsigned int i = 0; i < coordenadaEmUsoDireita.size(); i++)
								{
									if((*ptrsb).delta == coordenadaEmUsoDireita[i])
									{
										coordenadaEmUsoDireita.erase(coordenadaEmUsoDireita.begin() + i);
									}
								}
							}
							else if((*ptrsb).tipoinicio == PN_DESVIO_ESQUERDA)
							{
								//eliminar coordenada em uso->permite desenho da proxima abertura de sb na mesma coordenada
								for(unsigned int i = 0; i < coordenadaEmUsoEsquerda.size(); i++)
								{
									if((*ptrsb).delta == coordenadaEmUsoEsquerda[i])
									{
										coordenadaEmUsoEsquerda.erase(coordenadaEmUsoEsquerda.begin() + i);
									}
								}
							}
						}
					}
				}
			break;

			case PN_MARCO:
				painter.setPen(Qt::black);
				painter.setBrush(Qt::VerPattern);

				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 
			break;

			case PN_MARCOAUTOMATICO:
				painter.setPen(Qt::black);
				painter.setBrush(Qt::VerPattern);

				painter.drawLine(pontox, COORDY_LINHAPRINCIPAL - 50, pontox, COORDY_LINHAPRINCIPAL + 50); 
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

	mvecGuiData.push_back(t);
}
