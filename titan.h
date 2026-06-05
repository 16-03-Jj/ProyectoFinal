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

    // Titán golpea más duro que Apolo
    float getFuerzaX() const override { return 10.0f; }
    float getFuerzaY() const override { return 12.0f; }

protected:
    void actualizar() override;  // aquí vive la lógica autónoma

private:
    balon *balonRef;             // referencia al balón para seguirlo
    QVector<QPixmap> sprites;

    // Estados del agente
    enum EstadoTitan {
        IDLE,        // esperando
        PERSEGUIR,   // moverse hacia el balón
        SALTAR,      // saltar para golpear
        RETROCEDER   // volver al centro de su campo
    };

    EstadoTitan estado;
    float centroX;   // posición de reposo del Titán

    void decidirAccion();        // máquina de estados
    void perseguirBalon();
    void retrocederAlCentro();
};

#endif // TITAN_H
