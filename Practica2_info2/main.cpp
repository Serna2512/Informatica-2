#include <iostream>
#include "existentes.h"
using namespace std;


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
            //PROBLEMA 1
            problema1();
            break;

        case 2:
            //PROBLEMA 3
            problema3();
            break;

        case 3:{
            //PROBLEMA 5
            /*
            int digito = 2;
            char digitoChar = digito + '0';
            cout <<"debe salir 2: "<<digitoChar<<endl;
            */
            int n = 50;
            intAcadena(n);
            break;
        }
        case 0:
            cout << "Has salido!"<<endl;
            ban = false;
        }

    }
    while(ban);

    return 0;
}
