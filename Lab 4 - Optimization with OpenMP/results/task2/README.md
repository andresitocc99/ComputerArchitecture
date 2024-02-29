# Tarea 2: Análisis de Threading
## Preguntas

* Procede a realizar el análisis de threading hasta el análisis **Suitability**

* Antes de comenzar a interpretar los resultados es importante saber la información representada. Ve a la pestaña Suitability Report y responde a las siguientes preguntas:
    * ¿Qué representa el gráfico Scalability of Maximum Site Gain? ¿Para que sirven las opciones Avg. Number of Iterations y Avg. Iteration Duration?
    * Explica que significa cada campo de las columnas **Impact to Program Gain**, **Combined Site Metrics, All Instances** y **Site Instance Metrics, Parallel Time**

* Analiza la escalabilidad de la ganancia por cada Site que has declarado:
    * En primer lugar configura el reporte acorde a tu sistema y al modelo de paralelización con hilos que vayas a utilizar.
    * Realiza un snapshot y guárdalo con el nombre task2 en la carpeta [task2](/results/task2)
    * Indica para cada uno de los sites definidos, a partir de qué número de CPUs la ganancia deja de mejorar o incluso empeora, y justifica la razón por la cual ocurre.
    * ¿Cuál de los bucles definidos en el código supone un mayor tiempo de ejecución del programa? ¿Cómo afectaría a la ganancia de este Site si, usando el máximo número de CPUs de la simulación (64), en vez de usar bloques de tamaño de 1024 se reduce a 256? Indica cómo has obtenido este nueva ganancia.
	
	
----


# Task 2: Threading Analysis
## Questions

* Proceed with the threading analysis up to the **Suitability** analysis.

* Before interpreting the results, it is important to understand the represented information. Go to the Suitability Report tab and answer the following questions:
    * What does the Scalability of Maximum Site Gain graph represent? What are the purposes of the Avg. Number of Iterations and Avg. Iteration Duration options?
    * Explain the meaning of each field in the columns **Impact to Program Gain**, **Combined Site Metrics, All Instances** y **Site Instance Metrics, Parallel Time**

* Analyze the scalability of gain for each of the Sites you've defined:
    * First, configure the report according to your system and the threading model you plan to use.
    * Take a snapshot and save it with the name task2 in the [task2](/results/task2) folder.
    * For each of the defined Sites, specify from how many CPUs the gain ceases to improve or even worsens, and justify why this occurs.
    * Which of the loops defined in the code consumes the most execution time in the program? How would reducing the block size from 1024 to 256, using the maximum number of CPUs in the simulation (64), affect the gain of this Site? Explain how you obtained this new gain.
