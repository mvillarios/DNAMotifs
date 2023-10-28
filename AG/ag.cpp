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


    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, long long> res = genetico(lines, l, 50, 10);

    return 0;
}