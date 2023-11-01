# Laboratorio 3: Vectorización
El objetivo de este laboratorio será el de comprender a nivel práctico como funciona y como se aplica la vectorización en un programa escrito en C. Para ello usaremos un programa que calcula la multiplicación de dos arrays (A y B) formados por números complejos, generando como resultado un nuevo array con el sumatorio de las multiplicaciones de los elementos de A por cada uno de los elementos de B. Este programa será analizado siguiendo un flujo de trabajo para vectorización.
Como resultado final, habrás aprendido a cómo vectorizar un programa y a analizar mediante las herramientas de
Intel las mejoras aplicadas.

# Tareas
Este laboratorio consta de varias tareas y para cada una de ellas el estudiante deberá contestar a una serie de preguntas
y análisis.

1. Tarea 1 - **Intel-Advisor y Hardware**: Esta tarea consistirá en responder a preguntas generales sobre intel advisor de modo que se adquieran todos los conocimientos necesarios para las siguientes tareas. [Enlace](results/task1/README.md)

2. Tarea 2 - **Roofline**: En esta tarea se realizará un análisis de tipo roofline y se buscará que seas capaz de analizar
la información representada en ese tipo de gráficos. [Enlace](results/task2/README.md)

3. Tarea 3 - **Vectorización**: En esta tarea se pedirá optimizar el programa haciendo uso de la vectorización y analizar
el resultado. [Enlace](results/task3/README.md)

4. Tarea 4 - **Análisis de memoria y mejora Vectorización**: A la hora de aplicar diferentes técnicas de paralelización es muy importante caracterizar el uso de la memoria y los patrones de acceso. En esta tarea se busca que seas capaz de analizar los movimientos de memoria en el algoritmo para optimizar la vectorización. [Enlace](results/task4/README.md)

----

# Lab 3: Vectorization
The objective of this laboratory is to gain practical understanding of the operation and application of vectorization within a program written in C. This will be accomplished through the use of a program designed to compute the multiplication of two arrays of complex numbers (A and B), which will produce a new array that embodies the summation of the elements in A for each element in B. The program will be analyzed following a workflow specific to vectorization.

Upon completion,you will have acquired the skills necessary to vectorize a program and to analyze the enhancements implemented, utilizing Intel's suite of tools.

# Tasks
This lab requires the completion of several tasks, that will imply performing some analysis and answering some questions:

1. Task 1 - **Intel-Advisor y Hardware**: In this task you will answer general questions about Intel Advisor with the aim to provide you with the knowledge to carry on the rest of the tasks. [Enlace](results/task1/README.md)
2. Tasl 2 - **Roofline**: In this task you'll perform a roofline analysis. Then you should be able to understand the information represented in this type of graphics. [Enlace](results/task3/README.md)
3. Task 3 - **Vectorización**: Here you will optimize the program through the use of the SIMD capabilities of OpemMP.  [Enlace](results/task3/README.md)
4. Task 4 - **Memory usage and Vectorization Analysis**: When parallelizing the code it is very important to understand the usage of memory and the different access patterns. In this task you will have to analyze the concrete algorithm tu understand such patterns and obtain a good vetorization result. [Enlace](results/task4/README.md)
