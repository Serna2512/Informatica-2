#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"
#include "camino.h"
using namespace std;

// La Red es la dueña de todos los enrutadores y la unica que conoce la
// topologia completa. Calcula los caminos mas cortos (Dijkstra) y entrega
// a cada enrutador su tabla de costos.
class Red {
private:
    map<string, Enrutador> enrutadores;   // nombre -> enrutador

    // Costos minimos desde 'origen' hacia todos los alcanzables
    void dijkstra(const string& origen, map<string, int>& dist) const;

public:
    Red();

    // Gestion de la topologia (todas recalculan las tablas al terminar)
    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);
    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    // Actualiza la tabla de costos de cada enrutador
    void recalcularTablas();

    // Consultas
    bool existeEnrutador(const string& nombre) const;
    const Enrutador* getEnrutador(const string& nombre) const;   // nullptr si no existe
    unsigned int cantidadEnrutadores() const;

    // Presentacion
    void mostrarRed() const;       // enrutadores y sus enlaces
    void mostrarTablas() const;    // tabla de costos conjunta de toda la red

    bool cargarDesdeArchivo(const string& nombreArchivo);
    bool guardarEnArchivo(const string& nombreArchivo) const;

    Camino obtenerCamino(const string& origen, const string& destino);
};

#endif // RED_H