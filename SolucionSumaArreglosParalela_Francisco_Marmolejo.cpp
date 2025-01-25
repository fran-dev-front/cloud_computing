#include "pch.h"
#include <iostream>
#include <omp.h>

#define N 100000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float *d);
void imprimeArregloFinal(float *d);

int main(){
    std::cout << "Suma Arreglos en paralelo!\n";
    float a[N], b[N], c[N];

    int i;
    for (i = 0 ; i < N ; i ++){
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;
        std::cout << "Imprimiendo los primeros" << mostrar << "valores del arreglo a: " << std::endl;
        imprimeArreglo(a);
        imprimeArreglo(b);
    

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i)\
    schedule(static, pedazos)

    for(i = 0; i < N; i++){
        c[i] = a[i] + b[i];
        // std::cout << "Imprimiendo los primeros" << mostrar << "valores del arreglo a: " << std::endl;
        // imprimeArreglo(a);
        // std::cout << "Imprimiendo los primeros" << mostrar << "valores del arreglo b: " << std::endl;
        // imprimeArreglo(b);


    }
    
    imprimeArregloFinal(c);
    std::cout << "Imprimiendo los primeros" << mostrar << "valores del arreglo c: " << std::endl;

}

void imprimeArreglo(float *d){
    for (int x = 0; x < mostrar; x++){
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}

void imprimeArregloFinal(float *d){
     std::cout << "-----------------------------------------------------------------------" << std::endl;
    for (int x = 0; x < mostrar; x++){
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}