#ifndef RIGBY_H
#define RIGBY_H

#include "jugador.h"

enum class EstadoRigby
{
    NORMAL,
    POTENCIADO,
    RELENTIZADO
};

class Rigby : public Jugador
{
private:
    EstadoRigby estado;
    float duracionEfecto;
    float factorVelocidadActual;

    void restaurarVelocidad();

public:
    Rigby(float x, float y, unsigned short int vidaMaxima, float velocidad);

    ~Rigby() override; //override para identificar los métodos virtual de la clase padre

    void actualizar(float dt) override;

    void activarPotenciador(float factor, float duracion);
    void aplicarLentitud(float factor, float duracion);

    // Getters
    EstadoRigby getEstado() const;
    float getDuracionEfecto() const;
    float getFactorVelocidadActual() const;

    // Setter
    void setDuracionEfecto(float duracion);
};

#endif // RIGBY_H