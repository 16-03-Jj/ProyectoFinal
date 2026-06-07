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

    bool checkBounds(float newX, float newY);

    inline void setBanIzq()     { banIzq    = true;  }
    inline void setBanDer()     { banDer    = true;  }
    inline void setBanSaltar()  { if(!enElAire){ banSaltar = true; enElAire = true; } }
    inline void resetBanIzq()   { banIzq    = false; }
    inline void resetBanDer()   { banDer    = false; }
    inline void resetBanSaltar(){ banSaltar = false; }
    inline bool getEnElAire()   { return enElAire; }
    inline void setBanArriba()    { banArriba  = true;  }
    inline void setBanAbajo()     { banAbajo   = true;  }
    inline void resetBanArriba()  { banArriba  = false; }
    inline void resetBanAbajo()   { banAbajo   = false; }
    inline void setModoCenital(bool val) { modoCenital = val; }


    // Setter de límites para ajustar según nivel (cenital vs lateral)
    inline void setLimites(float izq, float der, float arriba, float abajo){
        limIzq    = izq;
        limDer    = der;
        limArriba = arriba;
        limAbajo  = abajo;
    }

    virtual float getFuerzaX() const = 0;
    virtual float getFuerzaY() const = 0;

protected:
    float limIzq, limDer, limArriba, limAbajo;
    float vy;
    float gravedad;
    float fuerzaSalto;
    float velocidadHorizontal;
    bool  banIzq, banDer, banSaltar;
    bool  enElAire;
    QTimer *timer;
    bool banArriba, banAbajo;
    bool modoCenital;
protected slots:
    virtual void actualizar();

private:
    void aplicarSaltoYGravedad();
    void aplicarMovimientoHorizontal();
};

#endif // PERSONAJEMOVIL_H
