#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <cmath>
#include <QTransform>
#include <QMessageBox>
#include <random>
#include <QRectF>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <memory>
#include <QRandomGenerator>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear a Rigby
    rigby = unique_ptr<Rigby>(new Rigby(100, 300, 100, 180));

    // Crear rival lógico
    rivalPerseguidor = unique_ptr<RivalPerseguidor>(
        new RivalPerseguidor(
            rigby->getX() + 250,
            rigby->getY(),
            90,
            5,
            rigby.get()
            )
        );

    // Crear rival lanzador superior
    rivalesLanzadores.push_back(
        unique_ptr<RivalLanzador>(
            new RivalLanzador(342, 20, 0.0, 10, 2.0, 180.0)
            )
        );

    // Crear rival lanzador inferior
    rivalesLanzadores.push_back(
        unique_ptr<RivalLanzador>(
            new RivalLanzador(342, 480, 0.0, 10, 2.0, 180.0)
            )
        );

    // Crear escena
    escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    spritesRival[0] = QPixmap("imagenes_PF_info2/martillo1.png");
    spritesRival[1] = QPixmap("imagenes_PF_info2/martillo2.png");

    // Cargar sprites del lanzador superior
    spritesLanzador[0] = QPixmap("imagenes_PF_info2/sprite_lanzador1.png");
    spritesLanzador[1] = QPixmap("imagenes_PF_info2/sprite_lanzador2.png");

    // Cargar sprites del lanzador inferior
    spritesLanzador[2] = QPixmap("imagenes_PF_info2/sprite_lanzador1_espalda.png");
    spritesLanzador[3] = QPixmap("imagenes_PF_info2/sprite_lanzador2_espalda.png");

    // Cargar sprites de los proyectiles
    spritesProyectil[0] = QPixmap("imagenes_PF_info2/proyectil1.png");
    spritesProyectil[1] = QPixmap("imagenes_PF_info2/proyectil2.png");

    //qDebug() << "Sprite rival 1:" << spritesRival[0].size();
    //qDebug() << "Sprite rival 2:" << spritesRival[1].size();

    spriteBarro = QPixmap("imagenes_PF_info2/barro._sprite.png");
    spriteHueco = QPixmap("imagenes_PF_info2/hueco_sprite.png");

    //imagenes de los potenciadores cargados y ya escalados
    spritesPotenciador[0] = QPixmap("imagenes_PF_info2/potenciador1.png").scaled(
        32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    spritesPotenciador[1] = QPixmap("imagenes_PF_info2/potenciador2.png").scaled(
        32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    spritesPotenciador[2] = QPixmap("imagenes_PF_info2/potenciador3.png").scaled(
        32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);


    // Crear imagen del rival en el origen
    imagenRival = escena->addPixmap(spritesRival[0]);

    // Establecer su posición real en la escena
    imagenRival->setPos(
        rivalPerseguidor->getX(),
        rivalPerseguidor->getY()
        );

    imagenRival->setZValue(2);

    pelota = unique_ptr<Pelota>(new Pelota(0, 0, 8));
    pelota->transportarPor(rigby.get()); //.get() obtiene el puntero actual a Rigby

    //Cargar imagen de la cancha
    QPixmap imagenCancha("imagenes_PF_info2/cancha_futbol.png");

    //Agregar cancha a la escena
    QGraphicsPixmapItem* fondo = escena->addPixmap(imagenCancha);

    //Ajustar la cancha al tamaño de la escena
    fondo->setPos(0, 0);
    fondo->setScale(1.0);

    //generar aleatoriamente los obstaculos
    generarObstaculos();

    //generar aleatoriamente los potenciadores
    generarPotenciadores();


    // Crear imágenes de los dos lanzadores
    for (unsigned int i = 0; i < rivalesLanzadores.size(); i++) {

        int indiceSprite = (i == 0) ? 0 : 2;

        QGraphicsPixmapItem* imagen =
            escena->addPixmap(spritesLanzador[indiceSprite]);

        imagen->setPos(
            rivalesLanzadores[i]->getX(),
            rivalesLanzadores[i]->getY()
            );

        imagenesLanzadores.push_back(imagen);

        tiemposAnimacionDisparo.push_back(0.0);
        tiemposContactoLanzadores.push_back(0.0);
    }

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

    /*qDebug() << "RIGBY LOGICO:"
             << rigby->getX() << rigby->getY();

    //qDebug() << "RIGBY GRAFICO:"
             << imagenRigby->pos();

    //qDebug() << "RIVAL LOGICO:"
             << rivalPerseguidor->getX()
             << rivalPerseguidor->getY();

    //qDebug() << "RIVAL GRAFICO:"
             << imagenRival->pos();
    */

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

    case Qt::Key_E:
        pelota->desprender(-100.0 * ultimaDireccionX,
                           -100.0 * ultimaDireccionY);

        tiempoBloqueoRecuperacion = 0.5;
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


void MainWindow::comprobarRecuperacionPelota(){


    if (pelota->getEstado() == EstadoPelota::TRANSPORTADA)
        return;

    float centroRigbyX = rigby->getX() + 29.5; //centro del pixmap rigby en x
    float centroRigbyY = rigby->getY() + 14.5;//centro del pixmap rigby en y

    float centroPelotaX = pelota->getX() + 8.0; ;//centro del pixmap pelota en x
    float centroPelotaY = pelota->getY() + 8.0;//centro del pixmap pelota en y

    float dx = centroRigbyX - centroPelotaX;
    float dy = centroRigbyY - centroPelotaY;

    float distancia = sqrt(dx * dx + dy * dy); //obtener distancia de entre sus centros

    if (distancia < 35.0  && tiempoBloqueoRecuperacion <= 0.0) {
        pelota->transportarPor(rigby.get());
    }
}



void MainWindow::actualizarJuego(float dt)
{

    if (nivelCompletado){
        return;}

        rigby->actualizar(dt);//verificar si rigby tiene efectos temporales
        qDebug() << "Velocidad de Rigby:" << rigby->getVelocidad();

    //se calcula un vector con la direccion, ej: (0,1) sería hacía abajo por las coordenadas y, (0,-1) sería en -y, o sea, hacía arriba

    float dx = 0.0;
    float dy = 0.0;

    tiempoBloqueoRecuperacion -= dt;

    if (tiempoBloqueoRecuperacion < 0.0){
        tiempoBloqueoRecuperacion = 0.0;
    }

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

    // Guardar la posición anterior de Rigby para evitar superponerse al rival
    float posicionAnteriorX = rigby->getX();
    float posicionAnteriorY = rigby->getY();

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
    // Determinar hacia dónde está mirando Rigby así se quede quieto

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


    // Actualizar la lógica del rival
    rivalPerseguidor->actualizar(dt);

    // Comprobar colisión entre Rigby y el perseguidor
    QRectF rectRigby(
        rigby->getX(),
        rigby->getY(),
        59,
        29
        );

    QRectF rectRival(
        rivalPerseguidor->getX(),
        rivalPerseguidor->getY(),
        63,
        66
        );

    if (rectRigby.intersects(rectRival)) {

        // Devolver a Rigby a su última posición
        rigby->setX(posicionAnteriorX);
        rigby->setY(posicionAnteriorY);
    }

    // Actualizar su representación gráfica
    imagenRival->setPos(
        rivalPerseguidor->getX(),
        rivalPerseguidor->getY()
        );

    //tiempoAnimacionRival += dt; // continuar con la animacion del rival

    // Actualizar proyectiles y comprobar impactos
    // Actualizar proyectiles, animaciones y comprobar impactos
    // Actualizar lanzadores y generar proyectiles
    for (unsigned int i = 0; i < rivalesLanzadores.size(); i++) {

        rivalesLanzadores[i]->actualizar(dt);

        // Actualizar duración de la animación de disparo
        if (tiemposAnimacionDisparo[i] > 0.0) {

            tiemposAnimacionDisparo[i] -= dt;

            if (tiemposAnimacionDisparo[i] <= 0.0) {

                tiemposAnimacionDisparo[i] = 0.0;

                int spriteNormal = (i == 0) ? 0 : 2;

                imagenesLanzadores[i]->setPixmap(
                    spritesLanzador[spriteNormal]
                    );
            }
        }

        // Comprobar si puede disparar
        if (rivalesLanzadores[i]->estaListoParaAtacar()) {

            proyectiles.push_back(
                rivalesLanzadores[i]->atacar(rigby.get())
                );

            if (proyectiles.back() != nullptr) {

                // Cambiar sprite del lanzador
                int spriteDisparo = (i == 0) ? 1 : 3;

                imagenesLanzadores[i]->setPixmap(
                    spritesLanzador[spriteDisparo]
                    );

                tiemposAnimacionDisparo[i] = 0.3;

                // Crear imagen del proyectil
                QGraphicsPixmapItem* imagen = escena->addPixmap(spritesProyectil[0]);
                imagen->setScale(0.4);

                imagen->setPos(
                    proyectiles.back()->getX(),
                    proyectiles.back()->getY()
                    );

                imagenesProyectiles.push_back(imagen);

                // Inicializar datos de animación
                framesProyectiles.push_back(0);
                tiemposAnimacionProyectiles.push_back(0.0);
            }
            else {
                proyectiles.pop_back();
            }
        }
    }


    // Comprobar colisiones de Rigby con los lanzadores
    for (unsigned int i = 0; i < rivalesLanzadores.size(); i++) {

        // Actualizar tiempo de espera entre daños
        if (tiemposContactoLanzadores[i] > 0.0) {

            tiemposContactoLanzadores[i] -= dt;

            if (tiemposContactoLanzadores[i] < 0.0)
                tiemposContactoLanzadores[i] = 0.0;
        }

        QRectF rectRigby(
            rigby->getX(),
            rigby->getY(),
            59,
            29
            );

        QRectF rectLanzador(
            rivalesLanzadores[i]->getX(),
            rivalesLanzadores[i]->getY(),
            imagenesLanzadores[i]->boundingRect().width(),
            imagenesLanzadores[i]->boundingRect().height()
            );

        if (rectRigby.intersects(rectLanzador)) {

            if (tiemposContactoLanzadores[i] <= 0.0) {

                rigby->recibirDanio(2);

                tiemposContactoLanzadores[i] = 1.0;

                qDebug() << "¡RIGBY CHOCO CON UN LANZADOR!";
                qDebug() << "Vida restante:" << rigby->getVida();
            }
        }
    }

    tiempoAnimacionRival += dt; // continuar con la animacion del rival

    // Eliminar proyectiles que ya impactaron o salieron de la cancha
    for (int i = static_cast<int>(proyectiles.size()) - 1; i >= 0; i--) {

        proyectiles[i]->actualizar(dt);

        QRectF rectProyectil(proyectiles[i]->getX(), proyectiles[i]->getY(), 16, 16);
        QRectF rectRigby(rigby->getX(), rigby->getY(), 59, 29);

        bool eliminar = false;

        // Comprobar impacto contra Rigby
        if (rectProyectil.intersects(rectRigby)) {

            proyectiles[i]->impactar(rigby.get());

            qDebug() << "¡RIGBY RECIBIO UN PROYECTIL!";
            qDebug() << "Vida restante:" << rigby->getVida();

            eliminar = true;
        }

        // Eliminar proyectiles que salen de la cancha
        if (proyectiles[i]->getX() < -20 ||
            proyectiles[i]->getX() > 780 ||
            proyectiles[i]->getY() < -20 ||
            proyectiles[i]->getY() > 590) {

            eliminar = true;
        }

        if (!eliminar) {

            // Actualizar animación del proyectil
            tiemposAnimacionProyectiles[i] += dt;

            if (tiemposAnimacionProyectiles[i] >= 0.12) {

                framesProyectiles[i] = (framesProyectiles[i] + 1) % 2;

                tiemposAnimacionProyectiles[i] = 0.0;

                imagenesProyectiles[i]->setPixmap(spritesProyectil[framesProyectiles[i]]);
                imagenesProyectiles[i]->setScale(0.4);
            }

            // Actualizar posición de la imagen
            imagenesProyectiles[i]->setPos(
                proyectiles[i]->getX(),
                proyectiles[i]->getY()
                );
        }

        // Eliminar proyectil lógico y gráfico
        if (eliminar) {

            escena->removeItem(imagenesProyectiles[i]);
            delete imagenesProyectiles[i];

            proyectiles.erase(proyectiles.begin() + i);
            imagenesProyectiles.erase(imagenesProyectiles.begin() + i);
            framesProyectiles.erase(framesProyectiles.begin() + i);
            tiemposAnimacionProyectiles.erase(tiemposAnimacionProyectiles.begin() + i);
        }
    }

    if (tiempoAnimacionRival >= 0.2) {
        frameRival = (frameRival + 1) % 2;
        tiempoAnimacionRival = 0.0;

        imagenRival->setPixmap(spritesRival[frameRival]);
    }

    // Mostrar el sprite correspondiente a Rigby
    if (mirandoIzquierda)
        imagenRigby->setPixmap(spritesRigbyIzquierda[frameActual]);
    else
        imagenRigby->setPixmap(spritesRigby[frameActual]);


    comprobarColisionZonaLodosa(); //los llamo después de mover a rigby para usar sus coordenadas actuales
    comprobarColisionHueco();

    comprobarColisionPotenciador();

    //Controlar la reaparición de potenciadores
    if (potenciadores.empty()) {

        if (tiempoReaparicionPotenciador > 0.0) {
            tiempoReaparicionPotenciador -= dt;
        }
        else {
            generarPotenciadores();
        }
    }

    // Animar el potenciador mientras esté en la cancha (si no está activo
    if (!potenciadores.empty()) {

        tiempoAnimacionPotenciador += dt;

        if (tiempoAnimacionPotenciador >= intervaloAnimacionPotenciador) {

            framePotenciador = (framePotenciador + 1) % 3;

            tiempoAnimacionPotenciador -= intervaloAnimacionPotenciador;

            imagenesPotenciadores[0]->setPixmap(
                spritesPotenciador[framePotenciador]
                );
        }
    }
    else {
        framePotenciador = 0;
        tiempoAnimacionPotenciador = 0.0;
    }

    if (!nivelCompletado && rigby->getX() >= 684.0 && rigby->getY() >= 206.6 && rigby->getY() <= 318.2 && pelota->getEstado() == EstadoPelota::TRANSPORTADA){
        nivelCompletado = true;

        QMessageBox::information(
            this,
            "¡GOOOL!",
            "¡Rigby ha conseguido llevar la pelota hasta el arco rival!"
            );

        return;
    }


    // Actualizar posición gráfica de Rigby
    imagenRigby->setPos(rigby->getX(), rigby->getY());

    // Actualizar pelota según su estado
    if (pelota->getEstado() == EstadoPelota::TRANSPORTADA) {

        // Calcular posición deseada de la pelota respecto a Rigby
        float pelotaX = rigby->getX() + desplazamientoPelotaX;
        float pelotaY = rigby->getY() + desplazamientoPelotaY;

        // Limitar la pelota a los bordes de la cancha
        if (pelotaX < 0.0)
            pelotaX = 0.0;
        else if (pelotaX > 784.0)
            pelotaX = 784.0;

        if (pelotaY < 0.0)
            pelotaY = 0.0;
        else if (pelotaY > 584.0)
            pelotaY = 584.0;

        // Convertir nuevamente a desplazamientos respecto a Rigby
        desplazamientoPelotaX = pelotaX - rigby->getX();
        desplazamientoPelotaY = pelotaY - rigby->getY();

        pelota->actualizarPosicionTransportada(
            desplazamientoPelotaX,
            desplazamientoPelotaY
            );

    }
    else {

        // La pelota se mueve independientemente de Rigby
        pelota->actualizar(dt);

        // Comprobar si Rigby puede recuperarla
        comprobarRecuperacionPelota();
    }

    // Actualizar representación gráfica de la pelota
    imagenPelota->setPos(pelota->getX(), pelota->getY());
}


void MainWindow::comprobarColisionZonaLodosa()
{
    QRectF rectRigby(
        rigby->getX(),
        rigby->getY(),
        59,
        29
    );

    for (size_t i = 0; i < zonasLodosas.size(); i++) {

        QRectF rectZona(
            zonasLodosas[i]->getX(),
            zonasLodosas[i]->getY(),
            zonasLodosas[i]->getAncho(),
            zonasLodosas[i]->getAlto()
        );

        if (rectRigby.intersects(rectZona)) {

            // Aplicar lentitud mientras permanezca dentro
            zonasLodosas[i]->afectar(rigby.get());

            if (!dentroZonasLodosas[i]) {
                dentroZonasLodosas[i] = true;
                //qDebug() << "Rigby entro en la zona lodosa" << i;
            }
        }
        else {

            if (dentroZonasLodosas[i]) {
                dentroZonasLodosas[i] = false;
//qDebug() << "Rigby salio de la zona lodosa" << i;
            }
        }
    }
}



void MainWindow::comprobarColisionHueco()
{
    QRectF rectRigby(
        rigby->getX(),
        rigby->getY(),
        59,
        29
        );

    for (size_t i = 0; i < huecos.size(); i++) {

        QRectF rectHueco(
            huecos[i]->getX(),
            huecos[i]->getY(),
            huecos[i]->getAncho(),
            huecos[i]->getAlto()
            );

        if (rectRigby.intersects(rectHueco)) {

            // Solo aplicar el efecto al entrar por primera vez
            if (!dentroHuecos[i]) {

                dentroHuecos[i] = true;

                huecos[i]->afectar(rigby.get());

                //qDebug() << "Rigby cayo en el hueco" << i;

                // Desprender la pelota si Rigby la transportaba
                if (pelota->getEstado() == EstadoPelota::TRANSPORTADA) {

                    pelota->desprender(
                        -100.0f * ultimaDireccionX,
                        -100.0f * ultimaDireccionY
                        );

                    tiempoBloqueoRecuperacion = 0.5f;
                }
            }
        }
        else {

            // Detectar cuando Rigby sale del hueco
            if (dentroHuecos[i]) {
                dentroHuecos[i] = false;
                //qDebug() << "Rigby salio del hueco" << i;
            }
        }
    }
}



void MainWindow::generarObstaculos()
{
    // Generador de números aleatorios
    random_device rd;
    mt19937 generador(rd());

    // Lím)ites donde pueden aparecer los obstáculos
    uniform_int_distribution<int> posicionX(200, 560);
    uniform_int_distribution<int> posicionY(60, 440);

    // Rectángulo de Rigby
    QRectF rectRigby(
        rigby->getX(),
        rigby->getY(),
        59,
        29
        );

    // Reservar un espacio alrededor de Rigby
    rectRigby.adjust(-100, -100, 100, 100); // modifica los límites del rectángulo pero no modifica lo gráfico ni lo real


    // Guardar las posiciones ya ocupadas
    vector<QRectF> posicionesOcupadas;

    // Evitar que los obstáculos aparezcan cerca del arco
    QRectF zonaArco(620, 0, 180, 600);

    // Función auxiliar para verificar si una posición es válida
    auto posicionValida = [&](const QRectF& candidato)
    {
        if (candidato.intersects(rectRigby))
            return false;

        if (candidato.intersects(zonaArco))
            return false;

        for (const QRectF& ocupada : posicionesOcupadas) {
            if (candidato.intersects(ocupada))
                return false;
        }

        return true;
    };


    QPixmap barroEscalado = spriteBarro.scaled(
        100, 70,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    // Generar 4 zonas lodosas
    for (int i = 0; i < 4; i++) {

        bool generado = false;

        for (int intento = 0; intento < 500 && !generado; intento++) {

            float x = posicionX(generador);
            float y = posicionY(generador);

            QRectF rectangulo(x, y, 100, 70);

            // Margen para evitar que queden demasiado cerca
            QRectF areaSeparacion = rectangulo.adjusted(-12, -12, 12, 12); //devuelve
            //un rectangulo modificado pero no altera el original (solo para que haya margen y no estén muy juntos)

            if (!posicionValida(areaSeparacion)){
                continue;}

            zonasLodosas.push_back(unique_ptr<ZonaLodosa>
            (new ZonaLodosa(x, y, 100, 70, 0.5))); //como nuevaZona es objeto de ZonaLodosa con unique_ptr, este no permite copiarse
            //por eso pasamos la propiedad así al contenedor

            QGraphicsPixmapItem* imagen = escena->addPixmap(barroEscalado);

            imagen->setPos(x, y);

            imagenesZonasLodosas.push_back(imagen);

            posicionesOcupadas.push_back(areaSeparacion);

            generado = true;
        }

        if (!generado)
            qWarning() << "No se pudo generar una zona lodosa.";
    }

    QPixmap huecoEscalado = spriteHueco.scaled(
        65, 50,
        Qt::IgnoreAspectRatio,
        Qt::SmoothTransformation
        );

    // Generar 4 huecos
    for (int i = 0; i < 4; i++) {

        bool generado = false;

        for (int intento = 0; intento < 500 && !generado; intento++) {

            float x = posicionX(generador);
            float y = posicionY(generador);

            QRectF rectangulo(x, y, 65, 50);

            QRectF areaSeparacion = rectangulo.adjusted(-12, -12, 12, 12); //devuelve
                //un rectangulo modificado pero no altera el original (solo para que haya margen y no estén muy juntos)

            if (!posicionValida(areaSeparacion))
                continue;

            huecos.push_back(unique_ptr<Hueco>(
                    new Hueco(x, y, 65, 50, 15))
                );

            QGraphicsPixmapItem* imagen = escena->addPixmap(huecoEscalado);

            imagen->setPos(x, y);

            imagenesHuecos.push_back(imagen);

            posicionesOcupadas.push_back(areaSeparacion);

            generado = true;
        }

        if (!generado)
            qWarning() << "No se pudo generar un hueco.";
    }

    // Inicializar los estados de colisión
    dentroZonasLodosas.resize(zonasLodosas.size(), false); //cambia la cantidad de elementos, si aumenta se crean nuevos
//si disminuye elmina los sobrantes

    dentroHuecos.resize(huecos.size(), false);

    //qDebug() << "Zonas lodosas generadas:" << zonasLodosas.size();
    //qDebug() << "Huecos generados:" << huecos.size();
}

void MainWindow::generarPotenciadores()
{
    // Evitar generar otro si ya existe uno activo
    if (!potenciadores.empty())
        return;

    float x;
    float y;

    bool posicionValida = false;
    int intentos = 0;

    while (!posicionValida && intentos < 500) {

        int minimoX = 40;
        int maximoX = 740;

        int minimoY = 40;
        int maximoY = 540;

        x = QRandomGenerator::global()->bounded(minimoX, maximoX + 1);
        y = QRandomGenerator::global()->bounded(minimoY, maximoY + 1);

        QRectF rectPotenciador(x, y, 32, 32);

        posicionValida = true;

        // Evitar que aparezca encima de Rigby al comenzar
        QRectF rectRigby(rigby->getX(), rigby->getY(), 59, 29);

        if (rectPotenciador.intersects(rectRigby))
            posicionValida = false;

        // Evitar que aparezca encima de los huecos
        for (unsigned int i = 0; i < huecos.size(); i++) {

            QRectF rectHueco(
                huecos[i]->getX(),
                huecos[i]->getY(),
                huecos[i]->getAncho(),
                huecos[i]->getAlto()
                );

            if (rectPotenciador.intersects(rectHueco))
                posicionValida = false;
        }

        intentos++;
    }

    if (!posicionValida)
        return;

    // Crear el objeto lógico y transferir su propiedad a MainWindow
    potenciadores.push_back(
        unique_ptr<Potenciador>(
            new Potenciador(x, y, 32, 32, 1.5, 5.0)
            )
        );

    // Crear su representación gráfica
    QGraphicsPixmapItem* imagen = escena->addPixmap(spritesPotenciador[0]);

    imagen->setPos(x, y);

    imagenesPotenciadores.push_back(imagen);
}

void MainWindow::comprobarColisionPotenciador()
{
    if (potenciadores.empty())
        return;

    QRectF rectRigby(
        rigby->getX(),
        rigby->getY(),
        59,
        29
        );

    QRectF rectPotenciador(
        potenciadores[0]->getX(),
        potenciadores[0]->getY(),
        potenciadores[0]->getAncho(),
        potenciadores[0]->getAlto()
        );

    if (rectRigby.intersects(rectPotenciador)) {

        if (potenciadores[0]->recoger(rigby.get())) {

            // Retirar la imagen de la escena
            escena->removeItem(imagenesPotenciadores[0]);
            delete imagenesPotenciadores[0];

            // Eliminar el objeto lógico y su imagen de los vectores
            potenciadores.erase(potenciadores.begin());
            imagenesPotenciadores.erase(imagenesPotenciadores.begin());

            // Iniciar el tiempo de espera para generar otro
            tiempoReaparicionPotenciador = intervaloReaparicionPotenciador;

            qDebug() << "¡RIGBY RECOGIO UN POTENCIADOR!";
        }
    }
}