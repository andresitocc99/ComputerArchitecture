# Laboratory 1: Getting Acquainted with the Environment
The objective of this practice is for you to become familiar with the tools we will use during the course labs.

# Tasks

1. Compile and run the program matmul.cpp, saving the execution result in results/task1/task1.txt. For the compilation, use the g++ compiler and add the compiler options -g and -fopenmp. The -g option adds debugging information and it's advisable to use it whenever you're going to analyze a program's performance with Intel Advisor. The -fopenmp option links the OpenMP libraries for parallel programming.
2. Perform an analysis with Survey and Characterization types (Trip Counts and FLOP) on your PC using the Intel Advisor graphical interface:
  * Once the analysis is done, you should see a warning at the top with the message **Some target modules are not compiled with optimization enabled and with version 15.0 or higher of the Intel compiler**. What does this warning indicate? How would you solve this problem so that the warning disappears (it might not be possible to eliminate all warnings)? (**hint**: it has to do with the compiler used, check the compilers you have with intel oneAPI, once you find the right one **you should use it for all practices, including the remaining tasks of this lab**). Save the analysis results with the warning by taking a snapshot of Intel Advisor (important not to confuse it with a screenshot) named **warning** in [results/task2](results/task2).
  * Recompile the code with the appropriate compiler. Save the analysis results without the warning by taking a snapshot of Intel Advisor. This snapshot should be uploaded to the repository in results/task2 named snapshot.
3. Perform the same type of analysis as in task 2 on the devcloud environment (compile the source code with the compiler you used in task 2). If you could not run the analysis on your computer in the previous task, find a way to use two nodes with different CPUs on devcloud.
  * Indicate the commands you used to obtain both the results and the snapshot.
  * Upload the analysis results (the snapshot) to the repository in [results/task3](results/task3) named snapshot-devcloud.
4. Compare and **analyze** the results, emphasizing time, performance, and memory measures.
5. Upload the report to the [results/task4](results/task4) folder named comparacion.md. The report must be in markdown format.
6. Identify the key characteristics of the systems on which you have run the analyses (processor, memory, cache, etc.) and relate them to the analyzed results.
Upload the report to the [results/task5](results/task5) folder with the name caracteristicas.md.

# Grading

The practice will be graded based on the following rubrics:

1. Completeness 40%: this means that simply completing the tasks will ensure a 4. It's not necessary for the results to be correct, but it is necessary to demonstrate (through commits) that the work has been legitimately carried out.
2. Correct Results 30%: If the results are correct and the practice has been legitimately carried out, you will have a 7.
3. Engagement 30%: Your opportunity to stand out. If you are interested in the topic and demonstrate it through detailed analyses, quality references, and critical thinking in your analyses, you can achieve a 10. Remember, it is important to think beyond the immediate, reflect on the results, and ask questions. A practice that raises questions is a good indicator that you are going beyond simple results. If these questions are accompanied by possible answers, then you have done perfect work.

# Participants
ANDRÉS CASTELLANOS CANTOS

# Useful Links

[How to create a snapshot?](https://www.intel.com/content/www/us/en/develop/documentation/advisor-user-guide/top/command-line-interface/advisor-command-line-interface-reference/advisor-command-action-reference/snapshot.html) : It is recommended to use the last command
[How to use Advisor in the cloud?](https://www.intel.com/content/www/us/en/develop/documentation/advisor-user-guide/top/command-line-interface/advisor-command-line-interface-reference.html)
[Markdown syntax](https://guides.github.com/features/mastering-markdown/)


