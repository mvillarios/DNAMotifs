#include <iostream>
#include <fstream>
#include "../Funciones/funciones.h"
#include <ctime>
#include <tuple>
#include <cmath>

using namespace std;


int main(int argc, char* argv[]) {
    
    std::srand(std::time(NULL));

    string file_name = get_file_name(argc, argv);
    
    vector<string> lines = read_file(file_name);

    int inst, m, l;

    extractValues(file_name, inst, m, l);

    std::tuple<int, std::vector<char>> res = greedy(lines, 0, l);

    cout << std::get<0>(res) << endl; // Valor objetivo
    cout << std::string(std::get<1>(res).begin(), std::get<1>(res).end()) << endl; // Respuesta

    return 0;
}