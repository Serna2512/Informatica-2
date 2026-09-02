#include <iostream>

using namespace std;

//EJERCICIOS PRACTICA 2

//EJERCICIO 2


void fun_c(double *a, int n, double *promedio, double *suma);

double arreglo[] = {5.6,2.3,8.6,4.2,67.9,45.1};
double *a = &arreglo[0];

double prom = 0.0;
double *Pprom = &prom;

double sum = 0.0;
double *Psum = &sum;

//EJERCICIO 3

unsigned short b[4][2] = {{77, 50}, {5, 2}, {28, 39}, {99, 3}};


int main()
{
    /*fun_c(a, size(arreglo), Pprom, Psum); //se hacen los calculos

    cout << "Suma: "<< *Psum<< endl;
    cout << "Promedio: "<< *Pprom<< endl;
    cout << "Cant. Elementos en arreglo: "<<size(arreglo)<<endl;
    */
    cout << b;
    return 0;
}

void fun_c(double *a, int n, double *promedio, double *suma){
    int i;
    *suma = 0.0;
    for (i = 0; i < n; i++)
        *suma += *(a + i);
    *promedio = (*suma) / n;
}

