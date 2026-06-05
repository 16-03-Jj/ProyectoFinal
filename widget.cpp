#include "widget.h"
#include "ui_widget.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //configuración
    scene=new QGraphicsScene(ui->graphicsView->rect(),this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    //añadir fondo de pantalla
    QPixmap originalImage(":/backgroundOne.png");
    bg1=new QGraphicsPixmapItem(originalImage);
    bg1->setPos(0,0);
    scene->addItem(bg1);
    //Timer para mover fondo
    bg1Timer = new QTimer(this);

    connect(bg1Timer,&QTimer::timeout,this, &Widget::bg1Move);
    bg1Timer->start(20);

    //agregar nube

    QPixmap pixmapPlayer(":/laPropia.png");
    nube= new personaje(ui->graphicsView,pixmapPlayer,scene->sceneRect(),this);
    // ajustar tamaño
    nube->setScale(0.75);
    nube->setPos(200,250);
    nube->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(nube);
//agregar malla
    QPixmap pixmapMalla(":/malla.png");
    malla= new personaje(ui->graphicsView,pixmapMalla,scene->sceneRect(),this);
    malla->setScale(0.1);
    malla->setPos(680,363);
    malla->setTransformationMode(Qt:: SmoothTransformation);
    scene->addItem(malla);
// agregar balon
    QPixmap pixmapBalon(":/balon.png");
    balon=new personaje(ui->graphicsView,pixmapBalon,scene->sceneRect(),this);
    balon->setScale(0.05);
    balon->setPos(730,350);
    balon->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(balon);
    balon->iniciarMovimiento();
//agregar apolo
  aPolo = new personajesMoviles(ui->graphicsView, scene->sceneRect(), this, 370, 630, 420,385,true);
    aPolo->setScale(0.06);
    aPolo->setPos(610,420);
    aPolo->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(aPolo);
// agregar titan
    tItan = new personajesMoviles(ui->graphicsView, scene->sceneRect(), this, 0, 0, 0, 0,false);
    tItan->setScale(0.15);
    tItan->setPos(900,353);
    tItan->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(tItan);
//colsion balon
    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
    timerJuego->start(20);
    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
   colisionConApolo = false;
//puntos del partido
   puntosApolo=0;
   puntosTitan=0;
   labelPuntos=new QLabel("Apolo:0| titan:0",this);
   labelPuntos->setGeometry(600,10,300,30);
   labelPuntos->setStyleSheet("color: white;font-size: 16px; font-weight:bold;");


}
void Widget::actualizarJuego(){
    if(balon->collidesWithItem(aPolo) && !colisionConApolo){
        colisionConApolo = true;
        qDebug() << "Colisión con Apolo!";
        balon->rebotarConApolo();
    }
    if(!balon->collidesWithItem(aPolo)){
        colisionConApolo = false;
    }
    if(balon->y()>=420&& balon->x()<700){
        puntosTitan++;
        actualizarMarcador();
        reiniciarBalon();
    }
    if(balon->y()>=420 && balon->x()>700){
        puntosApolo++;
        actualizarMarcador();
        reiniciarBalon();

    }
}
void Widget::actualizarMarcador(){
    labelPuntos->setText("Apolo: "+QString::number(puntosApolo)+"| titan"+QString::number(puntosTitan));
}
void Widget:: reiniciarBalon(){
    balon->setPos(730,350);
    balon->reinicarVelocidad();
}
Widget::~Widget()
{
    delete ui;
}
void Widget::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        if(!aPolo->getEnElAire()){
            aPolo->setBanUp();
            aPolo->setEnElAire(true);
        }
    }

    else if(event->key()==Qt::Key_S){
    aPolo->setBanDown();
    }
    else if(event->key()==Qt::Key_A){
        aPolo->setBanLeft();
    }
    else if(event->key()==Qt::Key_D){
        aPolo->setBanRight();
    }
}
void Widget::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W){
        aPolo->resetBanUp();
    }
    else if(event->key()==Qt::Key_S){
        aPolo->resetBanDown();
    }
    else if(event->key()==Qt::Key_A){
        aPolo->resetBanLeft();
    }
    else if(event->key()==Qt::Key_D){
        aPolo->resetBanRight();
    }

}
void Widget::bg1Move(){


}
