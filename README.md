# DNAMotifs

Proyecto para Sistemas Adaptativos


Para compilar se tiene que compilar el archivo greedy.cpp o greedy_prob.cpp y el archivo funciones.cpp (recordar estar en la carpeta Greedy)

    g++ greedy.cpp funciones.cpp -o greedy

    g++ greedy_prob.cpp funciones.cpp -o greedy_prob

Y para ejecutar se usa el ejecutable y el nombre del archivo (o el path a la carpeta donde estan las instancias)

    .\greedy.exe -i <nombre archivo>

    .\greedy_prob.exe -i <nombre archivo> <alpha>

Ejemplo con la carpeta Instancias

     .\greedy.exe -i ..\Instancias\inst_200_15_4_0.txt

En el greedy probabilistico se necesita agregar un numero alpha entre 0 y 1.

Si no se agregan los parametros se les pide por consola.
 