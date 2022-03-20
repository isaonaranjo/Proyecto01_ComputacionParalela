#include <stdio.h>

class Matriz {
    public:
        int filas;
        int columnas;
        double *matriz;

        Matriz(int myFilas, int myColumnas){
            filas = myFilas;
            columnas = myColumnas;
            matriz = new double[filas * columnas];
        }
};