#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream mi_archivo;
    mi_archivo.open("archivo2.txt",ios::out);

    if(!mi_archivo){
        cerr <<"Archivo no creado";
    }
    else{
        cerr <<"Archivo creado";
    }
    /*
    for(int i = 0;i<=10;i++){

    }*/

    return 0;
}
