# 1. TASK 1

## 1.1. INTRODUCTION
First off all, im going to explain that i've used the following command to compile both files (paralellized and not parallelized files)

```bash
  gcc FILE.c -o COMPILED_FILE -fopenmp
```
* I have 2 'C' files: **ex1_no_directive.c** and **ex1_directive_for.c**.
* With that 2 files i've generated 6 executables.
- 2 Executables for **ex1_no_directive.c** file. First one using an array of 20 Numbers, and second one with an array of 40 numbers
- 4 Executables for **ex1_directive_for.c** file. Combination of files with different attributes, using arrays of 20 or 40 numbers, and using 4 or 8 threads to parallelize.

## 1.2. ANALYSIS

### 1.2.1. FIRST ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Size of array: 20**

| FILE | Execution Time |
|------|----------------|
| ex1_no_directive.c | 0.0000105260 seconds |
| ex1_directive_for.c | 0.0000179350 seconds |


### 1.2.2. SECOND ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Size of array: 20**

| FILE | Execution Time |
|------|----------------|
| ex1_no_directive.c | 0.0000085970 seconds |
| ex1_directive_for.c | 0.0000091880 seconds |

### 1.2.3. THIRD ANALYSIS

- **Number of threads: 4** *(Just for parallelized file)*
- **Size of array: 40**

| FILE | Execution Time |
|------|----------------|
| ex1_no_directive.c | 0.0000085970 seconds |
| ex1_directive_for.c | 0.0000091880 seconds |


### 1.2.4. FOURTH ANALYSIS

- **Number of threads: 8** *(Just for parallelized file)*
- **Size of array: 40**

| FILE | Execution Time |
|------|----------------|
| ex1_no_directive.c | 0.0000083900 seconds |
| ex1_directive_for.c | 0.0000087570 seconds |

## CONCLUSION
As we can see in differents program execution, the paralellized program last more time than non-parallelized program, and i think its due to the program is really simple, so it last more time in the parallelization of the parallelized program, comparing with doing that in the non-parallelized program.  As much we paralallelized or we add threads, execution time is increased. 
