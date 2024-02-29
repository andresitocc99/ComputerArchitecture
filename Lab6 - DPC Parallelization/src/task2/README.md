# Task 2
One the parallelization task is completed you'll check the performance of the solution.


## 1. Create a table for each image and configuration (serial, parallel) with the average times for each combination, you must use several blocks

| Modo       | Tiempo transcurrido (s) |
|------------|-------------------------|
| Secuencial | 6.71183                 |
| Paralelo   | 9.07989                 |
| GPU | 17.0247 |

It is surprising to observe that code executed in parallel mode takes longer than code executed sequentially. However, there are several reasons that can explain this behavior:

1. **Parallelization Overhead**: Introducing parallelism entails an extra cost associated with the division of work, synchronization between tasks and, potentially, data transfer between the host and the device. If the benefit obtained from parallel execution does not exceed this overhead, performance may be negatively affected.

2. **Inefficient Use of Resources**: The way hardware resources are used during parallel execution (memory access patterns, amount of work per task, etc.) may not be optimized, leading to a lower efficiency.

3. **Hardware Limitations**: Specific characteristics of the hardware device (GPU/CPU), such as the amount of memory and memory bandwidth, can limit the performance of parallel code.

4. **Work Granularity**: The effectiveness of parallelism also depends on the size of the tasks into which the work is divided. Inadequate task size can increase overhead without providing significant benefits.

5. **Device Selection**: The choice of hardware device to execute parallel code can impact performance if it is not the most suitable for the specific task.

## 2. Modify the code to deploy it in a GPU, using devcloud for the testing

## Modify the previous table to include the timing with respect to the GPU


## How did you run the code in the GPU?
MOdifying the following line:
    ```
    sycl::queue q(sycl::gpu_selector_v);
    ```

## Modify the program to gather information about the node running the task in the queue
**Save the resulting code in results/task2/task2.cpp**
