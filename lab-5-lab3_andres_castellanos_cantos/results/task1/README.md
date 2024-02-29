# Task 1
Get familiar with Intel DPC compiler.
First copy the code in src/task1/query.cpp to results/task1/src and compile it with dpcpp.

## 1. Which output do you obtain?

After compiling and running it, i get the information about my CPU, which is: Intel(R) Core(TM) i7-8750H CPU @ 2.20GHz

## 2. Which different types of selectors do we have in DPC? Can we obtain a GPU? What happens if the requested device doesn't exist?

- **Type of selectors**: *default, CPU, Host, Accelerator and GPU*
- We can obtain a GPU by modifying the code, using '*gpu_selector*'
- If the device doesnt exist, then it **shows an error**

It is very likely that some of the devices that can be used with DPC are not available in your PC. Don't worry about that, since we can use devcloud for such purpose.

## 3. Try to obtain a GPU from devcloud by the query.cpp program into gpu_query.cpp
**store the resulting file in results/task1/src.**

## 4. How did you obtained the GPU? How have you requested qsub that you want a node with a GPU?
First we had to do a change in the code, using 'gpu_selector', then the command to request a node is different as we use to use in devcloud:
    ```
    qsub -I -q batch -l nodes=1:gpu:ppn=2
    ```

## Modify the program to obtain more data from the device.
**store the resulting file in results/task1/src/more_query.cpp**
