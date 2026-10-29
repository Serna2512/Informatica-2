#include <iostream>
#include <string>
#include <limits>
//#include <cctype>
#include "Red.h"
#include "camino.h"

using namespace std;

// Lee un entero validando la entrada. Si se acaba la entrada, devuelve 0 (salir).
int leerEntero(const string& mensaje) {
    int valor;
    cout << mensaje;
    while (!(cin >> valor)) {
        if (cin.eof()) {
            return 0;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada invalida. " << mensaje;
    }
    return valor;
}

string leerTexto(const string& mensaje) {
    string texto;
    cout << mensaje;
    cin >> texto;
    return texto;
}

void mostrarMenu() {
    cout << endl;
    cout << "CONEXIOM DE ENRUTADORES" << endl;
    cout << "1. Agregar enrutador" << endl;
    cout << "2. Eliminar enrutador" << endl;
    cout << "3. Agregar enlace" << endl;
    cout << "4. Eliminar enlace" << endl;
    cout << "5. Ver vecinos de un enrutador" << endl;
    cout << "6. Ver tabla de costos de un enrutador" << endl;
    cout << "7. Ver topologia de la red" << endl;
    cout << "8. Ver tabla de costos de toda la red" << endl;
    cout << "0. Salir" << endl;
}


int main() {

    Red red;
    int opcion;

    do {
        mostrarMenu();
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
        case 1: {
            string nombre = leerTexto("Nombre del nuevo enrutador: ");
            if (nombre.length() == 1 && islower(nombre[0])) {
                nombre[0] = toupper(nombre[0]); //Convierte el carácter a mayúscula
            }
            if (red.agregarEnrutador(nombre)) {
                cout << "Enrutador " << nombre << " agregado." << endl;
            } else {
                cout << "No se pudo agregar (el nombre ya existe)." << endl;
            }
            break;
        }
        case 2: {
            string nombre = leerTexto("Enrutador a eliminar: ");
            if (red.eliminarEnrutador(nombre)) {
                cout << "Enrutador " << nombre << " eliminado. Tablas actualizadas." << endl;
            } else {
                cout << "El enrutador no existe." << endl;
            }
            break;
        }
        case 3: {
            string a = leerTexto("Primer enrutador: ");
            string b = leerTexto("Segundo enrutador: ");
            int costo = leerEntero("Costo del enlace: ");
            if (red.agregarEnlace(a, b, costo)) {
                cout << "Enlace " << a << " <-> " << b << " (costo " << costo
                     << ") registrado. Tablas actualizadas." << endl;
            } else {
                cout << "No se pudo agregar: ambos enrutadores deben existir, ser distintos "
                     << "y el costo debe ser mayor que 0." << endl;
            }
            break;
        }
        case 4: {
            string a = leerTexto("Primer enrutador: ");
            string b = leerTexto("Segundo enrutador: ");
            if (red.eliminarEnlace(a, b)) {
                cout << "Enlace eliminado. Tablas actualizadas." << endl;
            } else {
                cout << "No existe un enlace entre esos enrutadores." << endl;
            }
            break;
        }
        case 5: {
            string nombre = leerTexto("Enrutador: ");
            const Enrutador* e = red.getEnrutador(nombre);
            if (e == nullptr) {
                cout << "El enrutador no existe." << endl;
            } else {
                e->mostrarVecinos();
            }
            break;
        }
        case 6: {
            string nombre = leerTexto("Enrutador: ");
            const Enrutador* e = red.getEnrutador(nombre);
            if (e == nullptr) {
                cout << "El enrutador no existe." << endl;
            } else {
                e->mostrarTabla();
            }
            break;
        }
        case 7:
            red.mostrarRed();
            break;
        case 8:
            red.mostrarTablas();
            break;
        case 0:
            cout << "Hasta luego." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
        }
    } while (opcion != 0);

    return 0;
}