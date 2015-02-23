#include <iostream>
#include <cstdlib>
#define HV 999999999

using namespace std;

int menorTPS(int* TPS, int N);
int BuscarPuesto(int* TPS, int N);
int arrep(int ns);
int TA();
int IA();
void calcularImprimirResultados(int SPS, int STA, int PER, int ARR, int T);
float ran();

int main()
{ 
    //Condiciones iniciales
    int A = 0, ARR = 0, NS = 0, T = 0, i = 0, TF = 0, N = 0, TPLL = 0, STA = 0, SPS= 0, PER = 0, ta = 0;

    while (N <= 0){
        cout << "Especificar cantidad de puestos (N > 0)" << endl;
        cin >> N;
    }

    while (TF <= 0){
        cout << "Especificar tiempo de simulacion (TF > 0)" << endl;
        cin >> TF;
    }

    int TPS[N];

    for(int k = 1; k <= N; k++){
        TPS[k] = HV;
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
                TPS[i] = HV;
            }

            PER++;
        }
    }

    cout << "Fin de simulacion" << endl;

    calcularImprimirResultados(SPS, STA, PER, ARR, T);

}


int menorTPS(int* TPS, int N) {
    int m = 1;

    for(int i = 2; i <= N; i++){
        if(TPS[i] <= TPS[m]){
            m = i;
        }
    }

    return m;
}

int BuscarPuesto(int* TPS, int N) {
    int i = 1;

    while(i <= N && TPS[i] != HV){
        i++;
    }

    return i;
}

int arrep(int ns) {
    int r = ran();

    if(ns > 5){
        return 0;
    }
    else if(ns > 3){
        if(r < 0.2){
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
    return (20 - 15*R);
}
int IA() {
    float R = ran();
    return (30 - 25*R);
}

void calcularImprimirResultados(int SPS, int STA, int PER, int ARR, int T){

    double PTE = (SPS - STA) / PER;
    double PPS = SPS / PER;
    double PA = 100 * ARR / PER;

    cout << "Resultados: " << endl;
    cout << "Promedio de permanencia en el local: " << PPS << endl;
    cout << "Promedio de tiempo de espera en el local: " << PTE << endl;
    cout << "Porcentaje de arrepentidos: " << PA << endl;
}

float ran(){
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
