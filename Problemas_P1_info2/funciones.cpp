#include <iostream>

using namespace std;

void minima_comb(int cantidad){
    int billetes[10] = {50000,20000,10000,5000,2000,1000,500,200,100,50}; //arreglos de los billetes
    for(int i = 0;i <= 9;i++){
        int count = 0;

        while(billetes[i] <= cantidad){//miro si el billete es menor a la cantidad ingresada
            cantidad -= billetes[i]; //le resto a la cantidad ese billete
            count +=1;
        }
        cout << billetes[i] <<": "<<count<<endl;
    }
    if(cantidad < billetes[9]){
        cout << "Faltante: "<<cantidad<<endl;
    }
}

void problema2(){ //funcion auxiliar para llamar al problema
    cout << "Programa que dada una cantidad de dinero muestra la minima combinacion de bielletes necesarios"<<endl<<endl;
    int cantidad;
    do{
        cout << "ingresa una cantidad de dinero valida: ";
        cin >> cantidad;
    }while(cantidad < 0);


    minima_comb(cantidad);
}

void reloj(int a, int b){
    int horas_a, minutos_a, horas_b, minutos_b;
    horas_a = a/100; //separo las horas
    minutos_a = a%100; //separo los minutos

    horas_b = b/100;
    minutos_b = b%100;

    horas_a += horas_b; //suma horas ingresadas
    minutos_a += minutos_b; //la suma de los minutos ingresados
    if(minutos_a >= 60){
        horas_a += 1;
        minutos_a -= 60;
    }
    if(horas_a >= 24){
        horas_a -= 24;
    }
    cout << "La hora es: "<<horas_a<<minutos_a<<endl;
}


void problema4(){
    cout << "Programa que muestra si una hora especifica es valida o no"<<endl<<endl;

    int a,b;
    do{
        cout << "-Ingrese la hora en reloj de 24h: ";
        cin >> a;
        if((a/100) >= 24 || (a%100) >= 60){
            cout << a<<" es un tiempo invalido, prueba otro"<<endl;
        }
        else{
            cout << "-Horas a aniadir: ";
            cin >> b;
        }

    }while(a < 0 || b < 0 || (a/100) >= 24 || (a%100) >= 60);
    reloj(a,b);

}

double aprox_euler(int cantidad){
    double e_aprox = 1;

    for(int i = 1;i < cantidad;i++){
        int denominador = 1;
        for(int j = 1; j <= i;j++){
            denominador *= j;
        }
        e_aprox += (1.0/denominador);

    }
    return e_aprox;
}

void problema6(){
    int cant;
    cout << "Programa que calcula el numero e dependiendo cuantos valores ingrese el usuario"<<endl;

    do{
        cout << "Ingrese cantidad de valores para hallar e: ";
        cin >> cant;

    }while(cant < 0);
    double valor_e = aprox_euler(cant);
    cout << "e es aproximadamente: "<<valor_e<<endl;
}

int sumaMultiplos(int a, int b, int c){
    int multiplo_momento_a, sumatoria = 0, multiplo_momento_b;
    for(int i = 1;(i*a) < c;i++){ //calculo todos los multiplos de a
        sumatoria += (i*a);       //multiplo_momento_a = (i*a);
        cout <<(i*a)<<"+";
    }
    for(int j = 1;(j*b) < c;j++){
        multiplo_momento_b = (j*b);
        if((multiplo_momento_b % a) != 0){ //si no es multiplo de ambos entra
            sumatoria += multiplo_momento_b; //solo sumo los multilos de b que no son de a
            cout << multiplo_momento_b<<"+";
        }

    }
    cout << "="<<sumatoria;
    return sumatoria;
}




void problema8(){
    cout << "Programa que encuentra multiplos menores al tercer valor ingresado, los suma pero si estan repetidos no"<<endl;
    int a,b,c;
    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;
    cout << "Ingrese el tope del valor que no se puede pasar: ";
    cin >> c;
    sumaMultiplos(a,b,c);

}

