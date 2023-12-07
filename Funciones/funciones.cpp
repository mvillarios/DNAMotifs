#include "funciones.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <tuple>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>

using namespace std;

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

// Función que implementa el algoritmo de búsqueda local con Grasp
// Recibe un vector de strings con las secuencias de ADN
// Retorna un par con el valor objetivo y el tiempo de ejecución
std::tuple<int, long long> grasp(std::vector<std::string> s, int tam_string, long long t_limite, int tunning) {

    int num_init_sol = 3;
    int m = tam_string;
    int best_dist = std::numeric_limits<int>::max();
    long long best_time = -1;
    std::string best_sol;

    auto start_time = std::chrono::system_clock::now(); // Marcar el tiempo de inicio
    auto now = std::chrono::system_clock::now();
    auto duration = now - start_time;

    while (duration.count() <= t_limite) {
        std::string solucion_inicial;
        int dist_solucion_inicial;

        std::string sol_actual;
        int dist_actual;

        // Inicia el algoritmo de búsqueda local

        // Map de mejores soluciones con la solución y su distancia
        std::map<std::string, int> mejores_soluciones;

        for (int i = 0; i < num_init_sol; ++i) { // Recorremos soluciones iniciales
            // Genera una solución inicial aleatoria
            solucion_inicial.clear();
            for (int j = 0; j < m; ++j) {
                solucion_inicial.push_back("ACGT"[rand() % 4]);
            }
            dist_solucion_inicial = calcularDistancia(solucion_inicial, s);

            sol_actual = solucion_inicial;
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
            mejores_soluciones.insert({sol_actual, dist_actual});
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        //std::cout << duration.count() << std::endl;
        if (duration.count() >= t_limite) break;

        // Elige la mejor solución entre mejores_soluciones
        for (const auto& x : mejores_soluciones) {
            if (x.second < dist_actual) {
                dist_actual = x.second;
                sol_actual = x.first;
            }
        }
        // Termina el algoritmo de búsqueda local

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        //std::cout << duration.count() << std::endl;
        if (duration.count() >= t_limite) break;

        if (best_sol.empty() || dist_actual < best_dist) {
            best_dist = dist_actual;
            best_sol = sol_actual;
            best_time = duration.count();

            if (!tunning) {
                //std::cout << "Solucion: " << best_sol << std::endl;
                std::cout << "Costo: " << best_dist << std::endl;
                std::cout << "Tiempo: " << best_time / 1e9 << std::endl;
            }
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        //std::cout << duration.count() << std::endl;
    }

    //std::cout << "Solucion: " << best_sol << std::endl;

    return std::make_tuple(best_dist, best_time);
}

std::tuple<int, long long> genetico(std::vector<std::string> s, int tam_string, int tam_poblacion, float alpha, long long t_limite, bool tunning) {
    int n = tam_poblacion;
    int m = tam_string;
    int tam_s = s.size();

    std::vector<std::string> poblacion_inicial;
    std::vector<int> distancias_poblacion_inicial;

    auto start_time = std::chrono::system_clock::now(); // Marcar el tiempo de inicio   
    auto now = std::chrono::system_clock::now();
    auto duration = now - start_time;

    // Genera una población inicial aleatoria
    for (int i = 0; i < n; ++i) {
        std::string cromosoma;
        for (int j = 0; j < m; ++j) {
            cromosoma += "ACGT"[rand() % 4];
        }
        poblacion_inicial.push_back(cromosoma);
        distancias_poblacion_inicial.push_back(calcularDistancia(cromosoma, s));
    }
    
    std::string best_sol = "";
    int best_dist = -1;
    long long best_time = -1;


    while ( duration.count() < t_limite){

        // Selecciona individuos de la población por torneo
        std::vector<int> seleccionados; // Vector que guarda los indices de los individuos seleccionados
        int num_seleccionados = n * 0.5; // Numero de individuos seleccionados

        for (int i = 0; i < num_seleccionados; ++i) {
            int index1 = rand() % n;
            int index2 = rand() % n;
            int seleccionado = 0;
            if (distancias_poblacion_inicial[index1] < distancias_poblacion_inicial[index2]) {
                seleccionado = index1;
            } else {
                seleccionado = index2;
            }

            seleccionados.push_back(seleccionado);
        }

        // Cruza los individuos seleccionados
        std::vector<std::string> hijos;
        for (int i = 0; i < num_seleccionados - 1; i += 2) {
            std::string hijo1 = poblacion_inicial[seleccionados[i]].substr(0, m / 2) + poblacion_inicial[seleccionados[i + 1]].substr(m / 2, m / 2);
            std::string hijo2 = poblacion_inicial[seleccionados[i + 1]].substr(0, m / 2) + poblacion_inicial[seleccionados[i]].substr(m / 2, m / 2);
            hijos.push_back(hijo1);
            hijos.push_back(hijo2);
        }

        // Si quedó un individuo sin cruzar (cuando num_seleccionados es impar)
        if (num_seleccionados % 2 != 0) {
            hijos.push_back(poblacion_inicial[seleccionados[num_seleccionados - 1]]);
        }

        // Mutación
        for (int i = 0; i < num_seleccionados; ++i) {
            //Probabilidad de mutación
            // Si se cumple la probabilidad alpha, se muta
            if ((float)rand()/RAND_MAX < alpha) {
                // Selecciona un índice al azar
                int index = rand() % m;
                int index2 = rand() % 4;
                hijos[i][index] = "ACGT"[index2];
            }
        }

        // Reemplazo los hijos en la población inicial
        // Elimino los individuos con mayor distancia
        // Y lo reemplazo por los hijos

        // Calculo la distancia de los hijos
        std::vector<int> distancias_hijos;
        for (int i = 0; i < num_seleccionados; ++i) {
            distancias_hijos.push_back(calcularDistancia(hijos[i], s));
        }

        // Reemplazo los individuos con mayor distancia
        for (int i = 0; i < num_seleccionados; ++i) {
            int max_index = 0;
            for (int j = 0; j < n; ++j) {
                if (distancias_poblacion_inicial[j] > distancias_poblacion_inicial[max_index]) {
                    max_index = j;
                }
            }
            poblacion_inicial[max_index] = hijos[i];
            distancias_poblacion_inicial[max_index] = distancias_hijos[i];
        }

        // Busco el mejor hasta el momento
        int best_index = 0;
        for (int i = 0; i < n; ++i) {
            if (distancias_poblacion_inicial[i] < distancias_poblacion_inicial[best_index]) {
                best_index = i;
            }
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        if (duration.count() >= t_limite) break;

        // Si es mejor que el mejor hasta el momento, lo guardo
        if (best_sol.empty() || distancias_poblacion_inicial[best_index] < best_dist) {
            best_sol = poblacion_inicial[best_index];
            best_dist = distancias_poblacion_inicial[best_index];
            best_time = duration.count();

            if (!tunning){
                //std::cout << "Solucion: " << best_sol << std::endl;
                std::cout << "Costo: " << best_dist << std::endl;
                std::cout << "Tiempo: " << best_time / 1e9 << std::endl;
            }
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
    }


    return std::make_tuple(best_dist, best_time);
}

// Implementacion de metaheuristica hibrida de algoritmo genetico con busqueda local
// Recibe un vector de strings con las secuencias de ADN
// Retorna un par con el valor objetivo y el tiempo de ejecución
// tam_pobl_inicial: Tamaño de la población inicial ( >= 20)
// porcentaje_seleccionados: Porcentaje de individuos seleccionados por torneo (entre 0.1 y 0.5)
// prob_mutacion: Probabilidad de mutación (entre 0.1 y 0.3)
// prob_cruce: Probabilidad de cruce (entre 0.5 y 0.9)
// prob_local_search: Probabilidad de aplicar búsqueda local (entre 0.5 y 0.9)
std::tuple<int, long long> mh_hibrida(std::vector<std::string> s, int tam_string, long long t_limite, int tunning, int tam_pobl_inicial, 
                                    float porcentaje_seleccionados, float prob_mutacion, float prob_cruce, float prob_local_search){

    int m = tam_string;
    int tam_s = s.size();
    
    int best_dist = -1;
    long long best_time = -1;
    std::string best_sol = "";

    auto start_time = std::chrono::system_clock::now(); // Marcar el tiempo de inicio
    auto now = std::chrono::system_clock::now();
    auto duration = now - start_time;

    // Genera una población inicial aleatoria
    std::vector<std::string> poblacion_inicial;
    std::vector<int> distancias_poblacion_inicial;

    int n = tam_pobl_inicial;
    for (int i = 0; i < n; ++i) {
        std::string cromosoma;
        for (int j = 0; j < m; ++j) {
            cromosoma += "ACGT"[rand() % 4];
        }
        poblacion_inicial.push_back(cromosoma);
        distancias_poblacion_inicial.push_back(calcularDistancia(cromosoma, s));
    }

    while(duration.count() <= t_limite){

        // --------------- Torneo ----------------- //
        // Selecciona individuos de la población por torneo
        std::vector<int> seleccionados; // Vector que guarda los indices de los individuos seleccionados
        int tam_seleccionados = n * porcentaje_seleccionados; // Numero de individuos seleccionados

        // Seleccionar individuos aleatorios únicos para el torneo
        std::vector<int> participantes(n);
        std::iota(participantes.begin(), participantes.end(), 0);

        std::random_shuffle(participantes.begin(), participantes.end());

        // Recorro los participantes y a cada ganador lo agrego a seleccionados
        for (int i = 0; seleccionados.size() < tam_seleccionados; i += 2) {
            int index1 = participantes[i];
            int index2 = participantes[i + 1];

            int seleccionado = (distancias_poblacion_inicial[index1] < distancias_poblacion_inicial[index2]) ? index1 : index2;

            seleccionados.push_back(seleccionado);
        }

        // --------------- Cruza ----------------- //
        // Cruza los individuos seleccionados
        // A través de un punto de cruce al azar
        std::vector<std::string> hijos;

        for (int i = 0; i < tam_seleccionados - 1; i += 2) {

            if (i + 1 >= seleccionados.size()) break;

            std::string padre1 = poblacion_inicial[seleccionados[i]];
            std::string padre2 = poblacion_inicial[seleccionados[i + 1]];


            // Probabilidad de cruce
            if ((float)rand() / RAND_MAX < prob_cruce) {
                int punto_cruza = rand() % m;

                std::string hijo1 = padre1.substr(0, punto_cruza) + padre2.substr(punto_cruza);
                std::string hijo2 = padre2.substr(0, punto_cruza) + padre1.substr(punto_cruza);

                hijos.push_back(hijo1);
                hijos.push_back(hijo2);
            } else {
                // Sin cruce, simplemente copiar a los padres como hijos
                hijos.push_back(padre1);
                hijos.push_back(padre2);
            }
        }

        // Si quedó un individuo sin cruzar (cuando num_seleccionados es impar)
        if (tam_seleccionados % 2 != 0) {
            hijos.push_back(poblacion_inicial[seleccionados[tam_seleccionados - 1]]);
        }

        // --------------- Mutación ----------------- //
        // Mutación
        for (size_t i = 0; i < hijos.size(); ++i) {
            // Probabilidad de mutación
            // Si se cumple la probabilidad alpha, se muta
            if ((float)rand() / RAND_MAX < prob_mutacion) {
                // Selecciona un índice al azar
                int index = rand() % m;
                int index2 = rand() % 4;
                hijos[i][index] = "ACGT"[index2];
            }
        }

        // --------------- localSearch ----------------- //
        for (size_t i = 0; i < hijos.size(); ++i) {
            // Aplicar búsqueda local 
            if ((float)rand() / RAND_MAX <= prob_local_search) {
                hijos[i] = localSearch(hijos[i], s);
            }
            now = std::chrono::system_clock::now();
            duration = now - start_time;
            if (duration.count() >= t_limite) break;
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        if (duration.count() >= t_limite) break;

        // --------------- Reemplazo ----------------- //
        // Reemplazo los hijos en la población inicial
        // Elimino los individuos con mayor distancia
        // Y lo reemplazo por los hijos
        // Calcular distancias de los hijos
        std::vector<int> distancias_hijos;
        for (const auto& hijo : hijos) {
            distancias_hijos.push_back(calcularDistancia(hijo, s));
        }
        // Crear un vector de índices [0, 1, 2, ..., n-1]
        std::vector<int> indices_originales(n);
        std::iota(indices_originales.begin(), indices_originales.end(), 0);

        // Ordenar los índices según las distancias de la población original
        std::sort(indices_originales.begin(), indices_originales.end(), [&](int i, int j) {
            return distancias_poblacion_inicial[i] > distancias_poblacion_inicial[j];
        });

        // Reemplazar los individuos con mayor distancia por los hijos
        for (int i = 0; i < hijos.size(); ++i) {
            int indice_reemplazar = indices_originales[i];
            //cout << "Indice reemplazar: " << indice_reemplazar << endl;
            poblacion_inicial[indice_reemplazar] = hijos[i];
            distancias_poblacion_inicial[indice_reemplazar] = distancias_hijos[i];
        }

        // Busco el mejor hasta el momento
        auto best_iter = std::min_element(distancias_poblacion_inicial.begin(), distancias_poblacion_inicial.end());
        int best_index = std::distance(distancias_poblacion_inicial.begin(), best_iter);

        now = std::chrono::system_clock::now();
        duration = now - start_time;
        if (duration.count() >= t_limite) break;

        // Si es mejor que el mejor hasta el momento, lo guardo
        if (best_sol.empty() || distancias_poblacion_inicial[best_index] < best_dist) {
            best_sol = poblacion_inicial[best_index];
            best_dist = distancias_poblacion_inicial[best_index];
            best_time = duration.count();

            if (!tunning){
                //std::cout << "Solucion: " << best_sol << std::endl;
                std::cout << "Costo: " << best_dist << std::endl;
                std::cout << "Tiempo: " << best_time / 1e9 << std::endl;
            }
        }

        now = std::chrono::system_clock::now();
        duration = now - start_time;
    }

    return std::make_tuple(best_dist, best_time);
}

std::string localSearch(const std::string& sol_inicial, const std::vector<std::string>& s) {
    
    std::string sol_actual = sol_inicial;
    int dist_actual = calcularDistancia(sol_actual, s);
    bool mejora = false;

    for (size_t i = 0; i < sol_actual.size(); i++) {
        for (size_t j = i + 1; j < sol_actual.size(); j++) {
            std::string nueva_solucion = sol_actual;
            std::swap(nueva_solucion[i], nueva_solucion[j]);
            int nueva_dist = calcularDistancia(nueva_solucion, s);
            if (nueva_dist < dist_actual) {
                dist_actual = nueva_dist;
                sol_actual = nueva_solucion;
                mejora = true;
                break;
            }
        }
        if (mejora) break;
    }

    return sol_actual;
}

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
                break;
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
long long get_t_limite(int argc, char* argv[]) {
    long t_limite = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-t") == 0) {
            t_limite = stoi(argv[i + 1]) * 1e9;
            if (t_limite < 0) {
                cerr << "Error: El tiempo límite debe ser mayor a 0." << endl;
                break;
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

bool get_tunning(int argc, char* argv[]){
    bool tunning = false;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-tunning") == 0) {
            tunning = atoi(argv[i + 1]);
        }
    }
    return tunning;
}

int get_m (int argc, char* argv[]){
    int m = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-m") == 0) {
            m = atoi(argv[i + 1]);
            if (m < 0) {
                cerr << "Error: El tamaño de la población inicial debe ser mayor a 0." << endl;
                break;
            }
            return m;
        }
    }
    
    cout << "Ingrese el tamaño de la población inicial: ";
    cin >> m;
    
    if (m < 0) {
        cerr << "Error: El tamaño de la población inicial debe ser mayor a 0." << endl;
        exit(1);
    }
    
    return m;
}

int get_l (int argc, char* argv[]){
    int l = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-l") == 0) {
            l = atoi(argv[i + 1]);
            if (l < 0) {
                cerr << "Error: El tamaño de la población inicial debe ser mayor a 0." << endl;
                break;
            }
            return l;
        }
    }
    
    cout << "Ingrese el tamaño de la población inicial: ";
    cin >> l;
    
    if (l < 0) {
        cerr << "Error: El tamaño de la población inicial debe ser mayor a 0." << endl;
        exit(1);
    }
    
    return l;
}

int get_algoritmo (int argc, char* argv[]){
    int algoritmo = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-algoritmo") == 0) {
            algoritmo = atoi(argv[i + 1]);
            if (algoritmo < 0 && algoritmo > 3) {
                cerr << "Error: El algoritmo debe ser entre 0 y 3" << endl;
                break;
            }
            return algoritmo;
        }
    }
    
    cout << "Ingrese el algoritmo: ";
    cin >> algoritmo;
    
    if (algoritmo < 0 && algoritmo > 3) {
        cerr << "Error: El algoritmo debe ser entre 0 y 3" << endl;
        exit(1);
    }
    
    return algoritmo;
}

