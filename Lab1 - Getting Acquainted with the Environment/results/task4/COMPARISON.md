## COMPARACIÓN Y ANÁLISIS DEL EJECUTABLE 'MATMUL' EN ORDENADOR LOCAL Y NODO DE DEVCLOUD

### Comparación de resultados

A lo largo de la tarea voy a usar mi propio equipo y el nodo s001-n059 de devcloud, por lo tanto estamos usando distintos recursos con diferentes características para poder encontrar diferencias en la ejecución de 'MATMUL'.

De ahora en adelante, haré referencia a mi equipo como 'ACER' (debido a la marca de mi equipo) y 'nodo' al nodo usado en devcloud.

| Estadística | ACER | NODO |
|-------------|-------------|-------------|
| Tiempo CPU | 0,100s | 0,109s |
| Memoria | 53% | 53% |
| Media TripCounts | 299 | Unknown |
| GFLOPS | 0,54 | 0,49 |
| GINTOPS | 4,86 | 4,44 |

El mejor 'equipo' encargado del procesamiento es **ACER**. ¿Por qué? En tiempo de CPU se ve que tarda menos, pero esto se debe a que la cantidad de GLOPS y GINTOPS usado es mayor, y este dato es un condicionante crítico. Además de que usa Tripcounts.

Ambos resultados han sido obtenidos mediante el análisis de las snapshots de ambos.

![Survey-Roofline ACER](https://github.com/ASIGNATURA-ARCO-UCLM/lab1-andrescastellanoscantos/blob/master/results/task4/Analisis2.png)

![Survey-Roofline NODO](https://github.com/ASIGNATURA-ARCO-UCLM/lab1-andrescastellanoscantos/blob/master/results/task4/Analisis3.png)


