#include <iostream>
#include <fstream>
#include "../Funciones/funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>


using namespace std;

typedef std::tuple<int, long long> ResultadoGreedy;

int main(int argc, char* argv[]) {
    
    std::srand(std::time(NULL));

    // Obtener el valor objetivo y el tiempo de ejecucion de una instancia
    string file_name = get_file_name(argc, argv);
    
    vector<string> lines = read_file(file_name);

    float alpha = get_alpha(argc, argv);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, std::vector<char>> res = greedy(lines, alpha, l);

    cout << std::get<0>(res) << endl; // Valor objetivo
    cout << std::string(std::get<1>(res).begin(), std::get<1>(res).end()) << endl; // Respuesta

    return 0;
}