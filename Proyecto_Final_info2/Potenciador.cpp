#include "Potenciador.h"
#include "Rigby.h"

Potenciador::Potenciador(float x, float y, float ancho, float alto, float factorAumento, float duracion)
    : x(x), y(y), ancho(ancho), alto(alto),
    factorAumento(factorAumento), duracion(duracion),
    activo(true)
{
}

bool Potenciador::recoger(Rigby* jugador)
{
    if (jugador == nullptr || !activo)
        return false;

    jugador->activarPotenciador(factorAumento, duracion);

    activo = false;

    return true;
}

float Potenciador::getX() const
{
    return x;
}

float Potenciador::getY() const
{
    return y;
}

float Potenciador::getAncho() const
{
    return ancho;
}

float Potenciador::getAlto() const
{
    return alto;
}

float Potenciador::getFactorAumento() const
{
    return factorAumento;
}

float Potenciador::getDuracion() const
{
    return duracion;
}

bool Potenciador::estaActivo() const
{
    return activo;
}

void Potenciador::desactivar()
{
    activo = false;
}