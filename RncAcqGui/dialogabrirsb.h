#ifndef DIALOGABRIRSB_H
#define DIALOGABRIRSB_H

#include "ui_dialogabrirsb.h"
#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"

class DialogAbrirSB : public QDialog, private Ui::DialogAbrirSB
{
    Q_OBJECT
    
public:
    explicit DialogAbrirSB(QWidget *parent = 0);

	bool SelecaoSentido(PN_SENTIDO &pntipo);
	bool SelecaoInicio(PN_INICIOTIPO &pntipo);
	bool SelecaoDesvio(PN_DESVIO &pntipo);
	QString Marco();
	QString Sb();

private slots:
    void on_lineEditSb_textChanged(const QString &arg1);
};

#endif // DIALOGABRIRSB_H
