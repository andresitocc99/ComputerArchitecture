#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#ifndef N
#define N 40
#endif


int main () {


    // CREATE AND FILLING RANDOMG ARRAY
    int array [N];
    double a,z;

    for (int i=0; i< N; i++) {
        array[i] = (rand() % 10)+1;
        printf("%d ",array[i]);
    }
    printf("\n");

    a = omp_get_wtime();
    int biggest_number = array[0], smallest_number = array[0];

    // SEQUENTIAL CODE WITH NO DIRECTIVES
    
    for (int i=0; i<N;i++) {
        if (array[i] > biggest_number) {
            biggest_number = array[i];
        }
        if (array[i] < smallest_number) {
            smallest_number = array[i];
        }
    }

    printf("Highest number is %d and smallest %d\n",biggest_number,smallest_number);
    z = omp_get_wtime();
    printf("Elapsed seconds = %0.10f seconds\n",z-a);
    return 0;
}