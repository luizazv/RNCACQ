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


class FrameNav : public QFrame
{
private:

    std::vector <GUI_DATA> mvecGuiData;

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
	void DesenhaLinhaPrincipal(QPainter &painter, int x1, int coordy, int x2);

	void ConverteOrigemX(int xCartesiano, int &xOrigem);
	void ConverteOrigemY(int yCartesiano, int &yOrigem);

public:
    FrameNav(QWidget *t);

    void AddPontos(COORDENADAS coord, PN_DATA pn);
	void SetOrigem(int x, int y);
	void SetCursor(int x, int y);

};

#endif // FRAMENAV_H
