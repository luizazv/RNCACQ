#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "c:/Dados/Projetos Daiken/RncAcq/RncAcq/MVP.h"


class MainWindow : public QMainWindow, private Ui::MainWindow, public View
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    void SentencaOk();
	void ErroGps();
	void ErroGpsFalhaSentenca();
	void ErroGpsSentencaInvalida();
	void SetHdop(int valor);
	void SendMsg(const char *msg, int timer = 0);
	void SetDistanciaProximoMarco(int distancia);
	void Plota(COORDENADAS coord);

private:
	enum EstadoGPS
	{
		ESTADO_VERMELHO,
		ESTADO_AMARELO,
		ESTADO_VERDE
	}mestadoGps;

    int mdistanciaUltimoMarco;
    int mmarcoAtual;
    int mproximoMarco;

	std::vector< std::string > ListaSbsAbertas;
    void AtivaBarraLeds();

signals:
   void AbreMsgBox(const char *msg, int timer);
   void PlotaCoordenadas(COORDENADAS coord);


public slots:
    void on_AbreMsgBox(const char *msg, int timer);
	void on_PlotaCoordenadas(COORDENADAS coord);

private slots:
    void on_ButtonIniciar_clicked();
    void on_ButtonStop_clicked();
    void on_pushButtonPonte_clicked();
    void on_pushButtonTunel_clicked();
    void on_pushButtonPN_clicked();
    void on_pushButtonInicioSb_clicked();
    void on_pushButtonFimSb_clicked();
    void on_pushButtonMarco_clicked();
    void on_pushButtonUsuario_clicked();
    void on_pushButtonTunel_2_clicked();
    void on_pushButtonPonte_2_clicked();
    void on_toolButtonProximoMarco_clicked();
    void on_toolButtonMarcoAtual_clicked();

};

#endif // MAINWINDOW_H
