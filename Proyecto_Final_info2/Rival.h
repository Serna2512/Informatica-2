#ifndef RIVAL_H
#define RIVAL_H
#include <memory>
using namespace std;

class Jugador;
class Proyectil;

class Rival
{
private:
    float x;
    float y;
    float velocidad;
    unsigned short int danio;

public:
    Rival(float x, float y, float velocidad, unsigned short int danio);

    virtual ~Rival(); //destructor virtual para garantizar que,
                    //al destruir un objeto mediante un puntero a Rival, también se ejecute correctamente el destructor de su clase derivada

    virtual void actualizar(float dt) = 0;
    virtual unique_ptr<Proyectil> atacar(Jugador* objetivo) = 0; //método virtual puro ya que cada clase hija lo hace o usa de forma diferente,
                                                //tiene su propia forma de atacar
    //se usa unique_ptr para pasarle la propiedad de los poryectiles a la clase NivelConduccion

    //Getters
    float getX() const;
    float getY() const;
    float getVelocidad() const;
    unsigned short int getDanio() const;

    //Setters
    void setX(float x);
    void setY(float y);
    void setVelocidad(float velocidad);
    void setDanio(unsigned short int danio);
};

#endif // RIVAL_H