#include <iostream>
#include "existentes.h"

using namespace std;

//HACER LOS PROBLEMAS PARES
//HACER UN CICLO PARA PODER PROBAR LOS PROBLEMAS LAS VECES QUE SE DESEE
//DESPUES PASAR TODO A MODULOS (SI SE PUEDE)


int main()
{
    int opcion;
    bool ban = true;
    do{
        cout << "------Que problema desea ver [1-8] -------"<<endl;
        cout << "o ingrese 0 para terminar el programa: ";
        cin >> opcion;

        switch(opcion){
        case 1:
            //PROBLEMA 2
            problema2();
            break;
        case 2:
            //PROBLEMA 4
            problema4();
            break;
        case 3:
            //PROBLEMA 6
            problema6();
            break;
        case 4:
            //PROBLEMA 8
            problema8();
            break;
        case 5:
            //PROBLEMA 10
            problema10();
            break;
        case 6:
            //PROBLEMA 12
            problema12();
            break;
        case 7:
            //PROBLEMA 14
            problema14();
            break;
        case 8:
            //PROBLEMA 16
            problema16();
            break;

        case 0:
            cout << "Has salido!"<<endl;
            ban = false;
        }

    }
    while(ban);

    return 0;
}