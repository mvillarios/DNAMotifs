#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>

using namespace std;

typedef std::tuple<int, long long> ResultadoGreedy;

int main(int argc, char* argv[]) {

    std::srand(std::time(NULL));

    // Obtener el valor objetivo y el tiempo de ejecucion de una instancia
    string file_name = get_file_name(argc, argv);
    float alpha = get_alpha(argc, argv);
    vector<string> lines = read_file(file_name);
    ResultadoGreedy resultado = greedy(lines, alpha);

    cout << get<0>(resultado) << endl; // Valor objetivo
    cout << get<1>(resultado) << endl; // Tiempo de ejecucion

    return 0;
}