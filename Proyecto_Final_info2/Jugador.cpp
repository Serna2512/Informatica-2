#include "jugador.h"

Jugador::Jugador(float x, float y, unsigned short int vidaMaxima, float velocidad)
{
    this->x = x;
    this->y = y;
    this->vidaMaxima = vidaMaxima;
    this->vida = vidaMaxima;
    this->velocidad = velocidad;
}

Jugador::~Jugador()
{
}

void Jugador::mover(float dx, float dy)
{
    x += dx;
    y += dy;
}

void Jugador::recibirDanio(unsigned short int cantidad)
{
    if (cantidad >= vida)
        vida = 0;
    else
        vida -= cantidad;
}

bool Jugador::estaVivo() const
{
    return vida > 0;
}

float Jugador::getX() const
{
    return x;
}

float Jugador::getY() const
{
    return y;
}

unsigned short int Jugador::getVida() const
{
    return vida;
}

unsigned short int Jugador::getVidaMaxima() const
{
    return vidaMaxima;
}

float Jugador::getVelocidad() const
{
    return velocidad;
}

void Jugador::setX(float x)
{
    this->x = x;
}

void Jugador::setY(float y)
{
    this->y = y;
}

void Jugador::setVida(unsigned short int vida)
{
    if (vida <= vidaMaxima)
        this->vida = vida;
}

void Jugador::setVidaMaxima(unsigned short int vidaMaxima)
{
    this->vidaMaxima = vidaMaxima;

    if (vida > vidaMaxima)
        vida = vidaMaxima;
}

void Jugador::setVelocidad(float velocidad)
{
    if (velocidad >= 0)
        this->velocidad = velocidad;
}