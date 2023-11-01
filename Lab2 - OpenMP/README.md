[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/_UkDyd4F)
# Objetives
Get familiar with OpenMP through the completion of several exercises.

# Assesment
It is advisable for participants to complete this task individually to consolidate their understanding of OpenMP. The assignment will be evaluated based on the extent of its completion—whether the various exercises have been attempted or not. This assessment aims to enhance participants’ knowledge of OpenMP in preparation for upcoming labs and quizzes.

# Comparison and Analysis
For each exercise, participants will be asked to compare the execution times of the proposed solutions. It is crucial to understand the definition of a solution in this context. Initially, a program is deemed a solution if it is parallelized, and its outcome is identical to its sequential counterpart. For instance, if a program is parallelized to calculate the maximum number in a series, and the resulting maximum number differs from the one derived from its sequential version, it would imply incorrect parallelization.

When comparing solutions, various factors may affect a program’s execution time:

* Number of threads used
* Directives employed (as long as they can be applied to the problem, as not all directives are universally applicable)
* Work distribution
* 
To prevent the comparison task from being overly burdensome, as there may be numerous possible combinations, it is advisable to focus on a single variable mentioned above. For example, start by comparing all directives, then, once the best directive is identified, proceed to examine the effects of altering the number of threads used. It is recommended to analyze changes in work distribution lastly, as they have less impact than the other two factors.

For time comparison, consider utilizing a table where results can be easily viewed at a glance. Subsequently, elaborate on the conclusions drawn from these results.

# Exercise 1
Develop a sequential program that identifies the maximum and minimum values within a vector's components. Next, parallelize the program using various OpenMP directives applicable to the problem, and by modifying the number of threads used. Analyze and compare the execution times of the different solutions you propose to the problem, as well as the execution time of the sequential solution. To facilitate this analysis, consider creating a table indicating the directive used, number of threads, and execution time of each solution.

Make the modifications in results/task1/. In this directory, you can create a README.md with your analysis and store the different source codes.

# Exercise 2
Parallelize the code [sumavector.cpp](src/sumavector.cpp) using OpenMP. You can propose multiple solutions using different directives. Analyze and compare the results obtained from each solution using a table where you indicate the type of solution implemented.

Make changes to the source code in results/task2/. In this directory, you can create a README.md with your analysis and store the proposed solutions.

# Exercise 3
Parallelize the code pi.cpp using OpenMP. You are free to propose various solutions. Analyze and compare the results obtained from each solution. You may need to make changes to the algorithm itself to correctly parallelize it, due to dependencies between loop iterations.

Make changes to the source code in results/task3/. In this directory, you can create a README.md with your analysis and store the proposed solutions.
