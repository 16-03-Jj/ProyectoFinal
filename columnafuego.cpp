#include "columnaFuego.h"
#include <QtMath>

columnaFuego::columnaFuego(QGraphicsView *view,
                           const QRectF &sceneBounds,
                           float posX, float posY,
                           QObject *parent)
    : personaje(view, QPixmap(":/columnaFuego.png"), sceneBounds, parent)
{
    // Física oscilatoria parametrizable
    amplitud   = 20.0f;   // sube y baja 20px
    frecuencia = 0.05f;   // velocidad de oscilación
    tiempo     = 0.0f;
    yBase      = posY;
    frameActual = 0;

    // Sprites — reemplaza con los tuyos
    frames.append(QPixmap(":/columnaFuego.png"));
    frames.append(QPixmap(":/columnaFuego.png"));
    frames.append(QPixmap(":/columnaFuego.png"));

    setPos(posX, posY);
    timer = nullptr;
}

void columnaFuego::iniciarMovimiento()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &columnaFuego::animar);
    timer->start(20);
}

void columnaFuego::detener()
{
    if(timer) timer->stop();
}

void columnaFuego::animar()
{
    // Física oscilatoria: y(t) = yBase + A * sin(w * t)
    tiempo += 1.0f;
    float newY = yBase + amplitud * qSin(frecuencia * tiempo);
    setPos(x(), newY);

    // Animación de frames
    frameActual = (frameActual + 1) % frames.size();
    setPixmap(frames[frameActual]);
}
