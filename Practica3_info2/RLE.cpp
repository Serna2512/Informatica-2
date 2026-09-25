#include <iostream>
#include <string>

using namespace std;

string RLEptr(const char* cadena){
    //funcion que dada una cadena de texto la regresa de manera comprimida usando RLE

    string resultado = ""; //cadena de string vacía
    int contador = 1;

    for(int i = 0; cadena[i]  != '\0';i++){
        if(cadena[i] == cadena[i+ 1]){
            contador++;
        }
        else{
            resultado += to_string(contador);
            resultado += (cadena[i]);
            contador = 1;
        }
    }
    return resultado;
}


string iniciarRLE(){ //funcion que invoca algoritmo RLE e imprime la compresion
    char inicial[] = "AAAAAAAAAAB";
    const char* cadena = inicial;

    return RLEptr(cadena);
}

string recuperarInicial(string resul){
    string original = "";
    int n = 0;

    for(int i = 0;i < resul.length();i+=2){   //recorrer la compresión de derecha a izquierda

        int num_rep = resul[i] - '0'; //convertimos a int para iterar
        if(resul[i + 1] >= '0' && resul[i+1] <= '9'){
            num_rep = num_rep * 10 + (resul[i+1] - '0');
            char letra = resul[(n+2)];
            i+=1;

            for(int j = 0; j < num_rep;j++){

                original += letra;
            }
            n+=3;
        }

            else{
                char letra = resul[(n+1)];
                for(int j = 0; j < num_rep;j++){

                    original += letra;

                }
                n+=2;
            }


//fucnion de verificacion y verificar cuando la entrada es mayor a 9 dígitos
}
    return original;
}