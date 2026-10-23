#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

//uso map porque esta STL permite buscar por nombre (string), las otras por indices, lo que sería menos eficiente
//tambien porque se ordena por clave, ejemplo con A,B,C

class Enrutador {
public:
    // Costo que representa "destino sin ruta conocida"
    static constexpr int INFINITO = 1000000000;

private:
    std::string nombre;                       // identificador del enrutador
    std::map<std::string, int> vecinos;       // vecino -> costo del enlace directo
    std::map<std::string, int> tablaCostos;   // destino -> mejor costo conocido

public:

    Enrutador();
    explicit Enrutador(const std::string& nombre);

    // Identificador
    const std::string& getNombre() const;

    // Vecinos directamente conectados
    bool agregarVecino(const std::string& vecino, int costo);   // agrega o actualiza el costo
    bool eliminarVecino(const std::string& vecino);
    bool esVecino(const std::string& vecino) const;
    int getCostoEnlace(const std::string& vecino) const;        // INFINITO si no es vecino
    const std::map<std::string, int>& getVecinos() const;

    // Tabla de costos
    void reiniciarTabla();                                      // estado inicial: yo = 0 y mis vecinos directos
    void actualizarCosto(const std::string& destino, int costo);  // la Red entrega el resultado calculado
    int getCosto(const std::string& destino) const;             // INFINITO si no hay ruta
    const std::map<std::string, int>& getTablaCostos() const;

    // Presentacion
    void mostrarVecinos() const;
    void mostrarTabla() const;
};

#endif // ENRUTADOR_H