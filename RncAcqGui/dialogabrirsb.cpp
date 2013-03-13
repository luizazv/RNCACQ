#include "dialogabrirsb.h"


DialogAbrirSB::DialogAbrirSB(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void DialogAbrirSB::on_lineEdit_textChanged(const QString &arg1)
{
    QLineEdit *le = qobject_cast<QLineEdit *>(sender());
    if (!le)
    {
        return;
    }
    le->setText(le->text().toUpper());
}

bool DialogAbrirSB::SelecaoInicio(PN_INICIOTIPO &pntipo)
{
	bool selection;

	bool select = ((selection = radioButtonChave->isChecked()) || radioButtonMarco->isChecked());

	pntipo = selection ? PN_INICIO_CHAVE : PN_INICIO_MARCO;

	return select;
}

bool DialogAbrirSB::SelecaoSentido(PN_SENTIDO &pntipo)
{
	bool selection;

	bool select = ((selection = radioButtonCrescente->isChecked()) || radioButtonDecrescente->isChecked());

	pntipo = selection ? PN_CRESCENTE : PN_DECRESCENTE;

	return select;

}

bool DialogAbrirSB::SelecaoDesvio(PN_DESVIO &pntipo)
{
	bool selection;

	bool select = ((selection = radioButtonDireita->isChecked()) || radioButtonEsquerda->isChecked());

	pntipo = selection ? PN_DESVIO_DIREITA : PN_DESVIO_ESQUERDA;

	return select;

}

std::string DialogAbrirSB::Marco()
{
    return lineEditMarco->text().toStdString();
}

std::string DialogAbrirSB::Sb()
{
    return lineEditSb->text().toStdString();
}