int get_tam_poblacion(int argc, char* argv[]){
    int pobl_inicial = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-p") == 0) {
            pobl_inicial = atoi(argv[i + 1]);
            if (pobl_inicial < 20) {
                cerr << "Error: El tamaño de la población inicial debe ser mayor o igual a 20." << endl;
                break;
            }
            return pobl_inicial;
        }
    }
    
    cout << "Ingrese el tamaño de la población inicial: ";
    cin >> pobl_inicial;
    
    if (pobl_inicial < 20) {
        cerr << "Error: El tamaño de la población inicial debe ser mayor o igual a 20." << endl;
        exit(1);
    }
    
    return pobl_inicial;

}

float get_porcentaje_seleccionados(int argc, char* argv[]){
    float porcentaje_seleccionados = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-ps") == 0) {
            porcentaje_seleccionados = atof(argv[i + 1]);
            if (porcentaje_seleccionados < 0.1 || porcentaje_seleccionados > 0.5) {
                cerr << "Error: El porcentaje de seleccionados debe estar entre 0.1 y 0.5." << endl;
                break;
            }
            return porcentaje_seleccionados;
        }
    }
    
    cout << "Ingrese el porcentaje de seleccionados: ";
    cin >> porcentaje_seleccionados;
    
    if (porcentaje_seleccionados < 0.1 || porcentaje_seleccionados > 0.5) {
        cerr << "Error: El porcentaje de seleccionados debe estar entre 0.1 y 0.5." << endl;
        exit(1);
    }
    
    return porcentaje_seleccionados;
}

