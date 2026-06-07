#include "cronos.h"

cronos::cronos(QGraphicsView *view,
               const QRectF &sceneBounds,
               balon *balonRef,
               float velocidad,
               QObject *parent)
    : titan(view, sceneBounds, balonRef, parent)
{
    velocidadExtra      = velocidad;
    velocidadHorizontal = velocidad * 0.5f;
    fuerzaSalto         = 8.0f;
    spritesCronos.append(QPixmap(":/cronosEstatico.png"));
    spritesCronos.append(QPixmap(":/cronosSaltando.png"));
    spritesCronos.append(QPixmap(":/cronosSaltando.png"));
    setPixmap(spritesCronos[0]);

}

void cronos::decidirAccion()
{
    if(!balonRef) return;
    float balonX  = balonRef->x();
    float balonY  = balonRef->y();
    float cronosX = x();
    float cronosY = y();

    // En cenital: Cronos está arriba, su campo es Y < mitad de escena
    bool balonEnSuCampo = (balonY < sceneBounds.height() / 2.0f - 10.0f);
    bool balonCercaEnX  = (qAbs(balonX - cronosX) < 80.0f);
    bool balonCercaEnY  = (qAbs(balonY - cronosY) < 80.0f);

    if(balonEnSuCampo){
        if(balonCercaEnX && balonCercaEnY){
            estado = SALTAR;
        } else {
            estado = PERSEGUIR;
        }
    } else {
        estado = RETROCEDER;
    }
}

void cronos::actualizar()
{
    decidirAccion();

    switch(estado){
    case PERSEGUIR:
        perseguirBalon();
        break;
    case SALTAR:
        banIzq    = false;
        banDer    = false;
        banSaltar = true;
        enElAire  = false;
        break;
    case RETROCEDER:
        retrocederAlCentro();
        break;
    case IDLE:
    default:
        banIzq = false;
        banDer = false;
        break;
    }

    personajeMovil::actualizar();

    if(enElAire){
        setPixmap(spritesCronos[2]);
    } else if(banIzq || banDer){
        setPixmap(spritesCronos[1]);
    } else {
        setPixmap(spritesCronos[0]);
    }
}

void cronos::perseguirBalon()
{
    if(!balonRef) return;
    float diffX = balonRef->x() - x();
    float diffY = balonRef->y() - y();

    // Movimiento horizontal
    if(qAbs(diffX) > 10.0f){
        if(diffX > 0){ banIzq = false; banDer = true;  }
        else         { banDer = false; banIzq = true;  }
    } else {
        banIzq = false; banDer = false;
    }

    // Movimiento vertical (solo en cenital)
    if(modoCenital){
        if(qAbs(diffY) > 10.0f){
            if(diffY > 0){ banArriba = false; banAbajo = true;  }
            else         { banAbajo  = false; banArriba = true; }
        } else {
            banArriba = false; banAbajo = false;
        }
    }
}
