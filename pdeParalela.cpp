#include <stdio.h>
#include <math.h>
#include "Matriz.cpp"

void parallelizedSection(int i, Matriz myMatriz,double Tl,double Tr, double C, int intervalosX){
    #pragma omp parallel shared(myMatriz, Tl, Tr, C, intervalosX)
    #pragma omp single nowait
    {
        for (int j = 1; j < intervalosX - 1; j++){
            #pragma omp task

                if(j+1==intervalosX-1){
                    myMatriz.set(j + 1, i, Tr);
                }

                if(j-1==0){
                    myMatriz.set(j - 1, i, Tl);
                } 

                double T_ji;
                double T_J1i;
                double T_j1i;

                if(i!=0){
                    T_ji = myMatriz.get(j,i);
                    T_J1i = myMatriz.get(j+1,i);
                    T_j1i = myMatriz.get(j-1,i);
                } else {
                    T_ji = (Tr-Tl)/(j*intervalosX);
                    T_J1i = (Tr-Tl)/((j+1)*intervalosX);
                    T_j1i = (Tr-Tl)/((j-1)*intervalosX);
                    myMatriz.set(j , i, (Tr-Tl)/(j*intervalosX));
                }

                double valor = T_ji + C*(T_j1i - 2*T_ji + T_J1i);
                myMatriz.set(j , i+1, valor);
        }
        if(i<100000){
            parallelizedSection(i+1, myMatriz, Tl, Tr, C, intervalosX);
        }
    }
}

void calculate(int intervalos, double Tl, double Tr, double C, int intervalosX, int intervalosTiempo) {
    Matriz myMatriz = Matriz();
    myMatriz.columnas = intervalosTiempo;
    myMatriz.filas = intervalosX;
    myMatriz.matriz = new double[intervalosX * intervalosTiempo];

    parallelizedSection(0, myMatriz, Tl, Tr, C, intervalosX);
}