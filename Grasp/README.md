# DNAMotifs

Proyecto para Sistemas Adaptativos


Para compilar se tiene que compilar el archivo grasp.cpp y el archivo funciones.cpp (recordar estar en la carpeta Grasp)

    g++ grasp.cpp funciones.cpp -o grasp

Y para ejecutar se usa el ejecutable y el nombre del archivo con el tiempo que se quiere ejecutar el grasp(o el path a la carpeta donde estan las instancias)

    ./grasp.exe -i <nombre archivo> -t <tiempo de ejecucion>

Ejemplo con la carpeta Dataset desde la carpeta Grasp con tiempo de ejecucion 60 segundos

    ./grasp.exe -i ../Dataset/inst_200_15_4_0.txt -t 60

El tiempo debe ser mayor a 0 y tiene que ser en segundos

Si no se agregan los parametros se les pide por consola.

No importa el orden de los parametros.

El codigo imprime en consola el Valor Objetivo y el Tiempo en donde se obtuvo el valor objetivo.


Tambien se puede ejecutar el archivo de tablas.cpp el cual revisa todos los archivos del dataset y saca el valor del greedy y el del grasp

Para compilar

    g++ tablas.cpp funciones.cpp -o tablas

Para ejecutar

    ./tablas.exe -a <Alpha para el greedy> -t <Tiempo de ejecucion del Grasp>

Guarda todos los valores obtenidos en un archivo data.txt. Cuidado porque el dataset donde se busca es en un lugar especifico si no esta en el mismo path que en el codigo, este puede fallar.