#include <iostream>
#include <cstdlib>
#include <math.h>
#include <omp.h>

#define SIZE 50000
#define REAL 0
#define IMAG 1

int main() {
    auto a = new float[SIZE][2];
    auto b = new float[SIZE][2];
    auto c = new float[SIZE][2];
    double n = SIZE;
    double seed = 3.141592653589793;

    // Generate pseudo random numbers
    for(int i = 0; i < SIZE; i++) {
        a[i][REAL] = sin((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        a[i][IMAG] = cos((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
        b[i][REAL] = sin((6*seed*i * ( seed*i - 1) + 1));
        b[i][IMAG] = cos((6*seed*i * ( seed*i - 1) + 1));
    }

    double t = omp_get_wtime();

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            c[i][REAL] += (a[i][REAL] * b[j][REAL]) - (a[i][IMAG] * b[j][IMAG]);
            c[i][IMAG] += (a[i][IMAG] * b[j][REAL]) + (a[i][REAL] * b[j][IMAG]);
        }
    }

    t = omp_get_wtime() - t;

    printf("Time elapsed to execute program: %.2f seconds\n", t);
}