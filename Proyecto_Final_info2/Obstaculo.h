#ifndef OBSTACULO_H
#define OBSTACULO_H

class Jugador;

class Obstaculo
{
private:
    float x;
    float y;
    float ancho;
    float alto;

public:
    Obstaculo(float x, float y, float ancho, float alto);
    virtual ~Obstaculo();

    virtual void afectar(Jugador* jugador) = 0;

    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;
};

#endif // OBSTACULO_H