### Explicación del problema existente

El mensaje "Some target modules are not compiled with optmization enabled and with version 15.0 or higher of the Intel compiler" nos indica que hay algunos módulos de destino en el proyecto que no se han compilado con la optimización habilitada y no se han construido con una versión del compilador de Intel igual o superior a la versión 15.0


### Solución al problema
La solución es usar el compilador de Intel 'icpc': 
```bash
icpc -g -qopenmp -o matmul matmul.cpp
```
A continuación explico los componentes del comando:
- **icpc**: compilador de Intel
- **-g**: habilita la generación de información de depuración en el código compilado
- **-qopenmp**: habilita el soporte para OpenMP (Open Multi-Processing), que es una API de programación para la programación paralela en sistemas con múltiples núcleos de CPU
- **-o matmul**: permite asignar el nombre 'matmul' al archivo compilado.
- **matmul.cpp**: archivo a compilar


Para evitar el Warning relacionado con **ISA (Instruction Set Architecture)** hay que usar la opción **-XCORE-AVX2** cuando queramos compilar. He intentado usarlo pero me ha causado problemas, por lo que he considerado NO USARLO.
