#include "funciones.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <tuple>
#include <map>

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
std::tuple<int, std::vector<char>> greedy(vector<string> s, float alpha, int tam_string) {

    std::vector<char> dna = {'A', 'C', 'G', 'T'}; //Nucleotidos (Sigma(E griega))

    int m = tam_string; // Tamaño de los fragmentos de ADN (m)
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
        //Se cambian los valores de la matriz auxiliar por los de la distancia del mejor nucleotido
        for (int i = 0; i < tam_s; i++){
            for (int k = 0; k < 4; k++) matriz_aux[i][k] = distancia_s_i[i];
        }
        // Se reinicia el vector count
        for (int k = 0; k < 4; k++) count[k] = 0;
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de finalización
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    
    // Total
    int total = 0;
    for (int i = 0; i < tam_s; i++) total += distancia_s_i[i] * distancia_s_i[i];

    //std::cout << "Solucion: " << std::string(respuesta.begin(), respuesta.end()) << std::endl;

    return std::make_tuple(total, respuesta);
}

int calcularDistancia(const std::string& str, const std::vector<std::string>& dataset) {
    int costoTotal = 0;
    for (const std::string& s_i : dataset) {
        int distancia = 0;
        for (size_t j = 0; j < str.size(); j++) {
            if (str[j] != s_i[j]) {
                distancia++;
            }
        }
        costoTotal += distancia * distancia;
    }
    return costoTotal;
}

// Función que implementa el algoritmo de búsqueda local con Grasp
// Recibe un vector de strings con las secuencias de ADN
// Retorna un par con el valor objetivo y el tiempo de ejecución
std::tuple<int, long long> grasp(std::vector<std::string> s, int tam_string, int t_limite) {

    int num_init_sol = 30;
    int m = tam_string;
    int best_dist = std::numeric_limits<int>::max();
    std::string best_sol;

    auto start_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de inicio
    std::chrono::seconds duration;

    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start_time).count() < t_limite) {
        std::vector<char> solucion_inicial;
        int dist_solucion_inicial;

        std::string sol_actual;
        int dist_actual;

        // Inicia el algoritmo de búsqueda local

        // Map de mejores soluciones con la solución y su distancia
        std::map<std::string, int> mejores_soluciones;

        for (int i = 0; i < num_init_sol; ++i) { // Recorremos soluciones iniciales
            // Genera una solución inicial aleatoria usando el algoritmo Greedy
            std::tie(dist_solucion_inicial, solucion_inicial) = greedy(s, 1, m);
            sol_actual = string(solucion_inicial.begin(), solucion_inicial.end());
            dist_actual = dist_solucion_inicial;

            for (size_t j = 0; j < m; j++) {
                for (char c : {'A', 'T', 'C', 'G'}) {
                    if (sol_actual[j] == c) continue;
                    std::string nueva_solucion = sol_actual;
                    nueva_solucion[j] = c;
                    int nueva_dist = calcularDistancia(nueva_solucion, s);
                    if (nueva_dist < dist_actual) {
                        dist_actual = nueva_dist;
                        sol_actual = nueva_solucion;
                    }
                }
            }
            mejores_soluciones.insert(std::pair<std::string, int>(sol_actual, dist_actual));
        }

        // Elige la mejor solución entre mejores_soluciones
        for (const auto& x : mejores_soluciones) {
            if (x.second < dist_actual) {
                dist_actual = x.second;
                sol_actual = x.first;
            }
        }
        // Termina el algoritmo de búsqueda local

        if (best_sol.empty() || dist_actual < best_dist) {
            best_dist = dist_actual;
            best_sol = sol_actual;

            auto end_time = std::chrono::high_resolution_clock::now(); // Marcar el tiempo de finalización
            duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
        }
    }

    //std::cout << "Solucion: " << best_sol << std::endl;

    return make_tuple(best_dist, duration.count());
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

// Obtener el nombre del archivo
string get_file_name(int argc, char* argv[]) {
    string file_name;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-i") == 0) {
            file_name = argv[i + 1];
            return file_name;
        }
    }
    
    cout << "Ingrese el nombre del archivo: ";
    cin >> file_name;
    return file_name;
}

// Obtener el valor de alpha
float get_alpha(int argc, char* argv[]) {
    float alpha = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-a") == 0) {
            alpha = atof(argv[i + 1]);
            if (alpha < 0 || alpha > 1) {
                cerr << "Error: El valor de alpha debe estar entre 0 y 1." << endl;
                exit(1);
            }
            return alpha;
        }
    }
    
    cout << "Ingrese el valor de alpha: ";
    cin >> alpha;
    
    if (alpha < 0 || alpha > 1) {
        cerr << "Error: El valor de alpha debe estar entre 0 y 1." << endl;
        exit(1);
    }
    
    return alpha;
}

// Obtener el tiempo límite de ejecución del grasp
int get_t_limite(int argc, char* argv[]) {
    int t_limite = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-t") == 0) {
            t_limite = atoi(argv[i + 1]);
            if (t_limite < 0) {
                cerr << "Error: El tiempo límite debe ser mayor a 0." << endl;
                exit(1);
            }
            return t_limite;
        }
    }
    
    cout << "Ingrese el tiempo límite de ejecución: ";
    cin >> t_limite;
    
    if (t_limite < 0) {
        cerr << "Error: El tiempo límite debe ser mayor a 0." << endl;
        exit(1);
    }
    
    return t_limite;
}

bool extractValues(string filePath, int& inst, int& m, int& l) {

    size_t lastSlash = filePath.find_last_of('/');
    std::string fileName = filePath.substr(lastSlash + 1);

    if (sscanf(fileName.c_str(), "inst_%d_%d_4_%d", &m, &l, &inst) == 3) {
        return true;
    } else {
        std::cerr << "No se pudieron extraer los valores del nombre del archivo." << std::endl;
        return false;
    }
}

void save_data(std::ofstream &file, int inst, int m, int l, int greedy, long long mh) {

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Comprueba si el archivo está vacío
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "inst\tm\tl\tgreedy\tmh\n";
    }

    // Escribe los datos en el archivo
    file << inst << '\t' << m << '\t' << l << '\t' << greedy << '\t' << mh << '\n';
}


void close_data(ofstream &file){
    file.close();
}

void clear_data(std::string file_name){
    std::ofstream file(file_name, std::ofstream::trunc);
    file.close();
}
