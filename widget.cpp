#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene                = nullptr;
    bg1                  = nullptr;
    pelota               = nullptr;
    aPolo                = nullptr;
    tItan                = nullptr;
    malla                = nullptr;
    nube                 = nullptr;
    timerJuego           = nullptr;
    timerCuentaRegresiva = nullptr;
    labelPuntos          = nullptr;
    labelTiempo          = nullptr;
    labelTitulo          = nullptr;
    btnNivel1            = nullptr;
    btnNivel2            = nullptr;
    btnNivel1_1          = nullptr;
    btnNivel2_2          = nullptr;
    cRonos               = nullptr;

    colisionConApolo  = false;
    colisionConTitan  = false;
    puntosApolo       = 0;
    puntosTitan       = 0;
    segundosRestantes = 240;
    estadoActual      = MENU;

    setupEscena();
    setupMenu();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setupEscena()
{
    scene = new QGraphicsScene(ui->graphicsView->rect(), this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    QPixmap fondo(":/backgroundOne.png");
    bg1 = new QGraphicsPixmapItem(fondo);
    bg1->setPos(0, 0);
    scene->addItem(bg1);
}

void Widget::setupMenu()
{
    labelTitulo = new QLabel(" APOLO vs LA MITOLOGIA GRIEGA ", this);
    labelTitulo->setAlignment(Qt::AlignCenter);
    labelTitulo->setGeometry(100, 120, 820, 80);
    labelTitulo->setStyleSheet(
        "color: #FFD700;"
        "font-size: 32px;"
        "font-weight: bold;"
        "font-family: 'Georgia';"
        "background-color: rgba(0,0,0,160);"
        "border-radius: 12px;"
        "padding: 10px;"
        );

    btnNivel1 = new QPushButton("Nivel 1 - Apolo resiste 4 minutos", this);
    btnNivel1->setGeometry(300, 250, 420, 60);
    btnNivel1->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(30, 100, 200, 200);"
        "  color: white; font-size: 18px; font-weight: bold;"
        "  border-radius: 10px; border: 2px solid #FFD700;"
        "}"
        "QPushButton:hover { background-color: rgba(60, 140, 255, 220); }"
        );
    connect(btnNivel1, &QPushButton::clicked, this, &Widget::iniciarNivel1);

    btnNivel1_1 = new QPushButton("Nivel 1.1 - Modo dificil: primero en 5 puntos", this);
    btnNivel1_1->setGeometry(300, 340, 420, 60);
    btnNivel1_1->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(30, 100, 200, 200);"
        "  color: white; font-size: 18px; font-weight: bold;"
        "  border-radius: 10px; border: 2px solid #FFD700;"
        "}"
        "QPushButton:hover { background-color: rgba(60, 140, 255, 220); }"
        );
    connect(btnNivel1_1, &QPushButton::clicked, this, &Widget::iniciarNivel1_1);

    btnNivel2 = new QPushButton("Nivel 2 - Tartaro normal", this);
    btnNivel2->setGeometry(300, 430, 420, 60);
    btnNivel2->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(180, 30, 30, 200);"
        "  color: white; font-size: 18px; font-weight: bold;"
        "  border-radius: 10px; border: 2px solid #FFD700;"
        "}"
        "QPushButton:hover { background-color: rgba(220, 60, 60, 220); }"
        );
    connect(btnNivel2, &QPushButton::clicked, this, &Widget::iniciarOtraEscena);

    btnNivel2_2 = new QPushButton("Nivel 2.2 - Tartaro velocidad maxima", this);
    btnNivel2_2->setGeometry(300, 520, 420, 60);
    btnNivel2_2->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(180, 30, 30, 200);"
        "  color: white; font-size: 18px; font-weight: bold;"
        "  border-radius: 10px; border: 2px solid #FFD700;"
        "}"
        "QPushButton:hover { background-color: rgba(220, 60, 60, 220); }"
        );
    connect(btnNivel2_2, &QPushButton::clicked, this, &Widget::iniciarNivel2_2);

    mostrarMenu();
}

void Widget::mostrarMenu()
{
    labelTitulo->show();
    btnNivel1->show();
    btnNivel1_1->show();
    btnNivel2->show();
    btnNivel2_2->show();
}

void Widget::ocultarMenu()
{
    labelTitulo->hide();
    btnNivel1->hide();
    btnNivel1_1->hide();
    btnNivel2->hide();
    btnNivel2_2->hide();
}