int n_numero_primo(int numero){ //un primo solo de divide entre el mismo y entre 1

    int count_primos = 1;
    if(numero == 1){
        return 2;
    }
    else{

            for(int j = 3;count_primos != numero;j++){ //ciclo que coge de a un numero y para cuando se cumpla la condicion

            int i = 4;
                for(;j > (i/2);i+=2){ //ciclo que intenta verificar si un numero es primo

                    if((j%(i/2) == 0)){
                        break;
                    }
                }
                if((i/2) == j){
                    count_primos += 1;
                    if(count_primos == numero){
                        return j;
                    }

                }
            }
        }
}

void problema10(){
    int num;
    cout << "Programa que da el n-esimo numero primo"<<endl;
    cout << "Ingresa un numero: ";
    cin >> num;

    cout << "El primo numero: "<<num<< " es: "<<n_numero_primo(num)<<endl;
}

int max_factor_primo(int numero){

    for(int i = numero; i > 2;i--){

        if((numero%i) == 0){ //es multiplo y existe i*n = numero
            int j = 4;
            for(;i >(j/2);j+=2){ //verificar si i es primo
                if(i % (j/2) == 0){ //no seria primo
                    break;
                }

            }
            if((j/2) == i){ //miramos si j/2 coincide con el valor de i, o sea, si resulta ser el factor que coincide con i
                return i; //encontramos y retornamos el mayor factor
            }
        }
    }
    return -1;
}

void problema12(){
    int num;
    cout << "Programa que halla el mayor factor primo del numero ingresado"<<endl;
    cout << "Ingresa un numero: ";
    cin >> num;

    cout << "El mayor factor primo de: "<<num<< " es: "<<max_factor_primo(num)<<endl;
}

bool esPalindromo(int num){;
    int copia_num = num, invertido = 0;
    while(copia_num != 0){
        int digito = copia_num % 10; //sacamos el ultimo digito del numero
        invertido = (invertido*10) + digito; //agragamos el numero que sacamos al final del numero
        copia_num /= 10; //modificamos la copia del numero para seguir con el ciclo
    }
    return (invertido == num);
}

int max_num_palindromo(){
    int mejor_palindromo = 0, a, b,a_max,b_max;
    for(a = 100;a <= 999;a++){
        for(b = 100;b<=999;b++){
            int producto = a*b;
            if(esPalindromo(producto)){
                if(producto > mejor_palindromo){
                    mejor_palindromo = producto;
                    a_max = a;
                    b_max = b;
                }

            }
        }
    }
    cout << a_max <<"*"<<b_max<<"="<<mejor_palindromo<<endl;
    return mejor_palindromo;
}


void problema14(){
    cout << "Programa que halla el mayor palindromo posible en la multiplicacion de numeros de 3 cifras"<<endl;
    max_num_palindromo();
}

int serieCollatz(int n, bool mostrar){ //funcion que calcula la serie de Collatz de un numero n como semilla y dice cuantos terminos tiene
    int count_terminos = 1;
    if(mostrar){
        cout << n<<":"<<n<<",";
    }

    while(n != 1){
        if((n%2) == 0){
            n = n/2;
            count_terminos += 1;
            if(mostrar){
                cout << n<<",";
            }

        }
        else{
            n = (3*n) + 1;
            count_terminos += 1;
            if(mostrar){
                cout << n<<",";}

        }
    }
    if(mostrar){
        cout<<endl<<"Numero de terminos: "<<count_terminos<<endl;
    }

    return count_terminos;
}

int mejorSemillaSerieCollatz(int k){
    int mejor_semilla = 0, mejor_cantidad_terminos = 0;

    for(int candidato = 2;candidato < k;candidato++){
        int terminos_actuales = serieCollatz(candidato, false);
        if(terminos_actuales > mejor_cantidad_terminos){
            mejor_semilla = candidato;
            mejor_cantidad_terminos = terminos_actuales;
        }
    }
    cout << "La serie mas larga es con la semilla: "<<mejor_semilla<<","<<" teniendo "<< mejor_cantidad_terminos<<" terminos"<<endl;
    serieCollatz(mejor_semilla, true);
    return mejor_semilla;
}

void problema16(){
    cout << "Programa que calcula la mejor semilla y serie de Collatz y la imprime"<<endl;
    int k;
    cout << "ingresa un número positivo entero K para hallar los números menores a este y la mejor semilla:"<<endl;
    cin >> k;
    mejorSemillaSerieCollatz(k);
}