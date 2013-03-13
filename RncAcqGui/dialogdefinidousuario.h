#ifndef DIALOGDEFINIDOUSUARIO_H
#define DIALOGDEFINIDOUSUARIO_H

#include "ui_dialogdefinidousuario.h"

class DialogDefinidoUsuario : public QDialog, private Ui::DialogDefinidoUsuario
{
    Q_OBJECT
    
public:
    explicit DialogDefinidoUsuario(QWidget *parent = 0);
};

#endif // DIALOGDEFINIDOUSUARIO_H
