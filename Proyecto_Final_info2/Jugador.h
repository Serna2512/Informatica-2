#ifndef JUGADOR_H
#define JUGADOR_H


class Jugador{
private:

    float x;
    float y;
    unsigned short int vida;
    unsigned short int vidaMaxima;
    float velocidad;

public:
    Jugador(float x, float y, unsigned short int vidaMaxima, float velocidad);

    virtual ~Jugador();

    void mover(float dx, float dy);
    void recibirDanio(unsigned short int cantidad);
    bool estaVivo() const;

    virtual void actualizar(float dt) = 0; //clase abstracta para no crear jugadores genéricos

    //Getters
    float getX() const;
    float getY() const;
    unsigned short int getVida() const;
    unsigned short int getVidaMaxima() const;
    float getVelocidad() const;

    //Setters
    void setX(float x);
    void setY(float y);
    void setVida(unsigned short int vida);
    void setVidaMaxima(unsigned short int vidaMaxima);
    void setVelocidad(float velocidad);
};

#endif // JUGADOR_H
