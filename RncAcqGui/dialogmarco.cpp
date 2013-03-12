#include "dialogmarco.h"

DialogMarco::DialogMarco(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

QString DialogMarco::GetMarco()
{
    return lineEditMarco->text();
}
