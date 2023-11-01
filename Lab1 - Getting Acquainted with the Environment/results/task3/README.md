### Compilación en Intel DevCloud

He realizado estos pasos para compilar el archivo 'matmul.cpp' en Intel DevCloud:

1. Copia el archivo 'matmul.cpp' a DevCloud desde tu ruta local utilizando 'scp':
   ```bash
   scp matmul.cpp devcloud:

2. A continuación, accedemos a devcloud mediante el siguiente comando:
   ```bash
   ssh devcloud

3. Solicitamos un nodo de manera iterativa mediante el siguiente comando:
   ```bash
   qsub -I
   
5. Una vez se nos ha asignado el nodo, y desde otra terminal, accedemos mediante ssh, en mi caso sería (con el nodo asignado:
   ```bash
   ssh s001-n059.aidevcloud
   
6. Tras haber accedido, podemos usar el comando de compilación usado en la TAREA 2
   ```bash
   icpc -g -qopenmp -o matmul matmul.cpp

### Análisis y Snapshot dentro del nodo DevCloud

1. Tras investigar en la documentación de **advisor** he realizado varias comprobaciones de comando y el comando más adecuado para realizar el análisis que incluya 'Survey', 'Tripcounts' y 'Flops' es el siguiente:
   Para realizar el análisis con los tipos 'survey', 'flops' y 'tripcounts' he usado el siguiente comando:
   
   ```bash
   advisor --collect=roofline --project-dir=Lab1 -- ./matmul
   ```
   
   - **advisor**: comando que invoca a la herramienta Intel Advisor
   - **--collect**: tipo de información que se va a recolectar, en nuestro caso podríamos haber seleccionado survey (análisis muy simple), pero elegiremos roofline, que siguiendo la documentación de advisor, dice textualmente: "Run the Survey analysis immediately followed by the Trip Counts & FLOP analysis to visualize actual performance against hardware-imposed performance ceilings. "
   - **--project-dir**: donde se guardará el proyecto
   - **./matmul**: ruta de nuestro ejecutable
  
3. Para obtener la snapshot, usaremos el comando de acontinuación:
   ```bash
   advisor --snapshot --pack --project-dir=./Lab1 snapshot-devcloud
   ```

   - **advisor**: comando que invoca a la herramienta Indel Advisor
   - **--snapshot**: acción a realizar por parte de Intel Advisor. En este caso, crear la snapshot
   - **--pack**: se guardará la snapshot en un pack
   - **./project-dir**: ubicación del proyecto del cual se obtendrá la Snapshot
   - **snapshot-devcloud**: nombre de la snapshot.

4. Copiar la snapshot obtenida desde devcloud para enviar a nuestro equipo:
   ```bash
   scp devcloud:snapshot000.advixeexpz .
   ```



