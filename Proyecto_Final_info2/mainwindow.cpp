#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Tamaño de la ventana:" << this->size();
    qDebug() << "Tamaño del centralWidget:" << ui->centralwidget->size();
    qDebug() << "Tamaño del graphicsView:" << ui->graphicsView->size();

    escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    //Quitar barras laterales
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->graphicsView->setInteractive(false);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);


    //Cargar imagen de la cancha
    QPixmap imagenCancha("imagenes_PF_info2/cancha_futbol.png");

    qDebug() << "Dimensiones de la cancha:" << imagenCancha.size();
    qDebug() << "Dimensiones del visor:" << ui->graphicsView->viewport()->size();

    //Agregar cancha a la escena
    QGraphicsPixmapItem* fondo = escena->addPixmap(imagenCancha);

    //Ajustar la cancha al tamaño de la escena
    fondo->setPos(0, 0);
    fondo->setScale(1.0);

    //Cargar los sprites horizontales de Rigby
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_1.png"));
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_2.png"));
    spritesRigby.push_back(QPixmap("imagenes_PF_info2/rigby_corriendo_3.png"));

    //Crear el elemento gráfico de Rigby con el primer sprite
    imagenRigby = escena->addPixmap(spritesRigby[0]);

    //Posicionar a Rigby en la escena
    imagenRigby->setPos(300, 250);

}

MainWindow::~MainWindow()
{
    delete ui;
}
