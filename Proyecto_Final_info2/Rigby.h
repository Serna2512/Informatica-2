#ifndef RIGBY_H
#define RIGBY_H

#include "Jugador.h"

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

    float velocidadBase;

    float factorPotenciador;
    float factorLentitud;

    float duracionPotenciador;
    float duracionLentitud;

    void actualizarVelocidad();
    void restaurarVelocidad();

public:
    Rigby(float x, float y, unsigned short int vidaMaxima, float velocidad);

    ~Rigby() override; //override para identificar los métodos virtual de la clase padre

    void actualizar(float dt) override;

    void activarPotenciador(float factor, float duracion);
    void aplicarLentitud(float factor, float duracion);

    // Getters
    EstadoRigby getEstado() const;
    float getFactorPotenciador() const;
    float getFactorLentitud() const;
    float getDuracionPot() const;
    float getDuracionLen() const;

    // Setter
    void setDuracionEfecto(float duracion);
};

#endif // RIGBY_H