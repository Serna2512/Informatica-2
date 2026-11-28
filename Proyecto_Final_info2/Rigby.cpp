#include "Rigby.h"
#include <QDebug>

Rigby::Rigby(float x, float y, unsigned short int vidaMaxima, float velocidad)
    : Jugador(x, y, vidaMaxima, velocidad)
{
    estado = EstadoRigby::NORMAL;

    velocidadBase = velocidad;

    factorPotenciador = 1.0; //inicializar cada factor independiente para no sobreescribir un solo factor de velocidad
    factorLentitud = 1.0;

    duracionPotenciador = 0.0;
    duracionLentitud = 0.0;
}

Rigby::~Rigby()
{
}

void Rigby::actualizar(float dt)
{
    if (dt <= 0.0)
        return;

    // Actualizar potenciador
    if (duracionPotenciador > 0.0) {

        duracionPotenciador -= dt;

        if (duracionPotenciador <= 0.0) {
            duracionPotenciador = 0.0;
            factorPotenciador = 1.0;
        }
    }

    // Actualizar lentitud
    if (duracionLentitud > 0.0) {

        duracionLentitud -= dt;

        if (duracionLentitud <= 0.0) {
            duracionLentitud = 0.0;
            factorLentitud = 1.0;
        }
    }

    actualizarVelocidad();

    // Actualizar estado
    if (factorPotenciador > 1.0)
        estado = EstadoRigby::POTENCIADO;

    else if (factorLentitud < 1.0)
        estado = EstadoRigby::RELENTIZADO;

    else
        estado = EstadoRigby::NORMAL;
}

void Rigby::activarPotenciador(float factor, float duracion)
{
    if (factor <= 1.0 || factor > 5.0 || duracion <= 0.0)
        return;

    factorPotenciador = factor;
    duracionPotenciador = duracion;

    actualizarVelocidad();

    estado = EstadoRigby::POTENCIADO;
}

void Rigby::aplicarLentitud(float factor, float duracion)
{
    if (factor <= 0.0 || factor >= 1.0 || duracion <= 0.0)
        return;

    factorLentitud = factor;
    duracionLentitud = duracion;

    actualizarVelocidad();

    if (factorPotenciador == 1.0)
        estado = EstadoRigby::RELENTIZADO;
}

void Rigby::restaurarVelocidad()
{
    factorPotenciador = 1.0;
    factorLentitud = 1.0;

    duracionPotenciador = 0.0;
    duracionLentitud = 0.0;

    estado = EstadoRigby::NORMAL;

    actualizarVelocidad();
}

void Rigby::actualizarVelocidad()
{
    float velocidadActual = velocidadBase * factorPotenciador * factorLentitud;

    setVelocidad(velocidadActual);
}

EstadoRigby Rigby::getEstado() const
{
    return estado;
}

float Rigby::getFactorPotenciador() const{
    return factorPotenciador;
}

float Rigby::getFactorLentitud() const{
    return factorLentitud;
}

float Rigby::getDuracionPot() const{
    return duracionPotenciador;
}

float Rigby::getDuracionLen() const{
    return duracionLentitud;
}