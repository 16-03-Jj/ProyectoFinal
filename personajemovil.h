#ifndef PERSONAJEMOVIL_H
#define PERSONAJEMOVIL_H

#include "personaje.h"
#include <QTimer>

class personajeMovil : public personaje
{
    Q_OBJECT
public:
    explicit personajeMovil(QGraphicsView *view,
                            const QPixmap &pixmap,
                            const QRectF &sceneBounds,
                            float limIzq, float limDer,
                            float limArriba, float limAbajo,
                            QObject *parent = nullptr);

    void iniciarMovimiento() override;
    void detener() override;

    // Límites
    bool checkBounds(float newX, float newY);

    // Banderas de movimiento (Apolo las usa desde teclado)
    inline void setBanIzq()    { banIzq   = true;  }
    inline void setBanDer()    { banDer   = true;  }
    inline void setBanSaltar() { if(!enElAire){ banSaltar = true; enElAire = true; } }
    inline void resetBanIzq()  { banIzq   = false; }
    inline void resetBanDer()  { banDer   = false; }
    inline void resetBanSaltar(){ banSaltar = false; }

    inline bool getEnElAire()  { return enElAire;  }

    // Fuerza con la que golpea al balón (Titán la tendrá mayor)
    virtual float getFuerzaX() const = 0;
    virtual float getFuerzaY() const = 0;

protected:
    float limIzq, limDer, limArriba, limAbajo;
    float vy;              // velocidad vertical para salto
    float gravedad;
    float fuerzaSalto;     // qué tan alto salta
    float velocidadHorizontal;
    bool  banIzq, banDer, banSaltar;
    bool  enElAire;
    QTimer *timer;

protected slots:
    virtual void actualizar();   // el timer llama esto cada tick

private:
    void aplicarSaltoYGravedad();
    void aplicarMovimientoHorizontal();
};

#endif // PERSONAJEMOVIL_H
