#include "Red.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;

Red::Red() {
}

// ---------- Algoritmo de Dijkstra ----------

void Red::dijkstra(const string& origen, map<string, int>& dist) const {
    dist.clear();

    //siempre sale primero el nodo de menor costo acumulado
    typedef pair<int, string> Par;   //(costo acumulado, nombre), los pares se comparan primero por costo
    priority_queue<Par, vector<Par>, greater<Par> > cola; //con greater sale primero el nodo de menos costo
                        //usamos vector porque permite modificar la distancia de cualquier vértice por medio de su índice, eficiente
                        //tambien permite guardar la distancia desde el nodo origen a otro nodo

    dist[origen] = 0;
    cola.push(Par(0, origen));

    while (!cola.empty()) {
        Par actual = cola.top();
        cola.pop();
        int costoActual = actual.first;
        string nombreActual = actual.second;

        // Entrada vieja: ya se encontro un camino mejor para este nodo
        if (costoActual > dist[nombreActual]) {
            continue;
        }

        map<string, Enrutador>::const_iterator it = enrutadores.find(nombreActual); //iterador solo para lectura
        if (it == enrutadores.end()) {
            continue;
        }

        const map<string, int>& vecinos = it->second.getVecinos();
        for (map<string, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); ++v) {

            if (costoActual > numeric_limits<int>::max() - v->second) { //proteccion contra desbordamiento de enteros
                continue;
            }

            int nuevoCosto = costoActual + v->second;   //si nuevo costo es menor que el guardado actualizamos dist
            map<string, int>::iterator d = dist.find(v->first);
            if (d == dist.end() || nuevoCosto < d->second) {
                dist[v->first] = nuevoCosto;
                cola.push(Par(nuevoCosto, v->first)); //el push reorganiza automaticamente la cola para mantener el orden de prioridad
            }
        }
    }
}


Camino Red::obtenerCamino(const string& origen, const string& destino){

    Camino ruta;

    //Verificar que existan ambos enrutadores
    if (enrutadores.find(origen) == enrutadores.end() ||
        enrutadores.find(destino) == enrutadores.end()) {
        return ruta;
    }

    //Calcular las distancias mínimas desde el origen
    map<string, int> dist;
    dijkstra(origen, dist);

    //Comprobar si el destino es alcanzable
    map<string, int>::const_iterator d = dist.find(destino);

    if (d == dist.end()) {
        return ruta;
    }

    //Estructuras auxiliares para reconstruir la ruta
    map<string, string> previo;
    map<string, bool> visitados;
    queue<string> cola;

    cola.push(origen);
    visitados[origen] = true;

    //Recorrer únicamente conexiones que pertenecen
    //a alguna ruta de costo mínimo
    while (!cola.empty()) {

        string actual = cola.front();
        cola.pop(); //elimino el elemento que está al principio

        if (actual == destino) {
            break;
        }

        map<string, Enrutador>::const_iterator it = enrutadores.find(actual);

        if (it == enrutadores.end()) {
            continue;
        }

        const map<string, int>& vecinos = it->second.getVecinos();

        for (map<string, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); ++v) {

            const string& nombreVecino = v->first;
            int costoEnlace = v->second;

            // Verificar que el vecino sea alcanzable
            map<string, int>::const_iterator distanciaVecino = dist.find(nombreVecino);

            if (distanciaVecino == dist.end()) { //si vecino no aparece en el mapa de distancias lo pasamos y se sigue examinando los demás
                continue;
            }

            // Evitar visitar nuevamente un enrutador
            if (visitados[nombreVecino]) {
                continue;
            }

            // Comprobar si la conexión conserva el costo mínimo
            if (dist[actual] <= numeric_limits<int>::max() - costoEnlace && dist[actual] + costoEnlace == distanciaVecino->second) {

                visitados[nombreVecino] = true;
                previo[nombreVecino] = actual;
                cola.push(nombreVecino);
            }
        }
    }

    // Comprobar que se haya podido reconstruir la ruta
    if (!visitados[destino]) {
        return ruta;
    }

    // Reconstruir la ruta desde el destino hasta el origen
    vector<string> nodosInvertidos;

    string actual = destino;
    nodosInvertidos.push_back(actual);

    while (actual != origen) {

        map<string, string>::const_iterator it = previo.find(actual);

        if (it == previo.end()) {
            return Camino();
        }

        actual = it->second;
        nodosInvertidos.push_back(actual);
    }

    // Agregar los nodos en el orden correcto
    for (vector<string>::reverse_iterator it = nodosInvertidos.rbegin(); //recorremos el vector del final al inicio
         it != nodosInvertidos.rend(); ++it) {

        ruta.agregarNodo(*it);
    }

    // Asignar el costo mínimo encontrado
    ruta.establecerCosto(dist[destino]);

    return ruta;
}


// ---------- Gestion de la topologia ----------

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || existeEnrutador(nombre)) {
        return false;
    }
    enrutadores[nombre] = Enrutador(nombre);
    recalcularTablas();
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    map<string, Enrutador>::iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end()) {
        return false;
    }

    // Los vecinos dejan de tener enlace con el enrutador que se elimina
    const map<string, int>& vecinos = it->second.getVecinos();
    for (map<string, int>::const_iterator v = vecinos.begin(); v != vecinos.end(); ++v) {
        map<string, Enrutador>::iterator otro = enrutadores.find(v->first);
        if (otro != enrutadores.end()) {
            otro->second.eliminarVecino(nombre);
        }

    }

    enrutadores.erase(it);
    recalcularTablas();
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (a == b || costo <= 0) {
        return false;
    }
    map<string, Enrutador>::iterator ia = enrutadores.find(a); //.find() devuelve un iterador (D.M a ese valor)
    map<string, Enrutador>::iterator ib = enrutadores.find(b);
    if (ia == enrutadores.end() || ib == enrutadores.end()) {
        return false;
    }

    // El enlace es bidireccional: se registra en ambos extremos
    ia->second.agregarVecino(b, costo);
    ib->second.agregarVecino(a, costo);
    recalcularTablas();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    map<string, Enrutador>::iterator ia = enrutadores.find(a);
    map<string, Enrutador>::iterator ib = enrutadores.find(b);
    if (ia == enrutadores.end() || ib == enrutadores.end()) {
        return false;
    }
    if (!ia->second.esVecino(b)) {
        return false;
    }

    ia->second.eliminarVecino(b);
    ib->second.eliminarVecino(a);
    recalcularTablas();
    return true;
}

