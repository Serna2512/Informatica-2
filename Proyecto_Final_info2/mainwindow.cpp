#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <cmath>
#include <QTransform>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rigby = unique_ptr<Rigby> (new Rigby(300, 250, 100, 180)); //crear objeto de la clase Rigby

    pelota = unique_ptr<Pelota>(new Pelota(0, 0, 8));
    pelota->transportarPor(rigby.get()); //.get() obtiene el puntero actual a Rigby

    escena = new QGraphicsScene(this);//crear la escena
    ui->graphicsView->setScene(escena);

    //Cargar imagen de la cancha
    QPixmap imagenCancha("imagenes_PF_info2/cancha_futbol.png");

    //Agregar cancha a la escena
    QGraphicsPixmapItem* fondo = escena->addPixmap(imagenCancha);

    //Ajustar la cancha al tamaño de la escena
    fondo->setPos(0, 0);
    fondo->setScale(1.0);

    imagenPelota = escena->addEllipse(
        0, 0, 16, 16,
        QPen(Qt::black),
        QBrush(Qt::white)
        );

    imagenPelota->setPos(rigby->getX() + 59, rigby->getY() + 7);

    //Cargar los sprites horizontales de Rigby
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_1.png"));
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_2.png"));
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_3.png"));

    for (unsigned int i = 0; i < spritesRigby.size(); i++){ //creamos los invertidos una sola vez y agragos a ese vector
        QTransform transformacion;
        transformacion.scale(-1, 1);

        spritesRigbyIzquierda.push_back(
            spritesRigby[i].transformed(transformacion));
    }

    //Crear el elemento gráfico de Rigby con el primer sprite
    imagenRigby = escena->addPixmap(spritesRigby[0]);

    //Posicionar a Rigby en la escena

    imagenRigby->setPos(rigby->getX(), rigby->getY());

    qDebug() << "Ancho de Rigby:" << imagenRigby->boundingRect().width();
    qDebug() << "Alto de Rigby:" << imagenRigby->boundingRect().height();

    //Quitar barras laterales
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView->setInteractive(false);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

    this->setFocusPolicy(Qt::StrongFocus); //permitir que la ventana reciba evento del teclado

    temporizador = new QTimer(this);

    connect(temporizador, &QTimer::timeout, this, [this](){
        float dt = reloj.restart() / 1000.0;
        actualizarJuego(dt);
    });

    reloj.start();
    temporizador->start(16);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) //como solo guardamos el estado que se presionó podemos detectar varias teclas simultaneamente
//y movernos en diagonal
{
    switch (event->key())
    {
    case Qt::Key_W:
        arriba = true;
        break;

    case Qt::Key_S:
        abajo = true;
        break;

    case Qt::Key_A:
        izquierda = true;
        break;

    case Qt::Key_D:
        derecha = true;
        break;

    default:
        QMainWindow::keyPressEvent(event);
        break;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
        arriba = false;
        break;

    case Qt::Key_S:
        abajo = false;
        break;

    case Qt::Key_A:
        izquierda = false;
        break;

    case Qt::Key_D:
        derecha = false;
        break;

    default:
        QMainWindow::keyReleaseEvent(event);
        break;
    }
}


void MainWindow::actualizarJuego(float dt)
{
    //se calcula un vector con la direccion, ej: (0,1) sería hacía abajo por las coordenadas y, (0,-1) sería en -y, o sea, hacía arriba

    float dx = 0.0;
    float dy = 0.0;

    if (arriba)
        dy -= 1.0;

    if (abajo)
        dy += 1.0;

    if (izquierda)
        dx -= 1.0;

    if (derecha)
        dx += 1.0;

    float magnitud = sqrt(dx * dx + dy * dy);

    if (magnitud > 0.0)
    {
        dx /= magnitud; //para evitar que se mueva más rápdio en diagnoal normalizamos (magnitud de 1) ese desplazamiento
        dy /= magnitud;
    }

    if (dx != 0.0 || dy != 0.0) {
        ultimaDireccionX = dx; //guardar ultima direccion hacía donde Rigby mira
        ultimaDireccionY = dy;
    }

    float desplazamientoX = dx * rigby->getVelocidad() * dt; //velocidad de Rigby
    float desplazamientoY = dy * rigby->getVelocidad() * dt;

    rigby->mover(desplazamientoX, desplazamientoY); //actualizar movimiento lógico

    //Limitar movimiento horizontal (800 - 59 - (parte blanca escena) = 684), para ajustar límites de la ventana y cancha
    if (rigby->getX() < 0.0)
        rigby->setX(0.0);

    if (rigby->getX() > 684.0)
        rigby->setX(684.0);

    // Limitar movimiento vertical (600 - 29 - (parte en blanco de la escena) = 513)
    if (rigby->getY() < 29.0)
        rigby->setY(29.0);

    if (rigby->getY() > 513.0)
        rigby->setY(513.0);

    // Animar a Rigby cuando se desplaza horizontalmente
    // Determinar hacia dónde está mirando Rigby

    if (dx < 0.0)
        mirandoIzquierda = true;
    else if (dx > 0.0)
        mirandoIzquierda = false;

    //Comprobar si Rigby se está moviendo
    if (dx != 0.0 || dy != 0.0){

        tiempoAnimacion += dt;

        if (tiempoAnimacion >= intervaloAnimacion) {

            frameActual = (frameActual + 1) % spritesRigby.size();

            tiempoAnimacion = 0.0;
        }

    } else {

        frameActual = 0;
        tiempoAnimacion = 0.0;
    }

    float desplazamientoPelotaX = 59.0;
    float desplazamientoPelotaY = 6.5;

    //calculamos dónde debe ir la pelota explícitamente dependiendo hacía donde mira el jugador
    if (ultimaDireccionX < 0.0) {

        // Izquierda
        desplazamientoPelotaX = -16.0; //radio pelota
        desplazamientoPelotaY = 6.5;

    }
    else if (ultimaDireccionX > 0.0) {

        // Derecha
        desplazamientoPelotaX = 59.0; //ancho rigby
        desplazamientoPelotaY = 6.5;

    }
    else if (ultimaDireccionY < 0.0) {

        // Arriba
        desplazamientoPelotaX = 21.5;
        desplazamientoPelotaY = -16.0;

    }
    else if (ultimaDireccionY > 0.0) {

        // Abajo
        desplazamientoPelotaX = 21.5;
        desplazamientoPelotaY = 29.0;

    }

    pelota->actualizarPosicionTransportada(
        desplazamientoPelotaX,
        desplazamientoPelotaY
        );

    imagenPelota->setPos(pelota->getX(), pelota->getY());

    // Mostrar el sprite correspondiente
    if (mirandoIzquierda)
        imagenRigby->setPixmap(spritesRigbyIzquierda[frameActual]);
    else
        imagenRigby->setPixmap(spritesRigby[frameActual]);

    pelota->actualizar(dt);

    imagenPelota->setPos(pelota->getX(),pelota->getY());//actualizar movimiento en la parte gráfica

    imagenRigby->setPos(rigby->getX(), rigby->getY()); //actualizar movimiento en la parte gráfica

    // 5. Actualizar posición gráfica de Rigby.
}