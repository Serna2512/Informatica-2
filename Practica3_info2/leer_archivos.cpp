#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string leer_archivo(const string& rutaArchivo){
    ifstream archivo(rutaArchivo);

    if(!archivo.is_open()){
        cout << "Error: no se pudo abrir el archivo." << endl;
        return "";
    }

    string contenido = "";
    char caracter;

    while(archivo.get(caracter)){
        contenido += caracter;
    }
    archivo.close();
    return contenido;
}