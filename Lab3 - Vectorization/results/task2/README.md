# Task2: Roofline
## Questions

### 1. Generate a roofline and analyze the information depicted. Copy a screenshot of the roofline in your response to support your analysis. Finally, create a snapshot with the name "task2" and add it to this same folder.

* The Roofline diagram represents two coordinate axes. The 'X' axis represents arithmetic intensity, and the 'Y' axis represents achievable GFLOPs.
* Increasing arithmetic intensity does not necessarily imply an improvement in performance, but reducing arithmetic intensity will indeed decrease performance.
* As for bandwidth, it improves the maximum performance.

![Roofline](https://github.com/ASIGNATURA-ARCO-UCLM/lab-3-lab3_andres_castellanos_cantos/blob/master/results/task2/Lab3-Task2-Roofline.png)

### 2. Why is the algorithm limited? What techniques could we apply to improve performance?

* The algorithm is limited due to issues with limited memory, which is caused by the way matrices are handled. Taking into account the access to matrix row and column positions and how they are loaded into the cache, most accesses result in cache misses.
* To improve performance, we can divide the array into smaller ones, processing each array separately, even using different cores for each one.


