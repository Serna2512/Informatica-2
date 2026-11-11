#include "Camino.h"
#include <iostream>
using namespace std;

Camino::Camino() {
    costo = -1;
}

void Camino::agregarNodo(string nombre) {
    nodos.push_back(nombre); //push_back para agregar al final de la lista (aunque no haya contiguidad)
}

void Camino::establecerCosto(int nuevoCosto) {
    costo = nuevoCosto;
}

int Camino::getCosto() const {
    return costo;
}

const list<string>& Camino::getNodos() const {
    return nodos; //referencia a la lista
}

bool Camino::existe() const {
    return !nodos.empty() && costo >= 0;
}

void Camino::mostrar() const {
    if (!existe()) {
        cout << "No existe un camino valido." << endl;
        return;
    }

    cout << "Camino: ";

    for (auto it = nodos.begin(); it != nodos.end(); ++it) { //iterador específico para esta lista
        if (it != nodos.begin()) {
            cout << " -> ";
        }

        cout << *(it);
    }

    cout << endl;
    cout << "Costo total: " << costo << endl;
}
