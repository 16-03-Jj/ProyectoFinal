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
    void reiniciarPosicionCenital();   // para niveles 3 y 4

    void rebotarConJugador(float dirX, float fuerzaX, float fuerzaY);
    void rebotarConMalla(float direccion);

    // Rebote especial al tocar barra — sale disparado hacia abajo más rápido
    void rebotarConBarra();

    // Modo cenital: sin gravedad, movimiento libre en X e Y
    void setModoCenital(bool val) { modoCenital = val; }

    inline float getVx() const { return vx; }
    inline float getVy() const { return vy; }

private:
    float vx, vy, gravedad;
    bool  modoCenital;
    QTimer *timer;

public slots:
    void mover();
};

#endif // BALON_H