void Widget::setupHUD()
{
    if(!labelPuntos){
        labelPuntos = new QLabel(this);
        labelPuntos->setGeometry(400, 10, 300, 30);
        labelPuntos->setStyleSheet(
            "color: white; font-size: 16px; font-weight: bold;"
            "background-color: rgba(0,0,0,120); border-radius:6px; padding:2px;"
            );
    }
    if(!labelTiempo){
        labelTiempo = new QLabel(this);
        labelTiempo->setGeometry(400, 45, 300, 30);
        labelTiempo->setStyleSheet(
            "color: #FFD700; font-size: 16px; font-weight: bold;"
            "background-color: rgba(0,0,0,120); border-radius:6px; padding:2px;"
            );
    }
    labelPuntos->show();
    labelTiempo->show();
    actualizarMarcador();
}

void Widget::limpiarEscena()
{
    if(timerJuego)           { timerJuego->stop(); }
    if(timerCuentaRegresiva) { timerCuentaRegresiva->stop(); }

    if(pelota) { scene->removeItem(pelota); delete pelota; pelota = nullptr; }
    if(aPolo)  { scene->removeItem(aPolo);  delete aPolo;  aPolo  = nullptr; }
    if(tItan)  { scene->removeItem(tItan);  delete tItan;  tItan  = nullptr; }
    if(malla)  { scene->removeItem(malla);  delete malla;  malla  = nullptr; }
    if(nube)   { scene->removeItem(nube);   delete nube;   nube   = nullptr; }
    if(cRonos) { scene->removeItem(cRonos); delete cRonos; cRonos = nullptr; }

    for(columnaFuego *c : columnas){
        scene->removeItem(c);
        delete c;
    }
    columnas.clear();

    puntosApolo       = 0;
    puntosTitan       = 0;
    segundosRestantes = 240;
    colisionConApolo  = false;
    colisionConTitan  = false;
}

void Widget::iniciarNivel1()
{
    limpiarEscena();
    ocultarMenu();
    estadoActual = NIVEL1;

    QPixmap pixMalla(":/malla.png");
    malla = new QGraphicsPixmapItem(pixMalla);
    malla->setScale(0.1);
    malla->setPos(680, 363);
    malla->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(malla);

    QPixmap pixnube(":/laPropia.png");
    nube = new QGraphicsPixmapItem(pixnube);
    nube->setScale(0.75);
    nube->setPos(200, 285);
    nube->setTransformationMode(Qt::SmoothTransformation);
    nube->setZValue(1);
    scene->addItem(nube);
    bg1->setZValue(0);

    pelota = new balon(ui->graphicsView, QPixmap(":/balon.png"), scene->sceneRect(), this);
    pelota->setScale(0.05);
    pelota->setTransformationMode(Qt::SmoothTransformation);
    pelota->setZValue(3);
    scene->addItem(pelota);
    pelota->iniciarMovimiento();

    aPolo = new apolo(ui->graphicsView, scene->sceneRect(), this);
    aPolo->setScale(0.06);
    aPolo->setPos(500, 420);
    aPolo->setTransformationMode(Qt::SmoothTransformation);
    aPolo->setZValue(2);
    scene->addItem(aPolo);

    tItan = new titan(ui->graphicsView, scene->sceneRect(), pelota, this);
    tItan->setScale(0.15);
    tItan->setPos(830, 353);
    tItan->setTransformationMode(Qt::SmoothTransformation);
    tItan->setZValue(2);
    scene->addItem(tItan);
    tItan->iniciarMovimiento();

    setupHUD();

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
    timerJuego->start(20);

    timerCuentaRegresiva = new QTimer(this);
    connect(timerCuentaRegresiva, &QTimer::timeout, this, &Widget::tickTemporizador);
    timerCuentaRegresiva->start(1000);
}

