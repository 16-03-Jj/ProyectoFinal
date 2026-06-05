#ifndef WIDGET_H
#define WIDGET_H
#include "personaje.h"
#include "personajemoviles.h"
#include <QLabel>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <Qtimer>
#include <QkeyEvent>
#include "personaje.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //funciones propias
    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void bg1Move();
    void actualizarJuego();
    void actualizarMarcador();
    void reiniciarBalon();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *bg1;
    QTimer *bg1Timer;
    personaje *nube;
    personaje *malla;
    personaje *balon;
    personajesMoviles *aPolo;
    personajesMoviles *tItan;
    QTimer *timerJuego;
    bool colisionConApolo;
    int puntosApolo;
    int puntosTitan;
    QLabel *labelPuntos;

};
#endif // WIDGET_H
