#ifndef APOLO_H
#define APOLO_H

#include "personajeMovil.h"

class apolo : public personajeMovil
{
    Q_OBJECT
public:
    explicit apolo(QGraphicsView *view,
                   const QRectF &sceneBounds,
                   QObject *parent = nullptr);

    // Define con qué fuerza golpea Apolo al balón
    float getFuerzaX() const override { return 6.0f; }
    float getFuerzaY() const override { return 8.0f; }

protected:
    void actualizar() override;  // animación de sprites

private:
    QVector<QPixmap> sprites;
    int frameActual;
    int contadorFrames;
};

#endif // APOLO_H