void Widget::iniciarNivel1_1()
{
    limpiarEscena();
    ocultarMenu();
    estadoActual = NIVEL2;

    QPixmap pixMalla(":/malla.png");
    malla = new QGraphicsPixmapItem(pixMalla);
    malla->setScale(0.1);
    malla->setPos(680, 363);
    malla->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(malla);

    QPixmap pixnube(":/laPropia.png");
    nube = new QGraphicsPixmapItem(pixnube);
    nube->setScale(0.75);
    nube->setPos(200, 285);
    nube->setTransformationMode(Qt::SmoothTransformation);
    nube->setZValue(1);
    scene->addItem(nube);
    bg1->setZValue(0);

    pelota = new balon(ui->graphicsView, QPixmap(":/balon.png"), scene->sceneRect(), this);
    pelota->setScale(0.05);
    pelota->setTransformationMode(Qt::SmoothTransformation);
    pelota->setZValue(3);
    scene->addItem(pelota);
    pelota->iniciarMovimiento();

    aPolo = new apolo(ui->graphicsView, scene->sceneRect(), this);
    aPolo->setScale(0.06);
    aPolo->setPos(500, 420);
    aPolo->setTransformationMode(Qt::SmoothTransformation);
    aPolo->setZValue(2);
    scene->addItem(aPolo);

    tItan = new titan(ui->graphicsView, scene->sceneRect(), pelota, this);
    tItan->setScale(0.15);
    tItan->setPos(830, 353);
    tItan->setTransformationMode(Qt::SmoothTransformation);
    tItan->setZValue(2);
    scene->addItem(tItan);
    tItan->iniciarMovimiento();

    setupHUD();
    if(labelTiempo) labelTiempo->setText("Primero en 5 puntos gana");

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
    timerJuego->start(20);
}

void Widget::iniciarNivel2()
{
    limpiarEscena();
    ocultarMenu();
    estadoActual = NIVEL2;

    QPixmap pixMalla(":/malla.png");
    malla = new QGraphicsPixmapItem(pixMalla);
    malla->setScale(0.1);
    malla->setPos(680, 363);
    malla->setTransformationMode(Qt::SmoothTransformation);
    scene->addItem(malla);

    QPixmap pixnube(":/laPropia.png");
    nube = new QGraphicsPixmapItem(pixnube);
    nube->setScale(0.75);
    nube->setPos(200, 285);
    nube->setTransformationMode(Qt::SmoothTransformation);
    nube->setZValue(1);
    scene->addItem(nube);
    bg1->setZValue(0);

    pelota = new balon(ui->graphicsView, QPixmap(":/balon.png"), scene->sceneRect(), this);
    pelota->setScale(0.05);
    pelota->setTransformationMode(Qt::SmoothTransformation);
    pelota->setZValue(3);
    scene->addItem(pelota);
    pelota->iniciarMovimiento();

    aPolo = new apolo(ui->graphicsView, scene->sceneRect(), this);
    aPolo->setScale(0.06);
    aPolo->setPos(500, 420);
    aPolo->setTransformationMode(Qt::SmoothTransformation);
    aPolo->setZValue(2);
    scene->addItem(aPolo);

    tItan = new titan(ui->graphicsView, scene->sceneRect(), pelota, this);
    tItan->setScale(0.15);
    tItan->setPos(830, 353);
    tItan->setTransformationMode(Qt::SmoothTransformation);
    tItan->setZValue(2);
    scene->addItem(tItan);
    tItan->iniciarMovimiento();

    setupHUD();
    if(labelTiempo) labelTiempo->setText("Primero en 5 puntos gana");

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
    timerJuego->start(20);
}

void Widget::iniciarOtraEscena()
{
    limpiarEscena();
    ocultarMenu();
    estadoActual = NIVEL3;

    QPixmap pixFondo(":/fondoTartaro.png");
    pixFondo = pixFondo.scaled(
        (int)scene->sceneRect().width(),
        (int)scene->sceneRect().height(),
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation);
    bg1->setScale(0.5);
    bg1->setPixmap(pixFondo);
    bg1->setPos(290, 0);
    bg1->setZValue(0);

    pelota = new balon(ui->graphicsView,
                       QPixmap(":/balon.png"),
                       scene->sceneRect(), this);
    pelota->setScale(0.05);
    pelota->setTransformationMode(Qt::SmoothTransformation);
    pelota->setZValue(4);
    pelota->setModoCenital(true);
    scene->addItem(pelota);
    pelota->reiniciarPosicionCenital();
    pelota->iniciarMovimiento();
    pelota->setPos(480, 340);

    aPolo = new apolo(ui->graphicsView, scene->sceneRect(), this);
    aPolo->detener();
    aPolo->setModoCenital(true);
    aPolo->setLimites(290.0f, 750.0f, 160.0f, 310.0f);
    aPolo->setScale(0.08);
    aPolo->setPos(550, 230);
    aPolo->setTransformationMode(Qt::SmoothTransformation);
    aPolo->setZValue(3);
    scene->addItem(aPolo);
    aPolo->iniciarMovimiento();

    cRonos = new cronos(ui->graphicsView, scene->sceneRect(),
                        pelota, 1.0f, this);
    cRonos->detener();
    cRonos->setModoCenital(true);
    cRonos->setLimites(170.0f, 600.0f, 350.0f, 530.0f);
    cRonos->setScale(0.12);
    cRonos->setPos(550, 440);
    cRonos->setTransformationMode(Qt::SmoothTransformation);
    cRonos->setZValue(3);
    scene->addItem(cRonos);
    cRonos->iniciarMovimiento();

    float posX[] = { 450.0f, 850.0f };
    float posY[] = { 420.0f, 420.0f };
    for(int i = 0; i < 2; i++){
        columnaFuego *col = new columnaFuego(
            ui->graphicsView, scene->sceneRect(),
            posX[i], posY[i], this);
        col->setScale(0.08);
        col->setZValue(2);
        scene->addItem(col);
        col->iniciarMovimiento();
        columnas.append(col);
    }

    setupHUD();
    if(labelTiempo) labelTiempo->setText("Tartaro — primero en 5 puntos gana");

    timerJuego = new QTimer(this);
    connect(timerJuego, &QTimer::timeout, this, &Widget::actualizarJuego);
    timerJuego->start(20);
}

