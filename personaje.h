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
    explicit personaje(QGraphicsView *view,
                       const QPixmap &pixmapPlayer,
                       const QRectF &sceneBounds,
                       QObject *parent = nullptr);
    virtual void iniciarMovimiento() = 0;
    virtual void detener() = 0;

    // Getters/setters comunes
    inline QRectF getSceneBounds() const { return sceneBounds; }
    inline QGraphicsView* getView() const { return view; }

protected:
    QRectF sceneBounds;
    QGraphicsView *view;
};

#endif // PERSONAJE_H
