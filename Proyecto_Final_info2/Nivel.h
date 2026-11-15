#ifndef NIVEL_H
#define NIVEL_H

class Nivel
{
private:
    bool activo;

public:
    Nivel();
    virtual ~Nivel(); //destructor virtual permite destruir correctamente los objetos derivados cuando se eliminan por medio de un puntero

    virtual void iniciar();
    virtual void actualizar(float dt) = 0; //cada nivel implementa su propia actualizacion
    virtual void finalizar() = 0; //cada nivel decide cómo terminar

    bool getActivo() const;
};

#endif // NIVEL_H