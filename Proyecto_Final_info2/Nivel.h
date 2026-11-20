#ifndef NIVEL_H
#define NIVEL_H

class Nivel
{
private:
    bool activo;

public:
    Nivel();
    virtual ~Nivel(); //destructor virtual permite destruir correctamente los objetos derivados cuando se eliminan por medio de un puntero
    //virtual permite que las clases hijas sobreescriban los métodos

    virtual void iniciar();
    virtual void actualizar(float dt) = 0; //cada nivel implementa su propia actualizacion
    virtual void finalizar(); //implementacion común desde esta clase base

    bool getActivo() const;
};

#endif // NIVEL_H