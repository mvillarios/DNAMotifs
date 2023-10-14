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

            file.close();
        }
    }

    return 0;
}