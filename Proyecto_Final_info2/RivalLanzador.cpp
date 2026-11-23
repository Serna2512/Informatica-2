#include "RivalLanzador.h"
#include "Proyectil.h"
#include "Jugador.h"

#include <cmath>

RivalLanzador::RivalLanzador(float x, float y, float velocidad, unsigned short int danio, float intervaloLanzamiento,
                             float velocidadProyectil)
    : Rival(x, y, velocidad, danio),
    intervaloLanzamiento(intervaloLanzamiento),
    tiempoUltimoLanzamiento(0.0),
    velocidadProyectil(velocidadProyectil)
{
}

RivalLanzador::~RivalLanzador()
{
}

void RivalLanzador::actualizar(float dt)
{
    if (dt <= 0.0){
        return;}

    tiempoUltimoLanzamiento += dt;
}

bool RivalLanzador::estaListoParaAtacar() const
{
    return tiempoUltimoLanzamiento >= intervaloLanzamiento;
}

unique_ptr<Proyectil> RivalLanzador::atacar(Jugador* objetivo)
{
    if (objetivo == nullptr || !estaListoParaAtacar()){
        return nullptr;}

    unique_ptr<Proyectil> proyectil = lanzarObjeto(objetivo);

    if (proyectil != nullptr){
        tiempoUltimoLanzamiento = 0.0;}

    return proyectil; //devolvemos el proyectil para darle la propiedad al nivel
}


unique_ptr<Proyectil>RivalLanzador::lanzarObjeto(Jugador* objetivo)
{
    float dx = objetivo->getX() - getX();
    float dy = objetivo->getY() - getY();

    float distancia = sqrt(dx * dx + dy * dy);

    if (distancia <= 0.0){
        return nullptr;}

    float velocidadX = (dx / distancia) * velocidadProyectil;
    float velocidadY = (dy / distancia) * velocidadProyectil;

    unique_ptr<Proyectil> proyectil (new Proyectil(getX(), getY(), velocidadX, velocidadY, getDanio())); //crear objeto dinamico y obtener un puntero a este
    //que administra su memoria
    return proyectil;
}


float RivalLanzador::getIntervaloLanzamiento() const
{
    return intervaloLanzamiento;
}

float RivalLanzador::getTiempoUltimoLanzamiento() const
{
    return tiempoUltimoLanzamiento;
}

float RivalLanzador::getVelocidadProyectil() const
{
    return velocidadProyectil;
}

void RivalLanzador::setIntervaloLanzamiento(float intervalo)
{
    if (intervalo > 0.0)
        intervaloLanzamiento = intervalo;
}

void RivalLanzador::setVelocidadProyectil(float velocidad)
{
    if (velocidad > 0.0)
        velocidadProyectil = velocidad;
}