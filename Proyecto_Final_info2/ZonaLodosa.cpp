#include "ZonaLodosa.h"
#include "Rigby.h"

ZonaLodosa::ZonaLodosa(float x, float y, float ancho, float alto, float factorLentitud)
    : Obstaculo(x, y, ancho, alto)
{
    this->factorLentitud = factorLentitud;
}

void ZonaLodosa::afectar(Jugador* jugador) //afectar recibe Jugador* pero este método es de Rigby
{
    Rigby* rigby = dynamic_cast<Rigby*>(jugador);

    if (rigby == nullptr)
        return;

    rigby->aplicarLentitud(factorLentitud, 0.2);
}