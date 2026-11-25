#include "Pelota.h"
#include "Jugador.h"
#include <cmath>

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
    if (dt <= 0.0)
        return;

    if (estado != EstadoPelota::EN_MOVIMIENTO)
        return;

    // Calcular la rapidez actual
    float rapidez = sqrt(velocidadX * velocidadX + velocidadY * velocidadY);

    // Evitar cálculos innecesarios
    if (rapidez <= 0.01) {
        velocidadX = 0.0;
        velocidadY = 0.0;
        estado = EstadoPelota::DETENIDA;
        return;
    }

    // Desaceleración causada por la fricción
    const float desaceleracion = 80.0;

    float nuevaRapidez = rapidez - desaceleracion * dt;

    if (nuevaRapidez < 0.0)
        nuevaRapidez = 0.0;

    // Calcular la dirección del movimiento
    float direccionX = velocidadX / rapidez;
    float direccionY = velocidadY / rapidez;

    // Actualizar posición usando la velocidad promedio
    float rapidezPromedio = (rapidez + nuevaRapidez) / 2.0;

    x += direccionX * rapidezPromedio * dt;
    y += direccionY * rapidezPromedio * dt;

    // Actualizar velocidades
    velocidadX = direccionX * nuevaRapidez;
    velocidadY = direccionY * nuevaRapidez;

    // Si perdió toda su velocidad, detenerla
    if (nuevaRapidez == 0.0) {
        velocidadX = 0.0;
        velocidadY = 0.0;
        estado = EstadoPelota::DETENIDA;
    }
}

void Pelota::actualizarPosicionTransportada(float desplazamientoX, float desplazamientoY)
{
    if (estado != EstadoPelota::TRANSPORTADA || portador == nullptr)
        return;

    x = portador->getX() + desplazamientoX;
    y = portador->getY() + desplazamientoY;
}

void Pelota::desprender(float velocidadX, float velocidadY)
{
    if (estado != EstadoPelota::TRANSPORTADA)
        return;

    portador = nullptr;

    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;

    estado = EstadoPelota::EN_MOVIMIENTO;
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