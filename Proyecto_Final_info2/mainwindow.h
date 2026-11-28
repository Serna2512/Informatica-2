#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <vector>
#include "Rigby.h"
#include "Pelota.h"
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsEllipseItem>
#include "ZonaLodosa.h"
#include <QGraphicsRectItem>
#include "Hueco.h"
#include "RivalPerseguidor.h"
#include <random>
#include "RivalLanzador.h"
#include "Proyectil.h"
#include "Potenciador.h"
#include "NivelConduccion.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:

    //contendrá los objetos que deben ser propiedad de clase NivelConduccion
    unique_ptr<NivelConduccion> nivelConduccion;

    Rigby* rigby = nullptr; //objeto de la clase rigby (puntero unico a esta clase) //unique_ptr porque mainwindow es responsable de
    //administrar este objeto (de momento)
    QGraphicsPixmapItem* imagenRigby; //imagen que aparece en la pantalla

    vector<QPixmap> spritesRigby; //vector que cotiene los sprites de Rigby
    vector<QPixmap> spritesRigbyIzquierda; //vector de sprites pero mirando hacia atras
    bool mirandoIzquierda = false;

    //crear balón
    QGraphicsEllipseItem* imagenPelota;
    unique_ptr<Pelota> pelota; //objeto pelota de clase pelota, unique porque esta clase administra temporalemente este objeto
    float ultimaDireccionX = 1.0; //ultimas dirreciones por si rigby se queda quieto hacer que la pelota esté correctamente ubicada
    float ultimaDireccionY = 0.0;
    float tiempoBloqueoRecuperacion = 0.0;


    unsigned short int frameActual = 0; //sprite que mostramos
    float tiempoAnimacion = 0.0; //tiempo acumulado desde la última actualizacion de un srpite
    float intervaloAnimacion = 0.12; //tiempo arbitrario para cambiar el sprite

    //Rival perseguidor
    unique_ptr<RivalPerseguidor> rivalPerseguidor;
    QGraphicsPixmapItem* imagenRival;

    QPixmap spritesRival[2];
    unsigned short int frameRival = 0;
    float tiempoAnimacionRival = 0.0;

    //Rival lanzador

    vector<unique_ptr<RivalLanzador>> rivalesLanzadores;
    vector<unique_ptr<Proyectil>> proyectiles;

    // Sprites del rival lanzador
    QPixmap spritesLanzador[4];

    // Imágenes de los dos lanzadores
    vector<QGraphicsPixmapItem*> imagenesLanzadores;
    vector<float> tiemposContactoLanzadores;

    // Tiempo de animación del disparo de cada lanzador
    vector<float> tiemposAnimacionDisparo;

    // Imágenes de los proyectiles
    QPixmap spritesProyectil[2];
    vector<QGraphicsPixmapItem*> imagenesProyectiles;

    vector<int> framesProyectiles;
    vector<float> tiemposAnimacionProyectiles;

    // Potenciadores
    vector<unique_ptr<Potenciador>> potenciadores;
    vector<QGraphicsPixmapItem*> imagenesPotenciadores;

    QPixmap spritesPotenciador[3];

    int framePotenciador = 0;
    float tiempoAnimacionPotenciador = 0.0;
    float intervaloAnimacionPotenciador = 0.2;

    void generarPotenciadores();
    void comprobarColisionPotenciador();
    float tiempoReaparicionPotenciador = 0.0;
    float intervaloReaparicionPotenciador = 8.0;


    Ui::MainWindow *ui;
    QGraphicsScene *escena;

    QTimer *temporizador; //genera actualizaciones periódicas
    QElapsedTimer reloj; //calcula tiempo transcurrido

    bool arriba = false;
    bool abajo = false;
    bool izquierda = false;
    bool derecha = false;

    void actualizarJuego(float dt); //actuliza la lógica del personaje y su representación gráfica

    void comprobarRecuperacionPelota();

    bool nivelCompletado = false;

    // Obstáculos lodosos
    const vector<unique_ptr<ZonaLodosa>>* zonasLodosas = nullptr; //guarda direcciones para poder consultar los vectores que pertenecen al nivel
    vector<QGraphicsPixmapItem*> imagenesZonasLodosas;
    QPixmap spriteBarro;

    // Huecos
    const vector<unique_ptr<Hueco>>* huecos = nullptr;
    vector<QGraphicsPixmapItem*> imagenesHuecos;
    QPixmap spriteHueco;

    void generarObstaculos();

    vector<bool> dentroZonasLodosas;
    vector<bool> dentroHuecos;

    void comprobarColisionZonaLodosa();

    void comprobarColisionHueco();

protected:
    void keyPressEvent(QKeyEvent *event) override; //override para sobreecribir este método heredado de QWidget
    void keyReleaseEvent(QKeyEvent *event) override; //detecta cuando se suelta una tecla
};
#endif // MAINWINDOW_H
