#include <iostream>
#include "LZ78.h"
#include <string>
using namespace std;

// Buscar si (prefijo, carácter) ya existe
int findEntry(Entry* dict, int size, int prefix, char c) { //Funcion que retorna el valor del índice i si ya está esa 									//clave - valor en el diccionario
    for (int i = 1; i < size; i++) {
        if (dict[i].prefix == prefix && dict[i].c == c) {
            return i;
        }
    }
    return -1;
}


void reconstruirEntrada(Entry* dict, int index, string &resultado) {
    if (index == 0) {
        return; // prefijo 0 significa "no hay nada antes", se detiene la recursión
    }
    reconstruirEntrada(dict, dict[index].prefix, resultado); // primero el prefijo (lo de antes)
    resultado += dict[index].c; // luego el caracter nuevo de esta entrada
}

void decompressLZ78(Entry* dict, int dictSize) {
    cout << "Cadena descomprimida: ";

    for (int i = 1; i < dictSize; i++) {
        string resultado = "";
        reconstruirEntrada(dict, i, resultado);
        cout << resultado;
    }

    cout << endl;
}


Entry* compressLZ78(const char* input) {
    Entry* dict = new Entry[1000]; // tamaño fijo simple
    int dictSize = 1, count_tuplas = 0; // índice 0 vacío

    int currentPrefix = 0;

    cout << "Salida (indice, caracter):\n";

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        int index = findEntry(dict, dictSize, currentPrefix, c);

        if (index != -1) { //Si se retorna un número es porque ese índice actual debe ser el índice ya existente
            //las letras o combinaciones ya existían en cierto índice
            currentPrefix = index;
        } else {
            cout << "(" << currentPrefix << ", " << c << ")\n";

            dict[dictSize].prefix = currentPrefix; //en el diccionario reservado añado en esa posición, en el
            //atributo prefix -> prefijo actual (numero actual)
            dict[dictSize].c = c;	//en esa misma posición añado el valor de c que sería un carácter o combinación de
            //caracteres nueva
            dictSize++;
            count_tuplas++;

            currentPrefix = 0;	//se reinicia a 0 para verificar si las tuplas siguientes ya están o no en el diccionario
        }
    }
    //INVOCACION PARA DESENCRPITAR
    decompressLZ78(dict, count_tuplas);
    //cout << "Hay:" <<count_tuplas <<" tuplas"<<endl;
    return dict;     //retorno el puntero al diccionario (encriptacion)
    //liberamos el diccionario luego de usarlo

}


