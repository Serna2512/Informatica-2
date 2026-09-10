#include <iostream>

using namespace std;

//EJERCICIOS PRACTICA 2

//EJERCICIO 1 MODIFICADO

void fun_a(char *px, char *py){
    char tmp = *px;
    *px = *py;
    *py = tmp;
}

void fun_b(char a[], int tam){
    int f, l;
    for (f = 0, l = tam -1; f < l; f++, l--) {
        fun_a(&a[f], &a[l]);
    }

}


//EJERCICIO 2


void fun_c(double *a, int n, double *promedio, double *suma){
    int i;
    *suma = 0.0;
    for (i = 0; i < n; i++)
        *suma += *(a + i);
    *promedio = (*suma) / n;
}

//declaración e inicialización para las pruebas
/*
double arreglo[] = {5.6,2.3,8.6,4.2,67.9,45.1};
double *a = &arreglo[0];

double prom = 0.0;
double *Pprom = &prom;

double sum = 0.0;
double *Psum = &sum;
*/


//FUNCIONES DE LOS PROBLEMAS (IMPARES)


void minima_comb(int cantidad){

    int billetes[10] = {50000,20000,10000,5000,2000,1000,500,200,100,50}; //arreglos de los billetes
    int *Pbilletes = &billetes[0];

    for(int i = 0;i <= 9;i++){
        int count = 0;

        while(*(Pbilletes+i) <= cantidad){ //miro si el billete es menor a la cantidad ingresada
            cantidad -= *(Pbilletes+i); //le resto a la cantidad ese billete
            count +=1;
        }
        cout << *(Pbilletes+i) <<": "<<count<<endl;
    }
    if(cantidad < *(Pbilletes+9)){
        cout << "Faltante: "<<cantidad<<endl;
    }
}

void problema1(){ //funcion auxiliar para llamar al problema
    cout << "Programa que dada una cantidad de dinero muestra la minima combinacion de bielletes necesarios"<<endl<<endl;
    int cantidad;
    do{
        cout << "ingresa una cantidad de dinero valida: ";
        cin >> cantidad;
    }while(cantidad < 0);

    minima_comb(cantidad);
}

bool compararCaracteres(char *cadena1, char*cadena2){
    int i = 0;
    while(*(cadena1 + i) == *(cadena2 + i) && *(cadena1 + i) != '\0'){ //en las cadenas char se termina de imrpimir cuando se identifica el caracter '\0'
        i++;
    }
    if(*(cadena1 + i) == '\0' && *(cadena2 + i) == '\0' ){ //significa que terminaron al mismo tiempo y tienen los mismo caracteres si el while se cumple todo
        cout << "las cadnenas son iguales"<<endl;
        cout << cadena1 <<" = "<<cadena2<<endl;
        return true;

    }
    else{
        cout << "las cadnenas son diferentes"<<endl;
        cout << cadena1 <<" != "<<cadena2<<endl;
        return false;
    }

}

void problema3(){
    cout << "Programa que analiza dos cadenas de caracteres y verifica si son iguales, retorna true si si y false si no"<<endl;
    char arreglo1[] = "Hola MUNDO", arreglo2[] = "Hola a todos";
    char *Parreglo1 = arreglo1, *Parreglo2 = arreglo2;

    compararCaracteres(Parreglo1, Parreglo2);
}



void intAcadena(int &n, char a[]){ //pasar n a caracteres en ascii
    char digitoChar;
    int var = 0;
    while(n != 0){
        int digito = (n%10); //saco el digito de la derecha del todo
        n /= 10; //quito la parte decimal y dejo la entero
        digitoChar = digito + '0'; //coge el valor entero y le suma 48 para que en ascii sea ese valor
        a[var] = digitoChar;
        var++;
    }
    a[var] = '\0';
    fun_b(a,var);

}

void problema5(char a[]){
    int n;
    cout << "Programa que ingresado un int devuelve sus caracteres pero en cadena de char"<<endl;
    cout << "Ingrese un numero n entero positivo: ";
    cin >> n;
    intAcadena(n, a);
    cout << "'"<<a<<"'"<<endl;
}

void cadenaSinRepetir(char arr[]){

    char copia[100];
    char arregloFinal[100];
    int k = 0;

    //copiar el arreglo

    for(int a = 0;arr[a] != '\0';a++){
        copia[a] = arr[a];
    }

    for(int i = 0; *(arr + i) != '\0';i++){
        bool repetido = false;

        for(int j = 0;j < i;j++){
            if(*(arr + i) == *(arr + j)){
                repetido = true;
                break;
            }
        }
        if((!repetido)){
            arregloFinal[k] = arr[i];
            k++;
        }
    }
    arregloFinal[k] = '\0';
    cout << "orginal: "<< copia<<" Sin repetidos: "<< arregloFinal<<endl;
}

void problema7(char cadena[]){
    cout << "Programa que elimina las letras repetidas de una cadena de char (limitado a 99 caracteres)"<<endl;
    cadenaSinRepetir(cadena);
}

/*
void separarNcifras(int n,char numeros[]){
    int arregloEnteros[100];
    //1). pasar los caracteres a numeros
    cout << "Original: "<<numeros<<endl;

    for(int i = 0; numeros[i] != '\0';i++){
        arregloEnteros[i]  = numeros[i]; //necesito que numeros sean enteros
    }
    cout << arregloEnteros<<endl;
}
*/

void separarPornCifras(int n, string numeros){
    int numero = numeros.length(), suma = 0;
    char arr[n];
    int valor = 0;
    char* ptr[numero];

    for(int i = 0; i < numero ;i++){ //cojo de derecha a izquierda
        ptr[i] = &numeros[i];
        //cout << *(ptr[numero])<<endl;
        if(i==numero){
            for(int j = n-1;j>=0;j--){
                arr[j] = (*(ptr[numero - j - 1]));
                suma = arr[j] + '0';
            }


        }
    }



}

