#include "rival.h"

Rival::Rival(float x, float y, float velocidad,  unsigned short int danio)
    : x(x), y(y), velocidad(velocidad), danio(danio)
{
}

Rival::~Rival()
{
}

//Getters

float Rival::getX() const
{
    return x;
}

float Rival::getY() const
{
    return y;
}

float Rival::getVelocidad() const
{
    return velocidad;
}

unsigned short int Rival::getDanio() const
{
    return danio;
}

// Setters

void Rival::setX(float x)
{
    this->x = x;
}

void Rival::setY(float y)
{
    this->y = y;
}

void Rival::setVelocidad(float velocidad)
{
    if (velocidad >= 0.0)
        this->velocidad = velocidad;
}

void Rival::setDanio(unsigned short int danio)
{
    this->danio = danio;
}