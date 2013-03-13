#include "dialogfecharsb.h"

DialogFecharSB::DialogFecharSB(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

QString DialogFecharSB::SbParaFechar()
{
	return comboBox->currentText();
}

bool DialogFecharSB::SelecaoChave(PN_CHAVE &pntipo)
{
	bool selection;

	bool select = ((selection = radioButtonSim->isChecked()) || radioButtonNao->isChecked());

	pntipo = selection ? PN_CHAVE_A_FRENTE : PN_SEM_CHAVE;

	return select;
}

void DialogFecharSB::CarregaSbAberta(std::vector < std::string> Sbs)
{
	comboBox->clear();

	for(unsigned int i = 0; i < Sbs.size(); i++)
	{
		comboBox->addItem(Sbs[i].c_str());
	}
}
