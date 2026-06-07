#ifndef COLUMNAFUEGO_H
#define COLUMNAFUEGO_H
#include "personaje.h"
#include <QTimer>

class columnaFuego : public personaje
{
    Q_OBJECT
public:
    explicit columnaFuego(QGraphicsView *view,
                          const QRectF &sceneBounds,
                          float posX, float posY,
                          QObject *parent = nullptr);

    void iniciarMovimiento() override;
    void detener() override;

    // Física oscilatoria — la columna sube y baja
    // y(t) = y_base + A * sin(w * t)
    float getAmplitud()   const { return amplitud; }
    float getFrecuencia() const { return frecuencia; }

private:
    QTimer *timer;
    QVector<QPixmap> frames;
    int frameActual;
    float amplitud;     // qué tan alto sube la columna
    float frecuencia;   // qué tan rápido oscila
    float tiempo;       // contador de tiempo para la ecuación
    float yBase;        // posición base Y

public slots:
    void animar();
};
#endif // COLUMNAFUEGO_H
