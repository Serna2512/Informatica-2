#include "Rivalperseguidor.h"
#include "Rigby.h"
#include "Jugador.h"
#include <cmath>

RivalPerseguidor::RivalPerseguidor(float x, float y, float velocidad, unsigned short int danio, Rigby* objetivo)
    : Rival(x, y, velocidad, danio),
    objetivo(objetivo),
    distanciaAnterior(0.0),
    cantidadColisiones(0),
    intentosEsquivar(0)
{
}

RivalPerseguidor::~RivalPerseguidor()
{
}

float RivalPerseguidor::percibir()
{
    if (objetivo == nullptr)
        return -1.0;

    float dx = objetivo->getX() - getX(); //separación entre objetos pero desde coordenadas
    float dy = objetivo->getY() - getY();

    float distancia = sqrt(dx * dx + dy * dy); //distancia real entre jugador y rivalP

    return distancia; //retornamos esa distancia real
}

bool RivalPerseguidor::razonar(float distanciaActual) //si el rival se está acercando a rigby que siga, pero si no, que bloquee el paso
{
    if (distanciaActual < 0.0){
        return false;}

    if (distanciaAnterior <= 0.0){
        return false;}

    if (distanciaActual >= distanciaAnterior){ //bloaquear camino
        return true;}

    return false;
}

void RivalPerseguidor::aprender(float distanciaActual)
{
    if (distanciaActual < 0.0)
        return;

    distanciaAnterior = distanciaActual; //conserva la distancia obtenida antes del movimiento
}

void RivalPerseguidor::actuar(bool bloquear, float dt, float distancia)
{
    if (bloquear)
        bloquearCamino(dt, distancia);
    else
        perseguir(dt, distancia);
}

void RivalPerseguidor::perseguir(float dt, float distancia)
{
    if (objetivo == nullptr || dt <= 0.0){
        return;}

    float dx = objetivo->getX() - getX();
    float dy = objetivo->getY() - getY();

    float desplazamiento = getVelocidad() * dt;

    if (desplazamiento >= distancia) //evitamos que el rival sobrepase la posicion de rigby, si están muy cerca seteamos por de rival
                                    //a la de rigby
    {
        setX(objetivo->getX());
        setY(objetivo->getY());
    }
    else
    {
        setX(getX() + (dx / distancia) * desplazamiento); //a la posicion actual del rival le sumamos el desplazamiento
        setY(getY() + (dy / distancia) * desplazamiento);
    }
}

void RivalPerseguidor::bloquearCamino(float dt, float distancia)
{
    if (objetivo == nullptr || dt <= 0.0 || distancia <= 0.01){
        return;}

    // Calculamos un punto lateral respecto a Rigby
    const float distanciaLateral = 50.0;

    float dx = objetivo->getX() - getX();
    float dy = objetivo->getY() - getY();

    float puntoX = objetivo->getX() - (dy / distancia) * distanciaLateral; //desplazamiento laterales en los ejes respectivos
    float puntoY = objetivo->getY() + (dx / distancia) * distanciaLateral;

    //Calculamos el desplazamiento hacia ese punto
    float dxPunto = puntoX - getX();
    float dyPunto = puntoY - getY();

    float distanciaPunto = sqrt(dxPunto * dxPunto + dyPunto * dyPunto);

    if (distanciaPunto <= 0.01){
        return;}

    float desplazamiento = getVelocidad() * dt;

    if (desplazamiento >= distanciaPunto)
    {
        setX(puntoX);
        setY(puntoY);
    }
    else
    {
        setX(getX() + (dxPunto / distanciaPunto) * desplazamiento);
        setY(getY() + (dyPunto / distanciaPunto) * desplazamiento);
    }
}

void RivalPerseguidor::atacar(Jugador* jugador)
{
    if (jugador == nullptr){
        return;}

    jugador->recibirDanio(getDanio());

    cantidadColisiones++;
}

void RivalPerseguidor::actualizar(float dt)
{
    if (dt <= 0.0 || objetivo == nullptr){
        return;}

    float distanciaActual = percibir(); //obtenemos informacion de la distancia entre ribgy y rival

    if (distanciaActual < 0.0){
        return;}

    bool bloquear = razonar(distanciaActual); //vemos cual estrategia utilizar

    actuar(bloquear, dt, distanciaActual); //actua según el razonamiento

    aprender(distanciaActual); //actualiza la distancia
}