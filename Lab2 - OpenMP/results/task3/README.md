# 1. TASK 1

## 1.1. INTRODUCTION
First off all, im going to explain that i've used the following command to compile both files (paralellized and not parallelized files)

```bash
  g++ FILE.c -o COMPILED_FILE -fopenmp
```
* I have 3 'C' files: **pi_original.cpp**, **pi_parallelized_1.cpp** and **pi_parallelized_2.cpp**.
* With that 2 files i've generated 10 executables.
- 1 Executables for **pi_original.cpp** file. 
- 2 Executables for **pi_parallelized_1.cpp** file. One file using 4 Threads and other using 8 threads.
- 2 Executables for **pi_parallelized_2.cpp** file. One file using 4 Threads and other using 8 threads.

## 1.2. ANALYSIS

### 1.2.1. FIRST ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Precission**: 10

| FILE | Execution Time | Pi Value | Error |
|------|----------------|-------------|--------------------|
| pi_original.cpp | 0.0001926350 seconds | 3.1424259850010987 | 0.0008333314113056 |
| pi_parallelized_1.cpp | 0.0005277250 seconds | 2.8204262921724044 | 0.3211663614173887 |
| pi_parallelized_2.cpp | 0.0004842380 seconds | 3.2175783446677664 | 0.0759856910779733 |

### 1.2.2. SECOND ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Precission**: 10000

| FILE | Execution Time | Pi Value | Error |
|------|----------------|-------------|--------------------|
| pi_original.cpp | 0.0001926350 seconds | 3.1415926544232282 | 0.0000000008334351 |
| pi_parallelized_1.cpp | 0.0006448830 seconds | 0.9799146532456334 | 2.1616780003441596 |
| pi_parallelized_2.cpp | 0.0050030510 seconds | 3.1421254793962818 | 0.0005328258064887 |

### 1.2.3. THIRD ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Precission**: 10

| FILE | Execution Time | Pi Value | Error |
|------|----------------|-------------|--------------------|
| pi_original.cpp | 0.0001926350 seconds | 3.1424259850010987 | 0.0008333314113056 |
| pi_parallelized_1.cpp | 0.0008071380 seconds | 1.5509461640017606 | 1.5906464895880326 |
| pi_parallelized_2.cpp | 0.0008830710 seconds | 3.6073550089313140 | 0.4657623553415209 |

### 1.2.4. FOURTH ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Precission**: 10000

| FILE | Execution Time | Pi Value | Error |
|------|----------------|-------------|--------------------|
| pi_original.cpp | 0.0010404340 seconds | 3.1415926544232282 | 0.0000000008334351 |
| pi_parallelized_1.cpp | 0.0006448830 seconds | 0.6070500316309740 | 2.5345426219588192 |
| pi_parallelized_2.cpp | 0.0050262000 seconds | 3.1425867459982859 | .0009940924084928 |


## CONCLUSION
The conclusion I have reached is that adding critical sections is a key point, since without them the calculations are performed incorrectly. Also, the more the program is parallelized, the more execution time we get. Normally ne the oriignal file, the execution time is less at lower precisions.
