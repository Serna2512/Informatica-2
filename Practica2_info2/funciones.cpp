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

bool compararCaracteres(char *cadena1, char *cadena2){
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
    char arreglo1[] = "Hola MUNDO", arreglo2[] = "Hola mundo";
    char *Parreglo1 = arreglo1, *Parreglo2 = arreglo2;
    cout <<"D.M1: "<<&Parreglo1<<endl<<"D.M2:"<< &Parreglo2<<endl;

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


char *separarPornCifras(int n, char numeros[]){

    char *ptr =&numeros[0];
    int countDigitos = 0, relleno = 0;

    for(int i = 0;*(ptr + i) != '\0';i++){ //cuento los elementos de la cadena
        countDigitos++;
    }
    cout << "Cantidad de digitos: "<<countDigitos<<endl;
    relleno = (n - (countDigitos % n)) % n; //miramos cuantos ceros hay que agregar
    int nuevoTam = countDigitos + relleno;
    char *rellenada = new char[nuevoTam + 1];

    for(int j = 0;j < relleno;j++){ //lleno el arreglo dinamico de ceros
        rellenada[j] = '0';
    }

    for(int j = 0;j < countDigitos;j++){ //pongo los digitos desde donde se terminaron de poner los ceros
        rellenada[relleno + j] = numeros[j];
    }
    rellenada[nuevoTam] = '\0'; //cerramos la cadena

    return rellenada;
}

double sumarPorBloques(char* rellenada, int n) {
    double suma = 0;
    int valor = 0;
    int contador = 0;

    for (char *p = rellenada; *p != '\0'; p++) {
        valor = valor * 10 + (*p - '0');
        contador++;
        if (contador == n) {
            suma += valor;
            valor = 0;
            contador = 0;
        }
    }

    return suma;
}

void problema9(){
    int n;
    char cadena[100];
    cout << "Programa que coge n digitos de una cadena, los separa y los va sumando"<<endl;
    cout << "Ingrese la cantidad de cifras a coger: ";
    cin >> n;
    cout << "Ingrese la cadena de numeros: ";
    cin >> cadena;
    char *rellenada = separarPornCifras(n, cadena);
    cout <<"original: "<<cadena<<endl;
    double suma = sumarPorBloques(rellenada,n);
    cout <<"suma: "<<suma<<endl;

    delete[] rellenada;
}

void manipularSala(char (*Ptrmatriz)[20],char fila, unsigned int columna, char opcion){
    //la funcion permite cambiar el valor de una posicion de la sala
    //*Ptrmatriz apunta a la direccion de memoria del primer elemento de la matriz

    int IntLetra = fila  - 'A'; //pasar de letras mayusculas a char

    if(opcion == '+' && Ptrmatriz[IntLetra][columna - 1] == '+'){
        cout << "El asiento: "<<fila<<columna<<" ya está reservado!"<<endl;
    }
    else if(opcion == '+' && Ptrmatriz[IntLetra][columna - 1] == '-'){
        Ptrmatriz[IntLetra][columna - 1] = '+';
        cout <<"Se ha reservado el asiento: "<<fila<<columna<<endl;

    }
    else if(opcion == '-' && Ptrmatriz[IntLetra][columna - 1] == '+'){
        Ptrmatriz[IntLetra][columna - 1] = '-';
        cout <<"Se ha cancelado la reserva del asiento: "<<fila<<columna<<endl;
    }
    else if(opcion == '-' && Ptrmatriz[IntLetra][columna - 1] == '-'){
        cout <<"No se puede cancelar el asiento: "<<fila<<columna<<" porque no esta reservado!"<<endl;
    }

    //return &Ptrmatriz[0][0]; //por si necesito retornar la matriz

}

void mostrarSala(char (*Ptrmatriz)[20]){

    cout << "           TEATRO PABLO TOBON URIBE"<<endl<<"                PLATEA CENTRAL"<<endl;
    cout << "   1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20"<<endl;
    for(int i = 0;i<15;i++){ //pasar por cada fila
        char letraFila = i + 'A';
        cout << letraFila<< "| ";
        for(int j = 0;j<20;j++){ //pasar por cada columna
            cout << Ptrmatriz[i][j]<<" ";

        }
        cout << " |";
        cout <<endl;
    }
    cout <<endl;

}


void problema11(char (*Ptrmatriz)[20]){
    char opcion = '1';
    char fila;
    int columna;

    bool reservas = true;

    while(reservas){
        mostrarSala(Ptrmatriz);
        cout << "1). Digite '+' para reservar un asiento"<<endl<<"2). Digite '-' para cancelar la reserva de un asiento: "<<endl;
        cout << "3). DIGITE '0' PARA SALIR: ";
        cin >> opcion;
        if(opcion == '0'){
            reservas = false;
            break;
        }

        cout << "Ingrese la letra de la silla en mayuscula [A-O]: ";
        cin >> fila;

        cout << "Ingrese el numero de la silla: ";
        cin >> columna;
        cout <<endl;

        manipularSala(Ptrmatriz, fila, columna, opcion);

    }

}