void Widget::iniciarNivel2_2()
{
    iniciarOtraEscena();
    if(cRonos){
        scene->removeItem(cRonos);
        delete cRonos;
        cRonos = new cronos(ui->graphicsView, scene->sceneRect(),
                            pelota, 3.0f, this);
        cRonos->detener();
        cRonos->setModoCenital(true);
        cRonos->setLimites(170.0f, 600.0f, 350.0f, 530.0f);
        cRonos->setPos(550, 440);
        cRonos->setScale(0.12);
        cRonos->setTransformationMode(Qt::SmoothTransformation);
        cRonos->setZValue(3);
        scene->addItem(cRonos);
        cRonos->iniciarMovimiento();
    }
    estadoActual = NIVEL4;
    if(labelTiempo) labelTiempo->setText("Tartaro dificil — primero en 5 puntos gana");
}

void Widget::actualizarJuego()
{
    if(!pelota) return;

    bool esCenital = (estadoActual == NIVEL3 || estadoActual == NIVEL4);

    if(!esCenital){
        if(!aPolo || !tItan || !malla) return;

        if(pelota->collidesWithItem(aPolo) && !colisionConApolo){
            colisionConApolo = true;
            pelota->rebotarConJugador(1.0f, aPolo->getFuerzaX(), aPolo->getFuerzaY());
        }
        if(!pelota->collidesWithItem(aPolo)) colisionConApolo = false;

        if(pelota->collidesWithItem(tItan) && !colisionConTitan){
            colisionConTitan = true;
            pelota->rebotarConJugador(-1.0f, tItan->getFuerzaX(), tItan->getFuerzaY());
        }
        if(!pelota->collidesWithItem(tItan)) colisionConTitan = false;

        if(pelota->collidesWithItem(malla)){
            QRectF m = malla->sceneBoundingRect();
            QRectF b = pelota->sceneBoundingRect();
            if(b.center().x() < m.center().x()){
                pelota->setX(m.left() - b.width() - 1);
                pelota->rebotarConMalla(-1.0f);
            } else {
                pelota->setX(m.right() + 1);
                pelota->rebotarConMalla(1.0f);
            }
            pelota->setY(pelota->y() - 3);
        }

        float balonY = pelota->y();
        float balonX = pelota->x();
        float piso   = 420.0f;

        if(balonY >= piso){
            if(balonX > 200 && balonX < 680)       puntosTitan++;
            else if(balonX > 680 && balonX < 1000) puntosApolo++;
            actualizarMarcador();
            reiniciarBalon();

            if(estadoActual == NIVEL1 && puntosTitan >= 5){
                timerJuego->stop();
                timerCuentaRegresiva->stop();
                labelTiempo->setText("El Titan gano! Apolo perdio!");
                labelTiempo->setStyleSheet("color: red; font-size: 20px; font-weight:bold;");
            }
            if(estadoActual == NIVEL2){
                if(puntosApolo >= 5 || puntosTitan >= 5){
                    timerJuego->stop();
                    QString g = (puntosApolo >= 5) ? "Apolo gana!" : "El Titan gana!";
                    labelTiempo->setText(g);
                    labelTiempo->setStyleSheet("color: #FFD700; font-size: 22px; font-weight:bold;");
                }
            }
        }
        return;
    }

    if(!aPolo || !cRonos) return;

    if(pelota->collidesWithItem(aPolo) && !colisionConApolo){
        colisionConApolo = true;
        float dirX = (pelota->x() < aPolo->x()) ? -1.0f : 1.0f;
        pelota->rebotarConJugador(dirX, aPolo->getFuerzaX(), aPolo->getFuerzaY());
    }
    if(!pelota->collidesWithItem(aPolo)) colisionConApolo = false;

    if(pelota->collidesWithItem(cRonos) && !colisionConTitan){
        colisionConTitan = true;
        float dirX = (pelota->x() < cRonos->x()) ? -1.0f : 1.0f;
        pelota->rebotarConJugador(dirX, cRonos->getFuerzaX(), cRonos->getFuerzaY());
    }
    if(!pelota->collidesWithItem(cRonos)) colisionConTitan = false;

    for(columnaFuego *col : columnas){
        if(pelota->collidesWithItem(col)){
            pelota->rebotarConBarra();
            break;
        }
    }

    float balonY = pelota->y();

    if(balonY <= 160){
        puntosTitan++;
        actualizarMarcador();
        pelota->reiniciarPosicionCenital();
    }
    if(balonY >= 530){
        puntosApolo++;
        actualizarMarcador();
        pelota->reiniciarPosicionCenital();
    }

    if(puntosApolo >= 5 || puntosTitan >= 5){
        timerJuego->stop();
        if(timerCuentaRegresiva) timerCuentaRegresiva->stop();
        if(aPolo)  aPolo->detener();
        if(cRonos) cRonos->detener();
        if(pelota) pelota->detener();
        for(columnaFuego *col : columnas) col->detener();
        QString g = (puntosApolo >= 5) ? "Apolo gana!" : "Cronos gana!";
        labelTiempo->setText(g);
        labelTiempo->setStyleSheet("color: #FFD700; font-size: 22px; font-weight:bold;");
    }
}

