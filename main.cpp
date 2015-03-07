#include <iostream>
#include <cstdlib>
#include <climits>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define HV ULLONG_MAX

using namespace std;

unsigned int menorTPS(unsigned long long* TPS, unsigned int N);
unsigned int BuscarPuesto(unsigned long long* TPS, unsigned int N);
unsigned int arrep(unsigned int ns);
unsigned int TA();
unsigned int IA();
unsigned int ganancia();
void calcularImprimirResultados(unsigned long long SPS,
                                unsigned long long STA,
                                unsigned long long PER,
                                unsigned int ARR,
                                unsigned long long T,
                                unsigned int N,
                                unsigned long long* STO,
                                unsigned long long* NC,
                                unsigned long long GAN);
float ran();

int main()
{ 

    //Condiciones iniciales
    unsigned int A = 0, ARR = 0, NS = 0, i = 0, N = 0, ta = 0;
    unsigned long long GAN = 0, T = 0, TF = 0, TPLL = 0, STA = 0, SPS= 0, PER = 0;

    /* initialize random seed: */
    srand (time(NULL));

    while (N <= 0){
        cout << "Especificar cantidad de puestos (N > 0)" << endl;
        cin >> N;
    }

    unsigned long long TPS[N], STO[N], ITO[N], NC[N];

    while (TF <= 0){
        cout << "Especificar tiempo de simulacion (TF > 0)" << endl;
        cin >> TF;
    }

    for(unsigned int k = 1; k <= N; k++){
        TPS[k] = HV;
        STO[k] = 0;
        ITO[k] = 0;
        NC[k] = 0;
    }

    cout << "Inicio de simulacion para N igual a " << N << " y tiempo de simulacion TF igual a " << TF <<endl;

    while(T < TF){

        //Busqueda del puesto con menor tiempo de proxima salida
        i = menorTPS(TPS, N);

        //Determinacion del instante T en que ocurre el proximo evento
        if(TPLL < TPS[i]) { //rama condicional de los eventos de llegada

            SPS += (TPLL - T) * NS;

            T = TPLL;

            //calculo de la funcion de densidad de probabilidad para intervalo entre arribos
            TPLL += IA();

            //rutina de arrepentimiento
            A = arrep(NS);

            if(A) { //se arrepintio
                ARR++;
            }
            else { //se quedo en el local
                NS++;

                if(NS <= N){
                    ta = TA();
                    //Busqueda de puerto disponible para atender
                    i = BuscarPuesto(TPS, N);
                    STO[i] = T - ITO[i];
                    TPS[i] = T + ta;
                    STA += ta;
                    NC[i]++;
                }

                PER++;
            }
            //
        }
        else {//rama condicional de los eventos de salida

            SPS += (TPS[i] - T) * NS;

            T = TPS[i];

            NS--;
            GAN += ganancia();

            if(NS >= N){
                ta = TA();
                TPS[i] = T + ta;
                STA += ta;
            }
            else {
                ITO[i] = T;
                TPS[i] = HV;
            }

            PER++;
        }
    }

    cout << "Fin de simulacion" << endl;

    calcularImprimirResultados(SPS, STA, PER, ARR, T, N, STO, NC, GAN);

}


unsigned int menorTPS(unsigned long long* TPS, unsigned int N) {
    int m = 1;

    for(unsigned int i = 2; i <= N; i++){
        if(TPS[i] <= TPS[m]){
            m = i;
        }
    }

    return m;
}

unsigned int BuscarPuesto(unsigned long long* TPS, unsigned int N) {
    unsigned int i = 1;

    while(i <= N && TPS[i] != HV){
        i++;
    }

    return i;
}

unsigned int arrep(unsigned int ns) {
    float r = ran();

    if(ns > 5){
        return 0;
    }
    else if(ns > 3){
        if(r <= 0.2){
            return 0;
        }
        else {
            return 1;
        }
    }

    return 0;
}
unsigned int TA() {
    float R = ran();
    return (30.0 - 15.0 * R);
}

unsigned int IA() {
    float R = ran();
    return (25.0 - 15.0 * R);
}

unsigned int ganancia() {
    float R = ran();
    return (1000.0 - 950.0 * R);
}

void calcularImprimirResultados(unsigned long long SPS,
                                unsigned long long STA,
                                unsigned long long PER,
                                unsigned int ARR,
                                unsigned long long T,
                                unsigned int N,
                                unsigned long long* STO,
                                unsigned long long* NC,
                                unsigned long long GAN){

    float PTE;
    if(SPS - STA > 0) PTE = (float) (SPS - STA) / (float) PER;
    else  PTE = 0;
    float PPS = (float) SPS / (float) PER;
    float PA = 100 * (float) ARR / (float) PER;
    float PTO[N];

    cout << "Resultados: " << endl;
    cout << "Ganancia Total: $" << GAN << endl;
    cout << "Promedio de permanencia en el local: " << PPS << endl;
    cout << "Promedio de tiempo de espera en el local: " << PTE << endl;
    cout << "Porcentaje de arrepentidos: " << PA << "%" << endl;
    for(unsigned int k = 1; k <= N; k++){
        if(NC[k] == 0){
            PTO[k] = 100;
        }
        else{
            PTO[k] = 100 * (float) STO[k] / (float) T;
        }
        cout << "Porcentaje de tiempo ocioso empleada "<< k << ": " << PTO[k] << "%" << endl;
    }
}

float ran(){
    return ((float)rand()) / ((float)RAND_MAX);
}
