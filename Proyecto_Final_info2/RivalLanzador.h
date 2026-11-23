#ifndef RIVALLANZADOR_H
#define RIVALLANZADOR_H

#include "Rival.h"
#include <memory>

class Jugador;
class Proyectil;

class RivalLanzador : public Rival
{
private:
    float intervaloLanzamiento;
    float tiempoUltimoLanzamiento;
    float velocidadProyectil;

    unique_ptr<Proyectil> lanzarObjeto(Jugador* objetivo); //método privado para evitar que otras clases creen proyectiles a través de
    //este método

public:
    RivalLanzador(float x, float y, float velocidad, unsigned short int danio, float intervaloLanzamiento, float velocidadProyectil);

    ~RivalLanzador() override;

    void actualizar(float dt) override;

    unique_ptr<Proyectil> atacar(Jugador* objetivo) override; //no tenemos vector de proyectiles porque
    //este rival solo los crea y pasa su autridad, no necesita almacenarlos

    //Getters
    float getIntervaloLanzamiento() const;
    float getTiempoUltimoLanzamiento() const;
    float getVelocidadProyectil() const;

    //Setters
    void setIntervaloLanzamiento(float intervalo);
    void setVelocidadProyectil(float velocidad);

    bool estaListoParaAtacar() const;
};

#endif // RIVALLANZADOR_H