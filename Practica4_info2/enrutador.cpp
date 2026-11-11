#include "Enrutador.h"
#include <iostream>
using namespace std;

// ---------- Constructores ----------

Enrutador::Enrutador() {
}

Enrutador::Enrutador(const string& nombre) : nombre(nombre) {
    // Al encenderse, la tabla solo conoce al propio enrutador
    reiniciarTabla();
}

// ---------- Identificador ----------

const
    string& Enrutador::getNombre() const {
    return nombre;
}

// ---------- Vecinos ----------

bool Enrutador::agregarVecino(const
                              string& vecino, int costo) {
    // Un enrutador no puede conectarse consigo mismo y el costo debe ser positivo
    if (vecino.empty() || vecino == nombre || costo <= 0) {
        return false;
    }
    vecinos[vecino] = costo;   // si ya existia, actualiza el costo
    return true;
}

bool Enrutador::eliminarVecino(const
                               string& vecino) {
    return vecinos.erase(vecino) > 0;
}

bool Enrutador::esVecino(const
                         string& vecino) const {
    return vecinos.find(vecino) != vecinos.end();
}

int Enrutador::getCostoEnlace(const string& vecino) const {
    map<string, int>::const_iterator it = vecinos.find(vecino);
    if (it == vecinos.end()) {
        return INFINITO;
    }
    return it->second;
}

const map<string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

// ---------- Tabla de costos ----------

void Enrutador::reiniciarTabla() {
    tablaCostos.clear();
    tablaCostos[nombre] = 0;                       // costo hacia si mismo
    for (
        map<
            string, int>::const_iterator it = vecinos.begin();
         it != vecinos.end(); ++it) {
        tablaCostos[it->first] = it->second;       // enlaces directos
    }
}

void Enrutador::actualizarCosto(const
                                string& destino, int costo) {
    if (costo >= INFINITO) {
        tablaCostos.erase(destino);                // sin ruta: no se guarda
    } else {
        tablaCostos[destino] = costo;
    }
}

int Enrutador::getCosto(const
                        string& destino) const {

    map<
        string, int>::const_iterator it = tablaCostos.find(destino);
    if (it == tablaCostos.end()) {
        return INFINITO;
    }
    return it->second;
}

const
    map<
    string, int>& Enrutador::getTablaCostos() const {
    return tablaCostos;
}

// ---------- Presentacion ----------

void Enrutador::mostrarVecinos() const {

    cout << "Vecinos de " << nombre << ":" <<
        endl;
    if (vecinos.empty()) {

        cout << "  (ninguno)" <<
            endl;
    }
    for (
        map<
            string, int>::const_iterator it = vecinos.begin();
         it != vecinos.end(); ++it) {

        cout << "  " << it->first << " (costo " << it->second << ")" <<
            endl;
    }
}

void Enrutador::mostrarTabla() const {

    cout << "Tabla de costos de " << nombre << ":" <<
        endl;
    for (
        map<string, int>::const_iterator it = tablaCostos.begin(); it != tablaCostos.end(); ++it) {

        cout << "  -> " << it->first << " : " << it->second <<
            endl;
    }
}