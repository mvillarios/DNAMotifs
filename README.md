# DNAMotifs

Proyecto 2-Optimality Consensus Problem para Sistemas Adaptativos

## Greedy

Para compilar se tiene que compilar el archivo greedy.cpp o greedy_prob.cpp y el archivo funciones.cpp (recordar estar en la carpeta Greedy)

    g++ greedy.cpp ../Funciones/funciones.cpp -o greedy

    g++ greedy_prob.cpp ../Funciones/funciones.cpp -o greedy_prob

Y para ejecutar se usa el ejecutable y el nombre del archivo (o el path a la carpeta donde estan las instancias) y el alpha en el caso del greedy probabilistico.

    ./greedy.exe -i <nombre archivo>

    ./greedy_prob.exe -i <nombre archivo> -a <alpha>

El codigo imprime en consola el Valor Objetivo y el Resultado.

## Grasp

Para compilar se tiene que compilar el archivo grasp.cpp y el archivo funciones.cpp (recordar estar en la carpeta Grasp)

    g++ grasp.cpp ../Funciones/funciones.cpp -o grasp

Y para ejecutar se usa el ejecutable con el tiempo que se quiere ejecutar el grasp y el nombre del archivo(o el path a la carpeta donde estan las instancias)

    ./grasp.exe -i <nombre archivo> -t <tiempo de ejecucion> -tunning <0/1>

El codigo imprime en consola el Valor Objetivo y el Tiempo en donde se obtuvo el valor objetivo.

## AG

Para compilar se tiene que compilar el archivo ag.cpp y el archivo funciones.cpp (recordar estar en la carpeta AG)

    g++ ag.cpp ../Funciones/funciones.cpp -o ag

Y para ejecutar se usa el ejecutable con el tiempo que se quiere ejecutar el ag y el nombre del archivo(o el path a la carpeta donde estan las instancias), ademas tiene otros parametros como el tamaño de poblacion y la probabilidad de mutacion.

    ./ag.exe -i <nombre archivo> -t <tiempo de ejecucion> -tunning <0/1> -p <tamaño de poblacion> -a <probabilidad de mutacion>

El codigo imprime en consola el Valor Objetivo y el Tiempo en donde se obtuvo el valor objetivo.

## Indicaciones de uso

El tiempo "-t" debe ser mayor a 0 y tiene que ser en segundos

El alpha "-a" debe ser mayor a 0 y menor a 1

El tamaño de poblacion "-p" debe ser mayor a 0

El tunning "-tunning" debe ser 0 o 1 (0 imprime resultados por consola, 1 no imprime nada)

Si no se agregan los parametros se les pide por consola.

No importa el orden de los parametros.