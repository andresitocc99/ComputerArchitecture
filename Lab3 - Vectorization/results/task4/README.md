# Task 4: Memory Analysis and Vectorization improvement

## Questions:

### 1. Recompile the complexmul.cpp program without vectorization and generate a memory analysis, highlighting the computation loops that perform the multiplication of complex numbers. Specifically, mark the loops on lines 27 and 28 (if the analysis takes too long, consider reducing the size). Conduct the analysis using both the Intel Advisor graphical interface and the command line. Also, specify the command you used for the command-line analysis.
```bash
advisor --collect=tripcounts --flop --select=<string>(to select the loops) --project-dir=./advi_results -- ./myApplication
```

### 2. Open Advisor and select the "Refinement Reports" view.

  * What information does this view provide? List each item in the table, summarizing its meaning.
      - Site location: Information about parent function, source file and line where loop begins.
      - Loop-Carried Dependencies: summary of dependencies across iterations.
      - Strides Distribution: stride ratio for selected site.
      - Access Patern: stride types detected.
      - Footprint stimate: Memory footprint. It has three parts:  
           - Maximum distance between max and min memory address.   
           - First instance site footprint.   
           - Simulated memory footprint.      
        
      - Site name: name to see in the survey report.
      - Performance issues: related to deeper analysis.
      - Cache line utilization.
      - Memory loads (in the first instance).
      - Cache misses: memory loads by subsystem higher than cache.
      - RFO Cache Misses: lines loaded to the cache due a data modification request.
      - Dirty evictions: cache lines with a modified state.

  * What memory behavior is observed? Why is it desirable to have a uniform stride?
  * Examine the memory analysis results for both loops and confirm that the stride is 2.
  * Why is the stride value set at this level? (Review the concepts of row-order and column-order, as well as the order in which memory is allocated in C).
  * Which variables are being accessed with a stride of 2? How does this affect the cache?
  * Can you think of a way to modify the program, keeping the two loops and the same outcome, so that variable access is uniform? Implement the change and save the result in this same folder with the name complexmul_unit_stride.cpp.
* Generate a snapshot for the complete analysis (up to memory access patterns) for both the version with a stride of 2 and the version with a unitary stride (both vectorizing the code). Name them "task4a" and "task4b", respectively, and add them to this same folder.

  * In "task4b," what are the values for vector length and the estimated gain? Are these the expected results? Justify your answer.
  * Comparing these two solutions, by how much has the gain increased?
* Compare the analysis results of task2 and task4b:
  * What was the actual gain from the vectorized algorithm? Was it less or more than the estimate?
