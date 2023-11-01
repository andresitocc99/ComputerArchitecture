# 1. TASK 1

## 1.1. INTRODUCTION
First off all, im going to explain that i've used the following command to compile both files (paralellized and not parallelized files)

```bash
  g++ FILE.c -o COMPILED_FILE -fopenmp
```
* I have 3 'C' files: **sumavector_original.cpp**, **sumavector_parallelized_1.cpp** and **sumavector_parallelized_2.cpp**.
* With that 2 files i've generated 10 executables.
- 2 Executables for **sumavector_original.cpp** file. First one using an array of 50 Numbers, and second one with an array of 100 numbers
- 4 Executables for **sumavector_parallelized_1.cpp** file. Combination of files with different attributes, using arrays of 50 or 100 numbers, and using 4 or 8 threads to parallelize.
- 4 Executables for **sumavector_parallelized_2.cpp** file. Combination of files with different attributes, using arrays of 50 or 100 numbers, and using 4 or 8 threads to parallelize.

## 1.2. ANALYSIS

### 1.2.1. FIRST ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Size of array: 50**

| FILE | Execution Time |
|------|----------------|
| sumavector_original.cpp | 0.000035 seconds |
| sumavector_parallelized_1.cpp | 0.000802 seconds |
| sumavector_parallelized_2.cpp | 0.000783 seconds |


### 1.2.2. SECOND ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Size of array: 50**

| FILE | Execution Time |
|------|----------------|
| sumavector_original.cpp | 0.000194 seconds |
| sumavector_parallelized_1.cpp | 0.000691 seconds |
| sumavector_parallelized_2.cpp | 0.000881 seconds |

### 1.2.3. THIRD ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Size of array: 100**

| FILE | Execution Time |
|------|----------------|
| sumavector_original.cpp | 0.000248 seconds |
| sumavector_parallelized_1.cpp | 0.000818 seconds |
| sumavector_parallelized_2.cpp | 0.000854 seconds |


### 1.2.4. FOURTH ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Size of array: 100**

| FILE | Execution Time |
|------|----------------|
| sumavector_original.cpp | 0.000251 seconds |
| sumavector_parallelized_1.cpp | 0.001290 seconds |
| sumavector_parallelized_2.cpp | 0.000575 seconds |

## CONCLUSION
I've realised that the key has been adding the CRITICAL SECTION, because the calculations were beeing done wrongly. ALso, as bigger it be the size of the vector and more paralallelizable it be, it's run in less time.
