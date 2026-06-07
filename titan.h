#ifndef TITAN_H
#define TITAN_H

#include "personajeMovil.h"
#include "balon.h"

class titan : public personajeMovil
{
    Q_OBJECT
public:
    explicit titan(QGraphicsView *view,
                   const QRectF &sceneBounds,
                   balon *balonRef,
                   QObject *parent = nullptr);

    float getFuerzaX() const override { return 5.0f; }
    float getFuerzaY() const override { return 6.0f; }

protected:
    void actualizar() override;
    virtual void decidirAccion();
    virtual void perseguirBalon();
    void retrocederAlCentro();

    balon *balonRef;
    QVector<QPixmap> sprites;
    float centroX;

    enum EstadoTitan {
        IDLE,
        PERSEGUIR,
        SALTAR,
        RETROCEDER
    };

    EstadoTitan estado;
};

#endif // TITAN_H
