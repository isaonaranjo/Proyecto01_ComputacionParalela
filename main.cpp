#include "pdeSecuencial.cpp"  
#include <chrono>
#include <iostream>
#include <iomanip>
using namespace std::chrono;

// Valores iniciales de prueba
int numero_threads = 5000;
double Tl = 0.0;
double Tr = 80.0;

int main(int argc, char const *argv[])
{
    if (argc >= 3){
        numero_threads = strtol(argv[1], NULL, 10);
        Tl = strtol(argv[2], NULL, 10);
        Tr = strtol(argv[3], NULL, 10);
    }

    double C=0.35;

    int intervalosX = numero_threads;
    int intervalosTiempo = int((pow(intervalosX, 2) * 6e-3)/C);
    
    std::cout << "Corriendo programa con parámetros: " << std::endl;

    std::cout << "Intervalos de distancia = " << intervalosX << std::endl;
    std::cout << "Intervalos de tiempo = " << intervalosTiempo << std::endl;
    std::cout << "Tl = " << Tl << "°C" << std::endl;
    std::cout << "Tr = " << Tr << "°C\n" << std::endl;
    std::cout << "C = " << C << std::endl << std::endl;

    auto inicialSecuencial = high_resolution_clock::now();

    calculateHeat(numero_threads, Tl, Tr, C , intervalosX, intervalosTiempo);
    
    auto finalSecuencial = high_resolution_clock::now();

    auto tiempoSecuencial = duration_cast<milliseconds>(finalSecuencial - inicialSecuencial);

    std::cout << "Tiempo secuencial: " << tiempoSecuencial.count() << " ms" << std::endl;

    return 0;
}