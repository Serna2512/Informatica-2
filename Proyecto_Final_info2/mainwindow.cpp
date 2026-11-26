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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    rigby = unique_ptr<Rigby> (new Rigby(100, 300, 100, 180)); //crear objeto de la clase Rigby

    pelota = unique_ptr<Pelota>(new Pelota(0, 0, 8));
    pelota->transportarPor(rigby.get()); //.get() obtiene el puntero actual a Rigby

    //crear ptr unico a clase RivalPerseguidor
    rivalPerseguidor = unique_ptr<RivalPerseguidor>(
        new RivalPerseguidor(350, 200, 100, 10,rigby.get()));


    escena = new QGraphicsScene(this);//crear la escena

    ui->graphicsView->setScene(escena);

    //Cargar imagen de la cancha
    QPixmap imagenCancha("imagenes_PF_info2/cancha_futbol.png");

    //Agregar cancha a la escena
    QGraphicsPixmapItem* fondo = escena->addPixmap(imagenCancha);

    //Ajustar la cancha al tamaño de la escena
    fondo->setPos(0, 0);
    fondo->setScale(1.0);

    //generar aleatoriamente los obstaculos
    generarObstaculos();

    imagenRival = escena->addEllipse(
        350, 200, 35, 35,
        QPen(Qt::black),
        QBrush(Qt::red)
        );


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

        rigby->actualizar(dt);//verificar si rigby está siendo afectado por zona lodosa

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

    // Actualizar su representación gráfica
    imagenRival->setPos(
        rivalPerseguidor->getX(),
        rivalPerseguidor->getY()
        );

    // Mostrar el sprite correspondiente a Rigby
    if (mirandoIzquierda)
        imagenRigby->setPixmap(spritesRigbyIzquierda[frameActual]);
    else
        imagenRigby->setPixmap(spritesRigby[frameActual]);

    comprobarColisionZonaLodosa(); //los llamo después de mover a rigby para usar sus coordenadas actuales
    comprobarColisionHueco();

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
                qDebug() << "Rigby entro en la zona lodosa" << i;
            }
        }
        else {

            if (dentroZonasLodosas[i]) {
                dentroZonasLodosas[i] = false;
                qDebug() << "Rigby salio de la zona lodosa" << i;
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

                qDebug() << "Rigby cayo en el hueco" << i;

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
                qDebug() << "Rigby salio del hueco" << i;
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

            QGraphicsRectItem* imagen = escena->addRect(
                x, y, 100, 70,
                QPen(Qt::NoPen),
                QBrush(QColor(120, 75, 35, 190))
                );

            imagenesZonasLodosas.push_back(imagen);

            posicionesOcupadas.push_back(areaSeparacion);

            generado = true;
        }

        if (!generado)
            qWarning() << "No se pudo generar una zona lodosa.";
    }

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

            QGraphicsRectItem* imagen = escena->addRect(
                x, y, 65, 50,
                QPen(Qt::NoPen),
                QBrush(QColor(35, 25, 20))
                );

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

    qDebug() << "Zonas lodosas generadas:" << zonasLodosas.size();
    qDebug() << "Huecos generados:" << huecos.size();
}