float get_prob_mutacion(int argc, char* argv[]){
    float prob_mutacion = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-pm") == 0) {
            prob_mutacion = atof(argv[i + 1]);
            if (prob_mutacion < 0.01 || prob_mutacion > 0.3) {
                cerr << "Error: La probabilidad de mutación debe estar entre 0.01 y 0.3." << endl;
                break;
            }
            return prob_mutacion;
        }
    }
    
    cout << "Ingrese la probabilidad de mutación: ";
    cin >> prob_mutacion;
    
    if (prob_mutacion < 0.01 || prob_mutacion > 0.1) {
        cerr << "Error: La probabilidad de mutación debe estar entre 0.01 y 0.3." << endl;
        exit(1);
    }
    
    return prob_mutacion;
}

float get_prob_cruce(int argc, char* argv[]){
    float prob_cruce = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-pc") == 0) {
            prob_cruce = atof(argv[i + 1]);
            if (prob_cruce < 0.5 || prob_cruce > 0.9) {
                cerr << "Error: La probabilidad de cruce debe estar entre 0.5 y 0.9." << endl;
                break;
            }
            return prob_cruce;
        }
    }
    
    cout << "Ingrese la probabilidad de cruce: ";
    cin >> prob_cruce;
    
    if (prob_cruce < 0.5 || prob_cruce > 0.9) {
        cerr << "Error: La probabilidad de cruce debe estar entre 0.5 y 0.9." << endl;
        exit(1);
    }
    
    return prob_cruce;
}

