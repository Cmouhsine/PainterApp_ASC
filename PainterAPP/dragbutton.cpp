#include "dragbutton.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>
#include <QLabel>

DragButton::DragButton(QWidget *parent) : QPushButton(parent),
    buttonColor(Qt::gray)
{

}

QColor DragButton::getButtonColor() const
{
    return buttonColor;
}

void DragButton::setButtonColor(const QColor &value)
{
    buttonColor = value;
}

void DragButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        lastPos = event->pos();
    }
    QPushButton::mousePressEvent(event);


    QDrag* drag = new QDrag(this);
    QMimeData* mimeData = new QMimeData;

    mimeData->setText("Objet capté");
    drag->setMimeData(mimeData);
    drag->setPixmap((QPixmap(":/images/star.png")));

    Qt::DropAction dropAction = drag->exec();

}

void DragButton::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){

        int distance = (event->pos() - lastPos).manhattanLength();

        if( distance >= QApplication::startDragDistance()){
            QDrag* drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            //mimeData->setColorData(buttonColor);
            QPixmap pix(20, 20);
            pix.fill(buttonColor);
            drag->setPixmap(pix);
            drag->setMimeData(mimeData);
            drag->exec();
        }
    }
    QPushButton::mouseMoveEvent(event);
}






