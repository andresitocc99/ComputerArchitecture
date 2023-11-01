# Tarea 1: Intel Advisor

## Preguntas

### 1. En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?
* Total Time representa el tiempo total que se tarda en ejecutar una sección de código o una finción.
* Self-Time se refiere al tiempo que una sección de código o función pasa ejecutándose de manera exclusiva, sin incluir el tiempo gastado en llamadas a otras funciones.
* En resumen, la diferencia clave es la inclusión o no del tiempo gastado en la llamada a otras funciones

### 2. Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará más tarde).

![Survey](https://github.com/ASIGNATURA-ARCO-UCLM/lab-3-lab3_andres_castellanos_cantos/blob/master/results/task1/Lab3-Task1-Survey.png))

### 3. Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?
* El análisis tipo 'Survey' es insuficiente para que muestr el 'roofline', ya que depende de los datos de operaciones de punto flotante y enteros.
* Para ello hay que habilitar la casilla 'FLOP' y 'Tripcount' y posteriormente realizar el análisis de recuento de FLOPS y Tripcounts.

### 4. Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta los datos nuevos más relevantes.
* En cuanto las llamadas a funciones y bucles, nos muestra 4: el loop en el fichero en linea 28, _start, main y loop en el main en linea 27.
* Posteriormente, en cuanto a la información aportada para cada llamada a función o bucle, tenemos: Tiempo de CPU, que puede ser dividido en Tiempo Total y 'Tiempo Solo'.
* Nos informa de los bucles vectorizados, en nuestro caso es el primero, y esto se divide en 4 apartados: la ISA utilizada (AVX2), la Eficiencia (44%) de la vectorización, la ganancia estimada (7,07x), y el tamaño del vector (16).
* El tipo de llamada, que en este caso hay 2 escalares y dos funciones.
* En el rendimietno computacional, es divido en Sels GFLOPS, que es la cantidad de operaciones en punto flotante de coma flotante (FLOP) que realiza una sección de código o una función por segundo, y Self AI (Self Arithmetic Intensity), que mide la relación entre las operaciones aritméticas realizadas (como sumas o multiplicaciones) y el acceso a la memoria. "Self AI" se refiere a la intensidad aritmética generada por una sección de código o una función sin incluir las operaciones realizadas en las llamadas a funciones dentro de esa sección
* Posteriormente nos indica el tráfico de memoria y métricas de ancho de banda (el primer loop usa 20).
* TripCounts se refiere al recuento de iteraciones de bucles en tu código. Se divide en recuento promedio y 'Call Count' que mide el numero de llamadas en la sección de código.

![Survey-Roofline](https://github.com/ASIGNATURA-ARCO-UCLM/lab-3-lab3_andres_castellanos_cantos/blob/master/results/task1/Lab3-Task1-Survey-TripCountsFlops.png)
