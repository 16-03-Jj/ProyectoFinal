#ifndef BALON_H
#define BALON_H

#include "personaje.h"
#include <QTimer>

class balon : public personaje
{
    Q_OBJECT
public:
    explicit balon(QGraphicsView *view,
                   const QPixmap &pixmap,
                   const QRectF &sceneBounds,
                   QObject *parent = nullptr);

    void iniciarMovimiento() override;
    void detener() override;
    void reiniciarPosicion();

    // Rebotes
    void rebotarConJugador(float dirX, float fuerzaX, float fuerzaY);
    void rebotarConMalla(float direccion);

    inline float getVx() const { return vx; }
    inline float getVy() const { return vy; }

private:
    float vx, vy, gravedad;
    QTimer *timer;

public slots:
    void mover();
};

#endif // BALON_H
