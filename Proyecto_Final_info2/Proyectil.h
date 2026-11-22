#ifndef PROYECTIL_H
#define PROYECTIL_H

class Jugador;

class Proyectil
{
private:
    float x;
    float y;
    float velocidadX;
    float velocidadY;
    unsigned short int danio;
    bool activo;

public:
    Proyectil(float x, float y, float velocidadX, float velocidadY, unsigned short int danio);

    void actualizar(float dt);
    void impactar(Jugador* jugador);
    void desactivar();

    // Getters
    float getX() const;
    float getY() const;
    float getVelocidadX() const;
    float getVelocidadY() const;
    unsigned short int getDanio() const;
    bool getActivo() const;
};

#endif // PROYECTIL_H