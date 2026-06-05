#include "balon.h"

balon::balon(QGraphicsView *view,
             const QPixmap &pixmap,
             const QRectF &sceneBounds,
             QObject *parent)
    : personaje(view, pixmap, sceneBounds, parent)
{
    vx = -5.0f;
    vy =  2.0f;
    gravedad = 0.3f;
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
    // Siempre sale hacia el lado de Apolo para que el juego sea difícil
    setPos(730, 300);
    vx = -4.0f;
    vy =  1.5f;
    gravedad = 0.3f;
}

// dirX: -1 viene de izquierda, +1 viene de derecha
// fuerzaX y fuerzaY las define quien golpea (Apolo o Titán)
void balon::rebotarConJugador(float dirX, float fuerzaX, float fuerzaY)
{
    vx = dirX * fuerzaX;
    vy = -fuerzaY;   // siempre sube al golpear
}

void balon::rebotarConMalla(float direccion)
{
    // Invierte X con la dirección indicada, conserva algo de Y
    vx = direccion * qAbs(vx);
    vy = -qAbs(vy) * 0.5f;  // sube un poco al rebotar en la malla
}

void balon::mover()
{
    // Aplicar gravedad
    vy += gravedad;

    float newX = x() + vx;
    float newY = y() + vy;

    // Pared izquierda
    if(newX <= 0){
        newX = 0;
        vx = qAbs(vx);  // rebota hacia la derecha
    }

    // Pared derecha
    if(newX >= sceneBounds.width() - boundingRect().width() * scale()){
        newX = sceneBounds.width() - boundingRect().width() * scale();
        vx = -qAbs(vx); // rebota hacia la izquierda
    }

    // Techo
    if(newY <= 0){
        newY = 0;
        vy = qAbs(vy);  // rebota hacia abajo
    }

    // Piso — no detiene el balón, eso lo maneja Widget como punto
    if(newY >= sceneBounds.height() - 50){
        newY = sceneBounds.height() - 50;
        vy = 0;
        vx = 0;
    }

    setPos(newX, newY);
}


