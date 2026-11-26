#include "Rigby.h"
#include <QDebug>

Rigby::Rigby(float x, float y, unsigned short int vidaMaxima, float velocidad)
    : Jugador(x, y, vidaMaxima, velocidad) //creamos objeto mediante constructor clase padre además de sus atributos propios
{
    estado = EstadoRigby::NORMAL;
    duracionEfecto = 0.0;
    factorVelocidadActual = 1.0;
}

Rigby::~Rigby()
{
}

void Rigby::actualizar(float dt)
{
    if (dt <= 0 || estado == EstadoRigby::NORMAL)
        return;

    duracionEfecto -= dt;

    if (duracionEfecto <= 0)
        restaurarVelocidad();
}

void Rigby::activarPotenciador(float factor, float duracion)
{
    if (factor <= 1.0 || factor > 5 || duracion <= 0)
        return;

    restaurarVelocidad(); //siempre reinicamos velocidad para evitar cambios inesperados entre superficies

    setVelocidad(getVelocidad() * factor);

    factorVelocidadActual = factor; //factor que tiene actualmente la velocidad
    duracionEfecto = duracion;
    estado = EstadoRigby::POTENCIADO;
}

void Rigby::aplicarLentitud(float factor, float duracion)
{
    if (factor <= 0.0 || factor >= 1.0 || duracion <= 0.0)
        return;

    // Reducir la velocidad solamente al comenzar el efecto
    if (estado != EstadoRigby::RELENTIZADO) {
        setVelocidad(getVelocidad() * factor);
        factorVelocidadActual = factor;
        estado = EstadoRigby::RELENTIZADO;
    }

    // Renovar la duración mientras permanezca en el barro
    duracionEfecto = duracion;
}

void Rigby::restaurarVelocidad()
{
    if (estado != EstadoRigby::NORMAL)
    {
        setVelocidad(getVelocidad() / factorVelocidadActual); //velocidad actual entre el factor para volver a la vel original

        factorVelocidadActual = 1.0;
        duracionEfecto = 0.0;
        estado = EstadoRigby::NORMAL;
    }
}

EstadoRigby Rigby::getEstado() const
{
    return estado;
}

float Rigby::getDuracionEfecto() const
{
    return duracionEfecto;
}

float Rigby::getFactorVelocidadActual() const
{
    return factorVelocidadActual;
}

void Rigby::setDuracionEfecto(float duracion)
{
    if (duracion > 0)
        duracionEfecto = duracion;
}