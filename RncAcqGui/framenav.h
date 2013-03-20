#ifndef FRAMENAV_H
#define FRAMENAV_H

#include <QtWidgets\QFrame>
#include <QtGui\QPainter>
#include <string>
#include "C:\Dados\Projetos Daiken\RncAcq\RncAcq\model.h"

//numero de coordenadas (leituras) para dar um passo na tela
#define NUMERO_PASSOCOORDENADAS	1

//coordenadas y locais em relação à geometria do frame
//coordenada da linha principal
#define COORDY_LINHAPRINCIPAL	300
//delta entre linhas paralelas 
#define COORDY_DELTA			80
//coordenada dos pontos notaveis
#define COORDY_PN				COORDY_LINHAPRINCIPAL + 50
//largura da barra de PN em pixels
#define TAM_PN					12
//largura da barra de sb + linha principal
#define TAM_SB					24

//guarda começos das sbs
//para desenhar quando começo naõ
//estiver mais no vetor

struct INICIOFIM_SB
{
	std::string nomeSb;
	int coordY;
	int delta;
	PN_INICIOTIPO tipoinicio;
};


class FrameNav : public QFrame
{
private:

    std::vector <GUI_DATA> mvecGuiData;
	std::vector <INICIOFIM_SB> comecoSb;

	int mCursorX;
	int mCursorY;
	int mOrigemX;
	int mOrigemY;

	int mprimeiroPonto;

    void paintEvent(QPaintEvent *);
    static bool ComparaLatitudeMaior(COORDENADAS coord1, COORDENADAS coord2);
    static bool ComparaLongitudeMaior(COORDENADAS coord1, COORDENADAS coord2);
    static bool ComparaLatitudeMenor(COORDENADAS coord1, COORDENADAS coord2);
    static bool ComparaLongitudeMenor(COORDENADAS coord1, COORDENADAS coord2);

	void DesenhaCursor(QPainter &painter);
	void DesenhaPontosNotaveis(QPainter &painter);
	void DesenhaSb(QPainter &painter, int x1, int coordy, int x2, std::string nomeSb);
	void DesenhaLinhaPrincipal(QPainter &painter, int x1, int x2);
	void DesenhaPn(QPainter &painter, int x1, int x2, PN_TIPO pn);

public:
    FrameNav(QWidget *t);

    void AddPontos(COORDENADAS coord, PN_DATA pn);

};

#endif // FRAMENAV_H
