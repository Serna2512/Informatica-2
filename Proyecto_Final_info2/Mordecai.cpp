#include "mordecai.h"

Mordecai::Mordecai(float x, float y, unsigned short int vidaMaxima, float velocidad)
    : Jugador(x, y, vidaMaxima, velocidad)
{
    precisionTiro = PrecisionTiro::BAJA;
}

Mordecai::~Mordecai()
{
}

PrecisionTiro Mordecai::evaluarTiro(float posicionBarra)
{
    // Estos rangos son ilustrativos.
    // Los ajustaremos según las dimensiones de la barra.

    if (posicionBarra >= 45.0 && posicionBarra <= 55.0)
        precisionTiro = PrecisionTiro::ALTA;
    else if (posicionBarra >= 30.0 && posicionBarra <= 70.0)
        precisionTiro = PrecisionTiro::MEDIA;
    else
        precisionTiro = PrecisionTiro::BAJA;

    return precisionTiro;
}

void Mordecai::ejecutarTiro(float posicionBarra)
{
    PrecisionTiro precision = evaluarTiro(posicionBarra);

    // La precisión se utiliza para determinar
    // las condiciones iniciales del lanzamiento.
    // NivelTiroEsquina se encargará de lanzar la pelota.
    (void)precision;
}

void Mordecai::actualizar(float dt)
{
    // Mordecai no tiene un comportamiento temporal
    // propio por ahora. Se implementa porque Jugador
    // declara actualizar() como método virtual puro.
    (void)dt;
}

PrecisionTiro Mordecai::getPrecisionTiro() const
{
    return precisionTiro;
}