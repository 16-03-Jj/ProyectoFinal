#include "apolo.h"

apolo::apolo(QGraphicsView *view,
             const QRectF &sceneBounds,
             QObject *parent)
    : personajeMovil(view,
                     QPixmap(":/ApoloEstatico.png"),
                     sceneBounds,
                     370.0f,   // limIzq
                     630.0f,   // limDer
                     385.0f,   // limArriba  (techo del salto)
                     420.0f,   // limAbajo   (piso)
                     parent)
{
    // Apolo salta alto pero no golpea tan fuerte como el Titán
    fuerzaSalto         = 14.0f;
    velocidadHorizontal =  6.0f;

    // Cargar sprites
    sprites.append(QPixmap(":/ApoloEstatico.png"));
    sprites.append(QPixmap(":/ApoloCamina.png"));
    sprites.append(QPixmap(":/ApoloCorre.png"));
    sprites.append(QPixmap(":/ApoloSalta.png"));

    frameActual    = 0;
    contadorFrames = 0;

    iniciarMovimiento();
}

void apolo::actualizar()
{
    // Primero ejecuta movimiento base (horizontal + salto/gravedad)
    personajeMovil::actualizar();

    // Animación de sprites según estado
    contadorFrames++;
    if(contadorFrames >= 5){   // cambia frame cada 5 ticks (~100ms)
        contadorFrames = 0;

        if(enElAire){
            setPixmap(sprites[3]);  // ApoloSalta
        } else if(banIzq || banDer){
            frameActual = (frameActual == 1) ? 2 : 1;
            setPixmap(sprites[frameActual]);  // ApoloCamina / ApoloCorre
        } else {
            setPixmap(sprites[0]);  // ApoloEstatico
        }
    }
}
