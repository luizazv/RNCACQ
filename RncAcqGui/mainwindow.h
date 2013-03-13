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
	void SendMsg(const char *msg);

private:
	enum EstadoGPS
	{
		ESTADO_VERMELHO,
		ESTADO_AMARELO,
		ESTADO_VERDE
	}mestadoGps;

	std::vector< std::string > ListaSbsAbertas;

private slots:
	void on_ButtonRec_clicked();
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
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
