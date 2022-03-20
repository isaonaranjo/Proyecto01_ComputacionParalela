#include <stdio.h>
#include <math.h>
#include "Matriz.cpp"
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std::chrono;

void calculateHeat(int intervalos, double Tl, double Tr, double C, int intervalosX, int intervalosTiempo) {
    bool criterioSalida = false;
    int indicex = 0;

    Matriz myMatriz = Matriz(intervalosX, intervalosTiempo);

    while (!criterioSalida){
        for (int indicey = 1; indicey < intervalosX - 1; indicey++){
            double T_ji;
            double T_J1i;
            double T_j1i;
            
            if(indicey+1==intervalosX-1){
                myMatriz.matriz[myMatriz.columnas*(indicey+1) + indicex] = Tr;
            }

            if(indicey-1==0){
                myMatriz.matriz[myMatriz.columnas*(indicey-1) + indicex] = Tl;
            }

            if(indicex!=0){
                T_ji = myMatriz.matriz[myMatriz.columnas*indicey + indicex];
                T_J1i = myMatriz.matriz[myMatriz.columnas*(indicey+1) + indicex];
                T_j1i = myMatriz.matriz[myMatriz.columnas*(indicey-1) + indicex];
            } else {
                T_ji = (Tr-Tl)/(indicey*intervalosX);
                T_J1i = (Tr-Tl)/((indicey+1)*intervalosX);
                T_j1i = (Tr-Tl)/((indicey-1)*intervalosX);

                myMatriz.matriz[myMatriz.columnas*(indicey) + indicex] = (Tr-Tl)/(indicey*intervalosX);
            }

            double valor = C*(T_j1i - 2*T_ji + T_J1i) + T_ji;

            if(indicex!=0 && indicey-1!=0 && indicey+1!= intervalosX-1){
                if(indicex>10000){ criterioSalida = true;}
            }
            myMatriz.matriz[myMatriz.columnas*(indicey) + (indicex+1)] = valor;
        }
        indicex++;
    }
}

int main(int argc, char const *argv[]) {
    int cantidadthreads;
    double Tl;
    double Tr;

    std::cout << "Ingrese la cantidad de intervalos en X: ";
    std::cin >> cantidadthreads;

    std::cout << "Ingrese el Tl: ";
    std::cin >> Tl;

    std::cout << "Ingrese el Tr: ";
    std::cin >> Tr;

    double C=0.35;

    int intervalosX = cantidadthreads;
    int intervalosTiempo = int((pow(intervalosX, 2) * 6e-3)/C);
    
    std::cout << "\nCorriendo programa con parámetros: " << std::endl;
    std::cout << "Intervalos de distancia = " << intervalosX << std::endl;
    std::cout << "C = " << C << std::endl;
    std::cout << "Intervalos de tiempo = " << intervalosTiempo << std::endl;
    std::cout << "Tl = " << Tl << "°C" << std::endl;
    std::cout << "Tr = " << Tr << "°C" << std::endl;

    auto inicial = high_resolution_clock::now();

    calculateHeat(cantidadthreads, Tl, Tr, C , intervalosX, intervalosTiempo);
    
    auto final = high_resolution_clock::now();
    auto tiempoTotal = duration_cast<milliseconds>(final - inicial);

    std::cout << "Tiempo de programa secuencial: " << tiempoTotal.count() << " ms" << std::endl;

    return 0;
}