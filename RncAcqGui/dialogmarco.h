#ifndef DIALOGMARCO_H
#define DIALOGMARCO_H

#include "ui_dialogmarco.h"

class DialogMarco : public QDialog, private Ui::DialogMarco
{
    Q_OBJECT
    
public:
    explicit DialogMarco(QWidget *parent = 0);

    QString GetMarco();
};

#endif // DIALOGMARCO_H
