#ifndef DIALOGFECHARSB_H
#define DIALOGFECHARSB_H

#include "ui_dialogfecharsb.h"
#include "c:/dados/projetos daiken/rncacq/rncacq/Model.h"
#include <string>
#include <vector>

class DialogFecharSB : public QDialog, private Ui::DialogFecharSB
{
    Q_OBJECT
    
public:
    explicit DialogFecharSB(QWidget *parent = 0);

	void CarregaSbAberta(std::vector < std::string> Sbs);

	std::string SbParaFechar();

	bool SelecaoChave(PN_CHAVE &pntipo);

private slots:

};

#endif // DIALOGFECHARSB_H
