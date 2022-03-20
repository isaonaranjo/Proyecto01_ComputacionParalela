#include <stdio.h>
#include <math.h>
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std::chrono;
#include "Matriz.cpp"

void calcularHeat(int intervalosDistancia, int intervalosTiempo, double Tl, double Tr) {
    bool criterioSalida = false;
    int indicex = 0;

    Matriz myMatriz = Matriz(intervalosDistancia, intervalosTiempo);

    while (!criterioSalida){
        for (int indicey = 1; indicey < intervalosDistancia - 1; indicey++){
            double T_ji; double T_J1i; double T_j1i;
            
            if(indicey+1==intervalosDistancia-1) myMatriz.matriz[myMatriz.columnas*(indicey+1) + indicex] = Tr;

            if(indicey-1==0) myMatriz.matriz[myMatriz.columnas*(indicey-1) + indicex] = Tl;

            if(indicex!=0){
                T_ji = myMatriz.matriz[myMatriz.columnas*indicey + indicex];
                T_J1i = myMatriz.matriz[myMatriz.columnas*(indicey+1) + indicex];
                T_j1i = myMatriz.matriz[myMatriz.columnas*(indicey-1) + indicex];
            } else {
                T_ji = (Tr-Tl)/(indicey*intervalosDistancia);
                T_J1i = (Tr-Tl)/((indicey+1)*intervalosDistancia);
                T_j1i = (Tr-Tl)/((indicey-1)*intervalosDistancia);

                myMatriz.matriz[myMatriz.columnas*(indicey) + indicex] = (Tr-Tl)/(indicey*intervalosDistancia);
            }

            double valor = 0.35*(T_j1i - 2*T_ji + T_J1i) + T_ji;

            if(indicex!=0 && indicey-1!=0 && indicey+1!= intervalosDistancia-1){
                if(indicex>10000){ criterioSalida = true;}
            }
            myMatriz.matriz[myMatriz.columnas*(indicey) + (indicex+1)] = valor;
        }
        indicex++;
    }
}

int main() {
    int intervalosDistancia;
    double Tl;
    double Tr;

    std::cout << "Ingrese la cantidad de intervalos de distancia: ";
    std::cin >> intervalosDistancia;

    if (intervalosDistancia <= 0) {
        std::cout << "Por favor ingrese una cantidad de threads mayor a 0";
        return 1;
    }

    std::cout << "Ingrese la temperatura en la frontera izquierda (Tl): ";
    std::cin >> Tl;

    if (Tl <= 0.0) {
        std::cout << "Por favor ingrese una temperatura de frontera izquierda Tl mayor a 0";
        return 1;
    }

    std::cout << "Ingrese la temperatura en la fronter derecha (Tr): ";
    std::cin >> Tr;

    if (Tl <= 0.0) {
        std::cout << "Por favor ingrese una temperatura de frontera derecha Tr mayor a 0";
        return 1;
    }

    if ((Tr-Tl) < 60.0) {
        std::cout << "La diferencia entre las temperaturas de frontera debe ser de al menos 60.0 °C";
        return 1;
    }

    int intervalosTiempo = int((pow(intervalosDistancia, 2) * 6e-3)/0.35);
    
    std::cout << "\nCorriendo programa con parámetros: " << std::endl;
    std::cout << "Intervalos de distancia = " << intervalosDistancia << std::endl;
    std::cout << "Intervalos de tiempo = " << intervalosTiempo << std::endl;
    std::cout << "Tl = " << Tl << "°C" << std::endl;
    std::cout << "Tr = " << Tr << "°C" << std::endl;
    std::cout << "C = " << 0.35 << std::endl;

    auto inicial = steady_clock::now();

    calcularHeat(intervalosDistancia, intervalosTiempo, Tl, Tr);
    
    auto final = steady_clock::now();
    auto tiempoTotal = duration_cast<milliseconds>(final - inicial);

    std::cout << "Tiempo de programa secuencial: " << tiempoTotal.count() << " ms" << std::endl;

    return 0;
}