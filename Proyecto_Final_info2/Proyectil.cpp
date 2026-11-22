#include "proyectil.h"
#include "jugador.h"

Proyectil::Proyectil(float x, float y, float velocidadX, float velocidadY, unsigned short int danio)
    : x(x), y(y),
    velocidadX(velocidadX),
    velocidadY(velocidadY),
    danio(danio),
    activo(true)
{
}

void Proyectil::actualizar(float dt)
{
    if (dt <= 0.0 || !activo)
        return;

    x += velocidadX * dt;
    y += velocidadY * dt;
}

void Proyectil::impactar(Jugador* jugador)
{
    if (!activo || jugador == nullptr)
        return;

    jugador->recibirDanio(danio);
    activo = false;
}

void Proyectil::desactivar()
{
    activo = false;
}

float Proyectil::getX() const
{
    return x;
}

float Proyectil::getY() const
{
    return y;
}

float Proyectil::getVelocidadX() const
{
    return velocidadX;
}

float Proyectil::getVelocidadY() const
{
    return velocidadY;
}

unsigned short int Proyectil::getDanio() const
{
    return danio;
}

bool Proyectil::getActivo() const
{
    return activo;
}