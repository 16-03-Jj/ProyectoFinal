#include "personajemoviles.h"
#include <QDebug>
personajesMoviles::personajesMoviles(QGraphicsView *view, QRectF sceneBounds, QObject *parent, int LAI, int LAD, int LAA, int LAS, bool esApolo)
    : QObject{parent}, sceneBounds{sceneBounds}, view{view}
{
    this->LAI=370;
    this->LAD=630;
    this->LAA=420;
    this->LAS=385;
    enElAire = false;

    apolo.push_back(":/ApoloEstatico.png");
    apolo.push_back(":/ApoloCamina.png");
    apolo.push_back(":/ApoloCorre.png");
    apolo.push_back(":/ApoloSalta.png");
    titanes.push_back(":/TitanEstatico.png");
    titanes.push_back(":/TitanCamina.png");
    titanes.push_back(":/TitanSaltando.png");
    if(esApolo){
        setPixmap(QPixmap(apolo[0].c_str()));
    } else {
        setPixmap(QPixmap(titanes[2].c_str()));
    }
    //Estado inicial de las banderas
    banUp=false;
    banDown=false;
    banLeft=false;
    banRight=false;
    timer= new QTimer(this);
    connect(timer, &QTimer::timeout, this, &personajesMoviles::moveLeft);
    connect(timer, &QTimer::timeout, this, &personajesMoviles::moveRight);
    connect(timer, &QTimer::timeout, this, &personajesMoviles::moveUp);
    //connect(timer, &QTimer::timeout, this, &personajesMoviles::moveDown);


    timer->start(20);
}
bool personajesMoviles::checkBounds(int newX, int newY){
    if(newX<LAI){return false;}
    if(newX>LAD){return false;}
    if(newY>LAA){return false;}
    if(newY<LAS){return false;}
    else{return true;}

}
void personajesMoviles::moveLeft(){
    if(banLeft){
        int  newX=x()-5;
        if(checkBounds(newX,y())){
            setPos(newX,y());
        }

        //qDebug() << "X:" << x() << "Y:" << y();
    }
}
 void personajesMoviles::moveRight(){
     if(banRight){
         int newX=x()+5;
         if(checkBounds(newX,y())){
             setPos(newX,y());
         }
         //qDebug() << "X:" << x() << "Y:" << y();
     }

}
 void personajesMoviles::moveUp(){
     if(banUp){
         int newY = y()-5;
         if(checkBounds(x(), newY)){
             setPos(x(), newY);
         } else {
             banUp = false;
             banDown = true;
         }
     }

     if(banDown){
         int newY = y()+5;
         if(checkBounds(x(), newY)){
             setPos(x(), newY);
         } else {
             banDown = false;
             enElAire = false;
         }
     }
 }
         //qDebug() << "X:" << x() << "Y:" << y();



 /*void personajesMoviles::moveDown(){
     if(banDown){
         int newY=y()+5;
         if(checkBounds(x(),newY)){
         setPos(x(),newY);
         }
     }

 }
*/


