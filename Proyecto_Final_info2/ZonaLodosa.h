#ifndef ZONALODOSA_H
#define ZONALODOSA_H

#include "Obstaculo.h"

class ZonaLodosa : public Obstaculo
{
private:
    float factorLentitud;

public:
    ZonaLodosa(float x, float y, float ancho, float alto, float factorLentitud);

    void afectar(Jugador* jugador) override;
};

#endif // ZONALODOSA_H