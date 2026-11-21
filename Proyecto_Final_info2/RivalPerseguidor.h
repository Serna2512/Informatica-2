#ifndef RIVALPERSEGUIDOR_H
#define RIVALPERSEGUIDOR_H

#include "Rival.h"

class Rigby;

class RivalPerseguidor : public Rival
{
private:
    Rigby* objetivo;

    float distanciaAnterior;
    unsigned int cantidadColisiones;
    unsigned int intentosEsquivar;

public:
    RivalPerseguidor(float x, float y, float velocidad, unsigned short int danio, Rigby* objetivo);

    ~RivalPerseguidor() override;

    //Agente autonomo
    float percibir();
    bool razonar(float distanciaActual);
    void actuar(bool bloquear, float dt, float distancia);
    void aprender(float distanciaActual);

    //Comportamientos
    void perseguir(float dt, float distancia);
    void bloquearCamino(float dt, float distancia);
    void atacar(Jugador* jugador) override;

    void actualizar(float dt) override;

    //Getters
    Rigby* getObjetivo() const;
    float getDistanciaAnterior() const;
    unsigned int getCantidadColisiones() const;
    unsigned int getIntentosEsquivar() const;

    //Setters
    void setObjetivo(Rigby* objetivo);
    void setDistanciaAnterior(float distancia);
    void setCantidadColisiones(unsigned int cantidad);
    void setIntentosEsquivar(unsigned int intentos);
};

#endif // RIVALPERSEGUIDOR_H