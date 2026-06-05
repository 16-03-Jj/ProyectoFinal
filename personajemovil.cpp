#include "personajeMovil.h"

personajeMovil::personajeMovil(QGraphicsView *view,
                               const QPixmap &pixmap,
                               const QRectF &sceneBounds,
                               float limIzq, float limDer,
                               float limArriba, float limAbajo,
                               QObject *parent)
    : personaje(view, pixmap, sceneBounds, parent),
    limIzq(limIzq), limDer(limDer),
    limArriba(limArriba), limAbajo(limAbajo)
{
    vy                 = 0.0f;
    gravedad           = 0.6f;
    fuerzaSalto        = 12.0f;   // subclases pueden sobreescribir
    velocidadHorizontal= 6.0f;
    banIzq    = false;
    banDer    = false;
    banSaltar = false;
    enElAire  = false;
    timer     = nullptr;
}

void personajeMovil::iniciarMovimiento()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &personajeMovil::actualizar);
    timer->start(20);
}

void personajeMovil::detener()
{
    if(timer) timer->stop();
}

bool personajeMovil::checkBounds(float newX, float newY)
{
    if(newX < limIzq)   return false;
    if(newX > limDer)   return false;
    if(newY < limArriba) return false;
    if(newY > limAbajo)  return false;
    return true;
}

void personajeMovil::aplicarSaltoYGravedad()
{
    if(banSaltar && !enElAire){
        vy = -fuerzaSalto;
        enElAire  = true;
        banSaltar = false;
    }

    if(enElAire){
        vy += gravedad;
        float newY = y() + vy;

        // Llegó al piso
        if(newY >= limAbajo){
            newY     = limAbajo;
            vy       = 0.0f;
            enElAire = false;
        }

        // Techo
        if(newY <= limArriba){
            newY = limArriba;
            vy   = qAbs(vy); // rebota hacia abajo
        }

        setPos(x(), newY);
    }
}

void personajeMovil::aplicarMovimientoHorizontal()
{
    if(banIzq){
        float newX = x() - velocidadHorizontal;
        if(checkBounds(newX, y()))
            setPos(newX, y());
    }
    if(banDer){
        float newX = x() + velocidadHorizontal;
        if(checkBounds(newX, y()))
            setPos(newX, y());
    }
}

void personajeMovil::actualizar()
{
    aplicarMovimientoHorizontal();
    aplicarSaltoYGravedad();
}
