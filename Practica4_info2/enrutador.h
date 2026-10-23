#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>
using namespace std;

//uso map porque esta STL permite buscar por nombre (string), las otras por indices, lo que sería menos eficiente
//tambien porque se ordena por clave, ejemplo con A,B,C

class Enrutador {
public:
    // Costo que representa "destino sin ruta conocida"
    static constexpr int INFINITO = 1000000000;

private:
    string nombre;                       // identificador del enrutador
    map<string, int> vecinos;       // vecino -> costo del enlace directo
    map<string, int> tablaCostos;   // destino -> mejor costo conocido

public:

    Enrutador();
    explicit Enrutador(const string& nombre);

    // Identificador
    const string& getNombre() const;

    // Vecinos directamente conectados
    bool agregarVecino(const string& vecino, int costo);   // agrega o actualiza el costo
    bool eliminarVecino(const string& vecino);
    bool esVecino(const string& vecino) const;
    int getCostoEnlace(const string& vecino) const;        // INFINITO si no es vecino
    const map<string, int>& getVecinos() const;

    // Tabla de costos
    void reiniciarTabla();                                      // estado inicial: yo = 0 y mis vecinos directos
    void actualizarCosto(const string& destino, int costo);  // la Red entrega el resultado calculado
    int getCosto(const string& destino) const;             // INFINITO si no hay ruta
    const map<string, int>& getTablaCostos() const;

    // Presentacion
    void mostrarVecinos() const;
    void mostrarTabla() const;
};

#endif // ENRUTADOR_H