#ifndef MORDECAI_H
#define MORDECAI_H
#include "Jugador.h"

enum class PrecisionTiro{
    BAJA,
    MEDIA,
    ALTA
};

class Mordecai : public Jugador{

private:
    PrecisionTiro precisionTiro;

public:

    Mordecai(float x, float y, unsigned short int vidaMaxima, float velocidad);

    ~Mordecai() override;

    PrecisionTiro evaluarTiro(float posicionBarra);
    void ejecutarTiro(float posicionBarra); //no va a tirar la pelota, eso se lo dejamos al nivel pero sí nos dice que tan bueno es el tiro

    void actualizar(float dt) override;

    //Getter
    PrecisionTiro getPrecisionTiro() const;
};

#endif // MORDECAI_H
