#ifndef PERSONAJEMOVILES_H
#define PERSONAJEMOVILES_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include <QObject>
#include <string>
using namespace std;
class personajesMoviles : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit personajesMoviles(QGraphicsView *view, QRectF sceneBounds, QObject *parent, int LAI,int LAD,int LAA, int LAS, bool esApolo);
    //inline void moveUp(){setPos(x(),y()-10);}
   //inline void moveDown(){setPos(x(),y()+10);}
   bool checkBounds(int newX, int newY);

   //Banderas de movimiento
   inline void setBanUp(){banUp=true;}
   inline void setBanDown(){banDown=true;}
   inline void setBanLeft(){banLeft=true;}
   inline void setBanRight(){banRight=true;}
   inline void resetBanUp(){banUp=false;}
   inline void resetBanDown(){banDown=false;}
   inline void resetBanLeft(){banLeft=false;}
   inline void resetBanRight(){banRight=false;}
   bool enElAire;
   inline bool getEnElAire(){ return enElAire; }
   inline void setEnElAire(bool val){ enElAire = val; }
private:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *bg1;
    QRectF sceneBounds;
    QGraphicsView *view;
    vector<string> apolo;
    vector <string> titanes;
    QPixmap Apolo;
    QPixmap Titan;
    bool banUp, banDown,banLeft, banRight;
    QTimer *timer;
    int LAI,LAD,LAA,LAS;
    bool esApolo;
signals:
public slots:
    void moveLeft();
    void moveRight();
   // void moveDown();
    void moveUp();

};

#endif // PERSONAJEMOVILES_H