void Widget::actualizarMarcador()
{
    if(!labelPuntos) return;
    bool esCenital = (estadoActual == NIVEL3 || estadoActual == NIVEL4);
    QString rival  = esCenital ? "Cronos" : "Titan";
    labelPuntos->setText("Apolo: " + QString::number(puntosApolo) +
                         "  |  " + rival + ": " +
                         QString::number(puntosTitan));
}

void Widget::reiniciarBalon()
{
    if(pelota) pelota->reiniciarPosicion();
}

void Widget::tickTemporizador()
{
    if(estadoActual != NIVEL1) return;
    segundosRestantes--;
    int min = segundosRestantes / 60;
    int seg = segundosRestantes % 60;
    if(labelTiempo)
        labelTiempo->setText(QString(" %1:%2")
                                 .arg(min, 1, 10, QChar('0'))
                                 .arg(seg, 2, 10, QChar('0')));
    if(segundosRestantes <= 0){
        timerCuentaRegresiva->stop();
        timerJuego->stop();
        if(labelTiempo){
            labelTiempo->setText("Apolo resistio! Victoria!");
            labelTiempo->setStyleSheet("color: #FFD700; font-size: 20px; font-weight:bold;");
        }
    }
}

void Widget::tickTemporizadorCenital()
{
    if(estadoActual != NIVEL3) return;
    segundosRestantes--;
    int min = segundosRestantes / 60;
    int seg = segundosRestantes % 60;
    if(labelTiempo)
        labelTiempo->setText(QString("%1:%2")
                                 .arg(min, 1, 10, QChar('0'))
                                 .arg(seg, 2, 10, QChar('0')));
    if(segundosRestantes <= 0){
        timerCuentaRegresiva->stop();
        timerJuego->stop();
        if(labelTiempo){
            labelTiempo->setText("Apolo resistio! Victoria!");
            labelTiempo->setStyleSheet("color: #FFD700; font-size: 20px; font-weight:bold;");
        }
    }
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(!aPolo) return;
    bool cenital = (estadoActual == NIVEL3 || estadoActual == NIVEL4);
    switch(event->key()){
    case Qt::Key_W:
        if(cenital) aPolo->setBanArriba();
        else        aPolo->setBanSaltar();
        break;
    case Qt::Key_S:
        if(cenital) aPolo->setBanAbajo();
        break;
    case Qt::Key_A: aPolo->setBanIzq(); break;
    case Qt::Key_D: aPolo->setBanDer(); break;
    default: break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if(!aPolo) return;
    switch(event->key()){
    case Qt::Key_W: aPolo->resetBanArriba(); break;
    case Qt::Key_S: aPolo->resetBanAbajo();  break;
    case Qt::Key_A: aPolo->resetBanIzq();    break;
    case Qt::Key_D: aPolo->resetBanDer();    break;
    default: break;
    }
}
