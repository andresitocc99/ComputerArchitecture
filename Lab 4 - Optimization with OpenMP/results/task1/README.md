# Tarea 1: Intel Advisor

Esta tarea requiere la compilación y ejecución del código del HyperLCA. Para ello dispones de un fichero makefile que automatiza ambos procesos.
Teclea **make** para realizar la compilación, y **make run** para ejecutarlo.
La ejecución requiere de un fichero de datos de entrada que previamente deberás descargar de 'https://mega.nz/file/Z5JUkSoI#boptGx0TD4YU1FGz5WxVkxgB0-fav1sQiVVCk2lz_CA'

**En este ejercicio NO debe utilizarse la optimización -xCORE-AVX2 ya que toda la vectorización SIMD se indicará de manera explícita a través de pragmas**

## Preguntas
* Antes de comenzar a realizar ningún análisis es interesante conocer las características de tu arquitectura, para ello contesta a las siguientes preguntas:
    * Indica tu modelo de procesador y de cuantos núcleos dispones
    * ¿Cuantos hilos pueden ser ejecutados por núcleo?

* A continuación procede a realizar anotaciones en todos los bucles que deberían ser paralelizados (al menos, indica tres Sites para analizar). Estas anotaciones permitirán al programa de análisis considerar que esos bucles serán paralelizados y hacer las estimaciones oportunas. Guarda el nuevo programa con las anotaciones con el sufijo "_annotated" (ten en cuenta que además de añadir las anotaciones tienes que incluir/modificar un nuevo archivo de cabecera).

* Indica el comando que usarías para compilar el programa con las anotaciones (Consejos: Mirar la opción -I y buscad la ruta del archivo advisor-annotate.h dentro del directorio intel/oneapi).


----
This tasks requires the compilation and executio of the HyperLCA code. You have a makefile that automates those operations.
Type **make** to compile the code and **make run** for the execution.
Take into account that you should first download a data file from 'https://mega.nz/file/Z5JUkSoI#boptGx0TD4YU1FGz5WxVkxgB0-fav1sQiVVCk2lz_CA'

**In this exercise you CAN'T user -xCORE-AVX2 optimization since you are expected to manually specificy vectorization through manually edited pragmas**
# Task 1: Intel Advisor

## Questions
* Before beginning any analysis, it's important to understand your architecture's characteristics. Please answer the following questions:
    * State your processor model and the number of cores it has.
    * How many threads can be executed per core?

* Next, proceed to introduce annotations in all the loops that should be parallelized (at least, specify three sites for analysis). These annotations will allow the analysis program to consider these loops for parallelization and make the appropriate estimates. Save the modified program with annotations using the suffix "_annotated" (keep in mind that in addition to including annotations, you must include/modify a new header file).

* Specify the command you would use to compile the program with the annotations (Tips: Look for the -I option and locate the path to the advisor-annotate.h file within the intel/oneapi directory).

