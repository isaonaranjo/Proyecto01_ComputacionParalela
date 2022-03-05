// Maria Isabel Ortiz 
// Luis Alejandro Urbina
// Proyecto 1 

#include <stdio.h>

class Matriz {
    public:
        double *matriz;
        int columnas;
        int filas;
    double get(int i, int j){
        return matriz[columnas*i + j];
    }
    void set(int i, int j, double element){
        matriz[columnas*i + j] = element;
    }
};
