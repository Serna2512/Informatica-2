#include "Obstaculo.h"

Obstaculo::Obstaculo(float x, float y, float ancho, float alto)
{
    this->x = x;
    this->y = y;
    this->ancho = ancho;
    this->alto = alto;
}

Obstaculo::~Obstaculo()
{
}

float Obstaculo::getX() const
{
    return x;
}

float Obstaculo::getY() const
{
    return y;
}

float Obstaculo::getAncho() const
{
    return ancho;
}

float Obstaculo::getAlto() const
{
    return alto;
}
