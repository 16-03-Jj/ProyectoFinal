#include "apolo.h"

apolo::apolo(QGraphicsView *view,
             const QRectF &sceneBounds,
             QObject *parent)
    : personajeMovil(view,
                     QPixmap(":/ApoloEstatico.png"),
                     sceneBounds,
                     370.0f,   // limIzq  — campo lateral nivel 1
                     630.0f,   // limDer
                     385.0f,   // limArriba
                     420.0f,   // limAbajo
                     parent)
{
    fuerzaSalto          = 14.0f;
    velocidadHorizontal  =  6.0f;

    sprites.append(QPixmap(":/ApoloEstatico.png"));
    sprites.append(QPixmap(":/ApoloCamina.png"));
    sprites.append(QPixmap(":/ApoloCorre.png"));
    sprites.append(QPixmap(":/ApoloSalta.png"));

    frameActual    = 0;
    contadorFrames = 0;

    iniciarMovimiento();
}

void apolo::actualizar()
{
    personajeMovil::actualizar();

    contadorFrames++;
    if(contadorFrames >= 5){
        contadorFrames = 0;

        if(enElAire){
            setPixmap(sprites[3]);
        } else if(banIzq || banDer){
            frameActual = (frameActual == 1) ? 2 : 1;
            setPixmap(sprites[frameActual]);
        } else {
            setPixmap(sprites[0]);
        }
    }
}
