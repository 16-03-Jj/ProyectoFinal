#include "personaje.h"

personaje::personaje(QGraphicsView *view,
                     const QPixmap &pixmapPlayer,
                     const QRectF &sceneBounds,
                     QObject *parent)
    : QObject(parent),
    QGraphicsPixmapItem(),
    sceneBounds(sceneBounds),
    view(view)
{
    setPixmap(pixmapPlayer);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformationMode(Qt::SmoothTransformation);
}
