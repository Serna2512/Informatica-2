#include "pelota.h"
#include "jugador.h"

Pelota::Pelota(float x, float y, float radio)
    : x(x), y(y), radio(radio),
    velocidadX(0.0f), velocidadY(0.0f),
    estado(EstadoPelota::LIBRE), portador(nullptr)
{
}

Pelota::~Pelota()
{
}

void Pelota::lanzar(float vx, float vy)
{
    velocidadX = vx;
    velocidadY = vy;

    portador = nullptr;
    estado = EstadoPelota::EN_MOVIMIENTO;
}

void Pelota::detener()
{
    velocidadX = 0.0;
    velocidadY = 0.0;

    portador = nullptr;
    estado = EstadoPelota::DETENIDA;
}

void Pelota::transportarPor(Jugador* jugador)
{
    if (jugador == nullptr)
        return;

    portador = jugador;

    velocidadX = 0.0;
    velocidadY = 0.0;

    estado = EstadoPelota::TRANSPORTADA;

    x = jugador->getX();
    y = jugador->getY();
}

void Pelota::actualizar(float dt)
{
    if (dt <= 0.0f)
        return;

    if (estado == EstadoPelota::TRANSPORTADA)
    {
        if (portador != nullptr)
        {
            x = portador->getX();
            y = portador->getY();
        }
    }
    else if (estado == EstadoPelota::EN_MOVIMIENTO)
    {
        x += velocidadX * dt; //usamos ecuaciones de movimiento x=x_0 +v_x*t
        y += velocidadY * dt; //usamos ecuaciones de movimiento verticalmente también

        //v_y la modificamos en el nivel 2 con la gravedad
    }
}

// Getters

float Pelota::getX() const
{
    return x;
}

float Pelota::getY() const
{
    return y;
}

float Pelota::getRadio() const
{
    return radio;
}

float Pelota::getVelocidadX() const
{
    return velocidadX;
}

float Pelota::getVelocidadY() const
{
    return velocidadY;
}

EstadoPelota Pelota::getEstado() const
{
    return estado;
}

Jugador* Pelota::getPortador() const
{
    return portador;
}

// Setters

void Pelota::setX(float x)
{
    this->x = x;
}

void Pelota::setY(float y)
{
    this->y = y;
}

void Pelota::setRadio(float radio)
{
    if (radio > 0.0f)
        this->radio = radio;
}