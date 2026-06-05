#include "personaje.h"

personaje::personaje(QGraphicsView *view ,const QPixmap pixmapPlayer, const QRectF sceneBounds, QObject *parent)
    : QObject{parent}, pixmapPlayer{pixmapPlayer}, sceneBounds{sceneBounds},view{view}
{
    setPixmap(pixmapPlayer);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);



}
void personaje::iniciarMovimiento(){
    this->vxbalon=-5;
    this-> vybalon=2;
    this-> gravedad=0.1;
    timerBalon=new QTimer(this);
    connect(timerBalon, &QTimer::timeout, this, &personaje::moveBalon);
    timerBalon->start(20);

}
void personaje::moveBalon(){
    vybalon+=gravedad;
    float newX=x()+vxbalon;
    float newY=y()+vybalon;
    if (newY>450){
        newY=450;
        vxbalon=0;
        vybalon=0;
    }
    qDebug() << "X:" << newX << "Y:" << newY;
    if(newX >= 1000){
        vxbalon = -4;
    }
    if(newX <= 630){
        vxbalon = 4;
    }
    setPos(newX,newY);
}
void personaje::rebotarConApolo(){
    vxbalon=5;
    vybalon=-4;
}
void personaje:: reinicarVelocidad(){
    vxbalon=-2;
    vybalon=2;
    gravedad=0.4;
}
