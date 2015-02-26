#include <iostream>
#include <cstdlib>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#define HV 999999999

using namespace std;

int menorTPS(long* TPS, int N);
int BuscarPuesto(long* TPS, int N);
int arrep(int ns);
int TA();
int IA();
void calcularImprimirResultados(long SPS, long STA, long PER, int ARR, long T, int N, long* STO);
float ran();

int main()
{ 

    //Condiciones iniciales
    int A = 0, ARR = 0, NS = 0, i = 0, N = 0, ta = 0;
    long T = 0, TF = 0, TPLL = 0, STA = 0, SPS= 0, PER = 0;
    long TPS[N], STO[N], ITO[N];

    /* initialize random seed: */
    srand (time(NULL));

    while (N <= 0){
        cout << "Especificar cantidad de puestos (N > 0)" << endl;
        cin >> N;
    }

    while (TF <= 0){
        cout << "Especificar tiempo de simulacion (TF > 0)" << endl;
        cin >> TF;
    }

    for(int k = 1; k <= N; k++){
        TPS[k] = HV;
        STO[k] = 0;
        ITO[k] = 0;
    }

    cout << "Inicio de simulacion para N igual a " << N << " y tiempo de simulacion TF igual a " << TF <<endl;

    while(T < TF){

        cout << ran() << endl;

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
                }

                PER++;
            }
            //
        }
        else {//rama condicional de los eventos de salida

            SPS += (TPS[i] - T) * NS;

            T = TPS[i];

            NS--;

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

    calcularImprimirResultados(SPS, STA, PER, ARR, T, N, STO);

}


int menorTPS(long* TPS, int N) {
    int m = 1;

    for(int i = 2; i <= N; i++){
        if(TPS[i] <= TPS[m]){
            m = i;
        }
    }

    return m;
}

int BuscarPuesto(long* TPS, int N) {
    int i = 1;

    while(i <= N && TPS[i] != HV){
        i++;
    }

    return i;
}

int arrep(int ns) {
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
int TA() {
    float R = ran();
    return (30.0 - 10.0 * R);
}
int IA() {
    float R = ran();
    return (26.0 - 25.0 * R);
}

void calcularImprimirResultados(long SPS, long STA, long PER, int ARR, long T, int N, long* STO){

    float PTE = (SPS - STA) / PER;
    float PPS = SPS / PER;
    float PA = 100 * ARR / PER;
    float PTO[N];

    cout << "Resultados: " << endl;
    cout << "Promedio de permanencia en el local: " << PPS << endl;
    cout << "Promedio de tiempo de espera en el local: " << PTE << endl;
    cout << "Porcentaje de arrepentidos: " << PA << endl;
    for(int k = 1; k <= N; k++){
        PTO[k] = 100 * STO[k] / T;
        cout << "Porcentaje de tiempo ocioso empleada "<< k << ": " << PTO[k] << endl;
    }
}

float ran(){
    return ((float)rand()) / ((float)RAND_MAX);
}
