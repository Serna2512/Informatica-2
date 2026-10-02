#include <iostream>
#include "existentes1.h"
#include "LZ78.h"
#include "encrip_desencrip.h"
#include "leer_arch.h"
#include <string>
#include <bitset>

using namespace std;

/*
  USAR SIEMPRE EXCEPCIONES

En esta pr ́actica, la encriptaci ́on de cada byte del mensaje comprimido se realizar ́a aplicando:
1. Una rotaci ́on de bits.
2. Una operaci ́on XOR con una clave de un byte K.

Para recuperar el mensaje original seŕa necesario aplicar nuevamente la operacíon XOR con la misma
clave y posteriormente invertir la rotacion realizada.

*/

unsigned int opc;

int main()
{

    //leer un texto leído desde un archivo
    string cadena_archivo = leer_archivo("Prueba.txt");
    do{
        cout << "Ingrese (1) para usar RLE o (2) para usar LZ78"<<endl<<"O (0) para salir: ";
        try{
            cin >> opc;

            if(opc != 0 && opc != 1 && opc != 2){
                cout << "Opcion invalida!"<<endl;
                throw opc;
            }

        } catch(unsigned int valor_invalido){
            cout << "Error en la opcion "<<valor_invalido<<endl;
        }
    switch(opc){
    case 1:{
        //RLE
        //cambiar dentro del RLE para hacerlo con el texto leido desde el archivo
        //cadena_archivo.c_str(); //convertimos el string a const char* para pasarselo al RLE
        //string cadena = iniciarRLE();
        string resul = RLEptr((cadena_archivo.c_str()));
        cout << "Comprimido: "<<resul<<endl;
        //cout << "Comrpimido: "<<resul<<endl;
        string original = recuperarInicial(resul);
        cout << "Original: "<<original<<endl;

        //Encriptamos
        const char* ptr = resul.c_str(); //convertimos el string a cadena de char
        cout << "Ingrese un valor entero entre 0 y 8 para rotar los bits hacia la izquierda: ";
        unsigned short int nRota;
        try{
            cin >> nRota;
            if(nRota == 0 || nRota >= 8){
                cout << "Numero de rotaciones invalido!"<<endl;
                throw nRota;
            }
        } catch(unsigned int valor_invalido){
            cout << "Error en la opcion "<<valor_invalido<<endl;
        }
        unsigned char* prtResultado_encriptado = encript(ptr, nRota); //rotamos cada char comprimido hacia la izquierda
        //cout << prtResultado_encriptado;
        delete[] prtResultado_encriptado;
        break;
    }

    case 2:
        //LZ78
        compressLZ78((cadena_archivo.c_str()));
        break;

    }
    }while(opc != 0);


    char resultado_xor = XOR(5, 7); //5: 00000101 y 7: 00000111
    cout <<"Valor binario original: "<< bitset<8>(5)<<endl;
    cout <<"Clave K: "<< bitset<8>(7)<<endl;

    cout << "Resultado con XOR: "<<bitset<8>(resultado_xor)<<endl;
    cout << "Devolver al dato original: "<<bitset<8>(resultado_xor^7)<<endl;


    unsigned char input = 80;

    unsigned char rotate = rotacion_izquierda(input,2);
    cout << "Entrada: "<<bitset<8>(input)<<endl;
    cout << "Salida rotada: "<<bitset<8>(rotate)<<endl;

    cout << "Salida original: "<<bitset<8>(rotacion_derecha(rotate, 2))<<endl;


    return 0;
}

/*
    fstream mi_archivo;
    mi_archivo.open("archivo1.txt",ios::app);

    if(!mi_archivo){
        cerr <<"Archivo no creado";
    }
    else{
        cerr <<"Archivo creado";
        for(int filas = 0;filas < 10;filas++){
            mi_archivo << "Cómo están?: "<<filas<<endl;
        }

        mi_archivo.close();
    }
    */
