#include "dialogabrirsb.h"


DialogAbrirSB::DialogAbrirSB(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void DialogAbrirSB::on_lineEditSb_textChanged(const QString &arg1)
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
    bool select = false;

    if(radioButtonChaveDireita->isChecked())
    {
        pntipo = PN_DESVIO_DIREITA;
        select = true;
    }
    else if(radioButtonChaveEsquerda->isChecked())
    {
        pntipo = PN_DESVIO_ESQUERDA;
        select = true;
    }
    else if(radioButtonMarco->isChecked())
    {
        pntipo = PN_INICIO_MARCO;
        select = true;
    }

    if(select == true)
    {
        //aceita SB com nome igual ou superior a tres digitos
        if(lineEditSb->text().size() < 3)
        {
            select = false;
        }
    }

	return select;
}

QString DialogAbrirSB::Marco()
{
    return lineEditMarco->text();
}

QString DialogAbrirSB::Sb()
{
    return lineEditSb->text();
}


