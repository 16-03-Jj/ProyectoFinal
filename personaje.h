#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QTimer>

class personaje : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit personaje(QGraphicsView *view ,const QPixmap pixmapPlayer, const QRectF sceneBounds, QObject *parent = nullptr);

signals:

private:
    QPixmap pixmapPlayer;
    QPixmap pixmapMalla;
    QPixmap pixmapBalon;
    QRectF sceneBounds;
    QGraphicsView *view;
    float vxbalon;
    float vybalon;
    float gravedad;
    QTimer *timerBalon;
public slots:
    void moveBalon();
    void iniciarMovimiento();
    void rebotarConApolo();
    void reinicarVelocidad();

};

#endif // PERSONAJE_H
