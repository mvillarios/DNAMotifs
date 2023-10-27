#include <iostream>
#include <fstream>
#include "../Funciones/funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {

    std::srand(std::time(NULL));

    string file_name = get_file_name(argc, argv);

    vector<string> lines = read_file(file_name);

    int t_limite = get_t_limite(argc, argv);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, long long> res = grasp(lines, l, t_limite);

    cout << std::get<0>(res) << endl; // Valor objetivo
    cout << std::get<1>(res) << endl; // Tiempo de ejecucion

    return 0;
}