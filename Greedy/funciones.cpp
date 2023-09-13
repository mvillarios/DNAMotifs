#include "funciones.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <tuple>

using namespace std;

// Función que retorna el índice del menor valor de un vector
// Si hay varios elementos con el mismo valor mínimo, elige uno al azar
// Si alpha > 0, retorna un índice al azar con probabilidad alpha
int menorValorDna(const std::vector<int>& count, float alpha) {
    if (count.empty()) return -1; // Si está vacío

    if (alpha > 0){
        if ((float)rand()/RAND_MAX < alpha) {
            // Si se cumple la probabilidad alpha, elige uno al azar
            int randomIndex = rand() % (count.size()); // Genera un índice aleatorio
            return randomIndex;
        }
    }

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

    if (indices.size() > 1) {
        // Si hay varios elementos con el mismo valor mínimo, elige uno al azar
        int randomIndex = rand() % (indices.size()); // Genera un índice aleatorio
        return indices[randomIndex];
    }else {
        return minIndex; // Retorna el índice del menor valor
    }
}

// Función que implementa el algoritmo Greedy
// Recibe un vector de strings con las secuencias de ADN
// Retorna un par con el valor objetivo y el tiempo de ejecución
typedef tuple<int, long long> ResultadoGreedy;
ResultadoGreedy greedy(vector<string> s, float alpha) {
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

    auto start_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de inicio

    //clock_t start_time = clock();

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

        int next = menorValorDna(count, alpha);//Se calcula la letra que añadira menos distancia
        respuesta.push_back(dna[next]);// y se añade a la respuesta

        // Se guarda la distancia del mejor nucleotido
        for (int i = 0; i < tam_s; i++){
            distancia_s_i[i] = matriz_aux[i][next];
        }

        //  ----Impresiones en consola para ver el funcionamiento del algoritmo ----
        // cout<<"-----------Columna "<<j<<" ------------"<<endl;
        // for (int k = 0; k < 4; k++) cout<<count[k]<<" ";
        // cout<<""<<endl;
        // cout<<"A C G T"<<endl;    

        // for (int i = 0; i < tam_s; i++){
        //     for (int k = 0; k < 4; k++) cout<<matriz_aux[i][k]<<" ";
        //     cout<<""<<endl;
        // }

        // cout<<"Mejor: "<<dna[next]<<endl;
    
        // for (int i = 0; i < tam_s; i++){
        //     cout<<"s"<<i<<": "<<distancia_s_i[i]<<" ";
        //     cout<<""<<endl;
        // }
        
        // //  ------------------ Terminan Impresiones

        //Se cambian los valores de la matriz auxiliar por los de la distancia del mejor nucleotido
        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) matriz_aux[i][k] = distancia_s_i[i];
        }
        // Se reinicia el vector count
        for (int k = 0; k < 4; k++) count[k] = 0;

        // // Imprime la matriz auxiliar
        // cout<<"Matriz auxiliar"<<endl;
        // for (int i = 0; i < tam_s; i++){
        //     for (int k = 0; k < 4; k++) cout<<matriz_aux[i][k]<<" ";
        //     cout<<""<<endl;
        // }
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de finalización
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // clock_t end_time = clock(); // Marcar el tiempo de finalización
    // double duration = double(end_time - start_time) / CLOCKS_PER_SEC; // Calcular la duración en segundos

    // cout<<"distancia: ";
    // for(int i=0;i<distancia_s_i.size();i++) cout<<distancia_s_i[i]<<" ";
    // cout<<""<<endl;

    // cout<<"respuesta: ";
    // for(int i=0;i<respuesta.size();i++) cout<<respuesta[i];
    // cout<<""<<endl;
    
    // Total
    int total = 0;
    for (int i = 0; i < tam_s; i++) total += distancia_s_i[i] * distancia_s_i[i];
    // cout << "Valor objetivo: " << total << endl;
    // cout << "Tiempo de ejecucion: " << duration.count() << " us" << endl;

    //cout << total << " " << duration.count() << endl;

    return make_tuple(total, duration.count());
}

// Lee el archivo y retorna un vector de strings con las secuencias de ADN
vector<string> read_file(const string& file_name) {
    vector<string> lines;
    ifstream file(file_name);

    if (!file.good()) {
        cerr << "Error: El archivo '" << file_name << "' no existe o no se pudo abrir." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();
    return lines;
}

// Obtiene el nombre del archivo
string get_file_name(int argc, char* argv[]) {
    string file_name;
    if (argc > 2 && strcmp(argv[1],"-i") == 0) {
        file_name = argv[2];
    } else {
        cout << "Ingrese el nombre del archivo: ";
        cin >> file_name;
    }
    return file_name;
}

// Obtiene el valor de alpha
float get_alpha(int argc, char* argv[]) {
    float alpha = 0;
    if (argc > 3) {
        alpha = atof(argv[3]);
    } else {
        cout << "Ingrese el valor de alpha: ";
        cin >> alpha;
    }

    if (alpha < 0 || alpha > 1) {
        cerr << "Error: El valor de alpha debe estar entre 0 y 1." << endl;
        exit(1);
    }

    return alpha;
}