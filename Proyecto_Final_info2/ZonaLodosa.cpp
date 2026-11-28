#include "ZonaLodosa.h"
#include "Rigby.h"

ZonaLodosa::ZonaLodosa(float x, float y, float ancho, float alto, float factorLentitud)
    : Obstaculo(x, y, ancho, alto)
{
    this->factorLentitud = factorLentitud;
}

void ZonaLodosa::afectar(Jugador* jugador) //afectar recibe Jugador* pero este método es de Rigby, verificar si si recibe un Rigby
{
    Rigby* rigby = dynamic_cast<Rigby*>(jugador); //comprobar el tipo del objeto en tiempo de ejecución

    if (rigby == nullptr)
        return;

    rigby->aplicarLentitud(factorLentitud, 0.2);
}