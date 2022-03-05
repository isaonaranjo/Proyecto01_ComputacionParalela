// Maria Isabel Ortiz 
// Luis Alejandro Urbina
// Proyecto 1 


#include <stdio.h>
#include <math.h>
#include "Matriz.cpp"

void calcular(int intervalos) {
    double Tl = 20.0;
    double T0 = 1e-2;
    double Tr = 60.0;

    double C = 0.1;
    int x_intervalos = intervalos;
    int t_intervalos = int((pow(x_intervalos, 2) * 1e-5)/C);
    Matriz matriz = Matriz();
    matriz.columnas = t_intervalos;
    matriz.filas = x_intervalos;
    matriz.matriz = new double[x_intervalos * t_intervalos];

    int fila = 0;

    bool continuar = true;

    while (continuar){
        for (int columna = 1; columna < x_intervalos - 1; columna++){
            double T_ji;
            double T_J1i;
            double T_j1i;
            
            if(columna-1==0){
                matriz.set(columna - 1, fila, Tl);
            } if(columna+1==x_intervalos-1){
                matriz.set(columna + 1, fila, Tr);
            }
            if(fila!=0){
                T_ji = matriz.get(columna,fila);
                T_J1i =  matriz.get(columna+1,fila);
                T_j1i = matriz.get(columna-1,fila);
            } else {
                T_ji = T0 ;
                T_J1i = columna-1==0 ? Tl : T0;
                T_j1i = columna+1==x_intervalos-1 ? Tr : T0;
                matriz.set(columna , fila, T0);
            }
            double valor_nuevo = T_ji + C*(T_j1i - 2*T_ji + T_J1i);
            printf("fila: %d, columna:%d\n", fila, columna);
            if(fila!=0 && columna-1!=0 && columna+1!=x_intervalos-1){
            }
            matriz.set(columna , fila+1, valor_nuevo);
        }
        fila++;
    }
}

int main(int argc, char* argv[]) {
    int numero_threads = strtol(argv[1], NULL, 10);
    calcular(numero_threads);
    return 0;
}