#include "pch.h"
#include <iostream>
#include <omp.h>

//Número de elementos en los arreglos A, B. C será llenado con la suma de estos.
#define N 100000
// Número de elementos por instrucción 
#define chunk 100
// Número de elementos de salida en pantalla
#define mostrar 10

//Definición del apuntador a las 2 funciones
void imprimeArreglo(float *d);
//Definición del apuntador de la función que mostrara la suma de los arreglos
void imprimeArregloFinal(float *d);

int main(){
    std::cout << "Suma Arreglos en paralelo!\n";
    // Inicialización de los arreglos. Se asigna la memoria del los N elementos que contendrán
    float a[N], b[N], c[N];
    //Inicialización del índice de tipo entero
    int i;
    //Ciclo for para llenar los arreglos a y b.
    for (i = 0 ; i < N ; i ++){
        //los elementos en el arreglo {a} serán el índice E.G 1*10;
        //a[0,10,20,30,40,...]
        a[i] = i * 10;
        //los elementos en el arreglo {b}  serán en índice mas 3 * 3.7. E.G (1+3)*3.7
        //b[11.1,14.8,18.5]
        b[i] = (i + 3) * 3.7;
    }
    int pedazos = chunk;
        std::cout << "Imprimiendo los primeros" << mostrar << "valores del arreglo a: " << std::endl;
        imprimeArreglo(a);
        imprimeArreglo(b);
    
    //Línea 40 índica que el siguiente ciclo for se ejecutara en paralelo utilizando múltiples Hilos
    //Línea 41 índica qué variables pueden ser accedidas(leer/escribir) por los hilos.
    //Línea 42 índica como el bucle se define en pedazos de 100 elementos   
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i)\
    schedule(static, pedazos)
    // estas es la operación que se hará en pedazos de 100 elementos cada vez.
    // del 0…100 se sumaran a[índice] + b[índice] en paralelo en diferentes hilos y el valor se asignara al índice de la suma
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


//Esta función itera sobre el arreglo al que se apunta. En iteraciones solo de 10 elementos del arreglo.
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
