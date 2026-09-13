#include <iostream>
#include "existentes.h"
#include <string>
using namespace std;

string palabra = "1234";


int main()
{
    int opcion;
    bool ban = true;
    do{
        cout << "------Que problema desea ver [1-7] -------"<<endl;
        cout << "o ingrese 0 para terminar el programa: ";
        cin >> opcion;

        switch(opcion){
        case 1:
            //PROBLEMA 1
            problema1();
            break;

        case 2:
            //PROBLEMA 3
            problema3();
            break;

        case 3:{
            //PROBLEMA 5
            char resultado[12]; //un int puede tener máximo 10 dígitos + 1 para signo +1 para \0 por eso el tamaño es 12
            problema5(resultado);
            break;
        }
        case 4:{
            //PROBLEMA 7
            char cad[] = "bananas";
            problema7(cad);
            break;
        }
        case 5:
            problema9();
            break;
        case 6:{

            char matriz[15][20];
            char (*Ptrmatriz)[20] = matriz;

            for(int i = 0;i<15;i++){ //pasar por cada fila
                for(int j = 0;j<20;j++){ //pasar por cada columna
                    Ptrmatriz[i][j] = '-';
                }
            }
            problema11(Ptrmatriz);
            break;
        }
        case 7:
             problema13();
            break;

        case 0:
            cout << "Has salido!"<<endl;
            ban = false;
        }

    }
    while(ban);

    return 0;
}
