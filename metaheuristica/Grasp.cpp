#include <iostream>
#include <fstream>
#include "funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {

    std::srand(std::time(NULL));

    string file_name = get_file_name(argc, argv);

    vector<string> lines = read_file(file_name);

    float alpha = get_alpha(argc, argv);

    std::ofstream file("data.txt", std::ofstream::app);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    int n_sol_ini = 100;
    int t_limite = 60;
    int tam_string = l;

    std::tuple<int, std::vector<char>> res = greedy(lines, alpha, tam_string);
    std::tuple<int, long long> res2 = grasp(lines, tam_string, n_sol_ini, t_limite);

    save_data(file, inst, m, l, std::get<0>(res), std::get<0>(res2));


    file.close();
    return 0;
}