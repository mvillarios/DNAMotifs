# DNAMotifs

Proyecto para Sistemas Adaptativos


Para compilar se tiene que compilar el archivo greedy.cpp o greedy_prob.cpp y el archivo funciones.cpp (recordar estar en la carpeta Greedy)

 - g++ greedy_prob.cpp funciones.cpp -o greedy_prob
 - g++ greedy.cpp funciones.cpp -o greedy

Y para ejecutar se usa el ejecutable y el nombre del archivo

 - .\greedy.exe -i <nombre archivo>
 - .\greedy_prob.exe -i <nombre archivo> <alpha>

En el greedy probabilistico se necesita agregar un numero entre 0 y 1.
Si no se agregan los parametros se les pide por consola 
 