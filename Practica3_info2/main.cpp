#include <iostream>
#include <fstream>
#include <cstring>
#include "existentes1.h"
#include <string>

using namespace std;

/*
  USAR SIEMPRE EXCEPCIONES

En esta pr ́actica, la encriptaci ́on de cada byte del mensaje comprimido se realizar ́a aplicando:
1. Una rotaci ́on de bits.
2. Una operaci ́on XOR con una clave de un byte K.

Para recuperar el mensaje original seŕa necesario aplicar nuevamente la operacíon XOR con la misma
clave y posteriormente invertir la rotacion realizada.

*/


int main()
{

    string resul = iniciarRLE();
    cout << "Comrpimido: "<<resul<<endl;
    string original = recuperarInicial(resul);
    cout << "Original: "<<original<<endl;


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
