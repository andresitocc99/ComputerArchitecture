# Tarea 4
El código src/task4/usm.cpp busca sumar una serie de valores a un valor inicial para obtener el valor final 20.
En principio el código puede parecer que es correcto, es más, si se ejecuta es muy probable que el resultado sea el correcto.
Sin embargo, esto no significa que el programa sea correcto. Esto pasa a menudo en programas paralelos.

En este caso, el problema está en acceder de forma concurrente a la memoria compartida. Si nos fijamos bien, no hay
ningún tipo de dependencia de datos explicita. Sin embargo, si todas las tareas acceden de manera concurrente pueden
causar problemas de comportamiento.

Para solucionar esta problemática cuando se usa USM hay varias opciones.
1. Marcar las dependencias mediante eventos.
2. Marcar las dependencias mediante waits.
3. Marcar las dependencias mediante in_order_queues.

## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante eventos.
**Guarda el código en results/task4/src/usm_events.cpp**
## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante waits.
**Guarda el código en results/task4/src/usm_waits.cpp**
## Realiza las modificaciones al código para solucionar las condiciones de carrera mediante in_order_queue.
**Guarda el código en results/task4/src/usm_inorder.cpp**

----
# Task 4
Code in src/task4.usm.cpp tries to compute the addition of a series of values over each item of an arrray. After the 
computation the result must be 20 for each item. The code may seem correct, and even provide a correct result when run.
However, that doesn't mean that it's correct. That is not strange in parallel programs.

Here the problem is that all kernels can access shared memory concurrently. If you pay attention you'll see no explicit
data dependence in the code, which may cause that two taks access in an incoherent way: one item of data read can be modified
after the reading, thus the task could update the new value with a wrong partial result.

This problem can be solved in different ways:
1. Set dependencies using events
2. Set dependencies using waits
3. Set dependencies using in_order_queues

## Modify the code to solve race conditions using events
**Store the code in results/task4/src/usm_events.cpp**
## Modify the code to solve race conditions using waits
**Store the code in results/task4/src/usm_waits.cpp**
## Modify the code to solve race conditions using an in_order_queue
**Store the code in results/task4/src/usm_inorder.cpp**
