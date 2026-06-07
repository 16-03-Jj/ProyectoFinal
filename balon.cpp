#include "balon.h"

balon::balon(QGraphicsView *view,
             const QPixmap &pixmap,
             const QRectF &sceneBounds,
             QObject *parent)
    : personaje(view, pixmap, sceneBounds, parent)
{
    vx = -5.0f;
    vy =  2.0f;
    gravedad    = 0.3f;
    modoCenital = false;
    timer = nullptr;
    setPos(730, 350);
}

void balon::iniciarMovimiento()
{
    vx = -5.0f;
    vy =  2.0f;
    gravedad = 0.3f;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &balon::mover);
    timer->start(20);
}

void balon::detener()
{
    if(timer) timer->stop();
}

void balon::reiniciarPosicion()
{
    setPos(730, 300);
    vx = -5.0f;
    vy =  2.0f;
    gravedad = 0.3f;
}

void balon::reiniciarPosicionCenital()
{
    setPos(550, 340);
    vx =  1.5f;   // antes 3.0f
    vy =  2.0f;   // antes 4.0f
    gravedad = 0.0f;
}

void balon::rebotarConJugador(float dirX, float fuerzaX, float fuerzaY)
{
    vx = dirX * fuerzaX;
    vy = -fuerzaY;

}

void balon::rebotarConMalla(float direccion)
{
    vx = direccion * qAbs(vx);
    vy = -qAbs(vy) * 0.5f;
}

// Al tocar barra de Cronos: invierte Y y aumenta velocidad hacia campo de Apolo
void balon::rebotarConBarra()
{
    vy =  qAbs(vy) * 1.2f;   // sale disparado hacia abajo (campo Apolo)
    vx = vx * 0.8f;           // pierde un poco de X para ser más predecible
    if(vy > 6.0f) vy = 6.0f;
}

void balon::mover()
{
    if(vx >  12.0f) vx =  12.0f;
    if(vx < -12.0f) vx = -12.0f;
    if(vy < -12.0f) vy = -12.0f;
    if(vy >  12.0f) vy =  12.0f;

    if(!modoCenital) vy += gravedad;

    float newX = x() + vx;
    float newY = y() + vy;

    if(modoCenital){
        if(newX <= 170){ newX = 170; vx =  qAbs(vx); }
        if(newX >= 600){ newX = 600; vx = -qAbs(vx); }
        if(newY <= 160){ newY = 160; vy =  qAbs(vy); }
        if(newY >= 530){ newY = 530; vy = -qAbs(vy); }
    } else {
        float W = sceneBounds.width();
        if(newX <= 0)   { newX = 0;   vx =  qAbs(vx); }
        if(newX >= W)   { newX = W;   vx = -qAbs(vx); }
        if(newY <= 0)   { newY = 0;   vy =  qAbs(vy); }
        if(newY >= 420) { newY = 420; vx = 0; vy = 0; }
    }

    setPos(newX, newY);
}

