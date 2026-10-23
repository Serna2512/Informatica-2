#include "Enrutador.h"
#include <iostream>

// ---------- Constructores ----------

Enrutador::Enrutador() {
}

Enrutador::Enrutador(const std::string& nombre) : nombre(nombre) {
    // Al encenderse, la tabla solo conoce al propio enrutador
    reiniciarTabla();
}

// ---------- Identificador ----------

const std::string& Enrutador::getNombre() const {
    return nombre;
}

// ---------- Vecinos ----------

bool Enrutador::agregarVecino(const std::string& vecino, int costo) {
    // Un enrutador no puede conectarse consigo mismo y el costo debe ser positivo
    if (vecino.empty() || vecino == nombre || costo <= 0) {
        return false;
    }
    vecinos[vecino] = costo;   // si ya existia, actualiza el costo
    return true;
}

bool Enrutador::eliminarVecino(const std::string& vecino) {
    return vecinos.erase(vecino) > 0;
}

bool Enrutador::esVecino(const std::string& vecino) const {
    return vecinos.find(vecino) != vecinos.end();
}

int Enrutador::getCostoEnlace(const std::string& vecino) const {
    std::map<std::string, int>::const_iterator it = vecinos.find(vecino);
    if (it == vecinos.end()) {
        return INFINITO;
    }
    return it->second;
}

const std::map<std::string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

// ---------- Tabla de costos ----------

void Enrutador::reiniciarTabla() {
    tablaCostos.clear();
    tablaCostos[nombre] = 0;                       // costo hacia si mismo
    for (std::map<std::string, int>::const_iterator it = vecinos.begin();
         it != vecinos.end(); ++it) {
        tablaCostos[it->first] = it->second;       // enlaces directos
    }
}

void Enrutador::actualizarCosto(const std::string& destino, int costo) {
    if (costo >= INFINITO) {
        tablaCostos.erase(destino);                // sin ruta: no se guarda
    } else {
        tablaCostos[destino] = costo;
    }
}

int Enrutador::getCosto(const std::string& destino) const {
    std::map<std::string, int>::const_iterator it = tablaCostos.find(destino);
    if (it == tablaCostos.end()) {
        return INFINITO;
    }
    return it->second;
}

const std::map<std::string, int>& Enrutador::getTablaCostos() const {
    return tablaCostos;
}

// ---------- Presentacion ----------

void Enrutador::mostrarVecinos() const {
    std::cout << "Vecinos de " << nombre << ":" << std::endl;
    if (vecinos.empty()) {
        std::cout << "  (ninguno)" << std::endl;
    }
    for (std::map<std::string, int>::const_iterator it = vecinos.begin();
         it != vecinos.end(); ++it) {
        std::cout << "  " << it->first << " (costo " << it->second << ")" << std::endl;
    }
}

void Enrutador::mostrarTabla() const {
    std::cout << "Tabla de costos de " << nombre << ":" << std::endl;
    for (std::map<std::string, int>::const_iterator it = tablaCostos.begin();
         it != tablaCostos.end(); ++it) {
        std::cout << "  -> " << it->first << " : " << it->second << std::endl;
    }
}