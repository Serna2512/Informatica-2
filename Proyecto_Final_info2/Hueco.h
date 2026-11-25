#ifndef HUECO_H
#define HUECO_H

#include "obstaculo.h"

class Hueco : public Obstaculo
{
private:
    unsigned int danio;

public:
    Hueco(float x, float y, float ancho, float alto, unsigned int danio);

    void afectar(Jugador* jugador) override;
};

#endif // HUECO_H