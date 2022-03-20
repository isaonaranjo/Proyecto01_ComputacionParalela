#include "pdeSecuencial.cpp"  
#include <chrono>
#include <iostream>
#include <iomanip>

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
    int intervalosTiempo = int((pow(numero_threads, 2) * 6e-3)/C);
    
    std::cout << "Corriendo programa con parámetros: " << std::endl;

    std::cout << "Intervalos de distancia = " << intervalosX << std::endl;
    std::cout << "Intervalos de tiempo = " << intervalosTiempo << std::endl;
    std::cout << "Tl = " << Tl << "°C" << std::endl;
    std::cout << "Tr = " << Tr << "°C\n" << std::endl;
    std::cout << "C = " << C << std::endl << std::endl;

    auto inicialSecuencial = std::chrono::high_resolution_clock::now();

    calculateHeat(numero_threads, Tl, Tr, C , intervalosX, intervalosTiempo);
    
    auto finalSecuencial = std::chrono::high_resolution_clock::now();

    auto tiempoSecuencial = std::chrono::duration_cast<std::chrono::milliseconds>(finalSecuencial - inicialSecuencial);

    std::cout << "Tiempo secuencial: " << tiempoSecuencial.count() << " ms" << std::endl;

    return 0;
}