float get_prob_local_search(int argc, char* argv[]){
    float prob_local_search = 0;
    for (int i = 1; i < argc - 1; i += 2) {
        if (strcmp(argv[i], "-pls") == 0) {
            prob_local_search = atof(argv[i + 1]);
            if (prob_local_search < 0.5 || prob_local_search > 0.9) {
                cerr << "Error: La probabilidad de búsqueda local debe estar entre 0.5 y 0.9." << endl;
                break;
            }
            return prob_local_search;
        }
    }
    
    cout << "Ingrese la probabilidad de búsqueda local: ";
    cin >> prob_local_search;
    
    if (prob_local_search < 0.5 || prob_local_search > 0.9) {
        cerr << "Error: La probabilidad de búsqueda local debe estar entre 0.5 y 0.9." << endl;
        exit(1);
    }
    
    return prob_local_search;
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

void save_data(std::ofstream &file, int inst, int m, int l, int result, long long time) {

    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo." << std::endl;
        return;
    }

    // Comprueba si el archivo está vacío
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "inst\tm\tl\tresult\ttime\n";
    }

    // Escribe los datos en el archivo
    file << inst << '\t' << m << '\t' << l << '\t' << result << '\t' << time << '\n';
}

void close_data(ofstream &file){
    file.close();
}

