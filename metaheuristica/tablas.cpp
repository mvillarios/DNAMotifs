#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>
#include <chrono>
#include <filesystem>
#include <map>
#include <vector>
#include <numeric>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    fs::path folder_path = "../Dataset/";

    std::srand(std::time(NULL));

    float alpha = get_alpha(argc, argv);
    int t_limite = get_t_limite(argc, argv);

    // Usamos un mapa para almacenar los resultados y tiempos por conjunto único de "m" y "l"
    std::map<std::pair<int, int>, std::tuple<int, long long>> results;

    // Recorre todos los archivos en la carpeta
    for (const auto& entry : fs::directory_iterator(folder_path)) {
        if (fs::is_regular_file(entry)) {
            // Obtén el nombre del archivo actual
            fs::path file_path = entry.path();
            string file_name = file_path.string();

            vector<string> lines = read_file(file_name);
            std::ofstream file("data.txt", std::ofstream::app);

            int inst, m, l;
            extractValues(file_name, inst, m, l);

            std::tuple<int, std::vector<char>> res = greedy(lines, alpha, l);
            std::tuple<int, long long> res2 = grasp(lines, l, t_limite);

            save_data(file, inst, m, l, std::get<0>(res), std::get<0>(res2));

            // Almacenar los resultados en el mapa
            results[{m, l}] = std::make_tuple(std::get<0>(res), std::get<1>(res2));

            file.close();
        }
    }

    // Imprimir los encabezados
    cout << "m\tl\tgreedy\tmh\tmhtime" << endl;

    // Iterar a través de los resultados y calcular los promedios
    for (const auto& entry : results) {
        int m = entry.first.first;
        int l = entry.first.second;

        int greedy_result = std::get<0>(entry.second);
        long long grasp_result = std::get<1>(entry.second);

        cout << m << "\t" << l << "\t" << greedy_result << "\t" << grasp_result << "\t" << grasp_result << endl;
    }

    return 0;
}
