#include <iostream>
#include <fstream>
#include "existentes1.h"
#include "LZ78.h"
#include "encrip_desencrip.h"
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


int main()
{
    /*
    //RLE

    string resul = iniciarRLE();
    cout << "Comrpimido: "<<resul<<endl;
    string original = recuperarInicial(resul);
    cout << "Original: "<<original<<endl;

    //LZ78

    const char entrada[] = "ABAABABA";
    const char* ptr = entrada;
    compressLZ78(ptr);

    char resultado_xor = XOR(5, 7); //5: 00000101 y 7: 00000111
    cout << bitset<8>(5)<<endl;
    cout << bitset<8>(7)<<endl;

    cout << bitset<8>(resultado_xor);
    */

    unsigned char input = 80;

    unsigned char rotate = rotacion_izquierda(input,2);
    cout << bitset<8>(input)<<endl;
    cout << bitset<8>(rotate)<<endl;

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
