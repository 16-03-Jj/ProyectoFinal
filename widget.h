#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include "personaje.h"
#include "balon.h"
#include "apolo.h"
#include "titan.h"
#include "cronos.h"
#include "columnaFuego.h"
#include <QVector>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void keyPressEvent(QKeyEvent *event)   override;
    void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void actualizarJuego();
    void actualizarMarcador();
    void reiniciarBalon();
    void tickTemporizador();
    void mostrarMenu();
    void iniciarNivel1();
    void iniciarNivel2();
    void limpiarEscena();
    void iniciarNivel1_1();
    void iniciarOtraEscena();
    void iniciarNivel2_2();
    void tickTemporizadorCenital();
private:
    Ui::Widget *ui;
    QGraphicsScene       *scene;
    QGraphicsPixmapItem  *bg1;
    balon  *pelota;
    apolo  *aPolo;
    titan  *tItan;
    QGraphicsPixmapItem *malla;
    QGraphicsPixmapItem *nube;
    QTimer *timerJuego;
    QTimer *timerCuentaRegresiva;
    QLabel *labelPuntos;
    QLabel *labelTiempo;
    int puntosApolo;
    int puntosTitan;
    int segundosRestantes;
    enum EstadoJuego { MENU, NIVEL1, NIVEL2, NIVEL3,NIVEL4  };
    EstadoJuego estadoActual;
    bool colisionConApolo;
    bool colisionConTitan;
    QLabel      *labelTitulo;
    QPushButton *btnNivel1;
    QPushButton *btnNivel2;
    QPushButton *btnNivel1_1;
    QPushButton *btnNivel2_2;
    void setupEscena();
    void setupMenu();
    void ocultarMenu();
    void setupHUD();
    cronos *cRonos;
    QVector<columnaFuego*> columnas;
};
#endif // WIDGET_H
