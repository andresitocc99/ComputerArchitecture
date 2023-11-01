/* Programa secuencial que calcula la suma de los elementos de un vector v[i] 
 * y la almacena en la variable sum */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <omp.h>
#define N 100 // Probar distintos tamaños de vector 

int main() 
{ 
    int i, sum = 0; 
    int v[N];   
    double t1, t2;
    t1 =  omp_get_wtime();

    // Damos valores aleatorios al vector (entre 0 y 99) 
    srand (time(NULL)); // Semilla de números aleatorios 
    for (i = 0; i < N; i++) v[i] = rand()%100; 

    // Cálculo del sumatorio 
    for (i = 0; i < N; i++) sum += v[i];           

    // Como comprobación, se visualizan los valores del vector y la suma 
    printf("\nVector de números: \n "); 
    for (i = 0; i < N; i++) printf("%d \t",v[i]);
    
	printf("\n La suma es: %d \n\n", sum); 

    t2 =  omp_get_wtime();
    printf("\n Execution Time: %f\n", t2-t1);
    return 0;
} 
