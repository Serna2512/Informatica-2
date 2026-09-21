#include <iostream>
#include <cstring>

using namespace std;
//el indice del diccionario aputna a una posición anterior de el mismo

struct Diccionario
{
    char letra;
    int indice;
    int indice_prefijo;
};

int cantidad_letras(){
    string cadena;
    cout << "Ingrese la cadena para comprimir: " ;
    cin >> cadena;
    return cadena.length();
}

int cant_letras = cantidad_letras();

void LZ78(Diccionario *ptr, string cadena){ //ptr[i] es una TUPLA
    int cant_letras = cadena.length();
    ptr = new Diccionario[cant_letras]; //la salida será menos que la cantidad de bytes reservados
    int cantidad_entradas = 0;

    ptr->indice_prefijo = 0; //agregamos al diccionario siempre la primera letra con indice_prefijo = 0
    ptr->letra = cadena[0];

    for(int i = 1;i < cant_letras - 1;i++){ //ABAABC
        if(cadena[i] != cadena[i+1]){
            if(ptr[i].letra){ //verificar si la letra o par de letras ya está en el diccionario

            }
        }
    }
}