#ifndef CRONOS_H
#define CRONOS_H

#include "titan.h"

class cronos : public titan
{
    Q_OBJECT
public:
    explicit cronos(QGraphicsView *view,
                    const QRectF &sceneBounds,
                    balon *balonRef,
                    float velocidad,
                    QObject *parent = nullptr);

    float getFuerzaX() const override { return 5.0f; }
    float getFuerzaY() const override { return 5.0f; }

protected:
    void actualizar() override;
    void decidirAccion() override;
    void perseguirBalon() override;
private:
    QVector<QPixmap> spritesCronos;
    float velocidadExtra;
};

#endif // CRONOS_H
