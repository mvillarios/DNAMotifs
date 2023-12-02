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

    long long t_limite = get_t_limite(argc, argv);

    bool tunning = get_tunning(argc, argv);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, long long> res = grasp(lines, l, t_limite, tunning);

    if(!tunning){
        cout << "Costo Final: " << std::get<0>(res) << endl;
        cout << "Tiempo Final: " << std::get<1>(res) / 1e9 << endl;
    }else{
        cout << std::get<0>(res) << endl;
    }

    return 0;
}