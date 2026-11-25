#include "Hueco.h"
#include "Jugador.h"

Hueco::Hueco(float x, float y, float ancho, float alto, unsigned int danio)
    : Obstaculo(x, y, ancho, alto)
{
    this->danio = danio;
}

void Hueco::afectar(Jugador* jugador)
{
    if (jugador == nullptr)
        return;

    jugador->recibirDanio(danio);
}