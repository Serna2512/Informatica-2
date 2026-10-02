#include <iostream>
using namespace std;

char XOR(unsigned char entrada, unsigned char clave){
    return entrada^clave;
}


unsigned char rotacion_izquierda(unsigned char input, unsigned short int nRot){
    return (input << nRot) | (input >> (8-nRot));

}

unsigned char rotacion_derecha(unsigned char input, unsigned short int nRot){
    return (input >> nRot) | (input << (8-nRot));

}


unsigned char* encript(const char* entrada, unsigned short int nRota){ //funcion que toma cada char de la cadena encirptada, rota ese char y los agrega a un arreglo
    unsigned int tamano = 0;
    while(entrada[tamano] != '\0'){ //calculamos la longitud real de la cadena
        tamano++;
    }

    unsigned char* resultado = new unsigned char[tamano +1];

    for(unsigned int i = 0;entrada[i] != '\0';i++){

        resultado[i] = rotacion_izquierda(entrada[i], nRota); //ya que la rotacion me devuelve un char
        //cout << "Agregado correctamente el caracter"<<entrada[i] << " en la pos " << i <<" del arreglo de char"<<endl;
    }
    resultado[tamano] = '\0'; //cerramos la cadena resultante

    return resultado;

}

//input: 80: 01010000
//nRot: 2 entonces: 01000000

//nRot: 6: 00000110
//input >> 6: 00000001

//salida: 01000000
//        00000001
//        01000001