// ---------- Actualizacion de tablas ----------

void Red::recalcularTablas() {
    for (map<string, Enrutador>::iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {

        map<string, int> dist;
        dijkstra(it->first, dist);

        it->second.reiniciarTabla();   // deja solo "yo" y los enlaces directos
        for (map<string, int>::const_iterator d = dist.begin();
             d != dist.end(); ++d) {
            it->second.actualizarCosto(d->first, d->second);
        }
    }
}

// ---------- Consultas ----------

bool Red::existeEnrutador(const string& nombre) const {
    return enrutadores.find(nombre) != enrutadores.end();
}

const Enrutador* Red::getEnrutador(const string& nombre) const {
    map<string, Enrutador>::const_iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end()) {
        return nullptr;
    }
    return &it->second;
}

unsigned int Red::cantidadEnrutadores() const {
    return enrutadores.size();
}

// ---------- Presentacion ----------

void Red::mostrarRed() const {
    if (enrutadores.empty()) {
        cout << "La red no tiene enrutadores." << endl;
        return;
    }
    cout << "Topologia de la red:" << endl;
    for (map<string, Enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        cout << "  " << it->first << " ->";
        const map<string, int>& vecinos = it->second.getVecinos();
        if (vecinos.empty()) {
            cout << " (sin enlaces)";
        }
        for (map<string, int>::const_iterator v = vecinos.begin();
             v != vecinos.end(); ++v) {
            cout << " " << v->first << "(" << v->second << ")";
        }
        cout << endl;
    }
}

void Red::mostrarTablas() const {
    if (enrutadores.empty()) {
        cout << "La red no tiene enrutadores." << endl;
        return;
    }

    // Encabezado con los destinos
    cout << setw(5) << " ";
    for (map<string, Enrutador>::const_iterator col = enrutadores.begin();
         col != enrutadores.end(); ++col) {
        cout << setw(5) << col->first;
    }
    cout << endl;

    // Una fila por enrutador; "-" significa que no hay ruta
    for (map<string, Enrutador>::const_iterator fila = enrutadores.begin();
         fila != enrutadores.end(); ++fila) {
        cout << setw(5) << fila->first;
        for (map<string, Enrutador>::const_iterator col = enrutadores.begin();
             col != enrutadores.end(); ++col) {
            int costo = fila->second.getCosto(col->first);
            if (costo >= Enrutador::INFINITO) {
                cout << setw(5) << "-";
            } else {
                cout << setw(5) << costo;
            }
        }
        cout << endl;
    }
}

bool Red::cargarDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return false;
    }

    Red temporal;
    string linea;
    string seccion;

    while (getline(archivo, linea)) {
        istringstream entrada(linea);
        string primero;

        if (!(entrada >> primero) || primero[0] == '#') {
            continue;
        }

        if (primero == "ENRUTADORES" || primero == "ENLACES") {
            string extra;
            if (entrada >> extra) {
                return false;
            }
            seccion = primero;
            continue;
        }

        if (seccion == "ENRUTADORES") {
            string extra;

            if (entrada >> extra || temporal.enrutadores.count(primero)) {
                return false;
            }

            temporal.enrutadores.insert(
                make_pair(primero, Enrutador(primero))
                );
        }
        else if (seccion == "ENLACES") {
            string b, extra;
            int costo;

            if (!(entrada >> b >> costo) || entrada >> extra) {
                return false;
            }

            if (primero == b || costo <= 0 ||
                !temporal.existeEnrutador(primero) ||
                !temporal.existeEnrutador(b)) {
                return false;
            }

            Enrutador& a = temporal.enrutadores[primero];
            Enrutador& otro = temporal.enrutadores[b];

            if (a.esVecino(b)) {
                return false;
            }

            a.agregarVecino(b, costo);
            otro.agregarVecino(primero, costo);
        }
        else {
            return false;
        }
    }

    if (!archivo.eof() || seccion != "ENLACES") {
        return false;
    }

    temporal.recalcularTablas();

    // Reemplazar la red actual solo si toda la lectura fue correcta.
    enrutadores.swap(temporal.enrutadores);

    return true;
}


bool Red::guardarEnArchivo(const string& nombreArchivo) const {
    ofstream archivo(nombreArchivo.c_str());

    if (!archivo.is_open()) {
        return false;
    }

    archivo << "ENRUTADORES" << endl;

    for (map<string, Enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {
        archivo << it->first << endl;
    }

    archivo << endl << "ENLACES" << endl;

    for (map<string, Enrutador>::const_iterator it = enrutadores.begin();
         it != enrutadores.end(); ++it) {

        const map<string, int>& vecinos = it->second.getVecinos();

        for (map<string, int>::const_iterator v = vecinos.begin();
             v != vecinos.end(); ++v) {

            // Guardamos cada enlace bidireccional una sola vez.
            if (it->first < v->first) {
                archivo << it->first << " "
                        << v->first << " "
                        << v->second << endl;
            }
        }
    }

    return archivo.good();
}