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

    int inst, m, l;

    int n_sol_ini = 10;
    int t_limite = 60;
    int tam_string = 100;

    std::tuple<int, std::vector<char>> res = greedy(lines, alpha, tam_string);
    std::tuple<int, long long> res2 = grasp(lines, tam_string, t_limite);


    cout << "Greedy: " << std::get<0>(res) << endl;
    cout << "Grasp: " << std::get<0>(res2) << endl;

    cout << "Grasp Tiempo: " << std::get<1>(res2) << endl;

    return 0;
}