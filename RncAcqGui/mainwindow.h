#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "c:/Dados/Projetos Daiken/RncAcq/RncAcq/MVP.h"



class MainWindow : public QMainWindow, private Ui::MainWindow, public View
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void on_ButtonRec_clicked();
    void on_ButtonIniciar_clicked();
};

#endif // MAINWINDOW_H