void clear_data(std::string file_name){
    std::ofstream file(file_name, std::ofstream::trunc);
    file.close();
}

void allInst (long long t_limite, float alpha, int tam_poblacion, bool tunning, int m, int l, int algoritmo) {

    int inst = 100;
    // std::vector<int> m = {200, 500, 1000};
    // std::vector<int> l = {15, 100, 300, 500};

    int costo = 0;
    long long tiempo = 0;

    // Ciclo que recorre todas las instancias
    for (int k = 0; k < inst; k++){
        std::string file_name = "../Dataset/inst_" + std::to_string(m) + "_" + std::to_string(l) + "_4_" + std::to_string(k) + ".txt";
        std::vector<std::string> lines = read_file(file_name);   

        if(algoritmo == 0){
            std::tuple<int, std::vector<char>> res1 = greedy(lines, alpha, l);
            std::ofstream file("../Test/resultados_greedy_" + std::to_string(m) + "_" + std::to_string(l) + ".txt", std::ios::app);
            save_data(file, k, m, l, std::get<0>(res1), 0);
            close_data(file);

            costo += std::get<0>(res1);


        }else if(algoritmo == 1){
            std::tuple<int, long long> res2 = grasp(lines, l, t_limite, tunning);
            std::ofstream file("../Test/resultados_grasp_" + std::to_string(m) + "_" + std::to_string(l) + ".txt", std::ios::app);
            save_data(file, k, m, l, std::get<0>(res2), std::get<1>(res2));
            close_data(file);

            costo += std::get<0>(res2);
            tiempo += std::get<1>(res2);

        }else if(algoritmo == 2){
            std::tuple<int, long long> res3 = genetico(lines, l, tam_poblacion, alpha, t_limite, tunning);
            std::ofstream file("../Test/resultados_ag_" + std::to_string(m) + "_" + std::to_string(l) + ".txt", std::ios::app);
            save_data(file, k, m, l, std::get<0>(res3), std::get<1>(res3));
            close_data(file);

            costo += std::get<0>(res3);
            tiempo += std::get<1>(res3);

        }else if(algoritmo == 3){
            std::tuple<int, long long> res4 = mh_hibrida(lines, l, t_limite, tunning, 640, 0.4083, 0.2141, 0.7732, 0.8233);
            std::ofstream file("../Testing/resultados_hibrida_" + std::to_string(m) + "_" + std::to_string(l) + ".txt", std::ios::app);
            save_data(file, k, m, l, std::get<0>(res4), std::get<1>(res4)/ 1e9);
            close_data(file);
        }
    }

    //costo = costo / inst;
    //tiempo = tiempo / inst;

    //cout << "Algoritmo:" << algoritmo << endl;
    //cout << m << " " <<l << endl; 

    //cout << costo << " " <<tiempo << endl;
}