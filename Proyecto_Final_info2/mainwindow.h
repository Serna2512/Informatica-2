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
    unique_ptr<Rigby> rigby; //objeto de la clase rigby (puntero unico a esta clase) //unique_ptr porque mainwindow es responsable de
    //administrar este objeto (de momento)

    vector<QPixmap> spritesRigby; //vector que cotiene los sprites de Rigby
    vector<QPixmap> spritesRigbyIzquierda; //vector de sprites pero mirando hacia atras
    bool mirandoIzquierda = false;

    //crear balón
    QGraphicsEllipseItem* imagenPelota;
    unique_ptr<Pelota> pelota; //objeto pelota de clase pelota, unique porque esta clase administra temporalemente este objeto
    float ultimaDireccionX = 1.0; //ultimas dirreciones por si rigby se queda quieto hacer que la pelota esté correctamente ubicada
    float ultimaDireccionY = 0.0;
    float tiempoBloqueoRecuperacion = 0.0;


    int frameActual = 0; //sprite que mostramos
    float tiempoAnimacion = 0.0; //tiempo acumulado desde la última actualizacion de un srpite
    float intervaloAnimacion = 0.12; //tiempo arbitrario para cambiar el sprite

    //Rival perseguidor
    unique_ptr<RivalPerseguidor> rivalPerseguidor;
    QGraphicsEllipseItem* imagenRival;

    QGraphicsPixmapItem* imagenRigby; //imagen que aparece en la pantalla

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
    vector<unique_ptr<ZonaLodosa>> zonasLodosas; //coleccion de punteros a clase ZonaLodosa, cada elemento tendrá su propio objeto
    vector<QGraphicsRectItem*> imagenesZonasLodosas; //coleccion de punteros GraphicsRectItem

    // Huecos
    vector<unique_ptr<Hueco>> huecos; //coleccion de punteros a clase Hueco, cada elemento tendrá su propio objeto
    vector<QGraphicsRectItem*> imagenesHuecos;

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
