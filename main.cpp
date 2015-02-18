#include <iostream>
#define HV 999999999

using namespace std;

int menorTPS(int* TPS, int N);
int BuscarPuesto(int* TPS, int N);
int arrep(int ns);
int TA();
int IA();
void calcularImprimirResultados(int SPS, int STA, int PER, int ARR);

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

    calcularImprimirResultados(SPS, STA, PER, ARR);

}


int menorTPS(int* TPS, int N) {
    //function-stub
    return 1;
}
int BuscarPuesto(int* TPS, int N) {
    //function-stub
    return 1;
}
int arrep(int ns) {
    //function-stub
    return 0;
}
int TA() {
    //function-stub
    return 1;
}
int IA() {
    //function-stub
    return 1;
}
void calcularImprimirResultados(int SPS, int STA, int PER, int ARR){
    //function-stub
    cout << "Resultados: " << SPS << " " << STA << " " << PER << " " << ARR << endl;
}
