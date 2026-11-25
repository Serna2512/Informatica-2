#ifndef PELOTA_H
#define PELOTA_H

class Jugador; //declaracion adelantada

enum class EstadoPelota
{
    LIBRE,
    TRANSPORTADA,
    EN_MOVIMIENTO,
    DETENIDA
};

class Pelota
{
private:
    float x;
    float y;
    float radio;

    float velocidadX;
    float velocidadY;

    EstadoPelota estado;
    Jugador* portador;

public:
    Pelota(float x, float y, float radio);

    ~Pelota();

    void lanzar(float vx, float vy);
    void detener();
    void transportarPor(Jugador* jugador);

    void actualizar(float dt);

    void actualizarPosicionTransportada(float desplazamientoX, float desplazamientoY); //actualiza la posicion lógica mientras está
    //siendo transportada

    //Getters
    float getX() const;
    float getY() const;
    float getRadio() const;
    float getVelocidadX() const;
    float getVelocidadY() const;
    EstadoPelota getEstado() const;
    Jugador* getPortador() const;

    //Setters
    void setX(float x);
    void setY(float y);
    void setRadio(float radio);
};

#endif // PELOTA_H