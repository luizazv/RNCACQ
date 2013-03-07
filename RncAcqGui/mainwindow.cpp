#include "mainwindow.h"
#include <QtGui\QPainter>

class FrameNav : public QFrame
{
public:
    FrameNav(QWidget *t) : QFrame(t)
    {
    }

    void paintEvent(QPaintEvent *)
    {
        QPainter painter(this);

        //First Circle:
        //width&height:150px
        //Beginning(x/y):50px/30px
        //Each step for Angle parameter is 1/16th of a Degree
        //so multiply Angle Value with 16
        painter.drawArc(5,5,150,150,0,16*360);
        painter.drawRect(0, 0, 10, 10);
    }


};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    FrameNav *frameNav = new FrameNav(frameBase/*QMainWindow::centralWidget()*/);
    frameNav->setGeometry(50, 50, 100, 100);
    frameNav->setFrameShape(QFrame::NoFrame);
    frameNav->setFrameShadow(QFrame::Sunken);
}

//void MainWindow::on_pushButton_8_clicked()
//{
//    pushButton_2->setText("bobo");
//}
