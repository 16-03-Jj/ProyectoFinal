#include "titan.h"

titan::titan(QGraphicsView *view,
             const QRectF &sceneBounds,
             balon *balonRef,
             QObject *parent)
    : personajeMovil(view,
                     QPixmap(":/TitanEstatico.png"),
                     sceneBounds,
                     700.0f,
                     950.0f,
                     340.0f,
                     420.0f,
                     parent),
    balonRef(balonRef)
{
    fuerzaSalto         = 18.0f;
    velocidadHorizontal =  4.0f;

    sprites.append(QPixmap(":/TitanEstatico.png"));
    sprites.append(QPixmap(":/TitanCamina.png"));
    sprites.append(QPixmap(":/TitanSaltando.png"));

    estado  = IDLE;
    centroX = 830.0f;
}

void titan::decidirAccion()
{
    if(!balonRef) return;

    float balonX = balonRef->x();
    float balonY = balonRef->y();
    float titanX = x();
    float titanY = y();

    bool balonEnSuCampo = (balonX > 680.0f);
    bool balonCercaEnY  = (balonY < titanY - 30.0f && balonY > limArriba);
    bool balonCercaEnX  = (qAbs(balonX - titanX) < 80.0f);

    if(balonEnSuCampo){
        if(balonCercaEnX && balonCercaEnY && !enElAire){
            estado = SALTAR;
        } else {
            estado = PERSEGUIR;
        }
    } else {
        estado = RETROCEDER;
    }
}

void titan::perseguirBalon()
{
    float diff = balonRef->x() - x();

    if(qAbs(diff) > 10.0f){
        if(diff > 0){ banIzq = false; banDer = true;  }
        else        { banDer = false; banIzq = true;  }
    } else {
        banIzq = false;
        banDer = false;
    }
}

void titan::retrocederAlCentro()
{
    float diff = centroX - x();

    if(qAbs(diff) > 10.0f){
        if(diff > 0){ banIzq = false; banDer = true;  }
        else        { banDer = false; banIzq = true;  }
    } else {
        banIzq = false;
        banDer = false;
    }
}

void titan::actualizar()
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
        setPixmap(sprites[2]);
    } else if(banIzq || banDer){
        setPixmap(sprites[1]);
    } else {
        setPixmap(sprites[0]);
    }
}
