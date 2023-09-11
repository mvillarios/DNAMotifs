#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>

using namespace std;

//para compilar:g++ main.cpp greedy.cpp -o main.exe

int menorValorDna(const std::vector<int>& count) {
    if (count.empty()) return -1; // Si está vacío

    int minIndex = 0;
    std::vector<int> indices;

    for (int i = 0; i < count.size(); ++i) {
        if (count[i] < count[minIndex]) {
            minIndex = i;    
            indices.clear(); // Nuevo valor mínimo encontrado, restablecer los índices
            indices.push_back(i); // Agregar índice al vector de índices iguales
        } else if (count[i] == count[minIndex]) {
            indices.push_back(i); // Agregar índice al vector de índices iguales
        }
    }

    if (!indices.empty()) {
        // Si hay varios elementos con el mismo valor mínimo, elige uno al azar
        srand(time(0)); // Inicializa la semilla para rand() usando el tiempo actual
        int randomIndex = rand() % (indices.size()); // Genera un índice aleatorio
        return indices[randomIndex];
    }

    return minIndex; // Retorna el índice del menor valor
}


int greedy(vector<string> s)
{
    std::vector<char> dna = {'A', 'C', 'G', 'T'}; //Nucleotidos (Sigma(E griega))

    int m = 15; // Tamaño de los fragmentos de ADN (m)
    int tam_s = s.size();// Tamaño de la secuencia total (U)

    //almacena la distancia de cada S_i hasta el momento
    std::vector<int> distancia_s_i(tam_s, 0);
    
    // Matriz auxiliar, guarda la distancia de cada letra en cada S_i
    std::vector<std::vector<int>> matriz_aux(tam_s, std::vector<int>(4,0)); 
    
    // Vector que guarda la sumatorio al cuadrado de cada fila de la matriz auxiliar
    // Se usa para calcular la distancia de cada letra en cada S_i
    std::vector<int> count(4,0);
    
    std::vector<char> respuesta;

    for (int j = 0; j < m; j++){ // recorre cada columna
        for (int k = 0; k < 4; k++){ // se prueba con todas las letras A-C-G-T
            for (int i = 0; i < tam_s; i++){ // recorre cada fila
                if (s[i][j] != dna[k]){ //si la letra A-C-G-T es diferente a la letra en la posicion j de la fila i
                    matriz_aux[i][k]++; //se le suma 1 a la matriz auxiliar en la posicion i,k
                }
            }
        }

        // Se calcula la distancia de cada letra en cada S_i
        // Esto sirve para buscar la letra que añada menos distancia
        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) count[k] += matriz_aux[i][k] * matriz_aux[i][k];
        }

        int next = menorValorDna(count);//Se calcula la letra que añadira menos distancia
        respuesta.push_back(dna[next]);// y se añade a la respuesta

        // Se guarda la distancia del mejor nucleotido
        for (int i = 0; i < tam_s; i++){
            distancia_s_i[i] = matriz_aux[i][next];
        }

        //  ----Impresiones en consola para ver el funcionamiento del algoritmo ----
        cout<<"-----------Columna "<<j<<" ------------"<<endl;
        for (int k = 0; k < 4; k++) cout<<count[k]<<" ";
        cout<<""<<endl;
        cout<<"A C G T"<<endl;    

        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) cout<<matriz_aux[i][k]<<" ";
            cout<<""<<endl;
        }

        cout<<"Mejor: "<<dna[next]<<endl;
    
        //Imprime vector distancias
        for (int i = 0; i < tam_s; i++){
            cout<<"s"<<i<<": "<<distancia_s_i[i]<<" ";
            cout<<""<<endl;
        }
        
        //  ------------------ Terminan Impresiones

        //Se cambian los valores de la matriz auxiliar por los de la distancia del mejor nucleotido
        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) matriz_aux[i][k] = distancia_s_i[i];
        }
        // Se reinicia el vector count
        for (int k = 0; k < 4; k++) count[k] = 0;


        // Imprime la matriz auxiliar
        cout<<"Matriz auxiliar"<<endl;
        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) cout<<matriz_aux[i][k]<<" ";
            cout<<""<<endl;
        }

    }
    cout<<"respuesta: ";
    for(int i=0;i<respuesta.size();i++) cout<<respuesta[i];
    cout<<""<<endl;

    // Total
    int total = 0;
    for (int i = 0; i < tam_s; i++) total += distancia_s_i[i] * distancia_s_i[i];
    cout << "Total: " << total << endl;
    return 0;
}