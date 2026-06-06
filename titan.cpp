#include "titan.h"

titan::titan(QGraphicsView *view,
             const QRectF &sceneBounds,
             balon *balonRef,
             QObject *parent)
    : personajeMovil(view,
                     QPixmap(":/TitanEstatico.png"),
                     sceneBounds,
                     700.0f,
                     950.0f,
                     340.0f,
                     420.0f,
                     parent),
    balonRef(balonRef)
{
    // Titán es más lento moviéndose pero golpea mucho más fuerte
    fuerzaSalto         = 18.0f;
    velocidadHorizontal =  4.0f;

    sprites.append(QPixmap(":/TitanEstatico.png"));
    sprites.append(QPixmap(":/TitanCamina.png"));
    sprites.append(QPixmap(":/TitanSaltando.png"));

    estado  = IDLE;
    centroX = 830.0f;  // centro del campo del Titán

    iniciarMovimiento();
}

void titan::decidirAccion()
{
    if(!balonRef) return;

    float balonX = balonRef->x();
    float balonY = balonRef->y();
    float titanX = x();
    float titanY = y();

    // El balón está en el campo del Titán (derecha de la malla)
    bool balonEnSuCampo = (balonX > 680.0f);

    // El balón está bajando y cerca verticalmente — momento de saltar
    bool balonCercaEnY  = (balonY < titanY - 30.0f && balonY > limArriba);
    bool balonCercaEnX  = (qAbs(balonX - titanX) < 80.0f);

    if(balonEnSuCampo){
        if(balonCercaEnX && balonCercaEnY && !enElAire){
            estado = SALTAR;
        } else {
            estado = PERSEGUIR;
        }
    } else {
        // El balón está en el campo de Apolo — vuelve al centro
        estado = RETROCEDER;
    }
}

void titan::perseguirBalon()
{
    float balonX = balonRef->x();
    float titanX = x();
    float diff   = balonX - titanX;

    // Margen de tolerancia para no vibrar en el mismo punto
    if(qAbs(diff) > 10.0f){
        if(diff > 0){
            banIzq = false;
            banDer = true;
        } else {
            banDer = false;
            banIzq = true;
        }
    } else {
        banIzq = false;
        banDer = false;
    }
}

void titan::retrocederAlCentro()
{
    float diff = centroX - x();

    if(qAbs(diff) > 10.0f){
        if(diff > 0){
            banIzq = false;
            banDer = true;
        } else {
            banDer = false;
            banIzq = true;
        }
    } else {
        banIzq = false;
        banDer = false;
    }
}

void titan::actualizar()
{
    // 1. Decidir qué hacer según el estado del juego
    decidirAccion();

    // 2. Ejecutar la acción decidida
    switch(estado){
    case PERSEGUIR:
        perseguirBalon();
        break;

    case SALTAR:
        banIzq    = false;
        banDer    = false;
        banSaltar = true;
        enElAire  = false;  // forzar para que setBanSaltar lo active
        break;

    case RETROCEDER:
        retrocederAlCentro();
        break;

    case IDLE:
    default:
        banIzq = false;
        banDer = false;
        break;
    }

    // 3. Ejecutar movimiento físico base (horizontal + salto + gravedad)
    personajeMovil::actualizar();

    // 4. Animación de sprites
    if(enElAire){
        setPixmap(sprites[2]);  // TitanSaltando
    } else if(banIzq || banDer){
        setPixmap(sprites[1]);  // TitanCamina
    } else {
        setPixmap(sprites[0]);  // TitanEstatico
    }
}
