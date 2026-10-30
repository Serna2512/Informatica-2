#ifndef CAMINO_H
#define CAMINO_H

#include <list>
#include <string>
using namespace std;

class Camino{
private:
    list<string> nodos;
    int costo = -1; //representa que no hay una ruta aún

public:

    Camino();

    void agregarNodo(string nombre);
    void establecerCosto(int nuevoCosto);

    int getCosto() const;
    const list<string>& getNodos() const;
    bool existe() const;
    void mostrar() const;
};

#endif // CAMINO_H
